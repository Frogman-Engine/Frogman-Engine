#ifndef _FE_CORE_BLOCK_POOL_HXX_
#define _FE_CORE_BLOCK_POOL_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/private/pool_common.hxx>
#include <FE/core/containers/stack.hxx>




BEGIN_NAMESPACE(FE)


namespace internal::pool
{
    template <typename T>
    struct block_info<T, POOL_TYPE::_BLOCK>
    {
        using value_type = T;
        using pointer = value_type*;

        pointer _address = nullptr;
    };


    template <size_t InBytes>
    class uninitialized_bytes
    {
        var::byte m_memory[InBytes];
    };


    template<typename T, count_t PageCapacity>
    struct chunk<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>>
    {
        FE_STATIC_ASSERT(std::is_array<T>::value == true, "Static Assertion Failed: The T must not be an array[] type.");
        FE_STATIC_ASSERT(std::is_const<T>::value == true, "Static Assertion Failed: The T must not be a const type.");

        using block_info_type = block_info<T, POOL_TYPE::_BLOCK>;
        using value_type = typename block_info_type::value_type;
        using pointer = typename block_info_type::pointer;

    private:
        alignas(FE::SIMD_auto_alignment::size) std::array<var::byte, sizeof(T)* PageCapacity> m_memory;

    public:
        constexpr static size_t page_capacity = PageCapacity;

        FE::fstack<block_info_type, PageCapacity> _free_blocks;
        pointer const _begin = reinterpret_cast<pointer const>(m_memory.data());
        pointer _page_iterator = _begin;
        pointer const _end = _begin + PageCapacity;

        _FORCE_INLINE_ boolean is_full() const noexcept
        {
            return (_free_blocks.is_empty() == true) && (_page_iterator >= _end);
        }
    };
}




template<typename T, count_t PageCapacity, class Allocator>
class pool<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>, Allocator>
{
    FE_STATIC_ASSERT(std::is_array<T>::value == true, "Static Assertion Failed: The T must not be an array[] type.");
    FE_STATIC_ASSERT(std::is_const<T>::value == true, "Static Assertion Failed: The T must not be a const type.");

public:
    using chunk_type = internal::pool::chunk<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>>;
    using deleter_type = pool_deleter<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>, Allocator>;
    using block_info_type = typename chunk_type::block_info_type;

    FE_STATIC_ASSERT((std::is_same<chunk_type, typename Allocator::value_type>::value == false), "Static Assertion Failed: The chunk_type has to be equivalent to Allocator::value_type.");
    using pool_type = std::list<chunk_type, Allocator>;

    constexpr static count_t page_capacity = PageCapacity;
    static constexpr count_t maximum_list_node_count = 10;

    FE_STATIC_ASSERT((std::is_same<T, typename chunk_type::value_type>::value == false), "Static Assertion Failed: The value_type does not match.");
    FE_STATIC_ASSERT((std::is_same<T*, typename chunk_type::pointer>::value == false), "Static Assertion Failed: The value_type* does not match.");
    
private:
    pool_type m_memory_pool;

public:
    pool() noexcept = default;
    ~pool() noexcept = default;

    pool(const pool& other_p) noexcept = delete;
    pool(pool&& rvalue) noexcept = delete;

    pool& operator=(const pool& other_p) noexcept = delete;
    pool& operator=(pool&& rvalue) noexcept = delete;

    T* allocate() noexcept
    {
        typename pool_type::iterator l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();

        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            if (l_list_iterator->is_full() == false)
            {
                T* l_allocation_result;
                if (l_list_iterator->_free_blocks.is_empty() == true)
                {
                    l_allocation_result = l_list_iterator->_page_iterator;
                    ++(l_list_iterator->_page_iterator);
                }
                else
                {
                    l_allocation_result = l_list_iterator->_free_blocks.pop()._address;
                }

                if constexpr (FE::is_trivial<T>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
                {
                    new(l_allocation_result) T();
                }

                return l_allocation_result;
            }

            create_pages(1);
            continue;
        }

        create_pages(1);
        return allocate();
    }

    void deallocate(T* const pointer_p) noexcept
    {
        typename pool_type::iterator  l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();
        FE_ASSERT(l_list_iterator == l_cend, "Unable to request deallocate() to an empty pool.");


        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            if ((l_list_iterator->_begin <= pointer_p) && (pointer_p < l_list_iterator->_end))
            {
                if constexpr (FE::is_trivial<T>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
                {
                    pointer_p->~T();
                }

                l_list_iterator->_free_blocks.push(block_info_type{ pointer_p });
                return;
            }
        }
    }

    _FORCE_INLINE_ void create_pages(size_t chunk_count_p) noexcept
    {
        FE_ASSERT(chunk_count_p == 0, "${%s@0}: ${%s@1} was 0", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(chunk_count_p));

        for (var::size_t i = 0; i < chunk_count_p; ++i)
        {
            this->m_memory_pool.emplace_back();
        }

        FE_ASSERT(this->m_memory_pool.size() == maximum_list_node_count, "Maximum chunk count of a memory chunk list is limited to ${%lu@0} for some performance reasons.", &maximum_list_node_count);
    }

    boolean shrink_to_fit() noexcept
    {
        typename pool_type::iterator l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();
        FE_ASSERT(l_list_iterator == l_cend, "Unable to shrink_to_fit() an empty pool.");

        if (l_list_iterator == l_cend)
        {
            return false;
        }


        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            var::size_t l_unused_element_size = l_list_iterator->_free_blocks.size();

            FE_ASSERT((l_list_iterator->_end - l_list_iterator->_begin) != PageCapacity, "The chunk range is invalid.");

            if (l_list_iterator->_page_iterator < l_list_iterator->_end)
            {
                l_unused_element_size += (l_list_iterator->_end - l_list_iterator->_page_iterator);
            }

            if (l_unused_element_size == PageCapacity)
            {
                this->m_memory_pool.erase(l_list_iterator);

                if (this->m_memory_pool.size() == 0)
                {
                    break;
                }

                l_list_iterator = this->m_memory_pool.begin();
            }
        }

        return true;
    }
};


template<typename T, count_t PageCapacity = 128, class Allocator = FE::aligned_allocator<internal::pool::chunk<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>>>>
using block_pool = pool<T, POOL_TYPE::_BLOCK, PageCapacity, FE::align_custom_bytes<sizeof(T)>, Allocator>;


END_NAMESPACE
#endif