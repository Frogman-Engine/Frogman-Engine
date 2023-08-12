#ifndef _FE_LOG_HPP_
#define _FE_LOG_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.h>
#include <FE/core/debug.h>
#include <fstream>
#include <string>


#if defined(_ENABLE_LOG_)
#define _IS_LOGGER_ENABLED_
#define IF_LOGGER_ENABLED(true_p, false_p) true_p
#define ENABLE_IF_LOGGER_ENABLED(code_p) code_p
#else
#define IF_LOGGER_ENABLED(true_p, false_p) false_p
#define ENABLE_IF_LOGGER_ENABLED(code_p)
#endif

#define _BUFFER_FLUSH_TRIGGERING_POINT_BY_PERCENT 80


CLASS_FORWARD_DECLARATION(FE, clock);




BEGIN_NAMESPACE(FE::log)


class logger
{
public:
    using buffer_type = char;
    _MAYBE_UNUSED_ static constexpr uint16 line_info_buffer_size = 32;
    _MAYBE_UNUSED_ static constexpr uint16 default_debug_log_buffer_size = 1024;

private:
    struct initializer
    {
        initializer(character* const logfile_folder_name_ptrc_p,
#ifdef _WINDOWS_64BIT_OS_
            wchar* const logfile_inner_folder_name_ptrc_p
#elif defined(_LINUX_64BIT_OS_)
            character* const logfile_inner_folder_name_ptrc_p
#endif
            ) noexcept;
        ~initializer() noexcept;
    };

public:
    constexpr logger() noexcept {}
    _CONSTEXPR20_ virtual ~logger() noexcept {}

protected:
    thread_local static ::std::ofstream tl_s_file_logger;
    thread_local static ::std::string tl_s_log_buffer;

public:
    static void log(character* const logfile_folder_name_ptrc_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept;
};


END_NAMESPACE
#endif
