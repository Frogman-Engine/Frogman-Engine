#ifndef _FE_CORE_LAUNCH_HPP_
#define _FE_CORE_LAUNCH_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../clock.hpp"


int main(int argc, char** argv);


BEGIN_NAMESPACE(FE::internal)


constexpr auto _MAIN_THREAD_ID_ = -1;


struct engine_main_initialization_arguments
{
	FE::exception* _exception_handling_strategy_ptr;
};


class engine_main
{
	static void initialize_engine(engine_main_initialization_arguments engine_main_initialization_arguments_p) noexcept;

	static void shutdown_engine() noexcept;
	static void abnormal_shutdown_with_exit_code(int signal_p) noexcept;

	friend int ::main(int argc, char** argv);
};


END_NAMESPACE

#endif // 