#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/heap_memory.hpp>
#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/thread.hpp>


TEST(concurrent_memory_block, concurrency)
{
	constexpr int l_thread_count = 4;
	using namespace FE;

	FE::concurrent_memory_block<std::string> l_concurrent_memblock;
	var::boolean l_was_construction_successful[l_thread_count];
	std::thread l_threads[l_thread_count];
	
	for (int i = 0; i < l_thread_count; ++i)
	{
		l_threads[i] = std::thread([&, i]()
		{
			l_was_construction_successful[i] = l_concurrent_memblock.call_constructor("call_constructor");
		});
	}
	
	int l_true_count = 0;
	for (int i = 0; i < l_thread_count; ++i)
	{
		l_threads[i].join();
		if (l_was_construction_successful[i] == true)
		{
			++l_true_count;
		}
	}

	EXPECT_EQ(l_true_count, 1);
}


