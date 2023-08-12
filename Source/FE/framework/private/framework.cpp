// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/framework/framework.hpp>
#include <FE/framework/reflection/function_table.hpp>
#include <FE/core/fstream_guard.hxx>
#include <boost/stacktrace.hpp>
#include <csignal>



BEGIN_NAMESPACE(FE::framework)

initialization_arguments application::s_options;

discard_t application::set_application(initialization_arguments initialization_arguments_p) noexcept
{
	ABORT_IF(initialization_arguments_p._application_ptr == nullptr, "ERROR: initialization_arguments_p._application_ptr cannot be nullptr");
	s_options._application_ptr = initialization_arguments_p._application_ptr;
	s_options._initial_function_table_size = initialization_arguments_p._initial_function_table_size;
	return true;
}

initialization_arguments application::get_application() noexcept
{
	return application::s_options;
}




void application::__launch_main(initialization_arguments& initialization_arguments_p) noexcept
{
	static ::FE::var::boolean l_s_is_initialized = false;
	ABORT_IF(l_s_is_initialized == true, "ERROR: The initialization cannot be done more than once");
	l_s_is_initialized = true;


	::std::signal(SIGTERM, __abnormal_shutdown_with_exit_code);
	::std::signal(SIGSEGV, __abnormal_shutdown_with_exit_code);
	::std::signal(SIGILL, __abnormal_shutdown_with_exit_code);
	::std::signal(SIGABRT, __abnormal_shutdown_with_exit_code);
	::std::signal(SIGFPE, __abnormal_shutdown_with_exit_code);

	//FE::function_table::tl_s_hash_map.reserve(initialization_arguments_p._initial_function_table_size);
}

void application::__shutdown_main() noexcept
{
}

_NORETURN_ void application::__abnormal_shutdown_with_exit_code(int32 signal_p) noexcept
{
	boost::stacktrace::stacktrace l_stack_frame_dumps;
	var::length_t l_stack_depth = 0;

	std::ofstream l_release_build_crash_report;
	{
		FE::ofstream_guard l_release_build_crash_report_guard(l_release_build_crash_report, "Crashed Thread Stack Frame Dump Report.txt");

		l_release_build_crash_report << "\n-------------------------------------------------- BEGIN STACK TRACE RECORD --------------------------------------------------\n\n";

		auto l_crend = l_stack_frame_dumps.crend();
		for (auto crbegin = l_stack_frame_dumps.crbegin(); crbegin != l_crend; ++crbegin)
		{
			l_release_build_crash_report << "#" << l_stack_depth << "\t";
			l_release_build_crash_report << boost::stacktrace::to_string(*crbegin).data();
			l_release_build_crash_report << "\n\n";
			++l_stack_depth;
		}

		l_release_build_crash_report << "-------------------------------------------------- END OF STACK TRACE RECORD --------------------------------------------------\n";

	}
	::std::exit(signal_p);
}


END_NAMESPACE




int main(int argc_p, char** argv_p) noexcept
{
	auto l_config_args = FE::framework::application::get_application();
	FE::framework::application::__launch_main(l_config_args);
	FE::framework::application::s_options._application_ptr->set_up();
	const int l_exit_code = FE::framework::application::s_options._application_ptr->run(argc_p, argv_p);
	FE::framework::application::s_options._application_ptr->clean_up();
	FE::framework::application::__shutdown_main();
	return l_exit_code;
}