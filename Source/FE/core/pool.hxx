#ifndef _FE_CORE_POOL_HXX_
#define _FE_CORE_POOL_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/block_pool_allocator.hxx>
#include <FE/core/private/pool_common.hxx>




BEGIN_NAMESPACE(FE)


namespace internal::pool
{
    template <>
    struct block_info<void, POOL_TYPE::_GENERIC>
    {
        var::byte* _address = nullptr;
        var::size_t _size_in_bytes = 0;
    };

    template<count_t PossibleAddressCount>
    class address_map : public std::map<var::byte*, var::size_t, std::greater<var::byte*>, FE::block_pool_allocator< std::pair<var::byte* const, var::size_t>, FE::object_count<PossibleAddressCount>>> 
    {
    public:
        using base_type = std::map< var::byte*, var::size_t, 
                                    std::greater<var::byte*>, 
                                    FE::block_pool_allocator<   std::pair<var::byte* const, var::size_t>, 
                                                                FE::object_count<PossibleAddressCount>>>;
        using key_type = var::byte*;
        using key_compare = std::greater<var::byte*>;
        using value_compare = typename base_type::value_compare;
        using value_type = typename base_type::value_type;
        using allocator_type = typename base_type::allocator_type;
        using size_type = typename base_type::size_type;
        using difference_type = typename base_type::difference_type;
        using pointer = typename base_type::pointer;
        using const_pointer = typename base_type::const_pointer;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;

    public:
        _FORCE_INLINE_ address_map() noexcept = default;
        _FORCE_INLINE_ ~address_map() noexcept = default;
        _FORCE_INLINE_ address_map(const address_map& other_p) noexcept = delete;
        _FORCE_INLINE_ address_map(address_map&& rvalue_p) noexcept = delete;

        _FORCE_INLINE_ boolean is_empty() const noexcept
        {
            return base_type::empty();
        }
    };

    template<count_t PageCapacity, class Alignment>
    struct chunk<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment>
    {
        constexpr static count_t page_capacity = PageCapacity;
        constexpr static size_t recycler_capacity = ((PageCapacity / Alignment::size) / 2) + 1; // The possible fragment count would be ((PageCapacity / Alignment::size) / 2) + 1 because adjacent fragments gets immediately merged during deallocate() operation.
        using recycler_type = FE::internal::pool::address_map<recycler_capacity>;
        using recycler_iterator = typename recycler_type::iterator;
        using block_info_type = typename recycler_type::value_type;

    private:
        alignas(FE::SIMD_auto_alignment::size) std::array<var::byte, PageCapacity> m_memory;
        /*
         std::pair's first contains the address of the memory block.
         std::pair's second contains the size of the memory block.
        */

    public:
        recycler_type _free_blocks;
        var::byte* const _begin = m_memory.data();
        var::byte* _page_iterator = _begin;
        var::byte* const _end = _begin + m_memory.size();

        _FORCE_INLINE_ boolean is_full() const noexcept
        {
            return (_free_blocks.is_empty() == true) && (_page_iterator >= _end);
        }
    };

    // For debugging purpose only
    template<size_t PossibleAddressCount>
    class pool_monitor
    {
    public:
        using tracker_type = address_map<PossibleAddressCount>;

    private:
        tracker_type m_tracker;

    public:
        template<typename T>
		void track_allocation(void* pointer_p, size_t size_in_bytes_including_alignment) noexcept
		{
            auto l_insertion_result = this->m_tracker.insert(typename tracker_type::value_type{ static_cast<var::byte*>(pointer_p), size_in_bytes_including_alignment });
			FE_ASSERT(l_insertion_result.second == false, "Pool Monitor: something went wrong with memory recycling algorithm. The same address has been allocated twice.");
		}

        template<typename T>
        void track_deallocation(void* pointer_p) noexcept
        {
			this->m_tracker.erase(static_cast<var::byte*>(pointer_p));
        }

		void log_current_memory_utilization() noexcept
		{
#ifdef _ENABLE_LOG_
            var::uint64 l_total_size_in_bytes = 0;
            auto l_last_address = this->m_tracker.end();
            for (auto address_iterator = this->m_tracker.begin(); address_iterator != l_last_address; ++address_iterator)
            {
				l_total_size_in_bytes += address_iterator->second;
            }
            float64 l_percent = (static_cast<float64>(l_total_size_in_bytes) / static_cast<float64>(PossibleAddressCount)) * 100.0f;
			FE_LOG("Pool Monitor: [${%lu@0} bytes of the pool memory has been used: currently using ${%lf@1}% of the pool memory.]", &l_total_size_in_bytes, &l_percent);
#endif
		}
    };
}


