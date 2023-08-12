#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/containers/queue.hxx>
#include <FE/core/cstring.hxx>
#include <FE/core/fstring.hxx>
#include <string>


TEST(queue, trivially_constructible_and_destructible)
{
	FE::queue<int, 10> l_queue = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	FE::queue<int, 10>::const_iterator l_const_queue_iterator_begin = l_queue.cbegin();
	FE::queue<int, 10>::const_iterator l_const_queue_iterator_end = l_queue.cend();

	FE::queue<int, 10>::const_reverse_iterator l_const_queue_iterator_rbegin = l_queue.crbegin();
	FE::queue<int, 10>::const_reverse_iterator l_const_queue_iterator_rend = l_queue.crend();

	{
		FE::queue<int, 10> l_copied_queue = l_queue;
		FE::queue<int, 10>::const_iterator l_const_copied_queue_iterator_begin = l_copied_queue.cbegin();
		FE::queue<int, 10>::const_iterator l_const_copied_queue_iterator_end = l_copied_queue.cend();

		int l_expected_value = 0;
		while(l_const_queue_iterator_begin != l_const_queue_iterator_end)
		{
			EXPECT_EQ(*l_const_queue_iterator_begin, l_expected_value++);
			EXPECT_EQ(*l_const_queue_iterator_begin, *l_const_copied_queue_iterator_begin);
			++l_const_queue_iterator_begin;
			++l_const_copied_queue_iterator_begin;
		}


		l_const_queue_iterator_begin = l_queue.cbegin();
		l_const_copied_queue_iterator_begin = l_copied_queue.cbegin();


		FE::queue<int, 10> l_moved_queue = std::move(l_copied_queue);
		FE::queue<int, 10>::const_iterator l_const_moved_queue_iterator_begin = l_moved_queue.cbegin();
		FE::queue<int, 10>::const_iterator l_const_moved_queue_iterator_end = l_moved_queue.cend();

		while (l_const_moved_queue_iterator_begin != l_const_moved_queue_iterator_end)
		{
			EXPECT_EQ(*l_const_moved_queue_iterator_begin, *l_const_queue_iterator_begin);
			++l_const_moved_queue_iterator_begin;
			++l_const_queue_iterator_begin;

			EXPECT_EQ(*l_const_copied_queue_iterator_begin, 0);
		}

		l_copied_queue = { 5, 4, 3, 2, 1 };
		FE::queue<int, 10>::swap(l_copied_queue, l_queue);
	}
}

TEST(queue, constructible_and_destructible)
{
	FE::queue<std::string, 5> l_queue = { "hi", ",", " ", "world", "."};
	FE::queue<std::string, 5>::const_iterator l_const_queue_iterator_begin = l_queue.cbegin();
	FE::queue<std::string, 5>::const_iterator l_const_queue_iterator_end = l_queue.cend();

	FE::queue<std::string, 5>::const_reverse_iterator l_const_queue_iterator_rbegin = l_queue.crbegin();
	FE::queue<std::string, 5>::const_reverse_iterator l_const_queue_iterator_rend = l_queue.crend();

	{
		FE::queue<std::string, 5> l_copied_queue = l_queue;
		FE::queue<std::string, 5>::const_iterator l_const_copied_queue_iterator_begin = l_copied_queue.cbegin();
		FE::queue<std::string, 5>::const_iterator l_const_copied_queue_iterator_end = l_copied_queue.cend();

		while (l_const_queue_iterator_begin != l_const_queue_iterator_end)
		{
			EXPECT_EQ(*l_const_queue_iterator_begin, *l_const_copied_queue_iterator_begin);
			++l_const_queue_iterator_begin;
			++l_const_copied_queue_iterator_begin;
		}


		l_const_queue_iterator_begin = l_queue.cbegin();
		l_const_copied_queue_iterator_begin = l_copied_queue.cbegin();


		FE::queue<std::string, 5> l_moved_queue = std::move(l_copied_queue);
		FE::queue<std::string, 5>::const_iterator l_const_moved_queue_iterator_begin = l_moved_queue.cbegin();
		FE::queue<std::string, 5>::const_iterator l_const_moved_queue_iterator_end = l_moved_queue.cend();

		while (l_const_moved_queue_iterator_begin != l_const_moved_queue_iterator_end)
		{
			EXPECT_EQ(*l_const_moved_queue_iterator_begin, *l_const_queue_iterator_begin);
			++l_const_moved_queue_iterator_begin;
			++l_const_queue_iterator_begin;

			EXPECT_EQ(*l_const_copied_queue_iterator_begin, "\0");
		}

		l_copied_queue = { "hello", ",", " ", "C++", "."};
		FE::queue<std::string, 5>::swap(l_copied_queue, l_queue);
	}
}


