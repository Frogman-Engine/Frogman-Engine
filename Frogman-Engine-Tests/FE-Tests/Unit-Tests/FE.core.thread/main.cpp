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

int main(int argc_p, char** argv_p)
{
    using namespace FE;

  	testing::InitGoogleTest(&argc_p, argv_p);

	if (argv_p == nullptr)
	{
		char l_arg0_default[] = "benchmark";
		char* l_args_default = l_arg0_default;
		argc_p = 1;
		argv_p = &l_args_default;
	}
	
    benchmark::Initialize(&argc_p, argv_p);
	FE_ABORT_IF(benchmark::ReportUnrecognizedArguments(argc_p, argv_p) == true, "Failed to meet the expectation: Unrecognized Benchmark Arguments Detected.");
    int32 l_exit_code = RUN_ALL_TESTS();
	std::cerr << "\n\n";
	benchmark::RunSpecifiedBenchmarks();
	std::cerr << "\n\n";
    benchmark::Shutdown();
    return l_exit_code;
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
	{
		FE::c_style_task<void(int32), FE::FORWARD_DATA::_AS_LVALUE_REF, var::int32> l_void_fn;
		l_void_fn._function = void_fn;

		var::int32 l_arg0 = 0;
		l_void_fn.set_arguments(&l_arg0, sizeof(var::int32));

		l_thread.fork(&l_void_fn);
		l_thread.join();
	}

	{
		FE::c_style_task<int32(int32), FE::FORWARD_DATA::_AS_LVALUE_REF, var::int32> l_int_fn;
		l_int_fn._function = int_fn;
		
		var::int32 l_arg0 = 0;
		l_int_fn.set_arguments(&l_arg0, sizeof(var::int32));

		l_thread.fork(&l_int_fn);
		l_thread.join();

		EXPECT_EQ( std::any_cast<int32>(l_int_fn.get_result()) , 0);
	}
}




TEST(function, call_by_value)
{
	FE::function<long double(long double)> l_abs = abs;
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
	FE::function<var::float64(float64*)> l_abs = test_sample::abs;
	var::float64 l_input = -5.0;
	float64 l_result = l_abs(&l_input);
	EXPECT_EQ(l_result, 5.0f);
}




TEST(method, call_by_value)
{
	FE::method<test_sample::s, int32(int32)> l_fn = &test_sample::s::fn;
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
	FE::method<test_sample::s, int32(int32*)> l_fn = &test_sample::s::fn;
	var::int32 l_input = 5;
	test_sample::s l_s;
	int32 l_result = l_fn(l_s, &l_input);
	EXPECT_EQ(l_result, l_input);
}




TEST(c_style_task, call_by_value)
{
	FE::c_style_task<long double(long double), FE::FORWARD_DATA::_AS_LVALUE_REF, long double> l_abs;
	l_abs._function = abs;

	long double l_arg0 = -9.0f;
	l_abs.set_arguments(&l_arg0, sizeof(long double));
	
	l_abs();

	EXPECT_EQ( std::any_cast<long double>(l_abs.get_result()) , 9.0);
}

TEST(c_style_task, call_by_lvalue_reference)
{
	FE::c_style_task<var::float64(float64&), FE::FORWARD_DATA::_AS_LVALUE_REF, var::float64> l_abs;
	l_abs._function = test_sample::abs;

	var::float64 l_arg0 = -9.0f;
	l_abs.set_arguments(&l_arg0, sizeof(float64&));

	l_abs();

	EXPECT_EQ( std::any_cast<var::float64>(l_abs.get_result()) , 9.0);
}

TEST(c_style_task, call_by_address)
{
	FE::c_style_task<var::float64(float64*), FE::FORWARD_DATA::_AS_LVALUE_REF, var::float64*> l_abs;
	l_abs._function = test_sample::abs;

	float64* l_p = new float64(-9.0f);
	l_abs.set_arguments(&l_p, sizeof(float64*));
	l_abs();
	delete l_p;

	EXPECT_EQ( std::any_cast<var::float64>(l_abs.get_result()) , 9.0);
}




TEST(cpp_style_task, call_by_value)
{
	FE::cpp_style_task<std::string, std::string&(const char*), FE::FORWARD_DATA::_AS_LVALUE_REF, const char*> l_assign;
	std::string l_some_str;

	l_assign._method = &std::string::assign;
	l_assign.set_instance(&l_some_str);

	const char* l_arg0 = "std::string";
	l_assign.set_arguments(&l_arg0, sizeof(const char*));

	l_assign();

	EXPECT_TRUE(std::any_cast<std::string>(l_assign.get_result()) == "std::string");
}

TEST(cpp_style_task, call_by_lvalue_reference)
{
	FE::cpp_style_task<std::string, std::string&(const std::string&), FE::FORWARD_DATA::_AS_LVALUE_REF, std::string> l_copy_assignment;
	std::string l_some_str;
	l_copy_assignment.set_instance(&l_some_str);
	l_copy_assignment._method = &std::string::operator=;

	std::string l_arg0 = "C++ is not Java.";
	l_copy_assignment.set_arguments(&l_arg0, sizeof(std::string));

	l_copy_assignment();

	EXPECT_TRUE(std::any_cast<std::string>(l_copy_assignment.get_result()) == "C++ is not Java.");
}

TEST(cpp_style_task, call_by_address)
{
	FE::cpp_style_task<test_sample::s, int32(int32*), FE::FORWARD_DATA::_AS_LVALUE_REF, int32*> l_fn;
	test_sample::s l_test_sample_instance;
	l_fn.set_instance(&l_test_sample_instance);
	l_fn._method = &test_sample::s::fn;

	int32* l_p = new int32(10);
	l_fn.set_arguments(&l_p, sizeof(int32*));
	l_fn();
	delete l_p;

	EXPECT_EQ(std::any_cast<int32>(l_fn.get_result()), 10);
}




namespace performance_benchmark
{
	void fn() noexcept
	{
		static var::uint64 l_uint = 0;

		++l_uint;
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