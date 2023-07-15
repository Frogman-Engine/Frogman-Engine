// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include <FE/core/exception.hpp>
#include <FE/core/algorithm/string.hxx>
#include <FE/core/fstring.hxx>
#include <FE/core/thread.hpp>
#include <FE/core/clock.hpp>
#include <cstdlib>
#include <csignal>
#include <cwchar>
#include <filesystem>


constexpr auto _FILE_NAME_MAX_LENGTH_ = 8192;
constexpr auto _MAX_THRED_ID_DIGIT_LENGTH_ = 24;
constexpr FE::length_t g_sec_string_length = 4;



FE::exception* FE::exception::s_logging_strategy_ptr = nullptr;

thread_local ::std::ofstream FE::exception::tl_s_file_logger;
thread_local ::FE::clock FE::exception::tl_s_clock;
thread_local ::std::string FE::exception::tl_s_full_debug_info_buffer;
::FE::var::size_t FE::exception::s_full_debug_info_buffer_size = 0;



bool FE::exception::log(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* const message_ptrc_p, const char* const file_name_ptrc_p, const char* const function_name_ptrc_p, const int line_p, const char* const exit_code_enum_ptrc_p, const int exit_code_p) noexcept
{
    return exception::s_logging_strategy_ptr->__logging_strategy(expression_p, expression_string_ptrc_p, runtime_exception_mode_p, message_ptrc_p, file_name_ptrc_p, function_name_ptrc_p, line_p, exit_code_enum_ptrc_p, exit_code_p);
}

void FE::exception::__construct_exception_on_main_thread() noexcept
{
    exception::s_logging_strategy_ptr->__main_thread_exception_construction_strategy();
}

void  FE::exception::__destruct_exception_on_main_thread() noexcept
{
    exception::s_logging_strategy_ptr->__main_thread_exception_destruction_strategy();
}

void FE::exception::__construct_exception() noexcept
{
    exception::s_logging_strategy_ptr->__exception_construction_strategy();
}

void FE::exception::__destruct_exception() noexcept
{
    exception::s_logging_strategy_ptr->__exception_destruction_strategy();
}


bool FE::real_time_exception_history_logging_strategy::__logging_strategy(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p, int32 exit_code_p) noexcept
{
    switch (expression_p)
    {
    case true:
        break;

    case false:
        return expression_p;

    default:
        break;
    }
    
    
    FE::exception::buffer_type l_source_code_line_info_buffer[_LINE_INFO_BUFFER_SIZE_] = "\0";


    ::snprintf(l_source_code_line_info_buffer, _LINE_INFO_BUFFER_SIZE_, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(),
            _DEFAULT_DEBUG_LOG_BUFFER_SIZE_,
            {
                "Time: ", exception::tl_s_clock.get_current_local_time(), "\n",
                "Error Message - ", message_ptrc_p, "\n",
                "Expected the expression \"", expression_string_ptrc_p, "\" to be false", "\n",
                "File Directory: ", file_name_ptrc_p, "\n",
                "Function Name: ", function_name_ptrc_p, "\n",
                "Code Line Number: ", l_source_code_line_info_buffer
            }
    );


    switch (runtime_exception_mode_p)
    {
    case _LOG_EXCEPTION_HISTORY_: // store exception logs in a global container and write  exception history file right before the unsafe_end of the application.  
        real_time_exception_history_logging_strategy::tl_s_file_logger << real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data() << "\n\n";

        ::FE::memset_s(l_source_code_line_info_buffer, _NULL_, _LINE_INFO_BUFFER_SIZE_, sizeof(exception::buffer_type));
        ::FE::memset_s(real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(), _NULL_, _DEFAULT_DEBUG_LOG_BUFFER_SIZE_, sizeof(exception::buffer_type));
        break;


    case _ABORT_IMMEDIATELY_:
        FE::algorithm::string::string_concatenation<var::character>(real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(), _DEFAULT_DEBUG_LOG_BUFFER_SIZE_, "\nabort() HAS BEEN CALLED.", ::FE::algorithm::string::string_length("\tabort() HAS BEEN CALLED."));

        real_time_exception_history_logging_strategy::tl_s_file_logger << real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data() << "\n\n";

        ::FE::memset_s(l_source_code_line_info_buffer, _NULL_, _LINE_INFO_BUFFER_SIZE_, sizeof(exception::buffer_type));
        ::FE::memset_s(real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(), _NULL_, _DEFAULT_DEBUG_LOG_BUFFER_SIZE_, sizeof(exception::buffer_type));

        ::abort(); // aborts the entire processes of the application.


    case _EXIT_WITH_CODE_:
        // store exit code
        ::snprintf(l_source_code_line_info_buffer, _LINE_INFO_BUFFER_SIZE_, "%d", exit_code_p);

        ::FE::algorithm::string::concatenate_strings<var::character>
            (
                real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(),
                _DEFAULT_DEBUG_LOG_BUFFER_SIZE_,
                {
                    "\nexit() HAS BEEN CALLED with exit code: ", l_source_code_line_info_buffer, "\n"
                    "Exit Code Enum: ", exit_code_enum_ptrc_p
                }
        );

        real_time_exception_history_logging_strategy::tl_s_file_logger << real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data() << "\n\n";

        ::FE::memset_s(l_source_code_line_info_buffer, _NULL_, _LINE_INFO_BUFFER_SIZE_, sizeof(exception::buffer_type));
        ::FE::memset_s(real_time_exception_history_logging_strategy::tl_s_full_debug_info_buffer.data(), _NULL_, _DEFAULT_DEBUG_LOG_BUFFER_SIZE_, sizeof(exception::buffer_type));

        ::std::raise(exit_code_p);
    }

    return true;
}

