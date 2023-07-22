#ifndef _FE_CORE_HEAP_MEMORY_TRACKER_HPP_
#define _FE_CORE_HEAP_MEMORY_TRACKER_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <oneapi/tbb/scalable_allocator.h>
#include "prerequisite_symbols.h"
#include <FE/core/algorithm/string.hxx>
#include <FE/core/memory_metrics.h>
#include <FE/miscellaneous/misc.h>
#include <FE/core/clock.hpp>
#include <FE/core/thread.hpp>
#include <filesystem>
#include <fstream>



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

    thread_local static std::ofstream tl_s_utilized_heap_memory_output_stream;
    thread_local static std::string tl_s_utilized_heap_memory_output_stream_buffer;
    thread_local static FE::clock tl_s_clock;
};


namespace internal
{
	struct heap_memory_tracker_initialization_argument
	{
		static lazy_const<var::size_t> s_output_stream_buffer_size;
	};
}


template<typename U, class address_alignment = align_8bytes>
class heap_memory_tracker final : public heap_memory_tracker_base
{
	friend class FE::internal::engine_main;
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

	_FORCE_INLINE_ static void create_report_file() noexcept
	{
		::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / "Heap Memory Tracker Report\0");
		if (::std::filesystem::exists(l_directory_name) == false)
		{
			::std::filesystem::create_directory(l_directory_name);
		}

		tl_s_utilized_heap_memory_output_stream_buffer.reserve(internal::heap_memory_tracker_initialization_argument::s_output_stream_buffer_size.load());
		std::memset(tl_s_utilized_heap_memory_output_stream_buffer.data(), _NULL_, internal::heap_memory_tracker_initialization_argument::s_output_stream_buffer_size.load() * sizeof(char));

#ifdef _WINDOWS_64BIT_OS_
		var::wchar l_thread_id[thread::_MAX_THRED_ID_DIGIT_LENGTH_] = L"\0";
		::swprintf(l_thread_id, thread::_MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", ::FE::thread::tl_s_this_thread_id); // hashed thread-ids from std::hash are too long and hard to read 

		var::wchar l_date_info_wstring[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = L"\0";
		::std::mbstowcs(l_date_info_wstring, exception::tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
		std::memset(l_date_info_wstring + (::std::wcslen(l_date_info_wstring) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(var::wchar)); // to remove seconds
		
		::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_wstring;

		var::wchar l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = L"\0";
		::std::wcscpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

		::FE::algorithm::string::concatenate_strings<var::wchar>
		(
				l_full_path_to_the_file,
				_FULL_PATH_TO_FILE_MAX_LENGTH_,
				{
					L"\\thread ",
					l_thread_id,
					L" @ ",
					l_date_info_wstring,
					L".txt"
				}
		);

#elif defined(_LINUX_64BIT_OS_)
		var::character l_thread_id[FE::thread::_MAX_THRED_ID_DIGIT_LENGTH_] = "\0";
		snprintf(l_thread_id, FE::thread::_MAX_THRED_ID_DIGIT_LENGTH_, "%llu", ::FE::thread::tl_s_this_thread_id);

		var::character l_date_info_string[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = "\0";
		::std::strcpy(l_date_info_string, tl_s_clock.get_current_local_time());
		std::memset(l_date_info_string + (::std::strlen(l_date_info_string) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(char)); // to remove min sec
		::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_string;

		var::character l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = "\0";
		strcpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

		::FE::algorithm::string::concatenate_strings<var::character>
			(
				l_full_path_to_the_file,
				_FULL_PATH_TO_FILE_MAX_LENGTH_,
				{
					"/thread ",
					l_thread_id,
					" @ ",
					l_date_info_string,
					".txt"
				}
		);

#endif

		if (::std::filesystem::exists(l_path_to_log_dump_file) == false)
		{
			::std::filesystem::create_directory(l_path_to_log_dump_file);
		}

		tl_s_utilized_heap_memory_output_stream.open(l_full_path_to_the_file);
		tl_s_utilized_heap_memory_output_stream << "-------------------------------------------------- BEGIN HEAP MEMORY TRACKER RECORD --------------------------------------------------\n\n";
	}

	_FORCE_INLINE_ static void close_report_file() noexcept
	{
		tl_s_utilized_heap_memory_output_stream << "\n\n-------------------------------------------------- END OF HEAP MEMORY TRACKER RECORD --------------------------------------------------";
		tl_s_utilized_heap_memory_output_stream.close();
	}

	_FORCE_INLINE_ static void write_data_to_file() noexcept
	{
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


template<typename T, class alignment = align_8bytes>
_NODISCARD_ _FORCE_INLINE_ T* trackable_calloc(length_t count_p, size_t bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::add(count_p * bytes_p);
#endif
	T* const l_result_ptrc = (T*)::scalable_aligned_malloc(count_p * bytes_p, alignment::s_size);
	UNALIGNED_MEMSET(l_result_ptrc, _NULL_, count_p * bytes_p);
	FE_ASSERT(l_result_ptrc == nullptr, "UNRECOVERABLE CRITICAL ERROR!: l_result_ptr is nullptr. Failed to allocate memory from scalable_aligned_malloc()");

	FE_ASSERT((reinterpret_cast<uintptr_t>(l_result_ptrc) % 2) != 0, "WANRING: The allocated heap memory address not aligned.");
	return l_result_ptrc;
}


template<typename T, class alignment = align_8bytes>
_FORCE_INLINE_ void trackable_free(T* const memblock_ptrc_p, _MAYBE_UNUSED_ length_t count_p, _MAYBE_UNUSED_ size_t bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::sub(count_p * bytes_p);
#endif 
	::scalable_aligned_free(memblock_ptrc_p);
}


template<typename T, class alignment = align_8bytes>
_NODISCARD_ _FORCE_INLINE_ T* trackable_realloc(T* const memblock_ptrc_p, length_t prev_length_p, size_t prev_bytes_p, length_t new_length_p, size_t new_bytes_p) noexcept
{
#ifdef _ENABLE_MEMORY_TRACKER_
	::FE::heap_memory_tracker<T, alignment>::sub(prev_length_p * prev_bytes_p);
	::FE::heap_memory_tracker<T, alignment>::add(new_length_p * new_bytes_p);
#endif

	T* l_realloc_result_ptr = (T*)::scalable_aligned_realloc(memblock_ptrc_p, new_bytes_p * new_length_p, alignment::s_size);

	if (l_realloc_result_ptr == nullptr) _UNLIKELY_
	{
		l_realloc_result_ptr = (T*)::scalable_aligned_malloc(new_length_p * new_bytes_p, alignment::s_size);
		UNALIGNED_MEMSET(l_realloc_result_ptr, _NULL_, new_length_p * new_bytes_p);

		FE_ASSERT(l_realloc_result_ptr == nullptr, "CRITICAL ERROR: Failed to re-allocate memory");

		::FE::unaligned_memcpy(l_realloc_result_ptr, new_length_p, new_bytes_p, memblock_ptrc_p, prev_length_p, prev_bytes_p);
		::scalable_aligned_free(memblock_ptrc_p);
	}

	FE_ASSERT((reinterpret_cast<uintptr_t>(l_realloc_result_ptr) % 2) != 0, "WANRING: The allocated heap memory address not aligned.");
	return l_realloc_result_ptr;
}


END_NAMESPACE
#endif 
