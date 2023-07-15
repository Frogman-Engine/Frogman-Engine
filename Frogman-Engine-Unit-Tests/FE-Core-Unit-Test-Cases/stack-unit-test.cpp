#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/containers/stack.hxx>
#include <FE/core/cstring.hxx>
#include <FE/core/fstring.hxx>
#include <string>


TEST(stack, trivially_constructible_and_destructible)
{
	FE::stack<int, 10> l_stack = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	FE::stack<int, 10>::const_iterator l_const_stack_iterator_begin = l_stack.cbegin();
	FE::stack<int, 10>::const_iterator l_const_stack_iterator_end = l_stack.cend();

	FE::stack<int, 10>::const_reverse_iterator l_const_stack_iterator_rbegin = l_stack.crbegin();
	FE::stack<int, 10>::const_reverse_iterator l_const_stack_iterator_rend = l_stack.crend();

	{
		FE::stack<int, 10> l_copied_stack = l_stack;
		FE::stack<int, 10>::const_iterator l_const_copied_stack_iterator_begin = l_copied_stack.cbegin();
		FE::stack<int, 10>::const_iterator l_const_copied_stack_iterator_end = l_copied_stack.cend();

		int l_expected_value = 0;
		while(l_const_stack_iterator_begin != l_const_stack_iterator_end)
		{
			EXPECT_EQ(*l_const_stack_iterator_begin, l_expected_value++);
			EXPECT_EQ(*l_const_stack_iterator_begin, *l_const_copied_stack_iterator_begin);
			++l_const_stack_iterator_begin;
			++l_const_copied_stack_iterator_begin;
		}


		l_const_stack_iterator_begin = l_stack.cbegin();
		l_const_copied_stack_iterator_begin = l_copied_stack.cbegin();


		FE::stack<int, 10> l_moved_stack = std::move(l_copied_stack);
		FE::stack<int, 10>::const_iterator l_const_moved_stack_iterator_begin = l_moved_stack.cbegin();
		FE::stack<int, 10>::const_iterator l_const_moved_stack_iterator_end = l_moved_stack.cend();

		while (l_const_moved_stack_iterator_begin != l_const_moved_stack_iterator_end)
		{
			EXPECT_EQ(*l_const_moved_stack_iterator_begin, *l_const_stack_iterator_begin);
			++l_const_moved_stack_iterator_begin;
			++l_const_stack_iterator_begin;

			EXPECT_EQ(*l_const_copied_stack_iterator_begin, 0);
		}

		l_copied_stack = { 5, 4, 3, 2, 1 };
		FE::stack<int, 10>::swap(l_copied_stack, l_stack);
	}
}

TEST(stack, constructible_and_destructible)
{
	FE::stack<std::string, 5> l_stack = { "hi", ",", " ", "world", "."};
	FE::stack<std::string, 5>::const_iterator l_const_stack_iterator_begin = l_stack.cbegin();
	FE::stack<std::string, 5>::const_iterator l_const_stack_iterator_end = l_stack.cend();

	FE::stack<std::string, 5>::const_reverse_iterator l_const_stack_iterator_rbegin = l_stack.crbegin();
	FE::stack<std::string, 5>::const_reverse_iterator l_const_stack_iterator_rend = l_stack.crend();

	{
		FE::stack<std::string, 5> l_copied_stack = l_stack;
		FE::stack<std::string, 5>::const_iterator l_const_copied_stack_iterator_begin = l_copied_stack.cbegin();
		FE::stack<std::string, 5>::const_iterator l_const_copied_stack_iterator_end = l_copied_stack.cend();

		while (l_const_stack_iterator_begin != l_const_stack_iterator_end)
		{
			EXPECT_EQ(*l_const_stack_iterator_begin, *l_const_copied_stack_iterator_begin);
			++l_const_stack_iterator_begin;
			++l_const_copied_stack_iterator_begin;
		}


		l_const_stack_iterator_begin = l_stack.cbegin();
		l_const_copied_stack_iterator_begin = l_copied_stack.cbegin();


		FE::stack<std::string, 5> l_moved_stack = std::move(l_copied_stack);
		FE::stack<std::string, 5>::const_iterator l_const_moved_stack_iterator_begin = l_moved_stack.cbegin();
		FE::stack<std::string, 5>::const_iterator l_const_moved_stack_iterator_end = l_moved_stack.cend();

		while (l_const_moved_stack_iterator_begin != l_const_moved_stack_iterator_end)
		{
			EXPECT_EQ(*l_const_moved_stack_iterator_begin, *l_const_stack_iterator_begin);
			++l_const_moved_stack_iterator_begin;
			++l_const_stack_iterator_begin;

			EXPECT_EQ(*l_const_copied_stack_iterator_begin, "\0");
		}

		l_copied_stack = { "hello", ",", " ", "C++", "."};
		FE::stack<std::string, 5>::swap(l_copied_stack, l_stack);
	}
}


