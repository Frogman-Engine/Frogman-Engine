#include <gtest/gtest.h>
#include <FE/core/string_view.hxx>
#include <FE/core/string.hxx>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.




TEST(basic_string_view, constructors_and_assignment)
{
	{
		FE::string l_string = "basic_string_view";
		FE::string_view l_string_view = l_string;
		EXPECT_TRUE(l_string_view == l_string);

		FE::string_view l_another_string_view = l_string_view;
		EXPECT_TRUE(l_another_string_view == l_string_view);
	}

	{
		FE::string l_string = "basic_string_view";
		FE::string_view l_string_view = l_string;
		EXPECT_TRUE(l_string_view == l_string);

		FE::string_view l_another_string_view = std::move(l_string_view);
		EXPECT_TRUE(l_another_string_view == l_string);
	}




	{
		FE::string l_string = "basic_string_view";
		FE::string_view l_string_view;
		l_string_view = l_string;
		EXPECT_TRUE(l_string_view == l_string);

		FE::string_view l_another_string_view;
		l_another_string_view = l_string_view;
		EXPECT_TRUE(l_another_string_view == l_string_view);
	}

	{
		FE::string l_string = "basic_string_view";
		FE::string_view l_string_view;
		l_string_view = l_string;
		EXPECT_TRUE(l_string_view == l_string);
		
		FE::string_view l_another_string_view;
		l_another_string_view = std::move(l_string_view);
		EXPECT_TRUE(l_another_string_view == l_string);
	}
}