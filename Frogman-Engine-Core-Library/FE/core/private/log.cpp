#include <FE/core/log.hpp>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include <FE/core/algorithm/string.hxx>
#include <FE/core/clock.hpp>
#include <FE/miscellaneous/misc.h>
#include <FE/core/thread.hpp>
#include <cstdlib>
#include <csignal>
#include <cwchar>
#include <filesystem>


#pragma warning(disable: 4996)




BEGIN_NAMESPACE(FE)




FE::logger* FE::logger::s_logging_strategy_ptr = nullptr;

thread_local ::std::ofstream FE::logger::tl_s_file_logger;
thread_local ::FE::clock FE::logger::tl_s_clock;
thread_local ::std::string FE::logger::tl_s_log_buffer;
::FE::lazy_const<FE::var::size_t> FE::internal::logger_initialization_arguments::s_log_buffer_size;
::FE::lazy_const<FE::var::uint8> FE::internal::logger_initialization_arguments::s_write_operation_triggering_point;




FE::logger::initializer::initializer() noexcept
{
    logger::s_logging_strategy_ptr->__log_initialization_strategy();
}

FE::logger::initializer::~initializer() noexcept
{
    logger::s_logging_strategy_ptr->__log_deinitialization_strategy();
}




void logger::log(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept
{
    ENABLE_IF_LOGGER_ENABLED(thread_local static logger::initializer tl_s_initializer);
    return logger::s_logging_strategy_ptr->__logging_strategy(message_ptrc_p, file_name_ptrc_p, function_name_ptrc_p, line_p);
}




void FE::real_time_logging_strategy::__logging_strategy(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept
{
    buffer_type l_source_code_line_info_buffer[_LINE_INFO_BUFFER_SIZE_] = "\0";


    ::snprintf(l_source_code_line_info_buffer, _LINE_INFO_BUFFER_SIZE_, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            tl_s_log_buffer.data(),
            _DEFAULT_DEBUG_LOG_BUFFER_SIZE_,
            {
                "Time: ", logger::tl_s_clock.get_current_local_time(), "\n",
                "Message - ", message_ptrc_p, "\n",
                "File Directory: ", file_name_ptrc_p, "\n",
                "Function Name: ", function_name_ptrc_p, "\n",
                "Code Line Number: ", l_source_code_line_info_buffer
            }
    );


    tl_s_file_logger << tl_s_log_buffer.data() << "\n\n";

    memset(l_source_code_line_info_buffer, _NULL_, _LINE_INFO_BUFFER_SIZE_ * sizeof(buffer_type));
    memset(tl_s_log_buffer.data(), _NULL_, _DEFAULT_DEBUG_LOG_BUFFER_SIZE_ * sizeof(buffer_type));
}

void FE::real_time_logging_strategy::__log_initialization_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / "Frogman-Engine-Logs\0");
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }

    tl_s_log_buffer.reserve(internal::logger_initialization_arguments::s_log_buffer_size.load());
    std::memset(tl_s_log_buffer.data(), _NULL_, internal::logger_initialization_arguments::s_log_buffer_size.load() * sizeof(buffer_type));

