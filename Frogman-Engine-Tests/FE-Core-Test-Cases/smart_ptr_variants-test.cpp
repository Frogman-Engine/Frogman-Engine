#include <gtest/gtest.h>
#include <FE/core/smart_pointers/exclusive_ptr.hxx>
#include <FE/core/smart_pointers/proxy_ptr.hxx>
#include <vector>




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
	
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	EXPECT_TRUE(l_first_proxy_ptr.is_expired());
	EXPECT_TRUE(l_second_proxy_ptr.is_expired());
	EXPECT_TRUE(l_third_proxy_ptr.is_expired());
#endif

	{
		FE::exclusive_ptr<std::vector<int>> l_first_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });
		FE::exclusive_ptr<std::vector<int>> l_exclusive_ptr = FE::make_exclusive<std::vector<int>>({ 1, 2, 3, 4, 5 });
		l_first_proxy_ptr = l_exclusive_ptr;
		l_second_proxy_ptr = l_exclusive_ptr;
		l_third_proxy_ptr = l_second_proxy_ptr;

		FE::exclusive_ptr<std::vector<int>> l_second_exclusive_ptr = std::move(l_first_exclusive_ptr);

		EXPECT_TRUE(l_first_exclusive_ptr == nullptr);

		EXPECT_EQ((*l_first_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_second_proxy_ptr)[0], 1);
		EXPECT_EQ((*l_third_proxy_ptr)[0], 1);
	}
}