#ifndef _FE_CORE_ALLOCATOR_HXX_
#define _FE_CORE_ALLOCATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include <tbb/cache_aligned_allocator.h>
#include <tbb/scalable_allocator.h>
#include "heap_memory_tracker.hpp"



BEGIN_NAMESPACE(FE)


template <typename T, class alignment = align_8bytes>
class scalable_aligned_allocator final
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = var::size_t;


	_NODISCARD_ _FORCE_INLINE_ static T* allocate(count_t count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.");

		return ::FE::trackable_calloc<T, alignment>(count_p, sizeof(T));
	}


	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, count_t prev_count_p, count_t new_count_p) noexcept
	{
		if (new_count_p == 0) _UNLIKELY_
		{
			deallocate(ptrc_p, prev_count_p);
			return nullptr;
		}

		return ::FE::trackable_realloc<T, alignment>(ptrc_p, prev_count_p, sizeof(T), new_count_p, sizeof(T));
	}


	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, count_t count_p) noexcept
	{
		FE_ASSERT((ptrc_p == nullptr) || (count_p == 0), "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr or the size input value is zero.");
		
		::FE::trackable_free<T, alignment>(ptrc_p, count_p, sizeof(T));
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


	_NODISCARD_ _FORCE_INLINE_ static T* allocate(count_t count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.");

#ifdef _ENABLE_MEMORY_TRACKER_
		::FE::heap_memory_tracker<T>::add(sizeof(T) * count_p);
#endif
		T* const l_result_ptrc = static_cast<T*>(::tbb::detail::r1::cache_aligned_allocate(count_p * sizeof(T)));
		FE_ASSERT(l_result_ptrc == nullptr, "UNRECOVERABLE CRITICAL ERROR!: failed to allocate memory from cache_aligned_allocator.");

		FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % 2) != 0 , "WANRING: The allocated heap memory address not aligned.");
		return l_result_ptrc;
	}
	

	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, count_t prev_count_p, count_t new_count_p) noexcept
	{
		if (new_count_p == 0) _UNLIKELY_
		{
			deallocate(ptrc_p, prev_count_p);
			return nullptr;
		}

		T* const l_result_ptrc = static_cast<T*>(cache_aligned_allocator<T>::allocate(new_count_p));
		FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % 2) != 0, "WANRING: The allocated heap memory address not aligned.");

		::FE::unaligned_memcpy(l_result_ptrc, new_count_p, sizeof(T), ptrc_p, prev_count_p, sizeof(T));
		cache_aligned_allocator<T>::deallocate(ptrc_p, prev_count_p);

		return l_result_ptrc;
	}


	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, _MAYBE_UNUSED_ count_t count_p) noexcept
	{
		FE_ASSERT((ptrc_p == nullptr) || (count_p == 0), "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr or the size input value is zero.");

#ifdef _ENABLE_MEMORY_TRACKER_
		::FE::heap_memory_tracker<T>::sub(sizeof(T) * count_p);
#endif 
		::tbb::detail::r1::cache_aligned_deallocate(ptrc_p);
	}
};


END_NAMESPACE
#endif