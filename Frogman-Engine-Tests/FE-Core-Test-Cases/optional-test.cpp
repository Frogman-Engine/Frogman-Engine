#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/optional.hxx>


_MAYBE_UNUSED_ inline static bool s_is_destructed = false;


struct my_optional_value
{
	~my_optional_value()
	{
		s_is_destructed = true;
	}
};


FE::optional<my_optional_value> fn()
{
	return std::move(my_optional_value{});
}


TEST(optional, return_)
{
	FE::optional<my_optional_value> l_opt;
	l_opt = fn();

	EXPECT_EQ(s_is_destructed, true);
}