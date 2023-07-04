// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include "../exception.hpp"
#include "../algorithm/string.hxx"
#include "../fstring.hxx"
#include "../thread.hpp"
#include "../clock.hpp"
#include <cwchar>
#include <fstream>
#include <filesystem>


constexpr auto _FILE_NAME_MAX_LENGTH_ = 8192;
constexpr auto _MAX_THRED_ID_DIGIT_LENGTH_ = 24;


::std::unique_ptr<FE::exception> FE::exception::s_exception_handling_strategy = nullptr;

thread_local ::std::ofstream FE::exception::tl_s_exception_reporter;

thread_local ::FE::clock FE::exception::tl_s_clock;

thread_local ::std::unique_ptr<FE::exception::char_type[]> FE::exception::tl_s_source_code_line_info_buffer IF_DEBUG_MODE((new FE::exception::char_type[_LINE_INFO_BUFFER_SIZE_] {(FE::exception::char_type)'\0' }), = nullptr);

thread_local ::std::unique_ptr<FE::exception::char_type[]> FE::exception::tl_s_full_debug_info_buffer IF_DEBUG_MODE((new FE::exception::char_type[_FULL_DEBUG_INFO_BUFFER_SIZE_] {(FE::exception::char_type)'\0'}), = nullptr);


bool FE::exception::handle_exception(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept
{
    return exception::s_exception_handling_strategy->__exception_handling_strategy(expression_p, expression_string_ptrc_p, runtime_exception_mode_p, message_ptr_p, file_name_ptr_p, function_name_ptr_p, line_p, exit_code_p);
}

void FE::exception::__construct_exception_on_main_thread() noexcept
{
    exception::s_exception_handling_strategy->__main_thread_exception_construction_strategy();
}

void  FE::exception::__destruct_exception_on_main_thread() noexcept
{
    exception::s_exception_handling_strategy->__main_thread_exception_destruction_strategy();
}

void FE::exception::__construct_exception() noexcept
{
    exception::s_exception_handling_strategy->__exception_construction_strategy();
}

void FE::exception::__destruct_exception() noexcept
{
    exception::s_exception_handling_strategy->__exception_destruction_strategy();
}








bool FE::real_time_exception_history_logging_strategy::__exception_handling_strategy(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept
{
    switch (static_cast<int>(expression_p))
    {
    case 0:
        return false;
    default:
        break;
    }


    ::snprintf(exception::tl_s_source_code_line_info_buffer.get(), _LINE_INFO_BUFFER_SIZE_, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<char>
        (
            exception::tl_s_full_debug_info_buffer.get(),
            _FULL_DEBUG_INFO_BUFFER_SIZE_,
            {
                "Time: ", exception::tl_s_clock.get_current_local_time(), "\n",
                "Error Message - ", message_ptr_p, "\n",
                "Expected the expression \"", expression_string_ptrc_p, "\" to be false", "\n",
                "File Directory: ", file_name_ptr_p, "\n",
                "Function Name: ", function_name_ptr_p, "\n",
                "Code Line Number: ", exception::tl_s_source_code_line_info_buffer.get()
            }
    );


    switch (runtime_exception_mode_p)
    {
    case _LOG_EXCEPTION_HISTORY_: // store exception logs in a global container and write  exception history file right before the unsafe_end of the application.  
        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);
        break;


    case _ABORT_IMMEDIATELY_:
        FE::algorithm::string::string_concatenation<char>(exception::tl_s_full_debug_info_buffer.get(), _FULL_DEBUG_INFO_BUFFER_SIZE_, "\nabort() HAS BEEN CALLED.", ::FE::algorithm::string::string_length("\tabort() HAS BEEN CALLED."));

        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);

        ::abort(); // aborts the entire processes of the application.


    case _EXIT_WITH_CODE_:
        // store exit code
        ::snprintf(exception::tl_s_source_code_line_info_buffer.get(), _LINE_INFO_BUFFER_SIZE_, "%d", exit_code_p);

        ::FE::algorithm::string::concatenate_strings<char>
            (
                exception::tl_s_full_debug_info_buffer.get(),
                _FULL_DEBUG_INFO_BUFFER_SIZE_,
                {
                    "\nexit() HAS BEEN CALLED with exit code: ", exception::tl_s_source_code_line_info_buffer.get()
                }
        );

        exception::tl_s_exception_reporter << exception::tl_s_full_debug_info_buffer.get() << "\n\n";

        ::memset(exception::tl_s_source_code_line_info_buffer.get(), '\0', _LINE_INFO_BUFFER_SIZE_);
        ::memset(exception::tl_s_full_debug_info_buffer.get(), '\0', _FULL_DEBUG_INFO_BUFFER_SIZE_);

        ::exit(exit_code_p);
    }

    return true;
}

void FE::real_time_exception_history_logging_strategy::__main_thread_exception_construction_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = ::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\0";
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }
#if _WINDOWS_64BIT_OS_ == 1
    ::FE::fwstring<clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_> l_date_info_wstring;
    ::std::mbstowcs(l_date_info_wstring.begin().operator->(), exception::tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);

    if (::FE::algorithm::string::string_length((::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\\thread \0").c_str()) >= _FILE_NAME_MAX_LENGTH_ - clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_) { ::abort(); }

    ::FE::fwstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\\thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fwstring<_FILE_NAME_MAX_LENGTH_>::value_type>
        (
            l_exception_history_file_name.begin().operator->(),
            _FILE_NAME_MAX_LENGTH_,
            {
                L"main() @ ",
                l_date_info_wstring.c_str(),
                L".txt"
            }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#elif _LINUX_64BIT_OS_ == 1
    if (::FE::algorithm::string::string_length((::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs/thread \0").c_str()) >= _FILE_NAME_MAX_LENGTH_ - clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_) { ::abort(); }

    ::FE::fstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs/thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fstring<_FILE_NAME_MAX_LENGTH_>::value_type>
        (
            l_exception_history_file_name.begin().operator->(),
            _FILE_NAME_MAX_LENGTH_,
            {
                "main() @ ",
                exception::tl_s_clock.get_current_local_time(),
                ".txt"
            }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#endif
}

void FE::real_time_exception_history_logging_strategy::__main_thread_exception_destruction_strategy() noexcept
{
    if (exception::tl_s_exception_reporter.is_open() == true)
    {
        exception::tl_s_exception_reporter << "\n}\n[END OF HISTORY]";
        exception::tl_s_exception_reporter << "\n\nThe leaked heap memory byte(s) by the main thread" << " is " << heap_utilization<void>::query_all_data()._thread_local_total_bytes << " byte(s)\n";
        exception::tl_s_exception_reporter << "The total leaked byte(s) on the heap is " << heap_utilization<void>::query_all_data()._global_total_bytes << " byte(s)";
        exception::tl_s_exception_reporter.close();
    }
}

void FE::real_time_exception_history_logging_strategy::__exception_construction_strategy() noexcept
{
    ::std::filesystem::path l_directory_name = ::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\0";
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }
#if _WINDOWS_64BIT_OS_ == 1
    ::FE::fwstring<_MAX_THRED_ID_DIGIT_LENGTH_> l_thread_id;
    ::swprintf(l_thread_id.begin().operator->(), _MAX_THRED_ID_DIGIT_LENGTH_, L"%llu", ::FE::thread::tl_s_this_thread_id); // hashed thread-ids from std::hash are too long and hard to read 

    ::FE::fwstring<clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_> l_date_info_wstring;
    ::std::mbstowcs(l_date_info_wstring.begin().operator->(), exception::tl_s_clock.get_current_local_time(), clock::_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_);

    ::FE::fwstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs\\thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fwstring<_FILE_NAME_MAX_LENGTH_>::value_type>
        (
            l_exception_history_file_name.begin().operator->(),
            _FILE_NAME_MAX_LENGTH_,
            {
                l_thread_id.c_str(),
                L" @ ",
                l_date_info_wstring.c_str(),
                L".txt"
            }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#elif _LINUX_64BIT_OS_ == 1
    ::FE::fstring<_MAX_THRED_ID_DIGIT_LENGTH_> l_thread_id;
    snprintf(l_thread_id.begin().operator->(), _MAX_THRED_ID_DIGIT_LENGTH_, "%llu", ::FE::thread::tl_s_this_thread_id);

    ::FE::fstring<_FILE_NAME_MAX_LENGTH_> l_exception_history_file_name = (::std::filesystem::current_path() / "Frogman-Engine-Exception-History-Logs/thread \0").c_str();

    ::FE::algorithm::string::concatenate_strings<::FE::fstring<_FILE_NAME_MAX_LENGTH_>::value_type>
        (
            l_exception_history_file_name.begin().operator->(),
            _FILE_NAME_MAX_LENGTH_,
            {
                l_thread_id.c_str(),
                " @ ",
                exception::tl_s_clock.get_current_local_time(),
                ".txt"
            }
    );

    exception::tl_s_exception_reporter.open(l_exception_history_file_name.c_str());
    exception::tl_s_exception_reporter << "[BEGIN RECORD]\n{\n";
#endif
}

void FE::real_time_exception_history_logging_strategy::__exception_destruction_strategy() noexcept
{
    if (exception::tl_s_exception_reporter.is_open() == true)
    {
        exception::tl_s_exception_reporter << "\n}\n[END OF HISTORY]";

        ::FE::exception::tl_s_exception_reporter << "\n\nThe leaked heap memory byte(s) by the thread " << ::FE::thread::tl_s_this_thread_id << " is " << heap_utilization<void>::query_all_data()._thread_local_total_bytes << " byte(s)";

        exception::tl_s_exception_reporter.close();
    }
}








bool FE::exception_history_log_pooling_strategy::__exception_handling_strategy(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept
{
    return false;
}

void FE::exception_history_log_pooling_strategy::__main_thread_exception_construction_strategy() noexcept
{
}

void FE::exception_history_log_pooling_strategy::__main_thread_exception_destruction_strategy() noexcept
{
}

void FE::exception_history_log_pooling_strategy::__exception_construction_strategy() noexcept
{
}

void FE::exception_history_log_pooling_strategy::__exception_destruction_strategy() noexcept
{
}