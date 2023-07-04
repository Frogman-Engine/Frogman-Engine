#ifndef _FE_CORE_RUNTIME_EXCEPTION_HPP_
#define _FE_CORE_RUNTIME_EXCEPTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "exception_mode.h"
#include "types.h"
#include "debug.h"
#include <memory>


BEGIN_NAMESPACE(FE)


class thread;

class clock;

FORWARD_CLASS_DECLARATION(internal, engine_main);


class exception
{
public:
    typedef char char_type;

    friend class internal::engine_main;
    friend class ::FE::thread;

    constexpr exception() noexcept {}
    _CONSTEXPR20_ virtual ~exception() noexcept {}

private:
    static ::std::unique_ptr<exception> s_exception_handling_strategy;
    
protected:
    thread_local static ::std::ofstream tl_s_exception_reporter;
    thread_local static ::FE::clock tl_s_clock;
    thread_local static ::std::unique_ptr<char_type[]> tl_s_full_debug_info_buffer;
    thread_local static ::std::unique_ptr<char_type[]> tl_s_source_code_line_info_buffer;

public:
    static bool handle_exception(const bool expression_p, const char* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, const char_type* message_ptr_p, const char_type* file_name_ptr_p, const char_type* function_name_ptr_p, const int line_p, const int exit_code_p = -1) noexcept;

private:
    static void __construct_exception_on_main_thread() noexcept;
    static void __destruct_exception_on_main_thread() noexcept;
  
	static void __construct_exception() noexcept;
    static void __destruct_exception() noexcept;
   
protected:
    virtual void __main_thread_exception_construction_strategy() noexcept = 0;
    virtual void __main_thread_exception_destruction_strategy() noexcept = 0;

    virtual void __exception_construction_strategy() noexcept = 0;
    virtual void __exception_destruction_strategy() noexcept = 0;

    virtual bool __exception_handling_strategy(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept = 0;
};


#if _ENABLE_ASSERT_ == true
// It logs an error and aborts if the expression_p is true
#define FE_ASSERT(expression_p, message_p, asserted_location_p) if(expression_p) _UNLIKELY_ { ::FE::exception::handle_exception(true, #expression_p, ::FE::_ABORT_IMMEDIATELY_, message_p, asserted_location_p); }
#define _ASSERTED_LOCATION_ __FILE__, __func__, __LINE__
#else
// It logs an error and aborts if the expression_p is true
#define FE_ASSERT(expression_p, message_p, asserted_location_p)
#define _ASSERTED_LOCATION_
#endif

#if _ENABLE_EXCEPTION_ == true
// It logs an exception if the expression_p is true
#define FE_EXCEPTION(expression_p, message_p, exception_origin_p) ::FE::exception::handle_exception(expression_p, #expression_p, ::FE::_LOG_EXCEPTION_HISTORY_, message_p, exception_origin_p)
#define _EXCEPTION_ORIGIN_ __FILE__, __func__, __LINE__
#else
// It logs an exception if the expression_p is true
#define FE_EXCEPTION(expression_p, message_p, exception_origin_p) expression_p
#define _EXCEPTION_ORIGIN_
#endif

#if _ENABLE_EXIT_ == true
// It logs an error and exits if the expression_p is true
#define FE_EXIT(expression_p, message_p, exit_location_p, exit_code_p) if(expression_p) _UNLIKELY_ { ::FE::exception::handle_exception(true, #expression_p, ::FE::_EXIT_WITH_CODE_, message_p, exit_location_p, exit_code_p); }
#define _EXIT_LOCATION_ __FILE__, __func__, __LINE__
#else
// It logs an error and exits if the expression_p is true
#define FE_EXIT(expression_p, message_p, exit_location_p, exit_code_p)
#define _EXIT_LOCATION_
#endif


class real_time_exception_history_logging_strategy : public exception
{
public:
    constexpr real_time_exception_history_logging_strategy() noexcept {}
    _CONSTEXPR20_ ~real_time_exception_history_logging_strategy() noexcept {}

private:
    virtual bool __exception_handling_strategy(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept override;

    virtual void __main_thread_exception_construction_strategy() noexcept override;
    virtual void __main_thread_exception_destruction_strategy() noexcept override;
    virtual void __exception_construction_strategy() noexcept override;
    virtual void __exception_destruction_strategy() noexcept override;
};

class exception_history_log_pooling_strategy : public exception
{
public:
    constexpr exception_history_log_pooling_strategy() noexcept {}
    _CONSTEXPR20_ ~exception_history_log_pooling_strategy() noexcept {}

private:
    virtual bool __exception_handling_strategy(const bool expression_p, const char* const expression_string_ptrc_p, const FE::EXCEPTION_MODE runtime_exception_mode_p, const char* message_ptr_p, const char* file_name_ptr_p, const char* function_name_ptr_p, const int line_p, const int exit_code_p) noexcept override;

    virtual void __main_thread_exception_construction_strategy() noexcept override;
    virtual void __main_thread_exception_destruction_strategy() noexcept override;
    virtual void __exception_construction_strategy() noexcept override;
    virtual void __exception_destruction_strategy() noexcept override;
};


END_NAMESPACE
#endif
