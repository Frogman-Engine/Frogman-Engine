﻿// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "launch.hpp"
#include "configuration_deserializer.hpp"
#include <csignal>


// read serialized configuration file. 
void ::FE::internal::engine_main::initialize_engine(engine_main_initialization_arguments engine_main_initialization_arguments_p) noexcept
{
	static ::FE::var::boolean l_s_is_API_initialized = false;
	ABORT_IF(l_s_is_API_initialized == true);
	l_s_is_API_initialized = true;

	ABORT_IF(engine_main_initialization_arguments_p._exception_handling_strategy_ptr == nullptr);
	::FE::exception::s_exception_handling_strategy_ptr = engine_main_initialization_arguments_p._exception_handling_strategy_ptr;
	::FE::exception::__construct_exception_on_main_thread();

	::std::signal(SIGTERM, abnormal_shutdown_with_exit_code);
	::std::signal(SIGSEGV, abnormal_shutdown_with_exit_code);
	::std::signal(SIGILL, abnormal_shutdown_with_exit_code);
	::std::signal(SIGABRT, abnormal_shutdown_with_exit_code);
	::std::signal(SIGFPE, abnormal_shutdown_with_exit_code);
}

void ::FE::internal::engine_main::shutdown_engine() noexcept
{
	::FE::exception::__destruct_exception_on_main_thread();
}

void ::FE::internal::engine_main::abnormal_shutdown_with_exit_code(int32 signal_p) noexcept
{
	::FE::exception::__destruct_exception();
	::std::exit(signal_p);
}