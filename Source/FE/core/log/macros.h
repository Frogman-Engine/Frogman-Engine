#ifndef _FE_LOG_MACRO_H_
#define _FE_LOG_MACRO_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#ifdef FE_LOG
#error FE_LOG is a reserved Frogman Engine macro keyword.
#endif 
#ifdef FE_CONDITIONAL_LOG
#error FE_CONDITIONAL_LOG is a reserved Frogman Engine macro keyword.
#endif 
#ifdef FE_ASSERT
#error FE_ASSERT is a reserved Frogman Engine macro keyword.
#endif 
#ifdef FE_EXCEPTION_LOG
#error FE_EXCEPTION_LOG is a reserved Frogman Engine macro keyword.
#endif 
#include <FE/core/log/logger.hpp>
#include <FE/core/log/format_string.h>
#include <FE/core/macros/attributes.h>




#ifdef _ENABLE_LOG_
// ${%d at n} - int32
// ${%u at n} - uint32
// ${%ld at n} - int64
// ${%lu at n} - uint64
// ${%lf at n} - float64
// ${%f at n} - float32
// ${%b at n} - bool
// ${%c at n} - char
// ${%s at n} - string
// ${%p at n} - hexadecimal 64bit pointer
#define FE_LOG(...)  ::FE::log::logger::log("Frogman Engine Logs", ::FE::log::buffered_string_formatter({__VA_ARGS__}), _SOURCE_CODE_LOCATION_)
#else
#define FE_LOG(...)
#endif


#ifdef _ENABLE_CONDITIONAL_LOG_
// ${%d at n} - int32
// ${%u at n} - uint32
// ${%ld at n} - int64
// ${%lu at n} - uint64
// ${%lf at n} - float64
// ${%f at n} - float32
// ${%b at n} - bool
// ${%c at n} - char
// ${%s at n} - string
// ${%p at n} - hexadecimal 64bit pointer
#define FE_CONDITIONAL_LOG(expression, ...) if(expression) { ::FE::log::logger::log("Frogman Engine Logs", ::FE::log::buffered_string_formatter({__VA_ARGS__}), _SOURCE_CODE_LOCATION_); }
#else
#define FE_CONDITIONAL_LOG(expression, ...)
#endif


#ifdef _ENABLE_ASSERT_
// ${%d at n} - int32
// ${%u at n} - uint32
// ${%ld at n} - int64
// ${%lu at n} - uint64
// ${%lf at n} - float64
// ${%f at n} - float32
// ${%b at n} - bool
// ${%c at n} - char
// ${%s at n} - string
// ${%p at n} - hexadecimal 64bit pointer
#define FE_ASSERT(expression, ...) if(expression) _UNLIKELY_ { ::FE::log::logger::log("Frogman Engine Crash Report", ::FE::log::buffered_string_formatter({__VA_ARGS__}), _SOURCE_CODE_LOCATION_); ::std::abort(); }
#else
#define FE_ASSERT(expression, ...)
#endif


#ifdef _ENABLE_EXCEPTION_LOG_
// ${%d at n} - int32
// ${%u at n} - uint32
// ${%ld at n} - int64
// ${%lu at n} - uint64
// ${%lf at n} - float64
// ${%f at n} - float32
// ${%b at n} - bool
// ${%c at n} - char
// ${%s at n} - string
// ${%p at n} - hexadecimal 64bit pointer
#define FE_EXCEPTION_LOG(expression, ...) ::FE::log::logger::log("Frogman Engine Exception Logs", ::FE::log::buffered_string_formatter({__VA_ARGS__}), _SOURCE_CODE_LOCATION_); expression
#else
#define FE_EXCEPTION_LOG(expression, ...) expression
#endif


#define TO_STRING(p) #p


#define _NODEFAULT_ default: _UNLIKELY_ FE_ASSERT(true, "Reached Default Case: This switch has no default."); break;


#endif