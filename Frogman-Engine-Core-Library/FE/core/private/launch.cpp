// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "launch.hpp"
#include <boost/stacktrace/stacktrace.hpp>
#include <csignal>


// read serialized configuration file. 
void ::FE::internal::engine_main::initialize_engine(engine_main_initialization_arguments engine_main_initialization_arguments_p) noexcept
{
	static ::FE::var::boolean l_s_is_initialized = false;
	ABORT_IF(l_s_is_initialized == true, "ERROR: The initialization cannot be done more than once");
	l_s_is_initialized = true;

#if _IS_EXCEPTION_LOGGER_ENABLED_ == true
	ABORT_IF(engine_main_initialization_arguments_p._exception_handling_strategy_ptr == nullptr, "CRITICAL ERROR: engine_main_initialization_arguments_p._exception_handling_strategy_ptr cannot be nullptr");
	::FE::exception::s_logging_strategy_ptr = engine_main_initialization_arguments_p._exception_handling_strategy_ptr;
	::FE::exception::__construct_exception_on_main_thread();
#endif
	
	::std::signal(SIGTERM, abnormal_shutdown_with_exit_code);
	::std::signal(SIGSEGV, abnormal_shutdown_with_exit_code);
	::std::signal(SIGILL, abnormal_shutdown_with_exit_code);
	::std::signal(SIGABRT, abnormal_shutdown_with_exit_code);
	::std::signal(SIGFPE, abnormal_shutdown_with_exit_code);
}

void ::FE::internal::engine_main::shutdown_engine() noexcept
{
#if _IS_EXCEPTION_LOGGER_ENABLED_ == true
	::FE::exception::__destruct_exception_on_main_thread();
#endif
}

_NORETURN_ void ::FE::internal::engine_main::abnormal_shutdown_with_exit_code(int32 signal_p) noexcept
{
	boost::stacktrace::stacktrace l_stack_frame_dumps;
	var::length_t l_stack_depth = l_stack_frame_dumps.size();
	exception::tl_s_file_logger << "\n-------------------------------------------------- BEGIN STACK TRACE RECORD --------------------------------------------------\n\n";

	for (const auto& frame_cref : l_stack_frame_dumps)
	{
		exception::tl_s_file_logger << "#" << l_stack_depth << "\t";
		exception::tl_s_file_logger << boost::stacktrace::to_string(frame_cref).data();
		exception::tl_s_file_logger << "\n\n";
		--l_stack_depth;
	}

	exception::tl_s_file_logger << "-------------------------------------------------- END OF STACK TRACE RECORD --------------------------------------------------\n";
	
#if _IS_EXCEPTION_LOGGER_ENABLED_ == true
	::FE::exception::__destruct_exception();
	::std::exit(signal_p);
#else
	raise(signal_p);
#endif
}
