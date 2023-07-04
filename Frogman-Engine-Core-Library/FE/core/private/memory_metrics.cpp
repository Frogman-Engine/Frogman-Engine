// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "../memory_metrics.h"
#include "../heap_utilization.hpp"
#include "memory.hpp"


#if _WINDOWS_64BIT_OS_ == 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>
#undef WIN32_LEAN_AND_MEAN


#elif _LINUX_64BIT_OS_ == 1
#include <sys/types.h>
#include <sys/sysinfo.h>
#endif


FE::var::uint64 FE::request_app_memory_utilization(const HEAP_MEMORY_UTIL_INFO select_data_p) noexcept
{
#if _WINDOWS_64BIT_OS_ == 1
	MEMORYSTATUSEX l_memory_information;
	l_memory_information.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&l_memory_information);

	PROCESS_MEMORY_COUNTERS_EX l_process_memory_counters;

	switch (select_data_p)
	{
	case HEAP_MEMORY_UTIL_INFO::_TOTAL_VIRTUAL_MEMORY_SIZE:
		return l_memory_information.ullTotalPageFile;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_VIRTUAL_MEMORY_UTIL:
		return l_memory_information.ullTotalPageFile - l_memory_information.ullAvailPageFile;

	case HEAP_MEMORY_UTIL_INFO::_THIS_PROCESS_VIRTUAL_MEMORY_UTIL:
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&l_process_memory_counters, sizeof(l_process_memory_counters));
		return l_process_memory_counters.PrivateUsage;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_PHYSICAL_MEMORY_SIZE:
		return l_memory_information.ullTotalPhys;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_PHYSICAL_MEMORY_UTIL:
		return l_memory_information.ullTotalPhys - l_memory_information.ullAvailPhys;

	case HEAP_MEMORY_UTIL_INFO::_THIS_PROCESS_PHYSICAL_MEMORY_UTIL:
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&l_process_memory_counters, sizeof(l_process_memory_counters));
		return l_process_memory_counters.WorkingSetSize;

	default:
		return _INVALID_MEMORY_UTIL_QUERY_ENUM_;
	}


#elif _LINUX_64BIT_OS_ == 1
	struct sysinfo l_memory_information;
	sysinfo(&l_memory_information);

	switch (select_data_p)
	{
	case HEAP_MEMORY_UTIL_INFO::_TOTAL_VIRTUAL_MEMORY_SIZE:
		return l_memory_information.totalram;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_VIRTUAL_MEMORY_UTIL:
		return l_memory_information.totalram - l_memory_information.freeram;

	case HEAP_MEMORY_UTIL_INFO::_THIS_PROCESS_VIRTUAL_MEMORY_UTIL:
		return l_memory_information.totalram - l_memory_information.freeram;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_PHYSICAL_MEMORY_SIZE:
		return l_memory_information.totalram;

	case HEAP_MEMORY_UTIL_INFO::_TOTAL_PHYSICAL_MEMORY_UTIL:
		return l_memory_information.totalram - l_memory_information.freeram;

	case HEAP_MEMORY_UTIL_INFO::_THIS_PROCESS_PHYSICAL_MEMORY_UTIL:
		return l_memory_information.totalram - l_memory_information.freeram;

	default:
		return _INVALID_MEMORY_UTIL_QUERY_ENUM_;
	}
#endif
}

