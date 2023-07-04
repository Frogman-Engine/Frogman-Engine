#ifndef _FE_CORE_MACROS_ATTRIBUTES_H_
#define _FE_CORE_MACROS_ATTRIBUTES_H_
#include "macro_definitions.h"
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


#define _NODISCARD_ [[nodiscard]]
#define _FALLTHROUGH_ [[fallthrough]]
#define _MAYBE_UNUSED_ [[maybe_unused]]
#define _DISCARD_ _MAYBE_UNUSED_
#define _NORETURN_ [[noreturn]]
#define _DEPRECATED_ [[deprecated]]
#define _IN_DEVELOPMENT_ _DEPRECATED_

#if _HAS_CXX20_ == 1
#define _LIKELY_ [[likely]]
#define _UNLIKELY_ [[unlikely]]
#else
#define _LIKELY_
#define _UNLIKELY_
#endif


#endif // !_CORE_ATTRIBUTES_H_