template<size_t PageCapacity, class Alignment>
struct generic_deleter_base
{
    template<typename T, POOL_TYPE pool_ype, size_t page_capacity, class alignment, class allocator>
    friend class pool;

    using chunk_type = internal::pool::chunk<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment>;
    using block_info_type = typename chunk_type::block_info_type;

    constexpr static size_t page_capacity = PageCapacity;
    constexpr static size_t temporary_storage_capacity = PageCapacity / Alignment::size;

protected:
    chunk_type* m_host_chunk = nullptr;
    var::size_t m_size_in_bytes = 0;

public:
    _FORCE_INLINE_ generic_deleter_base() noexcept : m_host_chunk(), m_size_in_bytes() {}
    _FORCE_INLINE_ generic_deleter_base(chunk_type* host_p, size_t size_in_bytes_p) noexcept : m_host_chunk(host_p), m_size_in_bytes(size_in_bytes_p) {}

    _FORCE_INLINE_ chunk_type* get_host_chunk_ptr() const noexcept
    {
		return this->m_host_chunk;
	}

    _FORCE_INLINE_ size_t get_size_in_bytes() const noexcept
    {
        return this->m_size_in_bytes;
    }
};


template<size_t PageCapacity, class Alignment, class Allocator>
struct nondestructive_generic_deleter final : public generic_deleter_base<PageCapacity, Alignment>
{
    using base_type = generic_deleter_base<PageCapacity, Alignment>;
    using chunk_type = typename base_type::chunk_type;
    using block_info_type = typename base_type::block_info_type;

    _FORCE_INLINE_ nondestructive_generic_deleter() noexcept : base_type() {}
    _FORCE_INLINE_ nondestructive_generic_deleter(chunk_type* host_p, size_t size_in_bytes_p) noexcept : base_type(host_p, size_in_bytes_p) {}

    void operator()(void* ptr_p) const noexcept
    {
        if (ptr_p == nullptr || this->m_host_chunk == nullptr) { return; }

        FE_ASSERT(this->m_size_in_bytes == 0, "Assertion Failed: ${%s@0} cannot be zero.", TO_STRING(this->m_size_in_bytes));

        auto l_address_tree_insertion_result = this->m_host_chunk->_free_blocks.insert(block_info_type{ static_cast<var::byte*>(ptr_p), this->m_size_in_bytes });
        FE_EXIT(l_address_tree_insertion_result.second == false, FE::MEMORY_ERROR_1XX::_FATAL_ERROR_DOUBLE_FREE, "Double-free detected.");

        if (this->m_host_chunk->_free_blocks.size() > 1)
        {
            pool<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>::__merge(l_address_tree_insertion_result.first, this->m_host_chunk->_free_blocks);
        }
    }
};


template<typename T, size_t PageCapacity, class Alignment, class Allocator>
struct pool_deleter<T, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator> final : public generic_deleter_base<PageCapacity, Alignment>
{
    FE_STATIC_ASSERT(std::is_array<T>::value == true, "Static Assertion Failed: The T must not be an array[] type.");
    FE_STATIC_ASSERT(std::is_const<T>::value == true, "Static Assertion Failed: The T must not be a const type.");

    using base_type = generic_deleter_base<PageCapacity, Alignment>;
    using chunk_type = typename base_type::chunk_type;
    using block_info_type = typename base_type::block_info_type;
    using value_type = typename FE::remove_const_reference<T>::type;

private:
    var::count_t m_element_count = 0;

public:
    _FORCE_INLINE_ pool_deleter() noexcept : base_type() {}
    _FORCE_INLINE_ pool_deleter(chunk_type* host_p, count_t elements_p, size_t size_in_bytes_p) noexcept : base_type(host_p, size_in_bytes_p), m_element_count(elements_p) {}

