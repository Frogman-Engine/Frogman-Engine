#ifndef _FE_CORE_ASYNC_HPP_
#define _FE_CORE_ASYNC_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"


BEGIN_NAMESPACE(FE)


enum struct ASYNC_TASK_PRIORITY : uint8
{
	_TRIVIAL = 0,
	_NORMAL = 1,
	_URGENT = 2,
};


END_NAMESPACE
#endif