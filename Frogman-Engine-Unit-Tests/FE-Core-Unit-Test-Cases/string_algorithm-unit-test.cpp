#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/algorithm/string.hxx>
using namespace FE;
using namespace algorithm;




TEST(FE_algorithm_string, string_to_integer)
{
	char l_buffer[10] = "2023";
	var::int32 l_result = ::FE::algorithm::string::string_to_integer<char, ::FE::var::int32>(l_buffer);
	EXPECT_EQ(2023, l_result);


	l_result = ::FE::algorithm::string::char_to_integer<char, int>('1');
	EXPECT_EQ(l_result, 1);


	l_result = ::FE::algorithm::string::string_to_integer<char, ::FE::var::int32>("2023");
	EXPECT_EQ(2023, l_result);
}




TEST(FE_algorithm_string, string_length)
{
	char l_buffer[] = "FE::algorithm::string::string_length is a templated function that provides more functionalities than the traditional C-style string_length.";

	::FE::int64 l_result = ::FE::algorithm::string::string_length<char>(l_buffer);

	EXPECT_EQ(139, l_result);
}

TEST(FE_algorithm_string, constexpr_string_length)
{
	::FE::int64 l_result = ::FE::algorithm::string::string_length<::FE::var::wchar>(L"FE::algorithm::string::string_length is a templated function that provides more functionalities than the traditional C-style string_length.");

	EXPECT_EQ(139, l_result);
}




TEST(FE_algorithm_string, compare_ranged_strings)
{
	std::string l_left_string = "* Apple Mango *";
	std::string l_right_string = "- Mango -";
	algorithm::string::range left_substring_range{8, 13};
	algorithm::string::range right_substring_range{2, 7};

	EXPECT_TRUE(algorithm::string::compare_ranged_strings(l_left_string.c_str(), left_substring_range, l_right_string.data(), right_substring_range));
	EXPECT_TRUE(algorithm::string::compare_ranged_strings(l_left_string.data(), left_substring_range, l_right_string.c_str(), right_substring_range));

	EXPECT_TRUE(algorithm::string::compare_ranged_strings(l_left_string.data(), left_substring_range, l_right_string.data(), right_substring_range));
	EXPECT_TRUE(algorithm::string::compare_ranged_strings(l_left_string.c_str(), left_substring_range, l_right_string.c_str(), right_substring_range));
}




TEST(FE_algorithm_string, string_comparison)
{
	char l_first_string[20] = "American";
	char l_second_string[20] = "British";

	EXPECT_TRUE( !::FE::algorithm::string::string_comparison(l_first_string, l_second_string) );
}

TEST(FE_algorithm_string, constexpr_string_comparison)
{
	EXPECT_TRUE( ::FE::algorithm::string::string_comparison(L"Jesus Loves You", L"Jesus Loves You") );
}




TEST(FE_algorithm_string, copy_string)
{
	char l_string[20] = "\n";

	::FE::algorithm::string::copy_string(l_string, 20, "Hi, World", ::FE::algorithm::string::string_length("Hi, World"));

	EXPECT_TRUE( ::FE::algorithm::string::string_comparison(l_string, "Hi, World") );
}




TEST(FE_algorithm_string, string_concatenation)
{
	char l_string[50] = "Boost Libraries are ";
	::FE::algorithm::string::string_concatenation( l_string, 50, "written in C++.", ::FE::algorithm::string::string_length("written in C++.") );

	EXPECT_TRUE( ::FE::algorithm::string::string_comparison("Boost Libraries are written in C++.", l_string) );
}




TEST(FE_algorithm_string, capitalize_string)
{
	std::string l_string = "experience our british premium bottle of water!";
	::FE::algorithm::string::capitalize_string<std::string::value_type>(l_string.data());

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string.c_str(), "EXPERIENCE OUR BRITISH PREMIUM BOTTLE OF WATER!"));


	var::character l_grade = 'a';
	EXPECT_EQ(::FE::algorithm::string::capitalize_character<var::character>(l_grade), 'A');
}




TEST(FE_algorithm_string, to_lowercase)
{
	std::string l_string = "EXPERIENCE OUR KOREAN PREMIUM KIMCHI!";
	::FE::algorithm::string::to_lowercase<std::string::value_type>(l_string.data());

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string.c_str(), "experience our korean premium kimchi!"));


	var::character l_grade = 'F';
	EXPECT_EQ(::FE::algorithm::string::to_lowercase<var::character>(l_grade), 'f');
}




