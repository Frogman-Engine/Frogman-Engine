#include <gtest/gtest.h>
#include <FE/core/math.hxx>


TEST(math, abs)
{
	EXPECT_EQ(::FE::abs(-5), 5);
}


TEST(math, select_greatest)
{
	EXPECT_EQ( ::FE::select_greatest(5, 3), 5 );
}


TEST(math, select_smallest)
{
	EXPECT_EQ( ::FE::select_smallest(5, 3), 3 );
}


TEST(math, is_it_nearly_equal)
{
	EXPECT_TRUE(::FE::is_it_nearly_equal(3.14125f, 3.14120f, 0.0001));
}