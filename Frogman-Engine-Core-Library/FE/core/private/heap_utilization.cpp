// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../heap_utilization.hpp"


std::atomic_size_t FE::heap_memory_tracker::s_global_total_bytes = 0;

thread_local FE::var::size_t FE::heap_memory_tracker::tl_s_thread_local_total_bytes = 0;


void ::FE::memset_s(void* const dest_ptrc_p, int8 value_p, length_t count_p, size_t element_bytes_p) noexcept
{
#if _AVX512_ == true
	::FE::memset_with_avx512(dest_ptrc_p, value_p, count_p, element_bytes_p);
#elif _AVX_ == true
	::FE::memset_with_avx(dest_ptrc_p, value_p, count_p, element_bytes_p);
#else
	::std::memset(dest_ptrc_p, value_p, count_p * element_bytes_p);
#endif
}

void ::FE::memcpy_s(void* const dest_memblock_ptrc_p, length_t dest_length_p, size_t dest_element_bytes_p, const void* const source_memblock_ptrc_p, length_t source_length_p, size_t source_element_bytes_p) noexcept
{
	size_t l_source_size = source_element_bytes_p * source_length_p;
	size_t l_dest_size = dest_element_bytes_p * dest_length_p;

	if (l_source_size >= l_dest_size)
	{
#if _AVX512_ == true
		::FE::memcpy_with_avx512(dest_memblock_ptrc_p, source_memblock_ptrc_p, dest_length_p, dest_element_bytes_p);
#elif _AVX_ == true
		::FE::memcpy_with_avx(dest_memblock_ptrc_p, source_memblock_ptrc_p, dest_length_p, dest_element_bytes_p);
#else
		::memcpy(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_dest_size);
#endif
	}
	else
	{
#if _AVX512_ == true
		::FE::memcpy_with_avx512(dest_memblock_ptrc_p, source_memblock_ptrc_p, source_length_p, source_element_bytes_p);
#elif _AVX_ == true
		::FE::memcpy_with_avx(dest_memblock_ptrc_p, source_memblock_ptrc_p, source_length_p, source_element_bytes_p);
#else
		::memcpy(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_source_size);
#endif
	}
}