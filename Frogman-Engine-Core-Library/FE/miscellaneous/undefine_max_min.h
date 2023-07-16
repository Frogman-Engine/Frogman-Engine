#ifndef _FE_UNDEFINE_MAX_MIN_H_
#define _FE_UNDEFINE_MAX_MIN_H_

#include <FE/core/macros/macro_definitions.h>

#ifdef _VISUAL_STUDIO_CPP_
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#endif

#endif