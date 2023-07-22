// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <FE/miscellaneous/configuration.h>

#include <FE/miscellaneous/undefine_max_min.h>

#include <FE/miscellaneous/define_max_min.h>

#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/heap_memory_tracker.hpp>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/function_table.hpp>
#include <FE/core/thread.hpp>

#include <FE/core/exception.hpp>
#include <FE/core/private/launch.hpp>
#include <FE/miscellaneous/private/macro_restrictions.h>
#define _ENABLE_PRE_TEST_ false




static FE::internal::engine_main_initialization_arguments s_config_args = []()
{
	static FE::real_time_exception_history_logging_strategy s_real_time_exception_history_logging_strategy;
	static FE::exception_history_log_buffering_strategy s_exception_history_log_buffering_strategy;


	FE::internal::engine_main_initialization_arguments l_configs;

	l_configs._exception_initialization_arguments._exception_logging_strategy_ptr = &s_exception_history_log_buffering_strategy;
	l_configs._exception_initialization_arguments.s_log_buffer_size = FE::exception::_DEFAULT_DEBUG_LOG_BUFFER_SIZE_;
	l_configs._exception_initialization_arguments.s_write_operation_triggering_point = FE::internal::exception_logger_initialization_arguments::percent_t{ 70 };
	l_configs._initial_function_table_size = 1000;
	l_configs._heap_memory_tracker_initialization_argument.s_output_stream_buffer_size = FE::exception::_DEFAULT_DEBUG_LOG_BUFFER_SIZE_;

	return l_configs;
}();


void fn() noexcept
{
	std::cout << "Jesus loves you";
}


int main(int argc, char** argv)
{
	FE::internal::engine_main::initialize_engine(s_config_args);

#if _ENABLE_PRE_TEST_ == true
	char l_buffer[1042];
	FE::clock l_clock;
	int l_frame_counter = 0;

	l_clock.start_clock();
	while (true)
	{
		UNALIGNED_MEMSET(l_buffer, 0, 1042);
		//memset(l_buffer, 0, 1042);
		l_clock.end_clock();
		++l_frame_counter;
		if (l_clock.get_delta_time() >= 1.0f)
		{
			l_clock.start_clock();
			std::cout << l_frame_counter << " fps\n";
			l_frame_counter = 0;
		}
	}
#endif

	::testing::InitGoogleTest(&argc, argv);
	int l_test_result = RUN_ALL_TESTS();

	FE::void_function l_fn{&fn};
	FE::function_table::register_method(std::make_pair("void fn() noexcept", &l_fn));
	FE::function_table::invoke("void fn() noexcept"); //Now, functions can be registered onto heap memory and called without function type restrictions.
	// It can also be useful when enqueuing a function as a task to a job system task scheduler.
	// It is one of the necessary components for Task-based parallel programming!

	FE::internal::engine_main::shutdown_engine();
	return l_test_result;
}

