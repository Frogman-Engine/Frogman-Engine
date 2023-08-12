#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/heap_memory_tracker.hpp>
#include <vector>
#include <deque>
#include <list>




TEST(allocator_adaptor_in_conjunction_with_heap_memory_util_tracker, instantiation)
{
	::std::vector<int, FE::std_style::scalable_aligned_allocator<int>> l_sample_vector;
	::std::list<int, FE::std_style::scalable_aligned_allocator<int>> l_sample_list;
	::std::deque<int, FE::std_style::scalable_aligned_allocator<int>> l_sample_deque;
}
