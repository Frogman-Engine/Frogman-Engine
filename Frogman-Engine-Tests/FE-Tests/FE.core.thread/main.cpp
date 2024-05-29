// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/thread.hpp>

#ifdef _LINUX_X86_64_
#include <sched.h>
#endif


/*
ls: lists all folders in the current working directory
ls filename: checks the presence of files with the specified name.
*/

class tls
{
public:
    tls()
    {
        std::cerr << "tls constructed\n";
    }

    ~tls()
    {
        std::cerr << "tls destructed\n";
    }
};

thread_local static tls tl_s_tls;

int main()
{
    using namespace FE;
    
    // This test sees if a host physical core of the logical thread can be changed over the app execution time.
    // It seems like Thread Local Storage lifetime is bound with the lifecycle of a logical thread on Ubuntu x86-64.
    // The result may vary on the operating system. 

    uint64 thread_id = std::thread::hardware_concurrency();
    FE_LOG("Total thread count: ${%lu@0}", &thread_id);

#ifdef _LINUX_X86_64_
    int64 physical_core_id = sched_getcpu();
    for(var::uint64 i = 0; i < 1000000000000000000; ++i)
    {
        int64 new_physical_core_id = sched_getcpu();
        FE_ASSERT(physical_core_id != new_physical_core_id, "Whiskey Tango Foxtrot?"); // It aborts the process if its host physical core gets chaged.
        (void)tl_s_tls;
    }
#endif

    return 0;
}