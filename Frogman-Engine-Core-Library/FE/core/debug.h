#ifndef _FE_CORE_DEBUG_H_
#define _FE_CORE_DEBUG_H_
#include <FE/miscellaneous/configuration.h>
#include <csignal>
#include <iostream>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


#ifdef _ENABLE_ABORT_IF_
// It aborts if the expression is true
#define ABORT_IF(expression, message) if (expression) _UNLIKELY_ { std::cerr << #expression << " is a false expression.\nAbort has been called from\ndirectory: " << __FILE__ << "\nfunction: " << __func__ << "()\nline number: " << __LINE__ << "\nmessage: " << #message; ::std::abort(); }
#else
// It aborts if the expression is true
#define ABORT_IF(expression, message)
#endif

#endif