void FE::real_time_exception_history_logging_strategy::__main_thread_exception_construction_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\0");
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }

    tl_s_full_debug_info_buffer.reserve(s_full_debug_info_buffer_size);
    FE::memset_s(tl_s_full_debug_info_buffer.data(), _NULL_, s_full_debug_info_buffer_size, sizeof(FE::exception::buffer_type));

#if _WINDOWS_64BIT_OS_ == 1
    var::wchar l_date_info_wstring[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = L"\0";
    ::std::mbstowcs(l_date_info_wstring, exception::tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
    std::memset(l_date_info_wstring + (::std::wcslen(l_date_info_wstring) - g_sec_string_length), _NULL_, g_sec_string_length * sizeof(var::wchar)); // to remove seconds

    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_wstring;
    ABORT_IF(::std::wcslen(l_path_to_log_dump_file.c_str()) >= _FILE_NAME_MAX_LENGTH_ - clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "ERROR: file name buffer overflowed.");

    var::wchar l_full_path_to_the_file[_FILE_NAME_MAX_LENGTH_] = L"\0";
    ::std::wcscpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::wchar>
        (
            l_full_path_to_the_file,
            _FILE_NAME_MAX_LENGTH_,
            {
                L"\\thread main() @ ",
                l_date_info_wstring,
                L".txt"
            }
    );

#elif _LINUX_64BIT_OS_ == 1
    var::character l_date_info_string[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = "\0";
    std::memset(l_date_info_string + (::std::strlen(l_date_info_string) - g_sec_string_length), _NULL_, g_sec_string_length * sizeof(var::character)); // to remove min sec
    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_string;

    ABORT_IF(::std::strlen(l_path_to_log_dump_file.c_str()) >= _FILE_NAME_MAX_LENGTH_ - clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "ERROR: file name buffer overflowed.");

    var::character l_full_path_to_the_file[_FILE_NAME_MAX_LENGTH_] = "\0";
    ::std::strcpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            l_full_path_to_the_file,
            _FILE_NAME_MAX_LENGTH_,
            {
                "\\thread main() @ ",
                l_date_info_string,
                ".txt"
            }
    );


#endif

    if (::std::filesystem::exists(l_path_to_log_dump_file) == false)
    {
        ::std::filesystem::create_directory(l_path_to_log_dump_file);
    }

    tl_s_file_logger.open(l_full_path_to_the_file);
    tl_s_file_logger << "[BEGIN RECORD]\n{\n";
}

void FE::real_time_exception_history_logging_strategy::__main_thread_exception_destruction_strategy() noexcept
{
    if (real_time_exception_history_logging_strategy::tl_s_file_logger.is_open() == true)
    {
        real_time_exception_history_logging_strategy::tl_s_file_logger << "\n}\n[END OF HISTORY]";
        real_time_exception_history_logging_strategy::tl_s_file_logger << "\n\nThe leaked heap memory byte(s) by the main thread" << " is " << heap_utilization<void>::query_all_data()._thread_local_total_bytes << " byte(s)\n";
        real_time_exception_history_logging_strategy::tl_s_file_logger << "The total leaked byte(s) on the heap is " << heap_utilization<void>::query_all_data()._global_total_bytes << " byte(s)";
        real_time_exception_history_logging_strategy::tl_s_file_logger.close();
    }
}

void FE::real_time_exception_history_logging_strategy::__exception_construction_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\0");
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }

    tl_s_full_debug_info_buffer.reserve(s_full_debug_info_buffer_size);
    FE::memset_s(tl_s_full_debug_info_buffer.data(), _NULL_, s_full_debug_info_buffer_size, sizeof(FE::exception::buffer_type));

