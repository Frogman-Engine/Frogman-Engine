#include <FE/core/log/logger.hpp>
#pragma warning(disable: 4996)
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include <FE/miscellaneous/misc.h>
#include <FE/core/algorithm/string.hxx>
#include <FE/core/do_once.hxx>
#include <FE/core/clock.hpp>
#include <FE/core/thread.hpp>
#include <filesystem>




BEGIN_NAMESPACE(FE::log)


thread_local ::std::ofstream logger::tl_s_file_logger;
thread_local ::std::string logger::tl_s_log_buffer;


logger::initializer::initializer(character* const logfile_folder_name_ptrc_p,
#ifdef _WINDOWS_64BIT_OS_
    wchar* const logfile_inner_folder_name_ptrc_p
#elif defined(_LINUX_64BIT_OS_)
    character* const logfile_inner_folder_name_ptrc_p
#endif
                                ) noexcept
{
    ::std::filesystem::path l_directory_name = (::std::filesystem::current_path() / logfile_folder_name_ptrc_p);
    if (::std::filesystem::exists(l_directory_name) == false)
    {
        ::std::filesystem::create_directory(l_directory_name);
    }

    tl_s_log_buffer.reserve(default_debug_log_buffer_size);
    std::memset(tl_s_log_buffer.data(), _NULL_, default_debug_log_buffer_size * sizeof(buffer_type));

#ifdef _WINDOWS_64BIT_OS_
    var::wchar l_thread_id[FE::thread::max_thread_id_digit_length] = L"\0";
    ::swprintf(l_thread_id, FE::thread::max_thread_id_digit_length, L"%llu", FE::thread::this_thread_id()); // hashed thread-ids from std::hash are too long and hard to read 

    var::wchar l_date_info_wstring[FE::clock::current_local_time_buffer_size] = L"\0";
    ::std::mbstowcs(l_date_info_wstring, FE::clock::get_current_local_time(), FE::clock::current_local_time_buffer_size);

    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / logfile_inner_folder_name_ptrc_p;

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
    var::character l_thread_id[FE::thread::max_thread_id_digit_length] = "\0";
    snprintf(l_thread_id, FE::thread::max_thread_id_digit_length, "%llu", FE::thread::this_thread_id());

    var::character l_date_info_string[FE::clock::current_local_time_buffer_size] = "\0";
    ::std::strcpy(l_date_info_string, FE::clock::get_current_local_time());
    ::std::filesystem::path l_path_to_log_dump_file = l_directory_name / logfile_inner_folder_name_ptrc_p;

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
    tl_s_file_logger << "Compilation Date: " << " " << __DATE__ << " - " << __TIME__ << "\n\n";
    tl_s_file_logger << "\n-------------------------------------------------- BEGIN LOG --------------------------------------------------\n\n";
}

logger::initializer::~initializer() noexcept
{
    if (tl_s_file_logger.is_open() == true)
    {
        tl_s_file_logger << "-------------------------------------------------- END OF LOG --------------------------------------------------\n";

        tl_s_file_logger.close();
    }
}




void logger::log(character* const logfile_folder_name_ptrc_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept
{
#ifdef _WINDOWS_64BIT_OS_
    static var::wchar l_date_info_string[FE::clock::current_local_time_buffer_size] = L"\0";
#elif defined(_LINUX_64BIT_OS_)
    static var::character l_date_info_string[_BUFFER_SIZE_] = "\0";
#endif

    static do_once l_s_do_once_per_app_execution
    {
        [&]()
        {
#ifdef _WINDOWS_64BIT_OS_
            ::std::mbstowcs(l_date_info_string, FE::clock::get_current_local_time(), FE::clock::current_local_time_buffer_size);
#elif defined(_LINUX_64BIT_OS_)
            ::std::strcpy(l_date_info_string, internal::get_current_local_time());
#endif
        }
    };

    thread_local static logger::initializer tl_s_initializer(logfile_folder_name_ptrc_p, l_date_info_string);
    



    buffer_type l_source_code_line_info_buffer[line_info_buffer_size] = "\0";


    ::snprintf(l_source_code_line_info_buffer, line_info_buffer_size, "%d", line_p);

    ::FE::algorithm::string::concatenate_strings<var::character>
        (
            tl_s_log_buffer.data(),
            default_debug_log_buffer_size,
            {
                "[Time: ", FE::clock::get_current_local_time(), "]\t", message_ptrc_p, "\n",
                "File Directory: ", file_name_ptrc_p, "\n",
                "Function Name: ", function_name_ptrc_p, "\n",
                "Code Line Number: ", l_source_code_line_info_buffer
            }
    );


    tl_s_log_buffer = tl_s_log_buffer.data();
    length_t l_log_buffer_length = tl_s_log_buffer.length();

    size_t l_divisor = (tl_s_log_buffer.capacity() / _BUFFER_FLUSH_TRIGGERING_POINT_BY_PERCENT);

    ABORT_IF(l_log_buffer_length == 0, "l_log_buffer_length cannot be zero");
    ABORT_IF(l_divisor == 0, "l_divisor cannot be zero");

    if (l_log_buffer_length >= (l_log_buffer_length / l_divisor))
    {
        tl_s_file_logger << tl_s_log_buffer.data() << "\n\n";

        memset(l_source_code_line_info_buffer, _NULL_, line_info_buffer_size * sizeof(buffer_type));
        memset(tl_s_log_buffer.data(), _NULL_, default_debug_log_buffer_size * sizeof(buffer_type));
    }
}


END_NAMESPACE
