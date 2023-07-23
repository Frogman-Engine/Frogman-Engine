#ifndef _FE_CORE_LAUNCH_HPP_
#define _FE_CORE_LAUNCH_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/heap_memory_tracker.hpp>


int main(int argc, char** argv);


BEGIN_NAMESPACE(FE::internal)


constexpr auto _MAIN_THREAD_ID_ = -1;


struct engine_main_initialization_arguments
{
	using initial_function_table_size_t = var::size_t;

	::FE::internal::exception_logger_initialization_arguments _exception_initialization_arguments;
	::FE::internal::logger_initialization_arguments _logger_initialization_arguments;
	initial_function_table_size_t _initial_function_table_size;
};


class engine_main
{
	static void initialize_engine(_MAYBE_UNUSED_ engine_main_initialization_arguments engine_main_initialization_arguments_p) noexcept;

	static void shutdown_engine() noexcept;
	_NORETURN_ static void abnormal_shutdown_with_exit_code(int32 signal_p) noexcept;

	friend int ::main(int argc, char** argv);
};


END_NAMESPACE

#endif // 