    void operator()(void* ptr_p) const noexcept
    {
        FE_ASSERT(this->m_size_in_bytes < this->m_element_count, "Assertion Failed: Detected arguments with illegal values.");

        if (ptr_p == nullptr || this->m_host_chunk == nullptr) { return; }
     
        if constexpr (FE::is_trivial<value_type>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
        {
            value_type* l_ptr = static_cast<value_type*>(ptr_p);
            void* const l_ptr_end = static_cast<value_type*>(ptr_p) + this->m_element_count;

            while (l_ptr != l_ptr_end)
            {
                l_ptr->~value_type();
                ++l_ptr;
            }
        }

        FE_ASSERT(this->m_size_in_bytes == 0, "FATAL ERROR: ${%s@0} cannot be zero.", TO_STRING(this->m_size_in_bytes));
        
        auto l_address_tree_insertion_result = this->m_host_chunk->_free_blocks.insert(block_info_type{ static_cast<var::byte*>(ptr_p), this->m_size_in_bytes });
        FE_EXIT(l_address_tree_insertion_result.second == false, FE::MEMORY_ERROR_1XX::_FATAL_ERROR_DOUBLE_FREE, "Double-free detected.");

        if (this->m_host_chunk->_free_blocks.size() > 1)
        {
            pool<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>::__merge(l_address_tree_insertion_result.first, this->m_host_chunk->_free_blocks);
        }
    }

    _FORCE_INLINE_ count_t get_element_count() const noexcept
    {
        return this->m_element_count;
    }
};



// static declaration of FE.generic_pool is not supported.
template<count_t PageCapacity, class Alignment, class Allocator>
class pool<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>
{
    template<typename T, POOL_TYPE pool_ype, count_t page_capacity, class alignment, class allocator>
    friend struct pool_deleter;

    template<count_t page_capacity, class alignment, class allocator>
    friend struct nondestructive_generic_deleter;

public:
    using chunk_type = internal::pool::chunk<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment>;
    using recycler_type = typename chunk_type::recycler_type;
    using recycler_iterator = typename chunk_type::recycler_iterator;

    template<typename U>
    using deleter_type = pool_deleter<U, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>;
   
	using pool_type = std::list<chunk_type, Allocator>;

    using block_info_type = typename chunk_type::block_info_type;

    static constexpr size_t page_capacity = chunk_type::page_capacity;
    static constexpr size_t recycler_capacity = chunk_type::recycler_capacity;
    static constexpr count_t maximum_list_node_count = 10;

private:
    pool_type m_memory_pool;

public:
#ifdef _ENABLE_LOG_
    internal::pool::pool_monitor<PageCapacity / Alignment::size> _pool_monitor;
#endif

    pool() noexcept = default;
    ~pool() noexcept = default;

    pool(const pool& other_p) noexcept = delete;
    pool(pool&& rvalue) noexcept = delete;

    pool& operator=(const pool& other_p) noexcept = delete;
    pool& operator=(pool&& rvalue) noexcept = delete;

    template<typename U>
    std::unique_ptr<U, deleter_type<U>> allocate(count_t size_p = 1) noexcept // +std::unique_ptr<U, deleter_type<U>> allocate(count_t size_p = 1, T* hint_p) noexcept to support re-allocation
    {
        FE_STATIC_ASSERT((Alignment::size % 2) != 0, "Static Assertion Failed: The Alignment::size must be an even number.");
        FE_STATIC_ASSERT(std::is_array<U>::value == true, "Static Assertion Failed: The T must not be an array[] type.");
        FE_STATIC_ASSERT(std::is_const<U>::value == true, "Static Assertion Failed: The T must not be a const type.");
        FE_ASSERT(size_p == 0, "${%s@0}: ${%s@1} was 0", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(size_p));
        FE_EXIT(size_p > PageCapacity, MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY, "Fatal Error: Unable to allocate the size of memmory that exceeds the pool chunk's capacity.");

        size_t l_queried_allocation_size_in_bytes = FE::calculate_aligned_memory_size_in_bytes<U, Alignment>(size_p);
        typename pool_type::iterator l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();

        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            if (l_list_iterator->is_full() == false)
            {
                void* l_allocation_result = nullptr;
                internal::pool::block_info<void, POOL_TYPE::_GENERIC> l_memblock_info;

                if (l_list_iterator->_free_blocks.is_empty() == false)
                {
                    /*
                    first contains the address of the memory block.
                    second contains the size of the memory block.
                    */

                    __recycle<U>(l_memblock_info, *l_list_iterator, l_queried_allocation_size_in_bytes);

                    if (l_memblock_info._size_in_bytes < l_queried_allocation_size_in_bytes)
                    {
                        if ((l_list_iterator->_page_iterator + l_queried_allocation_size_in_bytes) >= l_list_iterator->_end)
                        {
                            create_pages(1);
                            continue;
                        }

                        l_allocation_result = l_list_iterator->_page_iterator;
                        l_list_iterator->_page_iterator += l_queried_allocation_size_in_bytes;
                    }
                    else
                    {
                        l_allocation_result = l_memblock_info._address;
                    }
                }
                else
                {
                    if ((l_list_iterator->_page_iterator + l_queried_allocation_size_in_bytes) >= l_list_iterator->_end)
                    {
                        create_pages(1);
                        continue;
                    }

                    l_allocation_result = l_list_iterator->_page_iterator;
                    l_list_iterator->_page_iterator += l_queried_allocation_size_in_bytes;
                }


                if constexpr (FE::is_trivial<U>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
                {
                    U* l_iterator = static_cast<U*>(l_allocation_result);
                    for (var::index_t i = 0; i < size_p; ++i)
                    {
                        new(l_iterator) U();
                        ++l_iterator;
                    }
                }


                if (l_list_iterator->_page_iterator > l_list_iterator->_end)
                {
                    create_pages(1);
                    continue;
                }

                std::unique_ptr<U, deleter_type<U>> l_result{static_cast<U*>(l_allocation_result), deleter_type<U>{reinterpret_cast<chunk_type*>(l_list_iterator.operator->()), size_p, l_queried_allocation_size_in_bytes}};
#ifdef _ENABLE_LOG_
                this->_pool_monitor.template track_allocation<U>(l_result.get(), FE::calculate_aligned_memory_size_in_bytes<U, Alignment>(size_p));
#endif
                return std::move(l_result);
            }   
            else
            {
                create_pages(1);
            }
        }

        create_pages(1);
        return allocate<U>(size_p);
    }

