﻿#ifndef _FE_CORE_RUNTIME_EXCEPTION_HPP_
#define _FE_CORE_RUNTIME_EXCEPTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.h>
#include <fstream>
#include <string>


#if defined(_ENABLE_ASSERT_) || defined(_ENABLE_EXCEPTION_LOG_) || defined(_ENABLE_EXIT_)
#define _IS_EXCEPTION_LOGGER_ENABLED_
#define IF_EXCEPTION_LOGGER_ENABLED(true_p, false_p) true_p
#define ENABLE_IF_EXCEPTION_LOGGER_ENABLED(code_p) code_p
#else
#define IF_EXCEPTION_LOGGER_ENABLED(true_p, false_p) false_p
#define ENABLE_IF_EXCEPTION_LOGGER_ENABLED(code_p)
#endif


CLASS_FORWARD_DECLARATION(FE, clock);


BEGIN_NAMESPACE(FE::internal)


enum struct EXCEPTION_MODE : uint8
{
    _LOG_EXCEPTION_HISTORY_ = 0,
    _ABORT_IMMEDIATELY_ = 1,
    _EXIT_WITH_CODE_ = 2
};

_MAYBE_UNUSED_ inline constexpr EXCEPTION_MODE _EXIT_WITH_CODE_ = EXCEPTION_MODE::_EXIT_WITH_CODE_;
_MAYBE_UNUSED_ inline constexpr EXCEPTION_MODE _LOG_EXCEPTION_HISTORY_ = EXCEPTION_MODE::_LOG_EXCEPTION_HISTORY_;
_MAYBE_UNUSED_ inline constexpr EXCEPTION_MODE _ABORT_IMMEDIATELY_ = EXCEPTION_MODE::_ABORT_IMMEDIATELY_;


class exception
{
    friend class engine_main;

public:
    using buffer_type = char;
    _MAYBE_UNUSED_ static constexpr uint16 _LINE_INFO_BUFFER_SIZE_ = 32;
    _MAYBE_UNUSED_ static constexpr uint16 _DEFAULT_DEBUG_LOG_BUFFER_SIZE_ = 1024;

private:
    struct initializer
    {
        initializer() noexcept;
        ~initializer() noexcept;
    };
    
public:
    constexpr exception() noexcept {}
    _CONSTEXPR20_ virtual ~exception() noexcept {}

private:
    static exception* s_logging_strategy_ptr;

protected:
    thread_local static ::std::ofstream tl_s_file_logger;
    thread_local static ::FE::clock tl_s_clock;
    thread_local static ::std::string tl_s_log_buffer;
   
public:
    static bool log(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p = nullptr, int32 exit_code_p = -1) noexcept;

protected:
    virtual void __exception_construction_strategy() noexcept = 0;
    virtual void __exception_destruction_strategy() noexcept = 0;

    virtual bool __logging_strategy(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p, int32 exit_code_p) noexcept = 0;
};


struct exception_logger_initialization_arguments
{
    using percent_t = var::uint8;
    exception* _exception_logging_strategy_ptr;
    static lazy_const<var::size_t> s_log_buffer_size;
    static lazy_const<var::uint8> s_write_operation_triggering_point;
};


class real_time_exception_history_logging_strategy : public exception
{
public:
    constexpr real_time_exception_history_logging_strategy() noexcept {}
    _CONSTEXPR20_ ~real_time_exception_history_logging_strategy() noexcept {}

private:
    virtual bool __logging_strategy(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p, int32 exit_code_p) noexcept override;

    virtual void __exception_construction_strategy() noexcept override;
    virtual void __exception_destruction_strategy() noexcept override;
};


class exception_history_log_buffering_strategy : public exception
{
public:
    constexpr exception_history_log_buffering_strategy() noexcept {}
    _CONSTEXPR20_ ~exception_history_log_buffering_strategy() noexcept {}

private:
    virtual bool __logging_strategy(boolean expression_p, character* const expression_string_ptrc_p, const EXCEPTION_MODE runtime_exception_mode_p, character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p, character* const exit_code_enum_ptrc_p, int32 exit_code_p) noexcept override;

    virtual void __exception_construction_strategy() noexcept override;
    virtual void __exception_destruction_strategy() noexcept override;
};


END_NAMESPACE
#endif
