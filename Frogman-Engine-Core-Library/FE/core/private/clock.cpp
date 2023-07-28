// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include <FE/core/clock.hpp>
#include <FE/core/memory>  
#include <ctime>


const FE::clock::char_type* FE::clock::get_current_local_time() noexcept
{
    thread_local static FE::clock::char_type tl_s_local_time_string_buffer[_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_]{ (FE::clock::char_type)'\0' };

    auto l_current_time = ::std::chrono::system_clock::now();
    ::std::time_t l_current_time_t = ::std::chrono::system_clock::to_time_t(l_current_time);
    tm l_time;

#if _WINDOWS_64BIT_OS_
    localtime_s(&l_time, &l_current_time_t);
    ::std::strftime(tl_s_local_time_string_buffer, _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "%Y-%B-%d-%A  %p %Ih.%Mm.%Ss", &l_time);

#elif _LINUX_64BIT_OS_ == 1
    ::std::strftime(tl_s_local_time_string_buffer, _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "%Y-%B-%d-%A  %p %Ih.%Mm.%Ss", localtime_r(&l_current_time_t, &l_time));
#endif
    FE_EXIT(tl_s_local_time_string_buffer == nullptr, "ERROR: tl_s_local_time_string_buffer is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    return tl_s_local_time_string_buffer;
}
