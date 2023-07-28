#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/cstring.hxx>
using namespace FE;
using namespace algorithm;


TEST(cstring, constructor)
{
	FE::cstring::buffer_type l_buffer[] = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_TRUE(l_cstring == l_buffer);
}

TEST(cstring, copy_constructor)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_subject = l_cstring;

	EXPECT_TRUE(l_subject == l_cstring);
}

TEST(cstring, move_constructor)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_subject = std::move(l_cstring);

	EXPECT_TRUE(l_subject == l_cstring);
}

TEST(cstring, assignment_operator)
{
	FE::cstring l_cstring;
	l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_TRUE("FE::compile_time_constant_string is a compile-time string class template." == l_cstring);
}

TEST(cstring, copy_assignment_operator)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	
	FE::cstring l_second_cstring;
	l_second_cstring = l_cstring;

	EXPECT_TRUE(l_second_cstring == l_cstring);
}

TEST(cstring, move_assignment_operator)
{
	FE::cstring l_cstring;
	l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	FE::cstring l_subject;
	l_subject = std::move(l_cstring);

	EXPECT_TRUE(l_subject == l_cstring);
}

TEST(cstring, index_operator)
{
	FE::cstring l_cstring;
	l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_EQ(l_cstring[4], 'c');
}

TEST(cstring, front_back)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	
	FE::cstring::buffer_type l_buffer[3] = "\0";
	FE::algorithm::string::concatenate_characters<FE::cstring::buffer_type>( l_buffer, 3, { l_cstring.front(), l_cstring.back() } );

	EXPECT_TRUE( ::FE::algorithm::string::string_comparison(l_buffer, "F.") );
}

TEST(cstring, c_str)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_TRUE( ::FE::algorithm::string::string_comparison("FE::compile_time_constant_string is a compile-time string class template.", l_cstring.c_str()) );
}

TEST(cstring, std_str)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::compile_time_constant_string is a compile-time string class template.", l_cstring.std_str().c_str()));
}

TEST(cstring, begin_end)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring::buffer_type l_buffer[100] = "\0";

	FE::var::index_t l_idx = 0;
	for (auto character = l_cstring.cbegin(); character != l_cstring.cend(); ++character)
	{
		l_buffer[l_idx] = *character;
		++l_idx;
	}

	EXPECT_TRUE(l_cstring == l_buffer);


	l_idx = 0;
	for (auto character = l_cstring.crbegin(); character != l_cstring.crend(); ++character)
	{
		l_buffer[l_idx] = *character;
		++l_idx;
	}
	algorithm::string::invert_string(l_buffer);
	EXPECT_TRUE(l_cstring == l_buffer);
}

TEST(cstring, is_empty)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	EXPECT_FALSE(l_cstring.is_empty());

	FE::cstring l_empty_cstring;
	EXPECT_EQ(l_empty_cstring.is_empty(), true);
}

TEST(cstring, length)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	EXPECT_EQ(l_cstring.length(), 73);
}

TEST(cstring, clear)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	l_cstring.clear();

	EXPECT_EQ(l_cstring.is_empty(), true);
}

TEST(cstring, starts_with)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_substring = "FE";

	EXPECT_TRUE(l_cstring.starts_with(l_substring));

	EXPECT_TRUE(l_cstring.starts_with("FE::"));

	EXPECT_TRUE(l_cstring.starts_with('F'));

	EXPECT_FALSE(l_cstring.starts_with('E'));
}

TEST(cstring, ends_with)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_substring = "template.";

	EXPECT_TRUE(l_cstring.ends_with(l_substring));

	EXPECT_TRUE(l_cstring.ends_with("a compile-time string class template."));

	EXPECT_TRUE(l_cstring.ends_with('.'));

	EXPECT_FALSE(l_cstring.ends_with('e'));
}

TEST(cstring, contains)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_substring = "compile-time";

	EXPECT_TRUE(l_cstring.contains(l_substring));

	EXPECT_TRUE(l_cstring.contains("compile_time_constant_string"));

	EXPECT_TRUE(l_cstring.contains('i'));

	EXPECT_FALSE(l_cstring.contains('?'));
}

TEST(cstring, copy)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring::buffer_type l_buffer[20] = "\0";
	l_cstring.copy(l_buffer, 20, 38, 50);
	EXPECT_TRUE(string::string_comparison(l_buffer, "compile-time"));
}

TEST(cstring, find)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_substring = "string";

	FE::optional<string::range> l_search_result = l_cstring.find(l_substring);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_TRUE(string::compare_ranged_strings(l_cstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	l_substring = "time";
	l_search_result.reset();
	l_search_result = *(l_cstring.find(l_substring, 20));
	
	EXPECT_TRUE(string::compare_ranged_strings(l_cstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));
}

TEST(cstring, rfind)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";
	FE::cstring l_substring = "string";

	FE::optional<string::range> l_search_result = l_cstring.rfind(l_substring, 70);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_TRUE(string::compare_ranged_strings(l_cstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	string::char_search_result l_result2 = l_cstring.rfind('t', 20);

	EXPECT_EQ(l_result2._target_data, 't');
	EXPECT_EQ(l_result2._target_data_location, 12);
}

TEST(cstring, count_chars)
{
	FE::cstring l_cstring = "FE::compile_time_constant_string is a compile-time string class template.";

	EXPECT_EQ((l_cstring.count_chars('c'))._match_count, 4);

	index_t l_from = 20;
	EXPECT_EQ((l_cstring.count_chars('c', l_from))._match_count, 2);
}

TEST(cstring, swap)
{
	FE::cstring l_first_cstring = "ABC";
	FE::cstring l_second_cstring = "CBA";

	FE::cstring::swap(l_first_cstring, l_second_cstring);
	
	EXPECT_TRUE(l_first_cstring == "CBA");
}