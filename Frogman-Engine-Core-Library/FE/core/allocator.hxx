#ifndef _FE_CORE_ALLOCATOR_HXX_
#define _FE_CORE_ALLOCATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "private/memory.hpp"
#include "heap_utilization.hpp"
#include <tbb/cache_aligned_allocator.h>


BEGIN_NAMESPACE(FE)


template <typename T>
class new_delete_allocator final
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
		T* l_allocation_result_ptr = nullptr;
		// must invoke delete[] when returning memory to the system. Calling delete without index operator [] will abort() the application.
		switch (count_p)
		{
		case 0:
			FE_ASSERT(true, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.", _SOURCE_LOCATION_);
			break;

		case 1:
#if _ENABLE_MEMORY_TRACKER_ == true
			::FE::heap_utilization<T>::add(sizeof(T));
#endif
			l_allocation_result_ptr = new T;
			FE_ASSERT(l_allocation_result_ptr == nullptr, "UNRECOVERABLE CRITICAL ERROR!: failed to allocate memory from new_delete_allocator.", _SOURCE_LOCATION_);
			return l_allocation_result_ptr;

		default:
#if _ENABLE_MEMORY_TRACKER_ == true
			::FE::heap_utilization<T>::add(sizeof(T) * count_p);
#endif
			l_allocation_result_ptr = new T[count_p];
			FE_ASSERT(l_allocation_result_ptr == nullptr, "UNRECOVERABLE CRITICAL ERROR!: failed to allocate memory from new_delete_allocator.", _SOURCE_LOCATION_);
			return l_allocation_result_ptr;
		}
	}


	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, count_t prev_count_p, count_t new_count_p) noexcept
	{
		FE_ASSERT(new_count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried reallocation size is zero.", _SOURCE_LOCATION_);

		T* l_realloc_result_ptr = new_delete_allocator<T>::allocate(new_count_p);
		::FE::memcpy_s(l_realloc_result_ptr, new_count_p, sizeof(T), ptrc_p, prev_count_p, sizeof(T));
		new_delete_allocator<T>::deallocate(ptrc_p, prev_count_p);
		return l_realloc_result_ptr;
	}


	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, count_t count_p) noexcept
	{
		FE_ASSERT(ptrc_p == nullptr, "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr.", _SOURCE_LOCATION_);

		switch (count_p)
		{
		case 0:
			FE_ASSERT(true, "UNRECOVERABLE CRITICAL ERROR!: attempted to delete zero byte.", _SOURCE_LOCATION_);
			break;
		case 1:
#if _ENABLE_MEMORY_TRACKER_ == true
			::FE::heap_utilization<T>::sub(sizeof(T));
#endif
			delete ptrc_p;
			break;

		default:
			break;
		}

#if _ENABLE_MEMORY_TRACKER_ == true
		::FE::heap_utilization<T>::sub(sizeof(T) * count_p);
#endif 
		delete[] ptrc_p;
	}
};


template <typename T, class alignment = align_8bytes>
class scalable_aligned_allocator final
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
		FE_ASSERT(count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.", _SOURCE_LOCATION_);

		return ::FE::trackable_calloc<T, alignment>(count_p, sizeof(T));
	}


	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, count_t prev_count_p, count_t new_count_p) noexcept
	{
		FE_ASSERT(new_count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried reallocation size is zero.", _SOURCE_LOCATION_);

		return ::FE::trackable_realloc<T, alignment>(ptrc_p, prev_count_p, sizeof(T), new_count_p, sizeof(T));
	}


	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, count_t count_p) noexcept
	{
		FE_ASSERT((ptrc_p == nullptr) || (count_p == 0), "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr or the size input value is zero.", _SOURCE_LOCATION_);
		
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
		FE_ASSERT(count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried allocation size is zero.", _SOURCE_LOCATION_);

#if _ENABLE_MEMORY_TRACKER_ == true
		::FE::heap_utilization<T>::add(sizeof(T) * count_p);
#endif
		T* l_result_ptrc = static_cast<T*>(::tbb::detail::r1::cache_aligned_allocate(count_p * sizeof(T)));
		FE_ASSERT(l_result_ptrc == nullptr, "UNRECOVERABLE CRITICAL ERROR!: failed to allocate memory from cache_aligned_allocator.", _SOURCE_LOCATION_);
		return l_result_ptrc;
	}
	

	_NODISCARD_ _FORCE_INLINE_ static T* reallocate(T* const ptrc_p, count_t prev_count_p, count_t new_count_p) noexcept
	{
		FE_ASSERT(new_count_p == 0, "UNRECOVERABLE CRITICAL ERROR!: queried reallocation size is zero.", _SOURCE_LOCATION_);
		
		T* l_result_ptr = static_cast<T*>(cache_aligned_allocator<T>::allocate(new_count_p));
		::FE::memcpy_s(l_result_ptr, new_count_p, sizeof(T), ptrc_p, prev_count_p, sizeof(T));
		cache_aligned_allocator<T>::deallocate(ptrc_p, prev_count_p);

		return l_result_ptr;
	}


	_FORCE_INLINE_ static void deallocate(T* const ptrc_p, count_t count_p) noexcept
	{
		FE_ASSERT((ptrc_p == nullptr) || (count_p == 0), "UNRECOVERABLE CRITICAL ERROR!: attempted to delete nullptr or the size input value is zero.", _SOURCE_LOCATION_);

#if _ENABLE_MEMORY_TRACKER_ == true
		::FE::heap_utilization<T>::sub(sizeof(T) * count_p);
#endif 
		::tbb::detail::r1::cache_aligned_deallocate(ptrc_p);
	}
};


END_NAMESPACE
#endif