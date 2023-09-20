﻿#include <gtest/gtest.h>
#include <FE/core/smart_pointers/smart_ptrs.h>
#include <vector>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.




TEST(exclusive_ptr, construct_by_value_assignment)
{
	using namespace FE;
	
	{
		{
			FE::exclusive_ptr<var::int64> l_exclusive_ptr = 64;
		}

		FE::exclusive_ptr<var::int64> l_exclusive_ptr;
		l_exclusive_ptr = 64;
	}


	{
		{
			FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = std::vector{ 1, 2, 3, 4, 5 };
		}

		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr;
		l_exclusive_ptr = { 1, 2, 3, 4, 5 };
	}
}




TEST(exclusive_ptr, release)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = std::vector{ 1, 2, 3, 4, 5 };
		FE::exclusive_ptr<std::vector<int>>::pointer l_pointer = l_exclusive_ptr.release();
		EXPECT_EQ(l_exclusive_ptr.get(), nullptr);
		FE::exclusive_ptr<std::vector<int>>::allocator_type::deallocate(l_pointer, 1);
	}
}




TEST(exclusive_ptr, reset)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = std::vector{ 1, 2, 3, 4, 5 };
		l_exclusive_ptr.reset();
		EXPECT_EQ(l_exclusive_ptr.get(), nullptr);
	}
}




TEST(exclusive_ptr, swap)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr;
		FE::exclusive_ptr<std::vector<int>> l_another = std::vector{ 1, 2, 3, 4, 5 };
		
		l_exclusive_ptr.swap(l_another);
		EXPECT_EQ((*l_exclusive_ptr)[0], 1);
	}
}




TEST(exclusive_ptr, make_exclusive)
{
	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = FE::make_exclusive<std::vector<int>>();

		EXPECT_FALSE(l_exclusive_ptr == nullptr);
	}

	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });

		EXPECT_FALSE(l_exclusive_ptr == nullptr);

		EXPECT_EQ((*l_exclusive_ptr)[0], 1);
	}
}








TEST(smart_ptr_variants, exclusive_ptr_and_proxy_ptrs)
{
	FE::proxy_ptr<std::vector<int>> l_first_proxy_ptr;
	FE::proxy_ptr<std::vector<int>> l_second_proxy_ptr;
	FE::proxy_ptr<std::vector<int>> l_third_proxy_ptr;

	{
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });
		l_first_proxy_ptr = l_exclusive_ptr;
		l_second_proxy_ptr = l_exclusive_ptr;
		l_third_proxy_ptr = l_second_proxy_ptr;
	}

	EXPECT_TRUE(l_first_proxy_ptr.is_expired());
	EXPECT_TRUE(l_second_proxy_ptr.is_expired());
	EXPECT_TRUE(l_third_proxy_ptr.is_expired());

	{
		FE::exclusive_ptr<std::vector<int>> l_first_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });
		FE::exclusive_ptr<std::vector<int>> l_second_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });
		l_first_proxy_ptr = l_second_exclusive_ptr;
		l_second_proxy_ptr = l_second_exclusive_ptr;
		l_third_proxy_ptr = l_second_proxy_ptr;

		EXPECT_FALSE(l_first_proxy_ptr.is_expired());
		EXPECT_FALSE(l_second_proxy_ptr.is_expired());
		EXPECT_FALSE(l_third_proxy_ptr.is_expired());

		FE::exclusive_ptr<std::vector<int>> l_third_exclusive_ptr = std::move(l_first_exclusive_ptr);

		EXPECT_FALSE(l_first_proxy_ptr.is_expired());
		EXPECT_FALSE(l_second_proxy_ptr.is_expired());
		EXPECT_FALSE(l_third_proxy_ptr.is_expired());

		EXPECT_TRUE(l_first_exclusive_ptr == nullptr);

		EXPECT_EQ((*l_first_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_second_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_third_proxy_ptr)[0], 1);
	}

	EXPECT_TRUE(l_first_proxy_ptr.is_expired());
	EXPECT_TRUE(l_second_proxy_ptr.is_expired());
	EXPECT_TRUE(l_third_proxy_ptr.is_expired());
}








TEST(exclusive_ptr, construct_array_by_value_assignment)
{
	using namespace FE;

	{
		{
			FE::exclusive_ptr<var::int64[]> l_exclusive_ptr = { 0, 1, 2, 3 };
		}

		FE::exclusive_ptr<var::int64[]> l_exclusive_ptr;
		l_exclusive_ptr = { 0, 1, 2, 3 };
	}

	{
		{
			FE::exclusive_ptr<std::string[]> l_exclusive_ptr = { "std::string" };
		}

		FE::exclusive_ptr<std::string[]> l_exclusive_ptr;
		l_exclusive_ptr = { "std::string" };
	}




	{
		FE::exclusive_ptr<var::int64[]> l_exclusive_ptr = FE::reserve{ 10 };
	}
}




