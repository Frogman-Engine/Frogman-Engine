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
#define _ENABLE_PRE_TEST_ false


static ::FE::real_time_exception_history_logging_strategy s_real_time_exception_history_logging_strategy;
static ::FE::exception_history_log_buffering_strategy s_exception_history_log_buffering_strategy;
 
static ::FE::internal::engine_main_initialization_arguments s_config_args = ::FE::internal::engine_main_initialization_arguments
{
	FE::exception_initialization_arguments
	{
		&s_exception_history_log_buffering_strategy,
		FE::exception::_DEFAULT_DEBUG_LOG_BUFFER_SIZE_,
		50
	}
};


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
	FE_ASSERT(true, "hi");
	FE::internal::engine_main::shutdown_engine();
	return l_test_result;
}

