#ifndef _FE_CORE_UNIQUE_PTR_HXX_
#define _FE_CORE_UNIQUE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/allocator.hxx>




BEGIN_NAMESPACE(FE)


template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type, FE::align_8bytes>>>
class unique_ptr final
{
public:
	using pointer = typename allocator::pointer;
	using element_type = typename allocator::value_type;
	using allocator_type = allocator;

private:
	pointer m_smart_ptr;

public:
	_FORCE_INLINE_ constexpr unique_ptr() noexcept : m_smart_ptr() {}
	
	_CONSTEXPR23_ _FORCE_INLINE_ ~unique_ptr() noexcept 
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		allocator::deallocate(this->m_smart_ptr, 1);
		this->m_smart_ptr = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(const unique_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(unique_ptr&& rvalue_p) noexcept : m_smart_ptr(rvalue_p.m_smart_ptr)
	{
		rvalue_p.m_smart_ptr = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(element_type value_p) noexcept : m_smart_ptr(allocator::allocate(1))
	{
		*this->m_smart_ptr = std::move(value_p);
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(const unique_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(unique_ptr&& rvalue_p) noexcept 
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;
		return *this;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(element_type value_p) noexcept 
	{
		if (this->m_smart_ptr == nullptr)
		{
			this->m_smart_ptr = allocator::allocate(1);
		}

		*this->m_smart_ptr = std::move(value_p);
		return *this;
	}

	_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ pointer release() noexcept 
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		return l_result;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset() noexcept
	{
		this->~unique_ptr();
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset(element_type value_p) noexcept
	{
		this->~unique_ptr();
		*this = std::move(value_p);
	}

	_FORCE_INLINE_ void swap(unique_ptr& other_ref_p) noexcept
	{
		pointer l_temporary_smart_ptr = other_ref_p.m_smart_ptr;
		other_ref_p.m_smart_ptr = this->m_smart_ptr;
		this->m_smart_ptr = l_temporary_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return *this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean is_nullptr() const noexcept
	{
		return (this->m_smart_ptr == nullptr) ? true : false;
	}
};

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T, FE::align_8bytes>>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ unique_ptr<T, allocator> make_unique() noexcept
{
	return unique_ptr<T, allocator>(T());
}

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T, FE::align_8bytes>>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ unique_ptr<T, allocator> make_unique(T value_p) noexcept
{
	return unique_ptr<T, allocator>( T( std::move(value_p) ) );
}

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T, FE::align_8bytes>>, typename... arguments>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ unique_ptr<T, allocator> make_unique(arguments... arguments_p) noexcept
{
	return unique_ptr<T, allocator>( T( std::move(arguments_p...) ) );
}




template<typename T, class allocator>
class unique_ptr<T[], allocator> final
{
public:
	using pointer = typename allocator::pointer;
	using element_type = typename allocator::value_type;
	using allocator_type = allocator;

private:
	pointer m_smart_ptr;
	pointer m_smart_ptr_end;

public:
	_FORCE_INLINE_ constexpr unique_ptr() noexcept : m_smart_ptr(), m_smart_ptr_end() {}

	_CONSTEXPR23_ _FORCE_INLINE_ ~unique_ptr() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		allocator::deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
		this->m_smart_ptr = nullptr;
		this->m_smart_ptr_end = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(const unique_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(unique_ptr&& rvalue_p) noexcept : m_smart_ptr(rvalue_p.m_smart_ptr), m_smart_ptr_end(rvalue_p.m_smart_ptr_end)
	{
		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_smart_ptr_end = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr(std::initializer_list<element_type>&& values_p) noexcept : m_smart_ptr(allocator::allocate( values_p.size() )), m_smart_ptr_end(m_smart_ptr + values_p.size())
	{
		pointer l_array_smart_ptr_iterator = this->m_smart_ptr;
		for (element_type* initializer_list_iterator = const_cast<element_type*>(values_p.begin()); initializer_list_iterator != values_p.end(); ++initializer_list_iterator)
		{
			*l_array_smart_ptr_iterator = std::move(*initializer_list_iterator);
			++l_array_smart_ptr_iterator;
		}
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(const unique_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(unique_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		this->m_smart_ptr_end = rvalue_p.m_smart_ptr_end;

		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_smart_ptr_end = nullptr;
		return *this;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ unique_ptr& operator=(std::initializer_list<element_type>&& values_p) noexcept
	{
		this->m_smart_ptr = allocator::reallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr, values_p.size());

		pointer l_array_smart_ptr_iterator = this->m_smart_ptr;
		for (element_type* initializer_list_iterator = const_cast<element_type*>(values_p.begin()); initializer_list_iterator != values_p.end(); ++initializer_list_iterator)
		{
			*l_array_smart_ptr_iterator = std::move(*initializer_list_iterator);
			++l_array_smart_ptr_iterator;
		}
		return *this;
	}

	_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		this->m_smart_ptr_end = nullptr;
		return l_result;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset() noexcept
	{
		this->~unique_ptr();
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset(std::initializer_list<element_type>&& values_p) noexcept
	{
		this->~unique_ptr();
		this->m_smart_ptr = allocator::allocate(values_p.size());
		this->m_smart_ptr_end = this->m_smart_ptr + values_p.size();

		pointer l_array_smart_ptr_iterator = this->m_smart_ptr;
		for (element_type* initializer_list_iterator = const_cast<element_type*>(values_p.begin()); initializer_list_iterator != values_p.end(); ++initializer_list_iterator)
		{
			*l_array_smart_ptr_iterator = std::move(*initializer_list_iterator);
			++l_array_smart_ptr_iterator;
		}
	}

	_FORCE_INLINE_ void swap(unique_ptr& other_ref_p) noexcept
	{
		pointer l_temporary_smart_ptr = other_ref_p.m_smart_ptr;
		pointer l_temporary_smart_ptr_end = other_ref_p.m_smart_ptr_end;
		other_ref_p.m_smart_ptr = this->m_smart_ptr;
		other_ref_p.m_smart_ptr_end = this->m_smart_ptr_end;
		this->m_smart_ptr = l_temporary_smart_ptr;
		this->m_smart_ptr_end = l_temporary_smart_ptr_end;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return *this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ element_type& operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		FE_ASSERT(static_cast<index_t>(this->m_smart_ptr_end - this->m_smart_ptr) <= index_p, "${%s@0}: ${%s@1} exceeds the index boundary. ${%s@1} was ${%lu@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(index_p), &index_p);

		return this->m_smart_ptr[index_p];
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean is_nullptr() const noexcept
	{
		return (this->m_smart_ptr == nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::size_t size() const noexcept
	{
		return this->m_smart_ptr_end - this->m_smart_ptr;
	}
};




END_NAMESPACE
#endif