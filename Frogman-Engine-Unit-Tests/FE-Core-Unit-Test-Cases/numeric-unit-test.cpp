#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/algorithm/numeric.hxx>
#include <FE/core/algorithm/string.hxx>
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


TEST(convert_integer_to_string, _)
{
	int l_int = -10000;
	char l_buffer[10] = "\0";
	numeric::convert_integer_to_string<int, char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "-10000"));
}

TEST(convert_integer_to_string, constexpr)
{
	int l_int = 10000;
	char l_buffer[10] = "\0";
	numeric::convert_integer_to_string<int, char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "10000"));
}


TEST(convert_float_to_string, _)
{
	char l_buffer[12] = "\0";
	var::float32 l_pi = 3.14159f;
	numeric::convert_float_to_string(l_buffer, 15, l_pi);
	FE::memset_s(l_buffer + 7, 0, 4, 1);

	EXPECT_TRUE(string::string_comparison(l_buffer, "3.14159"));
}

TEST(convert_float_to_string, constexpr)
{
	char l_buffer[12] = "\0";
	numeric::constexpr_convert_float_to_string(l_buffer, 15, 356.768f);
	FE::memset_s(l_buffer + 7, 0, 4, 1);

	EXPECT_TRUE(string::string_comparison(l_buffer, "356.768"));
}


TEST(convert_boolean_to_string, _)
{
	var::boolean l_is_true = true;
	EXPECT_TRUE(string::string_comparison(numeric::convert_boolean_to_string<char>(l_is_true), "true"));
}

TEST(convert_boolean_to_string, constexpr)
{
	EXPECT_TRUE(string::string_comparison(numeric::constexpr_convert_boolean_to_string<char>(false), "false"));
}


