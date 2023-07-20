#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/fstring.hxx>
using namespace FE;
using namespace algorithm;


_MAYBE_UNUSED_ constexpr auto _UNIT_TEST_FSTRING_LENGTH_ = 100;


TEST(fstring, constructor)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(l_fstring == "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.");
}

TEST(fstring, constructor_assignment)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[] = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = l_buffer;

	EXPECT_TRUE(l_fstring == l_buffer);
}

TEST(fstring, copy_constructor)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_subject = l_fstring;

	EXPECT_TRUE(l_subject == l_fstring);
}

TEST(fstring, move_constructor)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_subject = std::move(l_fstring);

	EXPECT_TRUE(l_subject == l_fstring);
}

TEST(fstring, copy_assignment_operator)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[] = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring = l_buffer;

	EXPECT_TRUE(l_fstring == l_buffer);
}

TEST(fstring, assignment_operator)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template." == l_fstring);
}

TEST(fstring, at)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	EXPECT_EQ(l_fstring.at(4), 'f');
}

TEST(fstring, index_operator)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	EXPECT_EQ(l_fstring[4], 'f');
}

TEST(fstring, front_back)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[3] = "\0";
	string::concatenate_characters<FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type>(l_buffer, 3, { l_fstring.front(), l_fstring.back() });

	EXPECT_TRUE(string::string_comparison(l_buffer, "F."));
}

TEST(fstring, data)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));
}

TEST(fstring, c_str)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.c_str()));
}

TEST(fstring, std_str)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.std_str().c_str()));
}

TEST(fstring, begin_end)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[_UNIT_TEST_FSTRING_LENGTH_] = "\0";
	
	FE::var::index_t l_idx = 0;
	for (auto character = l_fstring.begin(); character < l_fstring.end(); ++character)
	{
		character < l_fstring.end();
		l_buffer[l_idx] = *character;
		++l_idx;
	}

	EXPECT_TRUE(l_fstring == l_buffer);
}

TEST(fstring, is_empty)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_empty_fstring = "\0";

	EXPECT_EQ(l_fstring.is_empty(), false);

	EXPECT_EQ(l_empty_fstring.is_empty(), true);
}

TEST(fstring, length)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	EXPECT_EQ(l_fstring.length(), 79);
}

TEST(fstring, max_length)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	
	EXPECT_EQ(l_fstring.max_length(), _UNIT_TEST_FSTRING_LENGTH_);
}

TEST(fstring, capacity)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_EQ(l_fstring.capacity(), _UNIT_TEST_FSTRING_LENGTH_);
}

TEST(fstring, push_back)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template";
	l_fstring.push_back('.');
	EXPECT_TRUE(string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));
}

TEST(fstring, pop_back)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	
	EXPECT_EQ(l_fstring.pop_back(), '.');
}

TEST(fstring, concatenation)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a";
	l_fstring += " fixed sized string class template.";

	EXPECT_TRUE(string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));
}

TEST(fstring, find)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	::std::optional<string::range> l_search_result = l_fstring.find("string");
	EXPECT_EQ(l_search_result.has_value(), true);

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[13] = "\0";
	string::copy_string(l_buffer, 13, l_fstring.data() + l_search_result->_begin, 6);
	EXPECT_TRUE(string::string_comparison(l_buffer, "string"));
}

TEST(fstring, count_target_character)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	string::char_count l_first_search_result = l_fstring.count_target_character('f');
	EXPECT_EQ(l_first_search_result._match_count, 2);
	EXPECT_EQ(l_first_search_result._target_data, 'f');
}

TEST(fstring, copy_substring)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[30] = "\0";
	l_fstring.copy_substring(12, 38, l_buffer, 30);
	EXPECT_TRUE(string::string_comparison(l_buffer, "_UNIT_TEST_FSTRING_LENGTH_"));
}

TEST(fstring, swap)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_first_fstring = "ABC";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_second_fstring = "CBA";

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::swap(l_first_fstring, l_second_fstring);

	EXPECT_TRUE(l_first_fstring == "CBA");
}