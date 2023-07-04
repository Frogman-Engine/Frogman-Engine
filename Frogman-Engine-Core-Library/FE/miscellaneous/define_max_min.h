#ifndef _FE_DEFINE_MAX_MIN_H_
#define _FE_DEFINE_MAX_MIN_H_

#include "../core/macros/macro_definitions.h"

#if _VISUAL_STUDIO_CPP_ == 1
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif

#endif