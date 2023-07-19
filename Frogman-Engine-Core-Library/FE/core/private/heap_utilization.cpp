// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/heap_utilization.hpp>


std::atomic_size_t FE::heap_memory_tracker::s_global_total_bytes = 0;

thread_local FE::var::size_t FE::heap_memory_tracker::tl_s_thread_local_total_bytes = 0;
