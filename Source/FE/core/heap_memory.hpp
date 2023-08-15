#ifndef _FE_CORE_HEAP_MEMORY_TRACKER_HPP_
#define _FE_CORE_HEAP_MEMORY_TRACKER_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/miscellaneous/misc.h>
#include <FE/core/memory_metrics.h>
#include <tbb/scalable_allocator.h>
#include <FE/core/memory.hxx>




BEGIN_NAMESPACE(FE)


template<typename T, class address_alignment>
class heap_memory_tracker;


template <typename T, class alignment>
class scalable_aligned_allocator;

template <typename T>
class cache_aligned_allocator;


class heap_memory_tracker_base
{
protected:
	static ::std::atomic_size_t s_global_total_bytes;
	thread_local static var::size_t tl_s_thread_local_total_bytes;
};


#if _AVX512_ == true
template<typename U, class address_alignment = align_64bytes>
#elif _AVX_ == true
template<typename U, class address_alignment = align_32bytes>
#endif
class heap_memory_tracker final : public heap_memory_tracker_base
{
	friend class scalable_aligned_allocator<U, address_alignment>;
	friend class cache_aligned_allocator<U>;


	static ::std::atomic_size_t s_global_total_bytes_by_type;
	thread_local static var::size_t tl_s_thread_local_total_bytes_by_type;

	_FORCE_INLINE_ static void add(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker_base::s_global_total_bytes.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker_base::tl_s_thread_local_total_bytes += size_bytes_p;

		heap_memory_tracker::s_global_total_bytes_by_type.fetch_add(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes_by_type += size_bytes_p;
	}

	_FORCE_INLINE_ static void sub(size_t size_bytes_p) noexcept
	{
		heap_memory_tracker_base::s_global_total_bytes.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker_base::tl_s_thread_local_total_bytes -= size_bytes_p;

		heap_memory_tracker::s_global_total_bytes_by_type.fetch_sub(size_bytes_p, ::std::memory_order_relaxed);
		heap_memory_tracker::tl_s_thread_local_total_bytes_by_type -= size_bytes_p;
	}

public:
	typedef U memory_value_type;

	_FORCE_INLINE_ static total_memory_utilization_data query_all_data() noexcept
	{
#ifdef _ENABLE_MEMORY_TRACKER_
		total_memory_utilization_data l_data
		{
			heap_memory_tracker_base::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker_base::tl_s_thread_local_total_bytes,
			heap_memory_tracker::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
		total_memory_utilization_data l_null{_NULL_};
		return l_null;
#endif
	}
	
	_FORCE_INLINE_ static global_memory_utilization query_global_data() noexcept
	{
#ifdef _ENABLE_MEMORY_TRACKER_
		global_memory_utilization l_data
		{
			heap_memory_tracker_base::s_global_total_bytes.load(std::memory_order_relaxed), heap_memory_tracker_base::tl_s_thread_local_total_bytes
		};
		return l_data;
#else
		global_memory_utilization l_null{ _NULL_ };
		return l_null;
#endif
	}

	_FORCE_INLINE_ static type_memory_utilization query_type_data() noexcept
	{
#ifdef _ENABLE_MEMORY_TRACKER_
		type_memory_utilization l_data
		{
			heap_memory_tracker::s_global_total_bytes_by_type.load(std::memory_order_relaxed), heap_memory_tracker::tl_s_thread_local_total_bytes_by_type
		};
		return l_data;
#else
		type_memory_utilization l_null{ _NULL_ };
		return l_null;
#endif
	}


	template<typename T, class alignment>
	friend _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept;

	template<typename T, class alignment>
	friend _FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, length_t count_p, size_t bytes_p) noexcept;

	template<typename T, class alignment>
	friend _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept;
};


template<typename T, class address_alignment>
::std::atomic_size_t FE::heap_memory_tracker<T, address_alignment>::s_global_total_bytes_by_type = 0;

template<typename T, class address_alignment>
thread_local var::size_t FE::heap_memory_tracker<T, address_alignment>::tl_s_thread_local_total_bytes_by_type = 0;


#if _AVX512_ == true
template<typename T, class alignment = align_64bytes>
#elif _AVX_ == true
template<typename T, class alignment = align_32bytes>
#endif
_NODISCARD_ _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::add(count_p * bytes_p);
#endif
	T* const l_result_ptrc = (T*)::scalable_aligned_malloc(count_p * bytes_p, alignment::size);
	ALIGNED_MEMSET(l_result_ptrc, _NULL_, count_p * bytes_p);
	FE_ASSERT(l_result_ptrc == nullptr, "${%s@0}: Failed to allocate memory from scalable_aligned_malloc()", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

	FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % alignment::size) != 0, "${%s@0}: The allocated heap memory address not aligned by ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_ILLEGAL_ADDRESS_ALIGNMENT), &alignment::size);
	return l_result_ptrc;
}


#if _AVX512_ == true
template<typename T, class alignment = align_64bytes>
#elif _AVX_ == true
template<typename T, class alignment = align_32bytes>
#endif
_FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, _MAYBE_UNUSED_ length_t count_p, _MAYBE_UNUSED_ size_t bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::sub(count_p * bytes_p);
#endif 
	::scalable_aligned_free(memblock_ptrc_p);
}


#if _AVX512_ == true
template<typename T, class alignment = align_64bytes>
#elif _AVX_ == true
template<typename T, class alignment = align_32bytes>
#endif
_NODISCARD_ _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::sub(prev_length_p * prev_bytes_p);
	::FE::heap_memory_tracker<T, alignment>::add(new_length_p * new_bytes_p);
#endif

	T* l_realloc_result_ptr = (T*)::scalable_aligned_realloc(memblock_ptrc_p, new_bytes_p * new_length_p, alignment::size);

	if (l_realloc_result_ptr == nullptr) _UNLIKELY_
	{
		l_realloc_result_ptr = (T*)::scalable_aligned_malloc(new_length_p * new_bytes_p, alignment::size);
		ALIGNED_MEMSET(l_realloc_result_ptr, _NULL_, new_length_p * new_bytes_p);

		FE_ASSERT(l_realloc_result_ptr == nullptr, "${%s@0}: Failed to re-allocate memory from scalable_aligned_malloc()", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

		FE::aligned_memcpy(l_realloc_result_ptr, new_length_p, new_bytes_p, memblock_ptrc_p, prev_length_p, prev_bytes_p);
		::scalable_aligned_free(memblock_ptrc_p);
	}

	FE_ASSERT((reinterpret_cast<uintptr_t>(l_realloc_result_ptr) % alignment::size) != 0, "${%s@0}: The allocated heap memory address not aligned by ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_ILLEGAL_ADDRESS_ALIGNMENT), &alignment::size);
	return l_realloc_result_ptr;
}


END_NAMESPACE
#endif 