TEST(FE_algorithm_string, capitalize_every_first_letter_of_words)
{
	std::string l_string = "experience the speed of light!";

	::FE::algorithm::string::capitalize_every_first_letter_of_words<std::string::value_type>(l_string.data());

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string.data(), "Experience The Speed Of Light!"));
}




TEST(FE_algorithm_string, insensitive_string_comparison)
{
	std::string l_capitalized_string = "MANGO";
	std::string l_lowercased_string = "mango";

	EXPECT_TRUE(::FE::algorithm::string::insensitive_string_comparison(l_capitalized_string.c_str(), l_lowercased_string.data()));
	EXPECT_TRUE(::FE::algorithm::string::insensitive_string_comparison(l_capitalized_string.data(), l_lowercased_string.c_str()));

	EXPECT_TRUE(::FE::algorithm::string::insensitive_string_comparison(l_capitalized_string.data(), l_lowercased_string.data()));
	EXPECT_TRUE(::FE::algorithm::string::insensitive_string_comparison(l_capitalized_string.c_str(), l_lowercased_string.c_str()));
}




TEST(FE_algorithm_string, insensitive_ranged_string_comparison)
{
	std::string l_left_string = "* Apple MANGO *";
	std::string l_right_string = "- Mango -";
	algorithm::string::range left_substring_range{8, 13};
	algorithm::string::range right_substring_range{2, 7};

	EXPECT_TRUE(algorithm::string::insensitive_ranged_string_comparison(l_left_string.c_str(), left_substring_range, l_right_string.data(), right_substring_range));
	EXPECT_TRUE(algorithm::string::insensitive_ranged_string_comparison(l_left_string.data(), left_substring_range, l_right_string.c_str(), right_substring_range));

	EXPECT_TRUE(algorithm::string::insensitive_ranged_string_comparison(l_left_string.data(), left_substring_range, l_right_string.data(), right_substring_range));
	EXPECT_TRUE(algorithm::string::insensitive_ranged_string_comparison(l_left_string.c_str(), left_substring_range, l_right_string.c_str(), right_substring_range));
}




TEST(FE_algorithm_string, invert_string)
{
	std::string l_string = "!hatU fo ytisrevinU ehT";

	::FE::algorithm::string::invert_string<std::string::value_type>(l_string.data());

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string.c_str(), "The University of Utah!"));
}




TEST(FE_algorithm_string, constexpr_hash_code)
{
	const char* l_cstring = "A bottle of water.";

	SWITCH(l_cstring)
	{
	CASE("A bottle of water."):
		EXPECT_TRUE(true);
		break;

	CASE("A bucket of milk."):
		EXPECT_TRUE(false);
		break;

	CASE("A cup of coke."):
		EXPECT_TRUE(false);
		break;

	default:
		EXPECT_TRUE(false);
		break;
	}
}




TEST(FE_algorithm_string, search_very_first_char)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::search_very_first_char(l_string, 'c');

	EXPECT_EQ(l_result._target_data, 'c');
	EXPECT_EQ(l_result._target_data_location, 8);
}

TEST(FE_algorithm_string, search_very_last_char)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::search_very_last_char(l_string, 'c');

	EXPECT_EQ(l_result._target_data, 'c');
	EXPECT_EQ(l_result._target_data_location, 42);
}




TEST(FE_algorithm_string, count_chars)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::count_chars(l_string, 't');

	EXPECT_EQ(l_result._match_count, 7);
	EXPECT_EQ(l_result._target_data, 't');
}

TEST(FE_algorithm_string, constexpr_count_chars)
{
	const char* l_string = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::count_chars(l_string, 't');

	EXPECT_EQ(l_result._match_count, 7);
	EXPECT_EQ(l_result._target_data, 't');
}




TEST(FE_algorithm_string, search_very_first_substring)
{
	char l_string[] = "the University of Utah";

	FE::optional l_result = ::FE::algorithm::string::search_very_first_substring<var::character>(l_string, "Orange County");
	EXPECT_FALSE(l_result.has_value());

	l_result = ::FE::algorithm::string::search_very_first_substring<var::character>(l_string, "Utah");

	EXPECT_TRUE(FE::algorithm::string::string_comparison<char>(l_string + l_result->_begin, "Utah"));
}


