﻿/*
Copyright © from 2022 to present, UNKNOWN STRYKER. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <FE/framework/framework.hpp>
#include <FE/framework/reflection/private/load_reflection_data.h>

#include <FE/algorithm/string.hxx>
#include <FE/algorithm/utility.hxx>
#include <FE/clock.hpp>
#include <FE/do_once.hxx>
#include <FE/fstream_guard.hxx>
#include <FE/log/logger.hpp>

// boost
#include <boost/stacktrace.hpp>

// std
#include <csignal>
#include <optional>
#include <filesystem>
#include <string>

#ifdef _FE_ON_WINDOWS_X86_64_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif




BEGIN_NAMESPACE(FE::framework)


program_options::program_options(FE::int32 argc_p, FE::ASCII** argv_p) noexcept : m_max_concurrency{ "-max-concurrency=", 4 }
{
	for (var::int32 i = 0; i < argc_p; ++i)
	{
		if (algorithm::string::find_the_first<var::ASCII>(argv_p[i], this->m_max_concurrency._first) == std::nullopt)
		{
			continue;
		}

		std::optional<algorithm::string::range> l_range = algorithm::string::find_the_first<var::ASCII>(this->m_max_concurrency._first, '=');
		l_range->_begin = 0;

		if (algorithm::string::compare_ranged<var::ASCII>(argv_p[i], *l_range, this->m_max_concurrency._first, *l_range) == true)
		{
			algorithm::utility::uint_info l_uint_info = algorithm::utility::string_to_uint<var::ASCII>(argv_p[i] + l_range->_end);
			this->m_max_concurrency._second = static_cast<FE::uint32>(l_uint_info._value);

			if (l_uint_info._value < 4)
			{
				FE_LOG("Warning, the option '${%s@0}${%u@1}' has no effect. The number of thread must be greater than 4.\nThe value given to the option will be overriden with the default value '4'.", this->m_max_concurrency._first, &l_uint_info._value);
				this->m_max_concurrency._second = 4;
			}
			else if (l_uint_info._value > 254)
			{
				FE_LOG("Warning, the option '${%s@0}${%u@1}' has no effect. The number of thread must be less than 255.\nThe value given to the option will be overriden with the default value '4'.", this->m_max_concurrency._first, &l_uint_info._value);
				this->m_max_concurrency._second = 4;
			}
			break;
		}
	}

#ifdef _FE_ON_WINDOWS_X86_64_
	SYSTEM_INFO l_system_info;
	GetSystemInfo(&l_system_info);
	
	FE_EXIT(l_system_info.dwNumberOfProcessors < 4, FE::ErrorCode::_FatalHardwareResourceError_CPU_HasNotEnoughThreads, "Error, a stone age CPU detected: a CPU with less than four threads is not supported.");
	if (this->m_max_concurrency._second > l_system_info.dwNumberOfProcessors)
	{
		FE_LOG("Warning, the option '${%s@0}${%u@1}' has no effect. The number of thread must be less than or equal to the number of logical processors.\nThe value given to the option will be overriden with ${%u@2}.", this->m_max_concurrency._first, &this->m_max_concurrency._second, &l_system_info.dwNumberOfProcessors);
		this->m_max_concurrency._second = static_cast<FE::uint32>(l_system_info.dwNumberOfProcessors);
	}
#endif
}

FE::uint32 program_options::get_max_concurrency() const noexcept
{
	return this->m_max_concurrency._second;
}

FE::ASCII* program_options::view_max_concurrency_option_title() const noexcept
{
	return this->m_max_concurrency._first;
}




framework_base* framework_base::s_framework = nullptr;
RestartOrNot framework_base::s_restart_or_not = RestartOrNot::_NoOperation;


framework_base::framework_base(FE::int32 argc_p, FE::ASCII** argv_p) noexcept
	: m_program_options(argc_p, argv_p), 
	  m_current_system_locale(std::setlocale(LC_ALL, "")), 
	  m_memory(std::make_unique<FE::memory_resource[]>(m_program_options.get_max_concurrency())), 
	  m_method_reflection(81920), m_property_reflection(81920)
{
	std::locale::global(this->m_current_system_locale);
}

framework_base::~framework_base() noexcept
{
	this->m_memory.reset();
}


FE::int32 framework_base::launch(_FE_MAYBE_UNUSED_ FE::int32 argc_p, _FE_MAYBE_UNUSED_ FE::ASCII** argv_p)
{
	return 0;
}

FE::int32 framework_base::run()
{
	return 0;
}

FE::int32 framework_base::shutdown()
{
	return 0;
}

void framework_base::__load_reflection_data() noexcept
{
	load_reflection_data();
}


void framework_base::request_restart() noexcept
{
	s_restart_or_not = RestartOrNot::_HasToRestart;
}

framework_base& framework_base::get_framework() noexcept
{
	return *s_framework;
}


std::pmr::memory_resource* framework_base::get_memory_resource() noexcept
{
	return &(this->m_memory[ get_current_thread_id() ]);
}

reflection::method_map& framework_base::get_method_reflection() noexcept
{
	return this->m_method_reflection;
}

reflection::property_map& framework_base::get_property_reflection() noexcept
{
	return this->m_property_reflection;
}


_FE_NORETURN_ void framework_base::__abnormal_shutdown_with_exit_code(int signal_p)
{
#ifdef _RELWITHDEBINFO_
	boost::stacktrace::stacktrace l_stack_trace_dumps;

	std::ofstream l_release_build_crash_report;
	{
		std::string l_dump_filename = "Crashed Thread Stack Trace Report from ";
		l_dump_filename += FE::clock::get_current_local_time();
		l_dump_filename += ".aar";
		FE::ofstream_guard l_release_build_crash_report_guard(l_release_build_crash_report);
		l_release_build_crash_report_guard.get_stream().open(l_dump_filename.c_str());
		l_release_build_crash_report << "Compilation Date: " << " " << __DATE__ << " - " << __TIME__ << "\n\n";
		l_release_build_crash_report << "\n-------------------------------------------------- BEGIN STACK TRACE RECORD --------------------------------------------------\n\n";

		l_release_build_crash_report << boost::stacktrace::to_string(l_stack_trace_dumps).data() << '\n';

		l_release_build_crash_report << "\n-------------------------------------------------- END OF STACK TRACE RECORD --------------------------------------------------\n";

	}
#endif
	//FE_DO_ONCE(_DO_ONCE_PER_APP_EXECUTION_, FE::framework::framework_base::s_framework->shutdown(); FE::framework::framework_base::s_framework->__shutdown_main());
	std::exit(signal_p);
}

std::function<framework_base* (FE::int32, FE::ASCII**)>& framework_base::allocate_framework(std::function<framework_base* (FE::int32, FE::ASCII**)> script_p) noexcept
{
	static std::function<framework_base* (FE::int32, FE::ASCII**)> l_s_script = script_p;
	return l_s_script;
}


END_NAMESPACE




int main(FE::int32 argc_p, FE::ASCII** argv_p)
{
	var::int32 l_exit_code;

	std::signal(SIGTERM, FE::framework::framework_base::__abnormal_shutdown_with_exit_code);
	std::signal(SIGSEGV, FE::framework::framework_base::__abnormal_shutdown_with_exit_code);
	std::signal(SIGILL, FE::framework::framework_base::__abnormal_shutdown_with_exit_code);
	std::signal(SIGABRT, FE::framework::framework_base::__abnormal_shutdown_with_exit_code);
	std::signal(SIGFPE, FE::framework::framework_base::__abnormal_shutdown_with_exit_code);
	std::set_terminate([]() { FE::framework::framework_base::__abnormal_shutdown_with_exit_code(SIGTERM); });

	do
	{
		FE::framework::framework_base::s_restart_or_not = FE::framework::RestartOrNot::_NoOperation;

		FE::framework::framework_base::s_framework = FE::framework::framework_base::allocate_framework()(argc_p, argv_p);
		FE_EXIT(FE::framework::framework_base::s_framework == nullptr, FE::ErrorCode::_FatalMemoryError_1XX_NullPtr, "\nAn error from FE.Framework: An app pointer is a nullptr.\n");
		
		l_exit_code = FE::framework::framework_base::s_framework->launch(argc_p, argv_p);

		if (l_exit_code != 0)
		{
			std::cerr << "\nAn error from FE.Framework: failed to set up an app.\n";
			delete FE::framework::framework_base::s_framework;
			return l_exit_code;
		}

		l_exit_code = FE::framework::framework_base::s_framework->run();

		if (l_exit_code != 0)
		{
			std::cerr << "\nAn error from FE.Framework: there was an error during the runtime.\n";
			delete FE::framework::framework_base::s_framework;
			return l_exit_code;
		}

		l_exit_code = FE::framework::framework_base::s_framework->shutdown();

		if (l_exit_code != 0)
		{
			std::cerr << "\nAn error from FE.Framework: unsuccessfully cleaned up an app.\n";
			delete FE::framework::framework_base::s_framework;
			return l_exit_code;
		}

		delete FE::framework::framework_base::s_framework;
	}
	while (FE::framework::framework_base::s_restart_or_not == FE::framework::RestartOrNot::_HasToRestart);

	return l_exit_code;
}

