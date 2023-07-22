#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/hash.hxx>


TEST(hash, string)
{
	EXPECT_EQ(FE::hash<const char*>{}("string"), FE::hash<const char*>{}("string"));

	EXPECT_EQ(FE::hash<const wchar_t*>{}(L"wide string"), FE::hash<const wchar_t*>{}(L"wide string"));

	int** l_double_ptr = new int* {new int};
	EXPECT_EQ(FE::hash<int*>{}(*l_double_ptr), FE::hash<int*>{}(*l_double_ptr));
	delete l_double_ptr;
}
