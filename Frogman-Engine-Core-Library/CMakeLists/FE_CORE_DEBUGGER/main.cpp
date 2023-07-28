// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/private/launch.hpp>


#include <FE/miscellaneous/undefine_max_min.h>


#include <FE/miscellaneous/define_max_min.h>


#include <FE/core/function_table.hpp>


#include <FE/miscellaneous/private/macro_restrictions.h>


// __DATE__, __TIME__
#define _ENABLE_PRE_TEST_ false




static FE::internal::engine_main_initialization_arguments s_config_args = []()
{
	static FE::internal::real_time_exception_history_logging_strategy s_real_time_exception_history_logging_strategy;
	static FE::internal::exception_history_log_buffering_strategy s_exception_history_log_buffering_strategy;

	static FE::internal::real_time_logging_strategy s_real_time_logging_strategy;
	static FE::internal::log_buffering_strategy s_log_buffering_strategy;


	FE::internal::engine_main_initialization_arguments l_configs;

	l_configs._exception_initialization_arguments._exception_logging_strategy_ptr = &s_exception_history_log_buffering_strategy;
	l_configs._exception_initialization_arguments.s_log_buffer_size = FE::internal::exception::_DEFAULT_DEBUG_LOG_BUFFER_SIZE_;
	l_configs._exception_initialization_arguments.s_write_operation_triggering_point = FE::internal::exception_logger_initialization_arguments::percent_t{ 70 };

	l_configs._logger_initialization_arguments._logging_strategy_ptr = &s_log_buffering_strategy;
	l_configs._logger_initialization_arguments.s_log_buffer_size = FE::internal::exception::_DEFAULT_DEBUG_LOG_BUFFER_SIZE_;
	l_configs._logger_initialization_arguments.s_write_operation_triggering_point = FE::internal::exception_logger_initialization_arguments::percent_t{ 70 };

	l_configs._initial_function_table_size = 1000;

	return l_configs;
}();


void fn() noexcept
{
	std::cout << "Jesus loves you";
}


//https://learn.microsoft.com/en-us/cpp/build/profile-guided-optimizations?view=msvc-170
// Profile Guided Optimization
int main(int argc, char** argv)
{
	FE::internal::engine_main::initialize_engine(s_config_args);

	FE_LOG("Stryker ID: {%}, Health: {%}, Speed: {%}", 20211084, 100, 3.14f);

#if _ENABLE_PRE_TEST_ == true
	FE::void_function l_fn{&fn};
	const char* const l_fn_name_ptrc = "void fn() noexcept";
	FE::function_table::register_method(std::make_pair(l_fn_name_ptrc, &l_fn));
	FE::function_table::invoke(l_fn_name_ptrc); //Now, functions can be registered onto heap memory and called without function type restrictions.
	// It can also be useful when enqueuing a function as a task to a job system task scheduler.
	// It is one of the necessary components for Task-based parallel programming!
#endif

	::testing::InitGoogleTest(&argc, argv);
	int l_test_result = RUN_ALL_TESTS();

	FE::internal::engine_main::shutdown_engine();
	return l_test_result;
}