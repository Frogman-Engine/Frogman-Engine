// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <FE/core/prerequisites.h>
#include <FE/framework/framework.hpp>
#include <FE/core/function.hxx>
#include <FE/miscellaneous/undefine_max_min.h>

#include <FE/miscellaneous/define_max_min.h>
#include <FE/miscellaneous/private/macro_restrictions.h>
#include <boost/circular_buffer.hpp>

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