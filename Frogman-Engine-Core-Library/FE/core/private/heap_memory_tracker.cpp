// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/heap_memory_tracker.hpp>


std::atomic_size_t FE::heap_memory_tracker_base::s_global_total_bytes = 0;

thread_local FE::var::size_t FE::heap_memory_tracker_base::tl_s_thread_local_total_bytes = 0;

FE::lazy_const<FE::var::size_t> FE::internal::heap_memory_tracker_initialization_argument::s_output_stream_buffer_size;
