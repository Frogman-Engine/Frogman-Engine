// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <FE/core/prerequisites.h>
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
	virtual void set_up() override final
	{
	}
	
	virtual int run(int argc_p, char** argv_p) override final
	{
#if _ENABLE_PRE_TEST_ == true

#endif
		::testing::InitGoogleTest(&argc_p, argv_p);
		return RUN_ALL_TESTS();
	}

	virtual void clean_up() override final
	{
		let var::boolean l_has_to_restart = false;
		std::cout << "\nEnter 1 to re-run the tests: ";
		std::cin >> l_has_to_restart;
		if (l_has_to_restart == true)
		{
			FE::framework::application::s_restart_or_not = FE::framework::RESTART_OR_NOT::_HAS_TO_RESTART;
		}
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