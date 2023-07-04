#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/iterator.hxx>


TEST(iterator, std_vector_iteration)
{
	std::vector<int> l_vector = { 0, 1, 2, 3, 4, 5 };
	FE::iterator<FE::contiguous_iterator<int>> l_begin_iterator(l_vector.begin().operator->());
	FE::iterator<FE::contiguous_iterator<int>> l_end_iterator((l_vector.begin().operator->()) + l_vector.size());

	auto l_std_vector_iterator = l_vector.begin();
	for (auto it = l_begin_iterator; it != l_end_iterator; ++it)
	{
		EXPECT_EQ(*l_std_vector_iterator, *it);
		++l_std_vector_iterator;
	}

	for (auto it = l_end_iterator - 1; it != l_begin_iterator; --it)
	{
		--l_std_vector_iterator;
		EXPECT_EQ(*l_std_vector_iterator, *it);
	}

	FE::iterator<FE::contiguous_iterator<int>> l_iterator = l_begin_iterator + 1;
	EXPECT_EQ(*l_iterator, 1);

	l_iterator += 2;
	EXPECT_EQ(*l_iterator, 3);

	l_iterator -= 2;
	EXPECT_EQ(*l_iterator, 1);
}


TEST(reverse_iterator, std_vector_reverse_iteration)
{
	std::vector<int> l_vector = { 0, 1, 2, 3, 4, 5 };
	FE::reverse_iterator<FE::contiguous_iterator<int>> l_rbegin_iterator(l_vector.rbegin().operator->());
	FE::reverse_iterator<FE::contiguous_iterator<int>> l_rend_iterator(l_vector.begin().operator->());

	auto l_std_vector_reverse_iterator = l_vector.rbegin();
	for (auto it = l_rbegin_iterator; it != l_rend_iterator; ++it)
	{
		EXPECT_EQ(*l_std_vector_reverse_iterator, *it);
		++l_std_vector_reverse_iterator;
	}

	for (auto it = l_rend_iterator - 1; it != l_rbegin_iterator; --it)
	{
		--l_std_vector_reverse_iterator;
		EXPECT_EQ(*l_std_vector_reverse_iterator, *it);
	}

	FE::reverse_iterator<FE::contiguous_iterator<int>> l_reverse_iterator = l_rbegin_iterator + 1;
	EXPECT_EQ(*l_reverse_iterator, 4);

	l_reverse_iterator += 2;
	EXPECT_EQ(*l_reverse_iterator, 2);

	l_reverse_iterator -= 2;
	EXPECT_EQ(*l_reverse_iterator, 4);
}