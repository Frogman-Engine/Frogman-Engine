﻿#ifndef _FE_UNDEFINE_MAX_MIN_H_
#define _FE_UNDEFINE_MAX_MIN_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/definitions.h>

#ifdef _FE_WITH_MSVC_
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#endif

#endif