TEST(queue, push_pop)
{
	{
		FE::queue<int, 5> l_integral_queue;
		for (int i = 0; i < l_integral_queue.max_length(); ++i)
		{
			l_integral_queue.push(i);
		}

		std::size_t l_expected_value = 0;
		for (int i = 0; i < l_integral_queue.max_length(); ++i)
		{
			EXPECT_EQ(l_expected_value, l_integral_queue.pop());
			++l_expected_value;
		}

		for (int i = 0; i < l_integral_queue.max_length(); ++i)
		{
			l_integral_queue.push(i);
		}

		l_integral_queue.pop_all();

		FE::queue<int, 5>::const_reverse_iterator l_const_iterator_begin = l_integral_queue.crbegin();

#ifdef _DEBUG_
		while (l_const_iterator_begin != l_integral_queue.crend())
		{
			EXPECT_EQ(*l_const_iterator_begin, 0);
			++l_const_iterator_begin;
		}
#endif
	}


	std::initializer_list<FE::cstring> l_initializer_list = { "hello", ",", " ", "C++", "." };
	FE::queue<FE::cstring, 5> l_cstring_queue = { "hello", ",", " ", "C++", "." };
	FE::queue<FE::fstring<10>, 5> l_fstring_queue;

	FE::queue<FE::cstring, 5>::const_iterator L_cstring_const_iterator_begin = l_cstring_queue.cbegin();
	FE::queue<FE::fstring<10>, 5>::const_iterator L_fstring_const_iterator_begin = l_fstring_queue.cbegin();

	EXPECT_EQ(l_cstring_queue.max_length(), l_fstring_queue.max_length());

	for (int i = 0; i < l_cstring_queue.max_length(); ++i)
	{
		l_fstring_queue.push(l_cstring_queue.pop().c_str());

		EXPECT_TRUE(FE::algorithm::string::string_comparison(L_fstring_const_iterator_begin[i].c_str(), l_initializer_list.begin()[i].c_str()));
	}
}

TEST(queue, multiple_assignments_)
{
	FE::queue<std::string, 5> l_queue = { "hi", ",", " ", "world", "." };
	l_queue = { "hello", ",", " ", "C++", "." };
	EXPECT_TRUE(FE::algorithm::string::string_comparison((l_queue.cbegin())->c_str(), "hello"));
	EXPECT_TRUE(FE::algorithm::string::string_comparison((l_queue.cend() - 1)->c_str(), "."));
	{
		std::initializer_list<const char*> l_initializer_list = { "hello", ",", " ", "C++", "." };
		auto l_initializer_list_cbegin = l_initializer_list.begin();
		EXPECT_TRUE(FE::algorithm::string::string_comparison((l_queue.cend() - 1)->c_str(), "."));
		for (auto iterator = l_queue.cbegin(); iterator != l_queue.cend(); ++iterator)
		{
			EXPECT_TRUE(FE::algorithm::string::string_comparison<FE::var::character>(iterator->c_str(), *l_initializer_list_cbegin));
			++l_initializer_list_cbegin;
		}
	}


	FE::queue<std::string, 5> l_another_queue = { "hi", ",", " ", "world", "." };
	l_queue = std::move(l_another_queue);
	{
		std::initializer_list<const char*> l_initializer_list = { "hi", ",", " ", "world", "." };
		auto l_initializer_list_cbegin = l_initializer_list.begin();
		for (auto iterator = l_queue.cbegin(); iterator != l_queue.cend(); ++iterator)
		{
			EXPECT_TRUE(FE::algorithm::string::string_comparison<FE::var::character>(iterator->c_str(), *l_initializer_list_cbegin));
			++l_initializer_list_cbegin;
		}
	}
	l_queue = std::move(l_another_queue);
}

TEST(queue, container_comparison_)
{
	FE::queue<std::string, 5> l_languages1 = { "C++", "C#", "Python", "Java", "C"};
    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages1.front().c_str(), "C++"));
	FE::queue<std::string, 5> l_languages2 = { "C++", "C#", "Python", "Java", "C" };
    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages2.back().c_str(), "C"));
	EXPECT_TRUE(l_languages1 == l_languages2);

    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages1.pop().c_str(), "C++"));
    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages1.pop().c_str(), "C#"));
    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages1.pop().c_str(), "Python"));
    EXPECT_TRUE(FE::algorithm::string::string_comparison(l_languages1.pop().c_str(), "Java"));
    EXPECT_FALSE(l_languages1 == l_languages2); // C++ is not equivalent to C

	l_languages1.rearrange();
	l_languages1.push("Python");
	l_languages2.pop();
	EXPECT_TRUE(l_languages1 != l_languages2); // Python is not equivalent to Java
}