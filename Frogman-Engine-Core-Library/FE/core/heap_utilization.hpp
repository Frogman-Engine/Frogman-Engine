#ifndef _FE_CORE_HEAP_UTILIZATION_HPP_
#define _FE_CORE_HEAP_UTILIZATION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <oneapi/tbb/scalable_allocator.h>
#include "prerequisite_symbols.h"
#include "memory_metrics.h"
#include "private/memory.hpp"


BEGIN_NAMESPACE(FE)


template<typename T, class alignment>
class heap_utilization;

template<typename T>
class new_delete_allocator;

template <typename T, class alignment>
class scalable_aligned_allocator;

template <typename T>
class cache_aligned_allocator;


void memset_s(void* const dst_ptrc_p, int8 value_p, length_t count_p, size_t element_bytes_p) noexcept;

void memcpy_s(void* const dest_memblock_ptrc_p, length_t dest_length_p, size_t dest_element_bytes_p, const void* const source_memblock_ptrc_p, length_t source_length_p, size_t source_element_bytes_p) noexcept;


class heap_memory_tracker
{
protected:
	static ::std::atomic_size_t s_global_total_bytes;
	thread_local static var::size_t tl_s_thread_local_total_bytes;
};


template<typename U, class alignment = align_8bytes>
class heap_utilization final : public heap_memory_tracker
{
	friend class new_delete_allocator<U>;
	friend class scalable_aligned_allocator<U, alignment>;
	friend class cache_aligned_allocator<U>;

private:
	static ::std::atomic_size_t s_global_total_bytes_by_type;
	thread_local static var::size_t tl_s_thread_local_total_bytes_by_type;

private:
	static void add(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker::s_global_total_bytes.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes += size_bytes_p;

		heap_utilization<U>::s_global_total_bytes_by_type.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_utilization<U>::tl_s_thread_local_total_bytes_by_type += size_bytes_p;
	}

	static void sub(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker::s_global_total_bytes.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes -= size_bytes_p;

		heap_utilization<U>::s_global_total_bytes_by_type.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_utilization<U>::tl_s_thread_local_total_bytes_by_type -= size_bytes_p;
	}

public:
	typedef U memory_type;

	static total_memory_utilization_data query_all_data() noexcept 
	{
#if _ENABLE_MEMORY_TRACKER_ == true
		total_memory_utilization_data l_data
		{
			heap_memory_tracker::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes,
			heap_utilization<U>::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_utilization<U>::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
		total_memory_utilization_data l_null{_NULL_};
		return l_null;
#endif
	}
	
	static global_memory_utilization query_global_data() noexcept
	{
#if _ENABLE_MEMORY_TRACKER_ == true
		global_memory_utilization l_data
		{
			heap_memory_tracker::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes
		};
		return l_data;
#else
		global_memory_utilization l_null{ _NULL_ };
		return l_null;
#endif
	}

	static type_memory_utilization query_type_data() noexcept
	{
#if _ENABLE_MEMORY_TRACKER_ == true
		type_memory_utilization l_data
		{
			heap_utilization<U>::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_utilization<U>::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
		type_memory_utilization l_null{ _NULL_ };
		return l_null;
#endif
	}

public:
	template<typename T, class alignment>
	friend _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept;

	template<typename T, class alignment>
	friend _FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, length_t count_p, size_t bytes_p) noexcept;

	template<typename T, class alignment>
	friend _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept;
};


template<typename T, class alignment>
::std::atomic_size_t FE::heap_utilization<T, alignment>::s_global_total_bytes_by_type = 0;

template<typename T, class alignment>
thread_local var::size_t FE::heap_utilization<T, alignment>::tl_s_thread_local_total_bytes_by_type = 0;


template<typename T, class alignment = align_8bytes>
_NODISCARD_ _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == true
	::FE::heap_utilization<T>::add(count_p * bytes_p);
#endif
	T* l_result_ptr = (T*)::scalable_aligned_malloc(count_p * bytes_p, alignment::s_size);
	::FE::memset_s(l_result_ptr, _NULL_, count_p, bytes_p);
	FE_ASSERT(l_result_ptr == nullptr, "UNRECOVERABLE CRITICAL ERROR!: l_result_ptr is nullptr. Failed to allocate memory from scalable_calloc()", _ASSERTED_LOCATION_);
	return l_result_ptr;
}


template<typename T, class alignment = align_8bytes>
_FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, length_t count_p, size_t bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == true
	::FE::heap_utilization<T>::sub(count_p * bytes_p);
#endif 
	::scalable_aligned_free(memblock_ptrc_p);
}


template<typename T, class alignment = align_8bytes>
_NODISCARD_ _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept
{
#if _ENABLE_MEMORY_TRACKER_ == true
	::FE::heap_utilization<T>::s_global_total_bytes_by_type::sub(prev_length_p * prev_bytes_p);
	::FE::heap_utilization<T>::s_global_total_bytes_by_type::add(new_length_p * new_bytes_p);
#endif

	T* l_realloc_result_ptr = (T*)::scalable_aligned_realloc(memblock_ptrc_p, new_bytes_p * new_length_p, alignment::s_size);

	if (l_realloc_result_ptr == nullptr) _UNLIKELY_
	{
		l_realloc_result_ptr = (T*)::scalable_aligned_malloc(new_length_p * new_bytes_p, alignment::s_size);
		::FE::memset_s(l_realloc_result_ptr, _NULL_, new_length_p, new_bytes_p);

		FE_ASSERT(l_realloc_result_ptr == nullptr, "CRITICAL ERROR: Failed to re-allocate memory", _ASSERTED_LOCATION_);

		::FE::memcpy_s(l_realloc_result_ptr, new_length_p, new_bytes_p, memblock_ptrc_p, prev_length_p, prev_bytes_p);
		::scalable_aligned_free(memblock_ptrc_p);
	}

	return l_realloc_result_ptr;
}


END_NAMESPACE
#endif 
