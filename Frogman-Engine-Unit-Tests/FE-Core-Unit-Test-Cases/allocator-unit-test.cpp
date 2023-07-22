#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/allocator.hxx>




TEST(allocator, scalable_aligned_allocator)
{
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);

	{
		int* const l_ptrc = FE::scalable_aligned_allocator<int>::allocate(100);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 400);
		FE::scalable_aligned_allocator<int>::deallocate(l_ptrc, 100);
	}

	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);


	{
		int* l_ptr = FE::scalable_aligned_allocator<int>::allocate(50);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 200);

		l_ptr = FE::scalable_aligned_allocator<int>::reallocate(l_ptr, 50, 100);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 400);

		l_ptr = FE::scalable_aligned_allocator<int>::reallocate(l_ptr, 100, 10);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 40);

		FE::scalable_aligned_allocator<int>::deallocate(l_ptr, 10);
	}
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);
}




TEST(allocator, cache_aligned_allocator)
{
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);

	{
		int* const l_ptrc = FE::cache_aligned_allocator<int>::allocate(100);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 400);
		FE::cache_aligned_allocator<int>::deallocate(l_ptrc, 100);
	}

	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);


	{
		int* l_ptr = FE::cache_aligned_allocator<int>::allocate(50);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 200);

		l_ptr = FE::cache_aligned_allocator<int>::reallocate(l_ptr, 50, 100);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 400);

		l_ptr = FE::cache_aligned_allocator<int>::reallocate(l_ptr, 100, 10);
		EXPECT_EQ(FE::heap_memory_tracker<int>::query_type_data()._thread_local_total_bytes_by_type, 40);

		FE::cache_aligned_allocator<int>::deallocate(l_ptr, 10);
	}
	EXPECT_EQ(FE::heap_memory_tracker<int>::query_all_data()._global_total_bytes, 0);
}