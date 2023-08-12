#ifndef _FE_CORE_DEBUG_H_
#define _FE_CORE_DEBUG_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <iostream>
#include <FE/miscellaneous/configuration.h>




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
    #if defined(_RELEASE_) || defined(_RELWITHDEBINFO_)
         // It invokes abort() if the expression_p is true
        #define ABORT_IF(expression, message) if (expression) _UNLIKELY_ { ::std::abort(); }
    #else
        // It invokes abort() if the expression_p is true
        #define ABORT_IF(expression, message) if (expression) _UNLIKELY_ { std::cerr << "Expected the expression \"" << #expression << "\" to be false.\nAbort has been called from\ndirectory: " << __FILE__ << "\nfunction: " << __func__ << "()\nline number: " << __LINE__ << "\nmessage: " << #message; ::std::abort(); }
    #endif
#else
    // It invokes abort() if the expression_p is true
    #define ABORT_IF(expression, message)
#endif


#define TO_STRING(p) #p

#endif