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

	EXPECT_FALSE(l_subject == l_fstring);
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

TEST(fstring, index_operator)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	EXPECT_EQ(l_fstring[4], 'f');
}

TEST(fstring, assign)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring.assign(3, '?');

	EXPECT_TRUE("???" == l_fstring);

	l_fstring.clear();
	l_fstring.assign("C++ 20", 3);

	EXPECT_TRUE("C++" == l_fstring);


	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_other = "A bottle of water from the United Kingdom";
	l_fstring.clear();
	l_fstring.assign(l_other, 0, 41);
	EXPECT_TRUE("A bottle of water from the United Kingdom" == l_fstring);

	l_fstring.clear();
	l_fstring.assign("A bottle of water", 8);
	EXPECT_TRUE("A bottle" == l_fstring);

	l_fstring.clear();
	l_fstring.assign(l_other.begin() + 23, l_other.end());
	EXPECT_TRUE("the United Kingdom" == l_fstring);

	l_fstring.clear();
	l_fstring.assign({'C', '/', 'C', '+', '+'});
	EXPECT_TRUE("C/C++" == l_fstring);
}

TEST(fstring, insert)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "TD is evil";
	l_fstring.insert(2, 1, 'D');
	EXPECT_TRUE("TDD is evil" == l_fstring);

	l_fstring = "TDD is T Driven Development";
	l_fstring.insert(8, "ime-Inefficiency");
	EXPECT_TRUE("TDD is Time-Inefficiency Driven Development" == l_fstring);

	EXPECT_EQ(l_fstring.length(), strlen(l_fstring.c_str()));

	l_fstring = "Unit testing is  TDD";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_not = "not";
	l_fstring.insert(16, l_not);
	EXPECT_TRUE("Unit testing is not TDD" == l_fstring);

	l_fstring.insert(0, "Unit testing is not TDD", 0, 12);
	EXPECT_TRUE("Unit testingUnit testing is not TDD" == l_fstring);

	l_fstring.insert(12, { ' ', 'f', 'r', 'a', 'm', 'e', 'w', 'o', 'r', 'k'});

	EXPECT_TRUE("Unit testing frameworkUnit testing is not TDD" == l_fstring);
}

TEST(fstring, front_back)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[3] = "\0";
	string::concatenate_characters<FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type>(l_buffer, 3, { l_fstring.front(), l_fstring.back() });

	EXPECT_TRUE(string::string_comparison(l_buffer, "F."));
}

TEST(fstring, c_str)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.std_str().c_str()));

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));

	EXPECT_TRUE(::FE::algorithm::string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.c_str()));
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

TEST(fstring, capacity_clear_and_is_empty)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_EQ(l_fstring.capacity(), _UNIT_TEST_FSTRING_LENGTH_);

	l_fstring.clear();

	EXPECT_EQ(l_fstring.is_empty(), true);
}

TEST(fstring, push_pop_back)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template";
	l_fstring.push_back('.');

	EXPECT_TRUE(string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));

	EXPECT_EQ(l_fstring.pop_back(), '.');
}

TEST(fstring, concatenation)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a";
	l_fstring += " fixed sized string class template.";

	EXPECT_TRUE(string::string_comparison("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));
}

TEST(fstring, starts_with)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_substring = "FE";

	EXPECT_TRUE(l_fstring.starts_with(l_substring));

	EXPECT_TRUE(l_fstring.starts_with("FE::"));

	EXPECT_TRUE(l_fstring.starts_with('F'));

	EXPECT_FALSE(l_fstring.starts_with('E'));
}

TEST(fstring, ends_with)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_substring = "template.";

	EXPECT_TRUE(l_fstring.ends_with(l_substring));

	EXPECT_TRUE(l_fstring.ends_with("template."));

	EXPECT_TRUE(l_fstring.ends_with('.'));

	EXPECT_FALSE(l_fstring.ends_with("%d"));
}

TEST(fstring, contains)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_substring = "string";

	EXPECT_TRUE(l_fstring.contains(l_substring));
			
	EXPECT_TRUE(l_fstring.contains("a string class template."));
			
	EXPECT_TRUE(l_fstring.contains('i'));

	EXPECT_FALSE(l_fstring.contains('?'));
}

TEST(fstring, copy)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::value_type l_buffer[20] = "\0";
	l_fstring.copy(l_buffer, 20, 24, 29);
	EXPECT_TRUE(string::string_comparison(l_buffer, "class"));
}

TEST(fstring, find)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_substring = "fstring";

	FE::optional<string::range> l_search_result = l_fstring.find(l_substring);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_TRUE(string::compare_ranged_strings(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	l_substring = "string";
	l_search_result.reset();
	l_search_result = *(l_fstring.find(l_substring, 10));

	EXPECT_TRUE(string::compare_ranged_strings(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));
}

TEST(fstring, rfind)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_substring = "string class";

	FE::optional<string::range> l_search_result = l_fstring.rfind(l_substring, 39);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_TRUE(string::compare_ranged_strings(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	string::char_search_result l_result2 = l_fstring.rfind('t', 20);

	EXPECT_EQ(l_result2._target_data, 't');
	EXPECT_EQ(l_result2._target_data_location, 18);
}

TEST(fstring, count_chars)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";

	EXPECT_EQ((l_fstring.count_chars('s'))._match_count, 5);

	index_t l_from = 20;
	EXPECT_EQ((l_fstring.count_chars('s', l_from))._match_count, 2);
}

TEST(fstring, swap)
{
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_first_fstring = "ABC";
	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> l_second_fstring = "CBA";

	FE::fstring<_UNIT_TEST_FSTRING_LENGTH_>::swap(l_first_fstring, l_second_fstring);

	EXPECT_TRUE(l_first_fstring == "CBA");
}