#if _WINDOWS_64BIT_OS_ == 1
    var::wchar l_thread_id[_MAX_THRED_ID_DIGIT_LENGTH_] = L"\0";
    ::swprintf(l_thread_id, _MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", ::FE::thread::tl_s_this_thread_id); // hashed thread-ids from std::hash are too long and hard to read 

    var::wchar l_date_info_wstring[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = L"\0";
    ::std::mbstowcs(l_date_info_wstring, exception::tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
    std::memset(l_date_info_wstring + (::std::wcslen(l_date_info_wstring) - g_sec_string_length), _NULL_, g_sec_string_length * sizeof(var::wchar)); // to remove seconds

    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_wstring;

    var::wchar l_full_path_to_the_file[_FILE_NAME_MAX_LENGTH_] = L"\0";
    ::std::wcscpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::wchar>
        (
            l_full_path_to_the_file,
            _FILE_NAME_MAX_LENGTH_,
            {
                L"\\thread ",
                l_thread_id,
                L" @ ",
                l_date_info_wstring,
                L".txt"
            }
    );

#elif _LINUX_64BIT_OS_ == 1
    var::character l_thread_id[_MAX_THRED_ID_DIGIT_LENGTH_] = "\0";
    snprintf(l_thread_id, _MAX_THRED_ID_DIGIT_LENGTH_, "%llu", ::FE::thread::tl_s_this_thread_id);

    var::character l_date_info_string[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = "\0";
    std::memset(l_date_info_string + (::std::strlen(l_date_info_string) - g_sec_string_length), _NULL_, g_sec_string_length * sizeof(var::character)); // to remove min sec
    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_string;

    var::character l_full_path_to_the_file[_FILE_NAME_MAX_LENGTH_] = "\0";
    strcpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            l_full_path_to_the_file,
            _FILE_NAME_MAX_LENGTH_,
            {
                "\\thread ",
                l_thread_id,
                " @ ",
                l_date_info_string,
                ".txt"
            }
    );

#endif

    if (::std::filesystem::exists(l_path_to_log_dump_file) == false)
    {
        ::std::filesystem::create_directory(l_path_to_log_dump_file);
    }

    real_time_exception_history_logging_strategy::tl_s_file_logger.open(l_full_path_to_the_file);
    real_time_exception_history_logging_strategy::tl_s_file_logger << "[BEGIN RECORD]\n{\n";
}

void FE::real_time_exception_history_logging_strategy::__exception_destruction_strategy() noexcept
{
    if (real_time_exception_history_logging_strategy::tl_s_file_logger.is_open() == true)
    {
        real_time_exception_history_logging_strategy::tl_s_file_logger << "\n}\n[END OF HISTORY]";

        real_time_exception_history_logging_strategy::tl_s_file_logger << "\n\nThe leaked heap memory byte(s) by the thread " << ::FE::thread::tl_s_this_thread_id << " is " << heap_utilization<void>::query_all_data()._thread_local_total_bytes << " byte(s)";

        real_time_exception_history_logging_strategy::tl_s_file_logger.close();
    }
}


bool FE::exception_history_log_buffering_strategy::__logging_strategy(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p, int32 exit_code_p) noexcept
{
    return false;
}

void FE::exception_history_log_buffering_strategy::__main_thread_exception_construction_strategy() noexcept
{
}

void FE::exception_history_log_buffering_strategy::__main_thread_exception_destruction_strategy() noexcept
{
}

void FE::exception_history_log_buffering_strategy::__exception_construction_strategy() noexcept
{
}

void FE::exception_history_log_buffering_strategy::__exception_destruction_strategy() noexcept
{
}