#ifndef _FE_CORE_DEBUG_H_
#define _FE_CORE_DEBUG_H_
#include "../miscellaneous/configuration.h"
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.

#if _ENABLE_ASSERT_WITHOUT_LOG_ == true
// It aborts if the condition_p is true
#define FE_ASSERT_WITHOUT_LOG(condition_p) if(condition_p) _UNLIKELY_ { ::std::abort(); }
#else
// It aborts if the condition_p is true
#define FE_ASSERT_WITHOUT_LOG(condition_p)
#endif

#if _DEBUG_MODE_ == true || _ENABLE_ASSERT_ == true || _ENABLE_EXCEPTION_ == true || _ENABLE_EXIT_ == true
#define IF_DEBUG_MODE(true_p, false_p) true_p
#define ENABLE_IF_DEBUG_MODE(code_p) code_p
#else
#define IF_DEBUG_MODE(true_p, false_p) false_p
#define ENABLE_IF_DEBUG_MODE(code_p)
#endif

#endif