//#define _IMPORT_RELEASE_BUILD_MODE_MSVC_COMPILER_BUG_
TEST(FE_algorithm_string, search_very_last_substring)
{
	const char* l_string = "Jesus is the son of GOD";
	FE::optional l_result = ::FE::algorithm::string::search_very_last_substring<var::character>(l_string, "son");
	char l_substring[7] = "\0";
	FE::algorithm::string::copy_string(l_substring, 4, l_string + l_result->_begin, 3);
	EXPECT_TRUE(FE::algorithm::string::string_comparison<char>(l_substring, "son"));

	l_string = "Third Person Spec Ops Stealth Action Shooter";

#ifndef _IMPORT_RELEASE_BUILD_MODE_MSVC_COMPILER_BUG_
	EXPECT_FALSE(::FE::algorithm::string::search_very_last_substring<var::character>(l_string, "Expects Failure").has_value());
#else
	l_result = ::FE::algorithm::string::search_very_last_substring<var::character>(l_string, "Expects Failure");
	EXPECT_FALSE(l_result.has_value());
#endif

	l_result = ::FE::algorithm::string::search_very_last_substring<var::character>(l_string, "Action");
	EXPECT_TRUE(l_result.has_value());
	FE::algorithm::string::copy_string(l_substring, 7, l_string + l_result->_begin, 6);

	EXPECT_TRUE(FE::algorithm::string::string_comparison<char>(l_substring, "Action"));
}




TEST(FE_algorithm_string, search_very_first_char_within_range)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::search_very_first_char_within_range(l_string, FE::algorithm::string::range{7, 15}, 'c');

	EXPECT_EQ(l_result._target_data, 'c');
	EXPECT_EQ(l_result._target_data_location, 8);
}




TEST(FE_algorithm_string, search_very_last_char_within_range)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = ::FE::algorithm::string::search_very_last_char_within_range(l_string, FE::algorithm::string::range{41, 49}, 'c');

	EXPECT_EQ(l_result._target_data, 'c');
	EXPECT_EQ(l_result._target_data_location, 42);
}




TEST(FE_algorithm_string, count_all_corresponding_chars_within_range)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = string::count_all_corresponding_chars_within_range(l_string, string::range{25, 49}, 't');

	EXPECT_EQ(l_result._match_count, 4);
	EXPECT_EQ(l_result._target_data, 't');
}

TEST(FE_algorithm_string, constexpr_count_all_corresponding_chars_within_range)
{
	char l_string[] = "Carrots contain carotene, antioxidants, etcetera.";

	auto l_result = string::count_all_corresponding_chars_within_range(l_string, string::range{25, 49}, 't');

	EXPECT_EQ(l_result._match_count, 4);
	EXPECT_EQ(l_result._target_data, 't');
}




TEST(FE_algorithm_string, search_very_first_substring_within_range)
{
	char l_string[] = "Love never fails. But where there are prophecies, they will cease; where there are tongues, they will be stilled; where there is knowledge, it will pass away.";

	FE::optional l_result = ::FE::algorithm::string::search_very_first_substring_within_range<var::character>(l_string, string::range{0, 17}, "Love never fails.");
	EXPECT_TRUE(l_result.has_value());

	l_result = ::FE::algorithm::string::search_very_first_substring_within_range<var::character>(l_string, string::range{0, 120}, "will");

	EXPECT_TRUE(FE::algorithm::string::compare_ranged_strings<char>(l_string, string::range{l_result->_begin, l_result->_end}, "will", string::range{0, 4}));
}

TEST(FE_algorithm_string, search_very_last_substring_within_range)
{
	const char* l_string = "Love is patient, love is kind. It does not envy, it does not boast, it is not proud. 5 It does not dishonor others, it is not self-seeking, it is not easily angered, it keeps no record of wrongs. 6 Love does not delight in evil but rejoices with the truth. 7 It always protects, always trusts, always hopes, always perseveres.\n";
	FE::optional l_result = ::FE::algorithm::string::search_very_last_substring_within_range<var::character>(l_string, string::range{0, 21}, "love");
	char l_substring[7] = "\0";
	FE::algorithm::string::copy_string(l_substring, 7, l_string + l_result->_begin, 4);
	EXPECT_TRUE(FE::algorithm::string::string_comparison<char>(l_substring, "love"));

	l_string = "1 Corinthians 13:4-8\n";
	l_result = ::FE::algorithm::string::search_very_last_substring_within_range<var::character>(l_string, string::range{0, 13}, "9");
	EXPECT_FALSE(l_result.has_value());

	l_result = ::FE::algorithm::string::search_very_last_substring_within_range<var::character>(l_string, string::range{2, 13}, "i");
	EXPECT_TRUE(l_result.has_value());
	FE::algorithm::string::copy_string(l_substring, 7, l_string + l_result->_begin, 1);

	EXPECT_TRUE(FE::algorithm::string::string_comparison<char>(l_substring, "i"));
}




