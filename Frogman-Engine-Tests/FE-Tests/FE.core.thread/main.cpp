#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/thread.hpp>
#include <FE/core/function.hxx>
using namespace FE;

#ifdef _LINUX_X86_64_
#include <sched.h>
#endif

// std
#include <cmath>

/*
ls: lists all folders in the current working directory
ls filename: checks the presence of files with the specified name.
*/

class tls
{
public:
    tls()
    {
        std::cerr << "tls constructed\n";
    }

    ~tls()
    {
        std::cerr << "tls destructed\n";
    }
};

thread_local static tls tl_s_tls;

int main()
{
    using namespace FE;
    
    // This test sees if a host physical core of the logical thread can be changed over the app execution time.
    // It seems like Thread Local Storage lifetime is bound with the lifecycle of a logical thread on Ubuntu x86-64.
    // The result may vary on the operating system. 

    uint64 thread_id = std::thread::hardware_concurrency();
    FE_LOG("Total thread count: ${%lu@0}", &thread_id);

#ifdef _LINUX_X86_64_
    int64 physical_core_id = sched_getcpu();
    for(var::uint64 i = 0; i < 1000000000000000000; ++i)
    {
        int64 new_physical_core_id = sched_getcpu();
        FE_ASSERT(physical_core_id != new_physical_core_id, "Whiskey Tango Foxtrot?"); // It aborts the process if its host physical core gets chaged.
        (void)tl_s_tls;
    }
#endif

    return 0;
}




namespace test_sample
{
	var::float64 abs(float64& value_ref_p)
	{
		return ::abs(value_ref_p);
	}

	var::float64 abs(float64* value_ptr_p)
	{
		return ::abs(*value_ptr_p);
	}

	struct s
	{
		int32 fn(int32 p)
		{
			return p;
		}

		int32 fn(int32& ref_p)
		{
			return ref_p;
		}

		int32 fn(int32* ptr_p)
		{
			return *ptr_p;
		}
	};
}


void void_fn(int32 param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
}

int32 int_fn(int32 param_p) noexcept
{
	EXPECT_EQ(param_p, 0);
	return param_p;
}

TEST(thread, fork_and_join)
{
	FE::thread l_thread;
	FE::c_style_task<void(int32), FE::FORWARD_DATA::_AS_RVALUE_REF, var::int32> l_void_fn;
	l_void_fn._function = void_fn;
	l_void_fn._arguments_buffer._first = 0;

	l_thread.fork(&l_void_fn);
	l_thread.join();




	FE::c_style_task<int32(int32), FE::FORWARD_DATA::_AS_RVALUE_REF, var::int32> l_int_fn;
	l_int_fn._function = int_fn;
	l_int_fn._arguments_buffer._first = 0;

	l_thread.fork(&l_int_fn);
	l_thread.join();

	EXPECT_EQ(l_int_fn._task_result, 0);
}




TEST(function, call_by_value)
{
	FE::function<long double(long double), FE::FORWARD_DATA::_AS_RVALUE_REF> l_abs = abs;
	float64 l_input = -7.0;
	float64 l_result = l_abs(l_input);
	EXPECT_EQ(l_result, 7.0f);
}

TEST(function, call_by_lvalue_reference)
{
	FE::function<var::float64(float64&), FE::FORWARD_DATA::_AS_LVALUE_REF> l_abs = test_sample::abs;
	var::float64 l_input = -5.0;
	float64 l_result = l_abs(l_input);
	EXPECT_EQ(l_result, 5.0f);
}

TEST(function, call_by_address)
{
	FE::function<var::float64(float64*), FE::FORWARD_DATA::_AS_RVALUE_REF> l_abs = test_sample::abs;
	var::float64 l_input = -5.0;
	float64 l_result = l_abs(&l_input);
	EXPECT_EQ(l_result, 5.0f);
}




TEST(method, call_by_value)
{
	FE::method<test_sample::s, int32(int32), FE::FORWARD_DATA::_AS_RVALUE_REF> l_fn = &test_sample::s::fn;
	var::int32 l_input = 5;
	test_sample::s l_s;
	int32 l_result = l_fn(l_s, std::move(l_input));
	EXPECT_EQ(l_result, l_input);
}