#ifdef _WINDOWS_64BIT_OS_
    var::wchar l_thread_id[thread::_MAX_THRED_ID_DIGIT_LENGTH_] = L"\0";
    ::swprintf(l_thread_id, thread::_MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", ::FE::thread::tl_s_this_thread_id); // hashed thread-ids from std::hash are too long and hard to read 

    var::wchar l_date_info_wstring[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = L"\0";
    ::std::mbstowcs(l_date_info_wstring, tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
    std::memset(l_date_info_wstring + (::std::wcslen(l_date_info_wstring) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(var::wchar)); // to remove seconds

    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_wstring;

    var::wchar l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = L"\0";
    ::std::wcscpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::wchar>
        (
            l_full_path_to_the_file,
            _FULL_PATH_TO_FILE_MAX_LENGTH_,
            {
                L"\\thread ",
                l_thread_id,
                L" @ ",
                l_date_info_wstring,
                L".txt"
            }
    );

#elif defined(_LINUX_64BIT_OS_)
    var::character l_thread_id[_MAX_THRED_ID_DIGIT_LENGTH_] = "\0";
    snprintf(l_thread_id, _MAX_THRED_ID_DIGIT_LENGTH_, "%llu", ::FE::thread::tl_s_this_thread_id);

    var::character l_date_info_string[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = "\0";
    ::std::strcpy(l_date_info_string, tl_s_clock.get_current_local_time());
    std::memset(l_date_info_string + (::std::strlen(l_date_info_string) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(var::character)); // to remove min sec
    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_string;

    var::character l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = "\0";
    strcpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            l_full_path_to_the_file,
            _FULL_PATH_TO_FILE_MAX_LENGTH_,
            {
                "/thread ",
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

    tl_s_file_logger.open(l_full_path_to_the_file);
    tl_s_file_logger << "\n-------------------------------------------------- BEGIN LOG --------------------------------------------------\n\n";
}

void FE::real_time_logging_strategy::__log_deinitialization_strategy() noexcept
{
    if (tl_s_file_logger.is_open() == true)
    {
        tl_s_file_logger << "-------------------------------------------------- END OF LOG --------------------------------------------------\n";

        tl_s_file_logger.close();
    }
}




void FE::log_buffering_strategy::__logging_strategy(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept
{
    buffer_type l_source_code_line_info_buffer[_LINE_INFO_BUFFER_SIZE_] = "\0";


    ::snprintf(l_source_code_line_info_buffer, _LINE_INFO_BUFFER_SIZE_, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            tl_s_log_buffer.data(),
            _DEFAULT_DEBUG_LOG_BUFFER_SIZE_,
            {
                "Time: ", tl_s_clock.get_current_local_time(), "\n",
                "Message - ", message_ptrc_p, "\n",
                "File Directory: ", file_name_ptrc_p, "\n",
                "Function Name: ", function_name_ptrc_p, "\n",
                "Code Line Number: ", l_source_code_line_info_buffer, "\n\n"
            }
    );


    tl_s_log_buffer = tl_s_log_buffer.data();
    length_t l_log_buffer_length = tl_s_log_buffer.length();

    size_t l_divisor = (tl_s_log_buffer.capacity() / internal::logger_initialization_arguments::s_write_operation_triggering_point.load());

    ABORT_IF(l_log_buffer_length == 0, "l_log_buffer_length cannot be zero");
    ABORT_IF(l_divisor == 0, "l_divisor cannot be zero");

    if (l_log_buffer_length >= (l_log_buffer_length / l_divisor))
    {
        tl_s_file_logger << tl_s_log_buffer.data() << "\n\n";

        memset(l_source_code_line_info_buffer, _NULL_, _LINE_INFO_BUFFER_SIZE_ * sizeof(buffer_type));
        memset(tl_s_log_buffer.data(), _NULL_, _DEFAULT_DEBUG_LOG_BUFFER_SIZE_ * sizeof(buffer_type));
    }
}

void FE::log_buffering_strategy::__log_initialization_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / "Frogman-Engine-Logs\0");
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }

    tl_s_log_buffer.reserve(internal::logger_initialization_arguments::s_log_buffer_size.load());
    std::memset(tl_s_log_buffer.data(), _NULL_, internal::logger_initialization_arguments::s_log_buffer_size.load() * sizeof(buffer_type));

#ifdef _WINDOWS_64BIT_OS_
    var::wchar l_thread_id[thread::_MAX_THRED_ID_DIGIT_LENGTH_] = L"\0";
    ::swprintf(l_thread_id, thread::_MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", ::FE::thread::tl_s_this_thread_id); // hashed thread-ids from std::hash are too long and hard to read 

    var::wchar l_date_info_wstring[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = L"\0";
    ::std::mbstowcs(l_date_info_wstring, tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);
    std::memset(l_date_info_wstring + (::std::wcslen(l_date_info_wstring) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(var::wchar)); // to remove seconds

    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_wstring;

    var::wchar l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = L"\0";
    ::std::wcscpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::wchar>
        (
            l_full_path_to_the_file,
            _FULL_PATH_TO_FILE_MAX_LENGTH_,
            {
                L"\\thread ",
                l_thread_id,
                L" @ ",
                l_date_info_wstring,
                L".txt"
            }
    );

#elif defined(_LINUX_64BIT_OS_)
    var::character l_thread_id[_MAX_THRED_ID_DIGIT_LENGTH_] = "\0";
    snprintf(l_thread_id, _MAX_THRED_ID_DIGIT_LENGTH_, "%llu", ::FE::thread::tl_s_this_thread_id);

    var::character l_date_info_string[clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_] = "\0";
    ::std::strcpy(l_date_info_string, tl_s_clock.get_current_local_time());
    std::memset(l_date_info_string + (::std::strlen(l_date_info_string) - _SECONDS_STRING_LENGTH_), _NULL_, _SECONDS_STRING_LENGTH_ * sizeof(var::character)); // to remove min sec
    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / l_date_info_string;

    var::character l_full_path_to_the_file[_FULL_PATH_TO_FILE_MAX_LENGTH_] = "\0";
    strcpy(l_full_path_to_the_file, l_path_to_log_dump_file.c_str());

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            l_full_path_to_the_file,
            _FULL_PATH_TO_FILE_MAX_LENGTH_,
            {
                "/thread ",
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

    tl_s_file_logger.open(l_full_path_to_the_file);
    tl_s_file_logger << "\n-------------------------------------------------- BEGIN LOG --------------------------------------------------\n\n";
}

void FE::log_buffering_strategy::__log_deinitialization_strategy() noexcept
{
    if (tl_s_file_logger.is_open() == true)
    {
        tl_s_file_logger << "-------------------------------------------------- END OF LOG --------------------------------------------------\n";

        tl_s_file_logger.close();
    }
}


END_NAMESPACE