TEST(stack, push_pop)
{
	{
		FE::stack<int, 5> l_integral_stack;
		for (int i = 0; i < l_integral_stack.max_length(); ++i)
		{
			l_integral_stack.push(i);
		}

		std::size_t l_expected_value = l_integral_stack.max_length();
		for (int i = 0; i < l_integral_stack.max_length(); ++i)
		{
			--l_expected_value;
			EXPECT_EQ(l_expected_value, l_integral_stack.pop());
		}

		for (int i = 0; i < l_integral_stack.max_length(); ++i)
		{
			l_integral_stack.push(i);
		}

		l_integral_stack.pop_all();

		FE::stack<int, 5>::const_reverse_iterator l_const_iterator_begin = l_integral_stack.crbegin();

		while (l_const_iterator_begin != l_integral_stack.crend())
		{
			EXPECT_EQ(*l_const_iterator_begin, 0);
			++l_const_iterator_begin;
		}
	}


	std::initializer_list<FE::cstring> l_initializer_list = { "hello", ",", " ", "C++", "." };
	FE::stack<FE::cstring, 5> l_cstring_stack = { ".", "C++", " ", ",", "hello" };
	FE::stack<FE::fstring<10>, 5> l_fstring_stack;

	FE::stack<FE::cstring, 5>::const_iterator L_cstring_const_iterator_begin = l_cstring_stack.cbegin();
	FE::stack<FE::fstring<10>, 5>::const_iterator L_fstring_const_iterator_begin = l_fstring_stack.cbegin();

	EXPECT_EQ(l_cstring_stack.max_length(), l_fstring_stack.max_length());

	for (int i = 0; i < l_cstring_stack.max_length(); ++i)
	{
		l_fstring_stack.push(l_cstring_stack.pop().c_str());
		
		EXPECT_TRUE(FE::algorithm::string::string_comparison(L_fstring_const_iterator_begin[i].c_str(), l_initializer_list.begin()[i].c_str()));
	}
}

TEST(stack, multiple_assignments_)
{
	FE::stack<std::string, 5> l_stack = { "hi", ",", " ", "world", "." };
	l_stack = { "hello", ",", " ", "C++", "." };
	{
		std::initializer_list<const char*> l_initializer_list = { "hello", ",", " ", "C++", "." };
		auto l_initializer_list_cbegin = l_initializer_list.begin();
		for (auto iterator = l_stack.cbegin(); iterator != l_stack.cend(); ++iterator)
		{
			EXPECT_TRUE(FE::algorithm::string::string_comparison<FE::var::character>(iterator->c_str(), *l_initializer_list_cbegin));
			++l_initializer_list_cbegin;
		}
	}


	FE::stack<std::string, 5> l_another_stack = { "hi", ",", " ", "world", "." };
	l_stack = std::move(l_another_stack);
	{
		std::initializer_list<const char*> l_initializer_list = { "hi", ",", " ", "world", "." };
		auto l_initializer_list_cbegin = l_initializer_list.begin();
		for (auto iterator = l_stack.cbegin(); iterator != l_stack.cend(); ++iterator)
		{
			EXPECT_TRUE(FE::algorithm::string::string_comparison<FE::var::character>(iterator->c_str(), *l_initializer_list_cbegin));
			++l_initializer_list_cbegin;
		}
	}
	l_stack = std::move(l_another_stack);
}

TEST(stack, container_comparison_)
{
	FE::stack<std::string, 5> l_languages1 = { "C++", "C#", "Python", "Java", "C"};
	FE::stack<std::string, 5> l_languages2 = { "C++", "C#", "Python", "Java", "C" };
	EXPECT_TRUE(l_languages1 == l_languages2);

	l_languages1.pop();
	l_languages1.pop();
	l_languages1.pop();
	l_languages1.pop();
	EXPECT_FALSE(l_languages1 == l_languages2); // C++ is not equivalent to C

	l_languages1.push("Python");
	l_languages2.pop();
	EXPECT_TRUE(l_languages1 != l_languages2); // Python is not equivalent to Java
}