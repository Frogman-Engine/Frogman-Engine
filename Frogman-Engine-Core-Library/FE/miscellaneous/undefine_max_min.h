#ifndef _FE_UNDEFINE_MAX_MIN_H_
#define _FE_UNDEFINE_MAX_MIN_H_

#include "../core/macros/macro_definitions.h"

#if _VISUAL_STUDIO_CPP_ == 1 
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#endif

#endif