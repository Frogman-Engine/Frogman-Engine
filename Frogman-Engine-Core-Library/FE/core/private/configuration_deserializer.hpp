#ifndef _FE_CORE_CONFIG_FILE_READER_HPP_
#define _FE_CORE_CONFIG_FILE_READER_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <fstream>
#include "../types.h"


BEGIN_NAMESPACE(FE::internal)


class configuration_deserializer
{
	static ::std::ifstream s_configuration_deserializer;
};


END_NAMESPACE

#endif