TEST(smart_ptr_variants, release_array)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::string[]> l_exclusive_ptr = { "std::string" };
		FE::size_t l_prev_size = l_exclusive_ptr.size();

		FE::exclusive_ptr<std::string[]>::pointer l_pointer = l_exclusive_ptr.release();
		EXPECT_EQ(l_exclusive_ptr.get(), nullptr);
		FE::exclusive_ptr<std::string[]>::allocator_type::deallocate(l_pointer, l_prev_size);
	}
}




TEST(smart_ptr_variants, reset_array)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::string[]> l_exclusive_ptr = { "std::string" };
		l_exclusive_ptr.reset();
		EXPECT_EQ(l_exclusive_ptr.get(), nullptr);
	}
}




TEST(smart_ptr_variants, swap_array)
{
	using namespace FE;

	{
		FE::exclusive_ptr<std::string[]> l_exclusive_ptr = { "std::string" };
		FE::exclusive_ptr<std::string[]> l_another = { };

		l_exclusive_ptr.swap(l_another);
		EXPECT_EQ(strcmp(l_another[0].c_str(), "std::string"), 0);
	}
}




TEST(smart_ptr_variants, make_unique_array)
{
	{
		FE::exclusive_ptr<std::string[]> l_exclusive_ptr = FE::make_exclusive<std::string[]>(4);
		EXPECT_FALSE(l_exclusive_ptr == nullptr);
	}

	{
		FE::exclusive_ptr<std::string[]> l_exclusive_ptr = FE::make_exclusive<std::string[]>({ "std", "string" });

		EXPECT_FALSE(l_exclusive_ptr == nullptr);

		EXPECT_EQ(strcmp(l_exclusive_ptr[0].c_str(), "std"), 0);
		EXPECT_EQ(strcmp(l_exclusive_ptr[1].c_str(), "string"), 0);
	}
}









TEST(smart_ptr_variants, array_exclusive_ptr_and_proxy_ptrs)
{
	FE::proxy_ptr<std::vector<int>[]> l_first_proxy_ptr;
	FE::proxy_ptr<std::vector<int>[]> l_second_proxy_ptr;
	FE::proxy_ptr<std::vector<int>[]> l_third_proxy_ptr;

	{
		FE::exclusive_ptr<std::vector<int>[]> l_exclusive_ptr = FE::make_exclusive<std::vector<int>[]>(10);
		l_first_proxy_ptr = l_exclusive_ptr;
		l_second_proxy_ptr = l_exclusive_ptr;
		l_third_proxy_ptr = l_second_proxy_ptr;
	}

	EXPECT_TRUE(l_first_proxy_ptr.is_expired());
	EXPECT_TRUE(l_second_proxy_ptr.is_expired());
	EXPECT_TRUE(l_third_proxy_ptr.is_expired());
	
	{
		FE::exclusive_ptr<std::vector<int>[]> l_first_exclusive_ptr = FE::make_exclusive<std::vector<int>[]>({ std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 4, 5, 6 } });
		FE::exclusive_ptr<std::vector<int>[]> l_second_exclusive_ptr = FE::make_exclusive<std::vector<int>[]>({ std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 4, 5, 6 } });
		l_first_proxy_ptr = l_second_exclusive_ptr;
		l_second_proxy_ptr = l_second_exclusive_ptr;
		l_third_proxy_ptr = l_second_proxy_ptr;

		EXPECT_FALSE(l_first_proxy_ptr.is_expired());
		EXPECT_FALSE(l_second_proxy_ptr.is_expired());
		EXPECT_FALSE(l_third_proxy_ptr.is_expired());

		FE::exclusive_ptr<std::vector<int>[]> l_third_exclusive_ptr = std::move(l_first_exclusive_ptr);

		EXPECT_FALSE(l_first_proxy_ptr.is_expired());
		EXPECT_FALSE(l_second_proxy_ptr.is_expired());
		EXPECT_FALSE(l_third_proxy_ptr.is_expired());

		EXPECT_TRUE(l_first_exclusive_ptr == nullptr);

		EXPECT_EQ((*l_first_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_second_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_third_proxy_ptr)[0], 1);
	}

	EXPECT_TRUE(l_first_proxy_ptr.is_expired());
	EXPECT_TRUE(l_second_proxy_ptr.is_expired());
	EXPECT_TRUE(l_third_proxy_ptr.is_expired());


	//FE::exclusive_ptr<FE::var::int64[]>::shrink_to_fit_table();
	//FE::exclusive_ptr<std::string[]>::shrink_to_fit_table();
	//FE::exclusive_ptr<std::vector<int>[]>::shrink_to_fit_table();
}



