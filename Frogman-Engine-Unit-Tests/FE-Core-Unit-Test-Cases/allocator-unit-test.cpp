#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/allocator.hxx>




#ifdef _DEBUG_

struct test {};

TEST(allocator, scalable_aligned_allocator)
{
	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);

	{
		test* const l_ptrc = FE::scalable_aligned_allocator<test>::allocate(100);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 100);
		FE::scalable_aligned_allocator<test>::deallocate(l_ptrc, 100);
	}

	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);


	{
		test* l_ptr = FE::scalable_aligned_allocator<test>::allocate(50);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 50);

		l_ptr = FE::scalable_aligned_allocator<test>::reallocate(l_ptr, 50, 100);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 100);

		l_ptr = FE::scalable_aligned_allocator<test>::reallocate(l_ptr, 100, 10);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 10);

		FE::scalable_aligned_allocator<test>::deallocate(l_ptr, 10);
	}
	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);
}




TEST(allocator, cache_aligned_allocator)
{
	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);

	{
		test* const l_ptrc = FE::cache_aligned_allocator<test>::allocate(100);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 100);
		FE::cache_aligned_allocator<test>::deallocate(l_ptrc, 100);
	}

	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);


	{
		test* l_ptr = FE::cache_aligned_allocator<test>::allocate(50);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 50);

		l_ptr = FE::cache_aligned_allocator<test>::reallocate(l_ptr, 50, 100);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 100);

		l_ptr = FE::cache_aligned_allocator<test>::reallocate(l_ptr, 100, 10);
		EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, sizeof(test) * 10);

		FE::cache_aligned_allocator<test>::deallocate(l_ptr, 10);
	}
	EXPECT_EQ(FE::heap_memory_tracker<test>::query_type_data()._thread_local_total_bytes_by_type, 0);
}
#endif