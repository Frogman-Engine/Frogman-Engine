#ifndef _FE_CORE_ALLOCATOR_HXX_
#define _FE_CORE_ALLOCATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <tbb/cache_aligned_allocator.h>
#include <tbb/scalable_allocator.h>
#include <FE/core/heap_memory.hpp>




BEGIN_NAMESPACE(FE)


template <class implementation>
class new_delete_proxy_allocator final
{
public:
	using value_type = typename implementation::value_type;
	using pointer = typename implementation::pointer;
	using const_pointer = typename implementation::const_pointer;
	using reference = typename implementation::reference;
	using const_reference = typename implementation::const_reference;
	using size_type = typename implementation::size_type;
	using allocator = implementation;

	_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
	_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = implementation::is_allocated_from_an_address_aligned_allocator;

	_NODISCARD_ _FORCE_INLINE_ static pointer allocate(size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

		pointer l_result = allocator::allocate(count_p);

		if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			new(l_result) value_type[count_p]{};
		}
		return l_result;
	}


	_NODISCARD_ _FORCE_INLINE_ static pointer reallocate(pointer const pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
	{
		if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			pointer const l_end = pointer_p + prev_count_p;
			for (pointer begin = pointer_p; begin != l_end; ++begin)
			{
				begin->~value_type();
			}
		}

		pointer l_result = allocator::reallocate(pointer_p, prev_count_p, new_count_p);

		if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			new(l_result) value_type[new_count_p]{};
		}
		return l_result;
	}


	_FORCE_INLINE_ static void deallocate(pointer const pointer_p, size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);
		FE_ASSERT(pointer_p == nullptr, "${%s@0}: attempted to delete ${%p@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), pointer_p);
		
		if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			pointer const l_end = pointer_p + count_p;
			for (pointer begin = pointer_p; begin != l_end; ++begin)
			{
				begin->~value_type();
			}
		}
		allocator::deallocate(pointer_p, count_p);
	}
};


#ifdef _AVX512_
template<typename T, class alignment = align_64bytes>
#elif defined(_AVX_)
template<typename T, class alignment = align_32bytes>
#endif
class scalable_aligned_allocator final
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = var::size_t;

	_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
	_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = true;


	_NODISCARD_ _FORCE_INLINE_ static pointer allocate(size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

		return ::FE::trackable_calloc<value_type, alignment>(count_p, sizeof(value_type));
	}


	_NODISCARD_ _FORCE_INLINE_ static pointer reallocate(pointer const pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
	{
		if (new_count_p == 0) _UNLIKELY_
		{
			deallocate(pointer_p, prev_count_p);
			return nullptr;
		}

		return ::FE::trackable_realloc<value_type, alignment>(pointer_p, prev_count_p, sizeof(value_type), new_count_p, sizeof(value_type));
	}


	_FORCE_INLINE_ static void deallocate(pointer const pointer_p, size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);
		FE_ASSERT(pointer_p == nullptr, "${%s@0}: attempted to delete ${%p@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), pointer_p);
		
		::FE::trackable_free<value_type, alignment>(pointer_p, count_p, sizeof(value_type));
	}
};


template <typename T>
class cache_aligned_allocator final
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef var::size_t size_type;

	_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
	_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = true;


	_NODISCARD_ _FORCE_INLINE_ static pointer allocate(size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

		pointer const l_result_ptrc = static_cast<pointer>(::tbb::detail::r1::cache_aligned_allocate(count_p * sizeof(value_type)));
		FE_ASSERT(l_result_ptrc == nullptr, "${%s@0}: failed to allocate memory from cache_aligned_allocator.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

		FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % 2) != 0 , "ERROR: The allocated heap memory address not aligned by two. The address value was ${%p@0}", l_result_ptrc);
		
#ifdef _ENABLE_MEMORY_TRACKER_
		::FE::heap_memory_tracker<T, align_64bytes>::__log_heap_memory_allocation(count_p * sizeof(value_type), TO_STRING(cache_aligned_allocate), l_result_ptrc, typeid(T).name());
#endif
		return l_result_ptrc;
	}
	

	_NODISCARD_ _FORCE_INLINE_ static pointer reallocate(pointer const pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
	{
		FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));

		if (new_count_p == 0) _UNLIKELY_
		{
			deallocate(pointer_p, prev_count_p);
			return nullptr;
		}

		pointer const l_result_ptrc = static_cast<pointer>(cache_aligned_allocator<T>::allocate(new_count_p));
		FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % 2) != 0, "ERROR: The allocated heap memory address not aligned by two. The address value was ${%p@0}", l_result_ptrc);
		 
		if (l_result_ptrc != pointer_p) _LIKELY_
		{
			FE::aligned_memcpy(l_result_ptrc, new_count_p, sizeof(value_type), pointer_p, prev_count_p, sizeof(value_type));
			cache_aligned_allocator<value_type>::deallocate(pointer_p, prev_count_p);
		}
		return l_result_ptrc;
	}


	_FORCE_INLINE_ static void deallocate(pointer const pointer_p, _MAYBE_UNUSED_ size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);
		FE_ASSERT(pointer_p == nullptr, "${%s@0}: attempted to delete ${%p@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), pointer_p);

#ifdef _ENABLE_MEMORY_TRACKER_
		::FE::heap_memory_tracker<T, align_64bytes>::__log_heap_memory_deallocation(count_p * sizeof(value_type), TO_STRING(cache_aligned_deallocate), pointer_p, typeid(T).name());
#endif 
		tbb::detail::r1::cache_aligned_deallocate(pointer_p);
	}
};


END_NAMESPACE
#endif