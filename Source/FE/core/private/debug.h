﻿#ifndef _FE_CORE_PRIVATE_DEBUG_H_
#define _FE_CORE_PRIVATE_DEBUG_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <iostream>
#include <FE/miscellaneous/configuration.h>
#include <FE/core/macros/attributes.h>




#ifdef FE_STATIC_ASSERT
#error FE_STATIC_ASSERT is a reserved Frogman Engine macro keyword.
#endif 
// statically asserts the condition, that must not be true at compile time.
#define FE_STATIC_ASSERT(expression, message) static_assert(!(expression), message)


#ifdef FE_ABORT_IF
#error ABORT_IF is a reserved Frogman Engine macro keyword.
#endif 
#ifdef _ENABLE_ABORT_IF_
    #if defined(_RELEASE_) || defined(_RELWITHDEBINFO_)
         // It invokes abort() if the expression is true
        #define FE_ABORT_IF(expression, message) if (expression) _UNLIKELY_ { ::std::abort(); }
    #else
        // It invokes abort() if the expression is true
        #define FE_ABORT_IF(expression, message) if (expression) _UNLIKELY_ { std::cerr << "Expected the expression \"" << #expression << "\" to be false.\nAbort has been called from\ndirectory: " << __FILE__ << "\nfunction: " << __func__ << "()\nline number: " << __LINE__ << "\nmessage: " << #message; ::std::abort(); }
    #endif
#else
    // It invokes abort() if the expression is true
    #define FE_ABORT_IF(expression, message)
#endif


#endif