TEST(FE_algorithm_string, concatenate_strings)
{
	char l_string_buffer[100] = "Today is";
	::FE::algorithm::string::concatenate_strings
	(
		l_string_buffer,
		100,
		{
			" May", " Fourteenth", " 2023."
		}
	);

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string_buffer, "Today is May Fourteenth 2023."));
}




TEST(FE_algorithm_string, concatenate_characters)
{
	char l_string_buffer[10] = "M";
	::FE::algorithm::string::concatenate_characters
	(
		l_string_buffer,
		10,
		{
			'e', 'l', 'o', 'n'
		}
	);

	EXPECT_TRUE(::FE::algorithm::string::string_comparison(l_string_buffer, "Melon"));
}


TEST(int_to_string, _)
{
	int l_int = -10000;
	char l_buffer[10] = "\0";
	string::int_to_string<char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "-10000"));

	memset(l_buffer, 0, 10);

	l_int = 10000;
	string::int_to_string<char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "10000"));
}

TEST(convert_uint_to_string, _)
{
	int l_int = 65165684;
	char l_buffer[10] = "\0";
	string::uint_to_string<char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "65165684"));

	memset(l_buffer, 0, 10);

	l_int = 45465;
	string::uint_to_string<char>(l_buffer, 10, l_int);
	EXPECT_TRUE(string::string_comparison(l_buffer, "45465"));
}


TEST(float_to_string, _)
{
	char l_buffer[30] = "\0";
	var::float32 l_pi = 3.14159f;
	string::float_to_string(l_buffer, sizeof(l_buffer), l_pi);
	std::memset(l_buffer + 7, 0, 4 * 1);

	EXPECT_TRUE(string::string_comparison(l_buffer, "3.14159"));
}

TEST(float_to_string, constexpr)
{
	char l_buffer[30] = "\0";
	string::constexpr_float_to_string<var::character>(l_buffer, sizeof(l_buffer), 356.768f);
	std::memset(l_buffer + 7, 0, 4 * 1);

	EXPECT_TRUE(string::string_comparison(l_buffer, "356.768"));
}


TEST(boolean_to_string, _)
{
	var::boolean l_is_true = true;
	EXPECT_TRUE(string::string_comparison(string::boolean_to_string<char>(l_is_true), "true"));
}

TEST(boolean_to_string, constexpr)
{
	EXPECT_TRUE(string::string_comparison(string::constexpr_boolean_to_string<char>(false), "false"));
}




TEST(any_primitive_to_string, thread_local_buffer)
{
	{
		const char* l_result_ptr = string::any_primitive_to_string<char>(true);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "true"));

		l_result_ptr = string::any_primitive_to_string<char>(1024);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "1024"));

		l_result_ptr = string::any_primitive_to_string<char>(3.14f);
		EXPECT_TRUE(string::compare_ranged_strings<char>(l_result_ptr, string::range{0, 4}, "3.14", string::range{0, 4}));

		l_result_ptr = string::any_primitive_to_string<char>('t');
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "t"));

		l_result_ptr = string::any_primitive_to_string<char>("hi, world");
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "hi, world"));


		std::unique_ptr<int> l_unique_pointer = std::make_unique<int>();
		l_result_ptr = string::any_primitive_to_string<char>(l_unique_pointer.get());

		char l_buffer[100] = "\0";
		std::snprintf(l_buffer, 100, "%p", l_unique_pointer.get());
		EXPECT_TRUE(string::string_comparison(l_result_ptr, l_buffer));


		l_result_ptr = string::any_primitive_to_string<char>(nullptr);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "nullptr"));
	}

	{
		var::boolean l_bool = false;
		const char* l_result_ptr = string::any_primitive_to_string<char>(l_bool);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "false"));

		var::int32 l_int32 = 1024;
		l_result_ptr = string::any_primitive_to_string<char>(l_int32);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "1024"));

		var::float32 l_float32 = 3.14f;
		l_result_ptr = string::any_primitive_to_string<char>(l_float32);
		EXPECT_TRUE(string::compare_ranged_strings<char>(l_result_ptr, string::range{0, 4}, "3.14", string::range{0, 4}));

		var::character l_character = 't';
		l_result_ptr = string::any_primitive_to_string<char>(l_character);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "t"));

		std::string hi_world = "hi, world";
		l_result_ptr = string::any_primitive_to_string<char>(hi_world.c_str());
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "hi, world"));


		std::unique_ptr<int> l_unique_pointer = std::make_unique<int>();
		l_result_ptr = string::any_primitive_to_string<char>(l_unique_pointer.get());

		char l_buffer[100] = "\0";
		std::snprintf(l_buffer, 100, "%p", l_unique_pointer.get());
		EXPECT_TRUE(string::string_comparison(l_result_ptr, l_buffer));


		l_result_ptr = string::any_primitive_to_string<char>(nullptr);
		EXPECT_TRUE(string::string_comparison(l_result_ptr, "nullptr"));
	}
}