TEST(method, call_by_lvalue_reference)
{
	FE::method<test_sample::s, int32(int32&), FE::FORWARD_DATA::_AS_LVALUE_REF> l_fn = &test_sample::s::fn;
	int32 l_input = 5;
	test_sample::s l_s;
	int32 l_result = l_fn(l_s, l_input);
	EXPECT_EQ(l_result, l_input);
}

TEST(method, call_by_address)
{
	FE::method<test_sample::s, int32(int32*), FE::FORWARD_DATA::_AS_RVALUE_REF> l_fn = &test_sample::s::fn;
	var::int32 l_input = 5;
	test_sample::s l_s;
	int32 l_result = l_fn(l_s, &l_input);
	EXPECT_EQ(l_result, l_input);
}




TEST(c_style_task, call_by_value)
{
	FE::c_style_task<long double(long double), FE::FORWARD_DATA::_AS_RVALUE_REF, long double> l_abs;
	l_abs._function = abs;
	l_abs._arguments_buffer._first = -9.0f;

	l_abs();

	EXPECT_EQ(l_abs._task_result, 9.0);
}

TEST(c_style_task, call_by_lvalue_reference)
{
	FE::c_style_task<var::float64(float64&), FE::FORWARD_DATA::_AS_RVALUE_REF, var::float64> l_abs;
	l_abs._function = test_sample::abs;
	l_abs._arguments_buffer._first = -9.0f;

	l_abs();

	EXPECT_EQ(l_abs._task_result, 9.0);
}

TEST(c_style_task, call_by_address)
{
	FE::c_style_task<var::float64(float64*), FE::FORWARD_DATA::_AS_RVALUE_REF, var::float64*> l_abs;
	l_abs._function = test_sample::abs;
	l_abs._arguments_buffer._first = &FE::buffer<var::float64>::set_and_get(-9.0f);

	l_abs();

	EXPECT_EQ(l_abs._task_result, 9.0);
}




TEST(cpp_style_task, call_by_value)
{
	std::string l_some_str;

	FE::cpp_style_task<std::string, std::string&(const char*), FE::FORWARD_DATA::_AS_RVALUE_REF, const char*> l_reserve;
	l_reserve._arguments_buffer._first = "std::string";
	l_reserve._method = &std::string::assign;
	l_reserve.set_instance(&l_some_str);

	l_reserve();
	EXPECT_TRUE(l_reserve._task_result == "std::string");
}

TEST(cpp_style_task, call_by_lvalue_reference)
{
	std::string l_some_str;

	FE::cpp_style_task<std::string, std::string&(const std::string&), FE::FORWARD_DATA::_AS_LVALUE_REF, std::string> l_copy_assignment;
	l_copy_assignment._arguments_buffer._first = "C++ is not Java.";
	l_copy_assignment._method = &std::string::operator=;
	l_copy_assignment.set_instance(&l_some_str);

	l_copy_assignment();

	EXPECT_TRUE(l_copy_assignment._task_result == "C++ is not Java.");
}

TEST(cpp_style_task, call_by_address)
{
	test_sample::s l_test_sample_instance;
	FE::cpp_style_task<test_sample::s, int32(int32*), FE::FORWARD_DATA::_AS_RVALUE_REF, int32*> l_fn;

	int32 l_input = 10;
	l_fn._arguments_buffer._first = &l_input;
	l_fn.set_instance(&l_test_sample_instance);
	l_fn._method = &test_sample::s::fn;

	l_fn();

	EXPECT_EQ(l_fn._task_result, 10);
}




namespace performance_benchmark
{
	void fn() noexcept
	{
		static FE::var::uint32 l_uint32 = 0;

		++l_uint32;
	}

	void FE_function(benchmark::State& state_p) noexcept
	{
		FE::function<void(void)> l_fn = fn;

		for (auto _ : state_p)
		{
			l_fn();
		}
	}
	BENCHMARK(FE_function);


	void FE_polymorphic_generic_task(benchmark::State& state_p) noexcept
	{
		FE::c_style_task<void(void)> l_task = fn;

		for (auto _ : state_p)
		{
			l_task();
		}
	}
	BENCHMARK(FE_polymorphic_generic_task);


	void std_function(benchmark::State& state_p) noexcept
	{
		std::function l_fn = fn;

		for (auto _ : state_p)
		{
			l_fn();
		}
	}
	BENCHMARK(std_function);
}