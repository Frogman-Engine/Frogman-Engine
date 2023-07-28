#ifndef _FE_CORE_DEBUG_H_
#define _FE_CORE_DEBUG_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <iostream>
#include <FE/miscellaneous/configuration.h>
#include <FE/core/private/exception.hpp>
#include <FE/core/private/log.hpp>




#ifdef _ENABLE_FE_CHECK_ONCE_
namespace FE::internal
{
    struct check_once
    {
        check_once(boolean did_it_fail_p) noexcept
        {
            if (did_it_fail_p == false) _LIKELY_
            {
                return;
            }

            abort();
        }
    };
}
// A directive for checking the expression once at function global level.
// If the same function gets called inside a loop or recursively, the expression_p can only be evaluated once.
#define _FN_LEVEL_GLOBAL_ static

// A directive for checking the expression once per thread.
// Verification can be performed once per thread.
#define _FN_LEVEL_THREAD_LOCAL_ thread_local static 

// It invokes abort() if the expression_p is true
#define FE_CHECK_ONCE(scope_p, expression_p, verification_case_name_p) { scope_p ::FE::internal::check_once scope_p##verification_case_name_p(expression_p); }
#else
// It invokes abort() if the expression_p is true
#define FE_CHECK_ONCE(scope_p, expression_p, verification_case_name_p)
#endif


#ifdef _ENABLE_ABORT_IF_
// It invokes abort() if the expression_p is true
#define ABORT_IF(expression, message) if (expression) _UNLIKELY_ { std::cerr << #expression << " is a false expression.\nAbort has been called from\ndirectory: " << __FILE__ << "\nfunction: " << __func__ << "()\nline number: " << __LINE__ << "\nmessage: " << #message; ::std::abort(); }
#else
// It invokes abort() if the expression_p is true
#define ABORT_IF(expression, message)
#endif


#ifdef _ENABLE_LOG_
#define FE_LOG(string_format, ...)  { char l_##FE_LOG##buffer[_256_BYTES_BIT_COUNT_] = "\0";  ::FE::algorithm::string::format_string_recursive(l_##FE_LOG##buffer, string_format, __VA_ARGS__);   ::FE::internal::logger::log(l_##FE_LOG##buffer, _SOURCE_CODE_LOCATION_); }
#else
#define FE_LOG(string_format, ...)
#endif

#ifdef _ENABLE_CONDITIONAL_LOG_
#define FE_CONDITIONAL_LOG(expression_p, ...) if(expression_p)  { char l_##FE_LOG##buffer[_256_BYTES_BIT_COUNT_] = "\0";  ::FE::algorithm::string::format_string_recursive(l_##FE_LOG##buffer, string_format, __VA_ARGS__);   ::FE::internal::logger::log(l_##FE_LOG##buffer, _SOURCE_CODE_LOCATION_); }
#else
#define FE_CONDITIONAL_LOG(expression_p, ...)
#endif


#ifdef _ENABLE_ASSERT_
// It logs an error and aborts the app if the expression_p is true
#define FE_ASSERT(expression_p, message_p) if(expression_p) _UNLIKELY_ { ::FE::internal::exception::log(true, #expression_p, ::FE::internal::_ABORT_IMMEDIATELY_, message_p, _SOURCE_CODE_LOCATION_); }
#else
// It logs an error and aborts the app if the expression_p is true
#define FE_ASSERT(expression_p, message_p)
#endif

#ifdef _ENABLE_EXCEPTION_LOG_
// It logs an exception if the expression_p is true
#define FE_EXCEPTION_LOG(expression_p, message_p) ::FE::internal::exception::log(expression_p, #expression_p, ::FE::internal::_LOG_EXCEPTION_HISTORY_, message_p, _SOURCE_CODE_LOCATION_)
#else
// It logs an exception if the expression_p is true
#define FE_EXCEPTION_LOG(expression_p, message_p) expression_p
#endif

#ifdef _ENABLE_EXIT_
// It logs an error and exits the entire app process if the expression_p is true
#define FE_EXIT(expression_p, message_p, exit_code_p) if(expression_p) _UNLIKELY_ { ::FE::internal::exception::log(true, #expression_p, ::FE::internal::_EXIT_WITH_CODE_, message_p, _SOURCE_CODE_LOCATION_, #exit_code_p, static_cast<::FE::var::int32>(exit_code_p)); }
#else
// It logs an error and exits the entire app process if the expression_p is true
#define FE_EXIT(expression_p, message_p, exit_code_p)
#endif


#endif