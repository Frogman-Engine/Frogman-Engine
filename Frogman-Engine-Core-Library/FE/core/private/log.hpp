#ifndef _FE_CORE_LOG_HPP_
#define _FE_CORE_LOG_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.h>
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


CLASS_FORWARD_DECLARATION(FE, clock);


BEGIN_NAMESPACE(FE::internal)


class engine_main;


class logger
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
    constexpr logger() noexcept {}
    _CONSTEXPR20_ virtual ~logger() noexcept {}

private:
    static logger* s_logging_strategy_ptr;

protected:
    thread_local static ::std::ofstream tl_s_file_logger;
    thread_local static ::FE::clock tl_s_clock;
    thread_local static ::std::string tl_s_log_buffer;

public:
    static void log(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept;

protected:
    virtual void __log_initialization_strategy() noexcept = 0;
    virtual void __log_deinitialization_strategy() noexcept = 0;

    virtual void __logging_strategy(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept = 0;
};


struct logger_initialization_arguments
{
    using percent_t = var::uint8;
    logger* _logging_strategy_ptr;
    static lazy_const<var::size_t> s_log_buffer_size;
    static lazy_const<var::uint8> s_write_operation_triggering_point;
};


class real_time_logging_strategy : public logger
{
public:
    constexpr real_time_logging_strategy() noexcept {}
    _CONSTEXPR20_ ~real_time_logging_strategy() noexcept {}

private:
    virtual void __logging_strategy(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept override;

    virtual void __log_initialization_strategy() noexcept override;
    virtual void __log_deinitialization_strategy() noexcept override;
};


class log_buffering_strategy : public logger
{
public:
    constexpr log_buffering_strategy() noexcept {}
    _CONSTEXPR20_ ~log_buffering_strategy() noexcept {}

private:
    virtual void __logging_strategy(character* const message_ptrc_p, character* const file_name_ptrc_p, character* const function_name_ptrc_p, int32 line_p) noexcept override;

    virtual void __log_initialization_strategy() noexcept override;
    virtual void __log_deinitialization_strategy() noexcept override;
};


END_NAMESPACE
#endif