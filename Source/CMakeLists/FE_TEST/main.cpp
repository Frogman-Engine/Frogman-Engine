// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <FE/core/prerequisite_symbols.h>
#include <FE/framework/framework.hpp>
#include <FE/core/function.hxx>
#include <FE/miscellaneous/undefine_max_min.h>

#include <FE/miscellaneous/define_max_min.h>
#include <FE/miscellaneous/private/macro_restrictions.h>


#define _ENABLE_PRE_TEST_ false


void fn() noexcept
{
	std::cout << "Jesus loves you";
}




//https://learn.microsoft.com/en-us/cpp/build/profile-guided-optimizations?view=msvc-170
// Profile Guided Optimization

class test final : public FE::framework::application
{
protected:
	virtual void set_up() noexcept override final
	{
		FE_LOG("int32 : ${%d@0}", &FE::buffer<FE::var::int32>::set_and_get(-5));
		FE_LOG("uint32 : ${%u@0}", &FE::buffer<FE::var::uint32>::set_and_get(5));

		FE_LOG("int64 : ${%ld@0}", &FE::buffer<FE::var::int64>::set_and_get(2147483648));
		FE_LOG("uint64 : ${%lu@0}", &FE::buffer<FE::var::uint64>::set_and_get(4294967296));

		FE_LOG("float32 : ${%f@0}", &FE::buffer<FE::var::float32>::set_and_get(3.14));
		FE_LOG("float64 : ${%lf@0}", &FE::buffer<FE::var::float64>::set_and_get(2023.1208));

		FE_LOG("boolean : ${%b@0}", &FE::buffer<FE::var::boolean>::set_and_get(true));
		FE_LOG("character : ${%c@0}", &FE::buffer<FE::var::character>::set_and_get('h'));

		FE_LOG("string : ${%s@0}", "C++ string");
		FE_LOG("pointer : ${%p@0}", nullptr);
	}
	
	virtual int run(int argc_p, char** argv_p) noexcept override final
	{

#if _ENABLE_PRE_TEST_ == true
		FE::void_function l_fn{&fn};
		const char* const l_fn_name_ptrc = "void fn() noexcept";
		FE::function_table::register_method(std::make_pair(l_fn_name_ptrc, &l_fn));
		FE::function_table::invoke(l_fn_name_ptrc); //Now, functions can be registered onto heap memory and called without function type restrictions.
		// It can also be useful when enqueuing a function as a task to a job system task scheduler.
		// It is one of the necessary components for Task-based parallel programming!
#endif

		::testing::InitGoogleTest(&argc_p, argv_p);
		return RUN_ALL_TESTS();
	}

	virtual void clean_up() noexcept override final
	{
	}
};




FE::framework::discard_t g_discard = FE::framework::application::set_application
(
	[]()
	{
		static test l_s_test_application;

		FE::framework::initialization_arguments l_configs;
		l_configs._initial_function_table_size = 1000;
		l_configs._application_ptr = &l_s_test_application;
		return l_configs;
	}()
);