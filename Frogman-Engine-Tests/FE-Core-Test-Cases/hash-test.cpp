#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/hash.hpp>


TEST(hash, all)
{
	EXPECT_EQ(FE::hash<const char*>{}("string"), FE::hash<const char*>{}("string"));

	EXPECT_EQ(FE::hash<const wchar_t*>{}(L"wide string"), FE::hash<const wchar_t*>{}(L"wide string"));

	std::unique_ptr<int*> l_double_ptr( new int* {new int});
	EXPECT_EQ( FE::hash<int*>{}(*l_double_ptr), FE::hash<int*>{}(*l_double_ptr) );

	std::vector<int> l_vec = { 1, 2, 3 };
	EXPECT_EQ(FE::hash<std::vector<int>>{}(l_vec), FE::hash<std::vector<int>>{}(l_vec));

	std::string l_std_str = "a bottle of water";
	EXPECT_EQ(FE::hash<std::string>{}(l_std_str), FE::hash<std::string>{}(l_std_str));
}
