#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/thread.hpp>
#include <FE/core/mutex.hpp>
using namespace FE;




void void_fn(int param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
}

int int_fn(int param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
	return param_p;
}

TEST(thread, fork_and_join)
{
	FE::thread l_thread;
	FE::one_arg<int> l_arg = 0;
	FE::void_function_with_1_arg<int> l_void_fn(void_fn, l_arg);
	l_thread.fork(&l_void_fn);
	l_thread.join();

	FE::function_with_1_arg<int, int> l_int_fn(int_fn, l_arg);
	int l_result;
	l_thread.fork(&l_int_fn, PASS_ARGUMENT_OBJECT(l_result));
	l_thread.join();

	EXPECT_EQ(l_result, 0);
}




void mutex_test(var::int32& int_ref_p) noexcept
{
	static FE::mutex l_s_mutex;
	FE::lock_guard<FE::mutex> l_lock_guard(l_s_mutex);
	

	for (int i = 0; i < 1000; ++i)
	{
		++int_ref_p;
	}
}

TEST(thread, mutex)
{
	constexpr auto l_thread_count = 4;
	static var::int32 l_int = 0;
	
	FE::thread l_thread[l_thread_count];

	FE::one_arg<var::int32&> l_one_arg = l_int;
	FE::void_function_with_1_arg<var::int32&> l_void_fn(mutex_test, l_one_arg);
	
	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].fork(&l_void_fn);
	}
	
	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].join();
	}

	EXPECT_EQ(l_int, l_thread_count * 1000);
}




void timed_mutex_test(var::int32& int_ref_p)
{
	static FE::timed_mutex l_s_timed_mutex;
	FE::lock_guard<FE::timed_mutex> l_lock_guard(l_s_timed_mutex, 1000);
	static var::int32 l_s_int = 0;

	for (int i = 0; i < 1000; ++i)
	{
		++int_ref_p;
	}
}

TEST(thread, timed_mutex)
{
	constexpr auto l_thread_count = 4;
	static var::int32 l_int = 0;

	FE::thread l_thread[l_thread_count];

	FE::one_arg<var::int32&> l_one_arg = l_int;
	FE::void_function_with_1_arg<var::int32&> l_void_fn(timed_mutex_test, l_one_arg);

	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].fork(&l_void_fn);
	}

	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].join();
	}

	EXPECT_EQ(l_int, l_thread_count * 1000);
}