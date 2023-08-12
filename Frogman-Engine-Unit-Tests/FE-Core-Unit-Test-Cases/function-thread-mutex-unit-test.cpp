#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/thread.hpp>
#include <FE/core/mutex.hpp>
using namespace FE;




TEST(method, call)
{
	FE::method<std::vector<int>, void(std::size_t)> l_reserve;
	l_reserve = &std::vector<int>::reserve;

	std::vector<int>l_some_vec;

	l_reserve(l_some_vec, FE::buffer<std::size_t>::set_and_get(10));

	EXPECT_EQ(l_some_vec.capacity(), FE::buffer<std::size_t>::get());
}



TEST(cpp_style_task, call)
{
	std::string l_some_str = "C++ is not Java.";
	
	FE::cpp_style_task<std::string, std::size_t(void) const> l_length;
	l_length._instance_ptr = &l_some_str;
	l_length._method = &std::string::length;
	
	std::size_t l_result = 0;
	l_length(&l_result);

	EXPECT_EQ(l_result, 16);
}




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
	FE::c_style_task<void(int)> l_void_fn;
	l_void_fn._function = void_fn;
	l_void_fn._arguments._first = 0;

	l_thread.fork(&l_void_fn);
	l_thread.join();

	FE::c_style_task<int(int)> l_int_fn;
	l_int_fn._function = int_fn;
	l_int_fn._arguments._first = 0;
	
	int l_result;
	l_thread.fork(&l_int_fn, PASS_RETURN_BUFFER(l_result));
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
	
	FE::thread l_thread[l_thread_count];

	FE::c_style_task<void(var::int32&)> l_mutex_test;
	l_mutex_test._function = mutex_test;
	l_mutex_test._arguments._first = 0;

	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].fork(&l_mutex_test, nullptr);
	}
	
	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].join();
	}

	EXPECT_EQ(l_mutex_test._arguments._first, l_thread_count * 1000);
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

	FE::thread l_thread[l_thread_count];

	FE::c_style_task<void(var::int32&)> l_mutex_test;
	l_mutex_test._function = timed_mutex_test;
	l_mutex_test._arguments._first = 0;

	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].fork(&l_mutex_test, nullptr);
	}

	for (int i = 0; i < l_thread_count; ++i)
	{
		l_thread[i].join();
	}

	EXPECT_EQ(l_mutex_test._arguments._first, l_thread_count * 1000);
}