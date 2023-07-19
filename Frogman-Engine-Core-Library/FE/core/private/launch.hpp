#ifndef _FE_CORE_LAUNCH_HPP_
#define _FE_CORE_LAUNCH_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/clock.hpp>


int main(int argc, char** argv);


BEGIN_NAMESPACE(FE::internal)


constexpr auto _MAIN_THREAD_ID_ = -1;


struct engine_main_initialization_arguments
{
	exception_initialization_arguments _exception_initialization_arguments;
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