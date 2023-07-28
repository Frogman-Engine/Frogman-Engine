#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/algorithm/numeric.hxx>
using namespace FE;
using namespace algorithm;


TEST(count_integral_digit_length, _)
{
	int l_int = 10000;
	EXPECT_EQ(numeric::count_integral_digit_length<int>(l_int), 5);

	EXPECT_EQ(numeric::count_integral_digit_length<int>(0), 1);
}

TEST(count_integral_digit_length, constexpr)
{
	EXPECT_EQ(numeric::constexpr_count_integral_digit_length<int>(10000), 5);

	EXPECT_EQ(numeric::constexpr_count_integral_digit_length<int>(0), 1);
}