    _FORCE_INLINE_ void create_pages(size_t chunk_count_p) noexcept
    {
        FE_ASSERT(chunk_count_p == 0, "${%s@0}: ${%s@1} was 0", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(chunk_count_p));

        for (var::size_t i = 0; i < chunk_count_p; ++i)
        {
            this->m_memory_pool.emplace_back();
        }

		FE_ASSERT(this->m_memory_pool.size() == maximum_list_node_count, "Maximum chunk count of a memory chunk list is limited to ${%lu@0} for some performance reasons.");
    }

    boolean shrink_to_fit() noexcept
    {
        typename pool_type::iterator  l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();
     
        if (l_list_iterator == l_cend)
        {
            FE_ASSERT(true, "Unable to shrink_to_fit() an empty pool.");
            return false; // this is to ignore the operation if it is running in a release mode.
        }

        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            var::size_t l_unused_memory_size_in_bytes = 0;
            for (auto block : l_list_iterator->_free_blocks)
            {
                l_unused_memory_size_in_bytes += block.second;
            }

            if (l_list_iterator->_page_iterator < l_list_iterator->_end)
            {
                l_unused_memory_size_in_bytes += l_list_iterator->_end - l_list_iterator->_page_iterator;
            }

            if (l_unused_memory_size_in_bytes == PageCapacity)
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

    template <typename T>
    void deallocate(T* pointer_p, count_t element_count_p) noexcept 
    {
        typename pool_type::iterator  l_list_iterator = this->m_memory_pool.begin();
        typename pool_type::const_iterator l_cend = this->m_memory_pool.cend();
        FE_ASSERT(l_list_iterator == l_cend, "Unable to request deallocate() to an empty pool.");

#ifdef _ENABLE_LOG_
        this->_pool_monitor.template track_deallocation<T>(pointer_p);
#endif

        var::byte* const l_value = reinterpret_cast<var::byte*>(pointer_p);

        for (; l_list_iterator != l_cend; ++l_list_iterator)
        {
            if ((l_list_iterator->_begin <= l_value) && (l_value < l_list_iterator->_end))
            {
                if constexpr (FE::is_trivial<T>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
                {
                    for (var::count_t i = 0; i < element_count_p; ++i)
                    {
                        pointer_p->~T();
                        ++pointer_p;
                    }
                }

                size_t l_block_size_in_bytes = FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(element_count_p);
                auto l_address_tree_insertion_result = l_list_iterator->_free_blocks.insert(block_info_type{ l_value, l_block_size_in_bytes });
                FE_EXIT(l_address_tree_insertion_result.second == false, FE::MEMORY_ERROR_1XX::_FATAL_ERROR_DOUBLE_FREE, "Double-free detected.");

                if (l_list_iterator->_free_blocks.size() > 1)
                {
                    __merge(l_address_tree_insertion_result.first, l_list_iterator->_free_blocks);
                }
                return;
            }
        }
    }

private:
    static void __merge(recycler_iterator in_out_recently_deleted_p, recycler_type& in_out_free_block_list_p) noexcept
    {
        auto l_null = in_out_free_block_list_p.end();
        auto l_adjacent_to_begin = in_out_free_block_list_p.upper_bound(in_out_recently_deleted_p->first); // Logarithmic time complexity: O(log N)
        auto l_adjacent_to_end = l_adjacent_to_begin;

        if(l_adjacent_to_end != l_null)
        {
            --l_adjacent_to_end; // Logarithmic time complexity: O(log N)
        }

        var::byte* l_merged_address = in_out_recently_deleted_p->first;
        var::size_t l_merged_size = in_out_recently_deleted_p->second;

        // merge upper part
        for(; l_adjacent_to_begin != l_null;)
        {
            if(l_merged_address + l_merged_size == l_adjacent_to_begin->first)
            {
                l_merged_size += l_adjacent_to_begin->second;

                auto l_previous = l_adjacent_to_begin;
                ++l_adjacent_to_begin; // Logarithmic time complexity: O(log N)if
                in_out_free_block_list_p.erase(l_previous); // Constant time complexity: O(1)f
                continue;
            }
            else
            {
                break;
            }
        }

        // merge lower part
        for(; l_adjacent_to_end != l_null;) 
        {
            if( l_adjacent_to_end->first + l_adjacent_to_end->second == l_merged_address)
            {
                l_merged_size += l_adjacent_to_end->second;
                l_merged_address = l_adjacent_to_end->first;
                auto l_previous = l_adjacent_to_end;
                --l_adjacent_to_end;  // Logarithmic time complexity: O(log N)
                in_out_free_block_list_p.erase(l_previous); // Constant time complexity: O(1)f
                continue;
            }
            else
            {
                break;
            }
        }

        in_out_free_block_list_p.insert({l_merged_address, l_merged_size}); // Logarithmic time complexity: O(log N)
    }

    template <typename T>
    static void __recycle(internal::pool::block_info<void, POOL_TYPE::_GENERIC>& out_memblock_info_p, chunk_type& in_out_memory_p, size_t queried_allocation_size_in_bytes_p) noexcept
    {
        FE_ASSERT(in_out_memory_p._free_blocks.is_empty() == true, "Assertion Failure: Cannot recycle from an empty bin.");

        /*
                     first contains the address of the memory block.
                     second contains the size of the memory block.
        */

        auto l_cend = in_out_memory_p._free_blocks.cend();

        for (auto free_block_iterator = in_out_memory_p._free_blocks.begin(); free_block_iterator != l_cend; ++free_block_iterator)
        {
            if (free_block_iterator->second >= queried_allocation_size_in_bytes_p)
            {
                out_memblock_info_p._address = free_block_iterator->first;
                out_memblock_info_p._size_in_bytes = queried_allocation_size_in_bytes_p;
                auto l_leftover_address = free_block_iterator->first + queried_allocation_size_in_bytes_p;
                auto l_leftover_size = free_block_iterator->second - queried_allocation_size_in_bytes_p;

                if (l_leftover_size > 0)
                {
                    _MAYBE_UNUSED_ auto l_address_tree_insertion_result = in_out_memory_p._free_blocks.insert(block_info_type{ l_leftover_address, l_leftover_size });
                    FE_EXIT(l_address_tree_insertion_result.second == false, FE::MEMORY_ERROR_1XX::_FATAL_ERROR_DOUBLE_FREE, "Double-free detected.");
                }
                in_out_memory_p._free_blocks.erase(free_block_iterator);

                return;
            }
        }
    }
};


template<size_t PageCapacity = 1 MB, class Alignment = FE::SIMD_auto_alignment, class Allocator = FE::aligned_allocator<internal::pool::chunk<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment>>>
using generic_pool = pool<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>;

template<typename T, size_t PageCapacity = 1 MB, class Alignment = FE::SIMD_auto_alignment, class Allocator = FE::aligned_allocator<internal::pool::chunk<void, POOL_TYPE::_GENERIC, PageCapacity, Alignment>>>
using generic_pool_ptr = std::unique_ptr<T, pool_deleter<T, FE::POOL_TYPE::_GENERIC, PageCapacity, Alignment, Allocator>>; 


END_NAMESPACE
#endif