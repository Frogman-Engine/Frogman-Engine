#include <gtest/gtest.h>
#include <FE/miscellaneous/configuration.h>


#include <FE/miscellaneous/undefine_max_min.h>

#include <FE/miscellaneous/define_max_min.h>


#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/heap_utilization.hpp>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/function.hxx>
#include <FE/core/thread.hpp>
#include <FE/core/hash.hxx>


#include <FE/core/exception.hpp>
#include <FE/core/private/launch.hpp>
#include <FE/miscellaneous/private/macro_restrictions.h>


#include <iostream>


#define _ENABLE_PRE_TEST_ true


static ::FE::real_time_exception_history_logging_strategy s_real_time_exception_history_logging_strategy;
static ::FE::internal::engine_main_initialization_arguments s_config_args = ::FE::internal::engine_main_initialization_arguments{&s_real_time_exception_history_logging_strategy};


int main(int argc, char** argv)
{
	FE::internal::engine_main::initialize_engine(s_config_args);

#if _ENABLE_PRE_TEST_ == true
#endif

	::testing::InitGoogleTest(&argc, argv);
	int l_test_result = RUN_ALL_TESTS();
	FE::internal::engine_main::shutdown_engine();
	return l_test_result;
}