TEST(any_to_string, thread_local_buffer)
{
	std::vector<std::unordered_map<std::string, void*>> l_complex;
	l_complex.emplace_back();
	const char* l_result_ptr = string::any_to_string<char>(l_complex);

	std::unique_ptr<var::character[]> l_unqiue_buffer(new var::character[_256_BYTES_BIT_COUNT_]{});
	string::any_object_binary_representation(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_complex);

	EXPECT_TRUE(string::string_comparison(l_result_ptr, l_unqiue_buffer.get()));
}




TEST(any_primitive_to_string, local_buffer)
{
	std::unique_ptr<var::character[]> l_unqiue_buffer(new var::character[_256_BYTES_BIT_COUNT_]{});


	{
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, true);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "true"));

		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, 1024);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "1024"));

		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, 3.14f);
		EXPECT_TRUE(string::compare_ranged_strings<char>(l_unqiue_buffer.get(), string::range{0, 4}, "3.14", string::range{0, 4}));

		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, 't');
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "t"));

		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, "hi, world");
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "hi, world"));


		std::unique_ptr<int> l_unique_pointer = std::make_unique<int>();
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_unique_pointer.get());

		char l_buffer[100] = "\0";
		std::snprintf(l_buffer, 100, "%p", l_unique_pointer.get());
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), l_buffer));


		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, nullptr);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "nullptr"));
	}


	{
		var::boolean l_bool = false;
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_bool);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "false"));

		var::int32 l_int32 = 1024;
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_int32);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "1024"));

		var::float32 l_float32 = 3.14f;
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_float32);
		EXPECT_TRUE(string::compare_ranged_strings<char>(l_unqiue_buffer.get(), string::range{0, 4}, "3.14", string::range{0, 4}));

		var::character l_character = 't';
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_character);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "t"));

		std::string hi_world = "hi, world";
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, hi_world.c_str());
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "hi, world"));


		std::unique_ptr<int> l_integral_address = std::make_unique<int>();
		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, l_integral_address.get());

		char l_answer[100] = "\0";
		std::snprintf(l_answer, 100, "%p", l_integral_address.get());
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), l_answer));


		string::any_primitive_to_string<char>(l_unqiue_buffer.get(), _256_BYTES_BIT_COUNT_, nullptr);
		EXPECT_TRUE(string::string_comparison(l_unqiue_buffer.get(), "nullptr"));
	}
}




TEST(any_to_string, local_buffer)
{
	std::unique_ptr<var::character[]> l_result_buffer(new var::character[_256_BYTES_BIT_COUNT_]{});
	std::vector<std::unordered_map<std::string, void*>> l_complex;
	l_complex.emplace_back();
	string::any_to_string<char>(l_result_buffer.get(), _256_BYTES_BIT_COUNT_, l_complex);

	std::unique_ptr<var::character[]> l_answer(new var::character[_256_BYTES_BIT_COUNT_]{});
	string::any_object_binary_representation(l_answer.get(), _256_BYTES_BIT_COUNT_, l_complex);

	EXPECT_TRUE(string::string_comparison(l_result_buffer.get(), l_answer.get()));
}




TEST(format_string_recursive, general)
{
	char l_student_id_buffer[_256_BYTES_BIT_COUNT_] = "\0";
	string::format_string_recursive(l_student_id_buffer, "Student ID: {%}\nDate of Birth: {%}\nGender: {%}\nCitizenship: {%}\nAddress: {%}", 20271084, 20130705, "female", "Republic Of Korea", nullptr);

	EXPECT_TRUE(string::string_comparison(l_student_id_buffer, "Student ID: 20271084\nDate of Birth: 20130705\nGender: female\nCitizenship: Republic Of Korea\nAddress: nullptr"));
}
