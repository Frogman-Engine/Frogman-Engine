#ifndef _FE_DEFINE_MAX_MIN_H_
#define _FE_DEFINE_MAX_MIN_H_

#include <FE/core/macros/macro_definitions.h>

#ifdef _VISUAL_STUDIO_CPP_
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif

#endif