#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/heap_memory_tracker.hpp>
#include <vector>



TEST(allocator_adaptor_in_conjunction_with_heap_memory_util_tracker, memory_usage_and_functionality_)
{
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);
	
	{
		::std::vector<int, FE::std_style::scalable_aligned_allocator<int>> l_sample_vector;
		l_sample_vector.reserve(100);
	
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 400);
	}
	
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);
}
