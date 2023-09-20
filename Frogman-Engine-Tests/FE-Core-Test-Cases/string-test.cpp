#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/string.hxx>
#include <FE/core/clock.hpp>




TEST(basic_string, constructors)
{
	using namespace FE;

	FE::string::smart_pointer::reserve_table(FE::string::smart_pointer::ref_table_type::ref_table_initial_size);
	

	{
		FE::string l_string(count_t{ 3 }, 'A');
		EXPECT_TRUE(l_string == "AAA");
		FE::string l_another_string(l_string, index_t{ 1 });
		EXPECT_TRUE(l_another_string == "AA");
	}

	{
		FE::string l_string(count_t{ 3 }, 'A');
		EXPECT_TRUE(l_string == "AAA");
		FE::string l_another_string(std::move(l_string), index_t{ 1 });
		EXPECT_TRUE(l_another_string == "AA");
	}


	{
		FE::string l_string = "FE::basic_string<CharT, Allocator, traits>";
		EXPECT_TRUE(l_string == "FE::basic_string<CharT, Allocator, traits>");

		FE::string l_another_string(l_string, index_t{ 4 }, count_t{ 12 });
		EXPECT_TRUE(l_another_string == "basic_string");
	}

	{
		FE::string l_string = "FE::basic_string<CharT, Allocator, traits>";
		EXPECT_TRUE(l_string == "FE::basic_string<CharT, Allocator, traits>");

		FE::string l_another_string(std::move(l_string), index_t{ 4 }, count_t{ 12 });
		EXPECT_TRUE(l_another_string == "basic_string");
	}
	

	{
		FE::string l_string = "basic_string";
		FE::string l_another_string = l_string;
		EXPECT_TRUE(l_another_string == "basic_string");
	}

	{
		FE::string l_string = "basic_string";
		FE::string l_another_string = std::move(l_string);
		EXPECT_TRUE(l_another_string == "basic_string");
	}
	//FE::string::smart_pointer::shrink_to_fit_table();
}




TEST(basic_string, element_access)
{
	using namespace FE;

	FE::string l_string = "Cheese Cake";
	EXPECT_EQ(l_string[7], 'C');

	EXPECT_EQ(l_string.front(), 'C');
	EXPECT_EQ(l_string.back(), 'e');

	EXPECT_TRUE(algorithm::string::string_comparison(l_string.data(), "Cheese Cake"));
	EXPECT_TRUE(algorithm::string::string_comparison(l_string.c_str(), "Cheese Cake"));


	FE::string_view l_string_view = l_string;
}