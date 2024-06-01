#include <gtest/gtest.h>
#include <benchmark/benchmark.h>


// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/containers/array.hxx>
#include <FE/core/string.hxx>
#include <FE/core/fstring.hxx>
using namespace FE;
using namespace algorithm;


// std
#include <string>


_MAYBE_UNUSED_ constexpr auto _TEST_FSTRING_LENGTH_ = 128;
/*
Profile Guided Optimization: https://learn.microsoft.com/en-us/cpp/build/profile-guided-optimizations?view=msvc-170

TO DO: 
1. variable table
                                 
																														  |--- int32 variable hash map
																														  |--- float64 variable hash map
																														  |--- FE::string variable hash map
std::unordered_map<Key: type name string, Value: std::unordered_map<Key: varaible name string, Value: varaible address>> -|--- FE::array variable hash map
																														  |--- std::list variable hash map
																														  |--- std::deque variable hash map
2. memory layout reflection for serialization  																		      |--- etc...
                                                                                      *
	                                                                                  |
	Shallower <----- Memory Hierarchy Depth ----> Deeper                      Lower Memory Address
                                                      |----------------|              |
	                                                  | - FE::string - |              |
	|----------------------------------|    ----------|FE::smart_ptr   |              |
	|  Target Entry Non-Trivial Object |    |         |length, capacity|              |
	|- member variables -              |    |         |----------------|              |
	|  FE::string m_name --------------|----|                                         |
	|  FE::vector<float64, 3> m_vector |-------|                                      |
	|----------------------------------|       |       |----------------|             |
	                                           |       | - FE::vector - |             |
											   |-------| x              |             |
													   | y              |             |
													   | z              |             |
													   |----------------|     Higher Memory Address
													                                  |
																					  *
																					  
Memory Layer Traversal Order: Entry.FE::string m_name -> FE::string.FE::smart_ptr -> FE::smart_ptr.m_smart_ptr data 
																									|
												    |-----------------------------------------------|
												    |
												    |--> FE::string.length -> FE::string.capacity
																					   |
																					   |
									           |---------------------------------------|
											   |
											   |--> FE::vector.x -> FE::vector.y -> FE::vector.z
*/ 
int main(int argc_p, char** argv_p)
{
	using namespace FE;

	std::cout << "Compilation test of FE.core.pool_test source code is successful.\n";
  	testing::InitGoogleTest(&argc_p, argv_p);

	if (argv_p == nullptr)
	{
		char l_arg0_default[] = "benchmark";
		char* l_args_default = l_arg0_default;
		argc_p = 1;
		argv_p = &l_args_default;
	}
	
    benchmark::Initialize(&argc_p, argv_p);
	FE_ABORT_IF(benchmark::ReportUnrecognizedArguments(argc_p, argv_p) == true, "Failed to meet the expectation: Unrecognized Benchmark Arguments Detected.");
    int32 l_exit_code = RUN_ALL_TESTS();
	std::cerr << "\n\n";
	benchmark::RunSpecifiedBenchmarks();
	std::cerr << "\n\n";
    benchmark::Shutdown();
    return l_exit_code;
}








TEST(fstring, constructor)
{
	{
		FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

		EXPECT_TRUE(l_fstring == "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.");
	}

	character* l_str = "Pizza";
	FE::const_iterator<FE::contiguous_iterator<character>> l_cbegin{ l_str };
	FE::const_iterator<FE::contiguous_iterator<character>> l_cend{ l_str  + strlen(l_str)};

	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring(l_cbegin, l_cend);

	EXPECT_TRUE(l_fstring == "Pizza");
}


TEST(fstring, constructor_assignment)
{
	FE::fstring<_TEST_FSTRING_LENGTH_>::value_type l_buffer[] = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = l_buffer;

	EXPECT_TRUE(l_fstring == l_buffer);
}


TEST(fstring, copy_constructor)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_subject = l_fstring;

	EXPECT_TRUE(l_subject == l_fstring);
}


TEST(fstring, move_constructor)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_subject = std::move(l_fstring);

	EXPECT_FALSE(l_subject == l_fstring);
}


TEST(fstring, copy_assignment_operator)
{
	FE::fstring<_TEST_FSTRING_LENGTH_>::value_type l_buffer[] = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring = l_buffer;

	EXPECT_TRUE(l_fstring == l_buffer);
}


TEST(fstring, assignment_operator)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template." == l_fstring);
}


TEST(fstring, index_operator)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	EXPECT_EQ(l_fstring[4], 'f');
}


TEST(fstring, assign)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring.assign(3, '?');

	EXPECT_TRUE("???" == l_fstring);

	l_fstring.clear();
	l_fstring.assign("C++ 20", 3);
	
	EXPECT_TRUE("C++" == l_fstring);


	FE::fstring<_TEST_FSTRING_LENGTH_> l_other = "A bottle of water from the United Kingdom";
	l_fstring.clear();
	l_fstring.assign(l_other, 0, 41);
	EXPECT_TRUE("A bottle of water from the United Kingdom" == l_fstring);

	l_fstring.assign("Hi, World.", 0, 10);
	EXPECT_TRUE("Hi, World." == l_fstring);

	l_fstring.clear();
	l_fstring.assign("A bottle of water", 8);
	EXPECT_TRUE("A bottle" == l_fstring);

	l_fstring.clear();
	l_fstring.assign(l_other.cbegin() + 23, l_other.cend());
	EXPECT_TRUE("the United Kingdom" == l_fstring);

	l_fstring.clear();
	l_fstring.assign({'C', '/', 'C', '+', '+'});
	EXPECT_TRUE("C/C++" == l_fstring);
}


TEST(fstring, assign_range)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring;
	l_fstring.assign_range("C# is awesome.", string::range{ 3, 14 });
	EXPECT_TRUE("is awesome." == l_fstring);
}


TEST(fstring, insert)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "etreme programming is a banana.";
	l_fstring.insert(1, 1, 'x');
	EXPECT_TRUE("extreme programming is a banana." == l_fstring);

	l_fstring = "TDD is T Driven Development";
	l_fstring.insert(8, "ime-Inefficiency");
	EXPECT_TRUE("TDD is Time-Inefficiency Driven Development" == l_fstring);

	EXPECT_EQ(l_fstring.length(), strlen(l_fstring.c_str()));

	l_fstring = "Unit testing is  TDD";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_not = "not";
	l_fstring.insert(16, l_not);
	EXPECT_TRUE("Unit testing is not TDD" == l_fstring);

	l_fstring.insert(0, "Unit testing is not TDD", 0, 12);
	EXPECT_TRUE("Unit testingUnit testing is not TDD" == l_fstring);

	l_fstring.insert(12, { ' ', 'f', 'r', 'a', 'm', 'e', 'w', 'o', 'r', 'k'});

	EXPECT_TRUE("Unit testing frameworkUnit testing is not TDD" == l_fstring);
}


TEST(fstring, insert_range)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "C++ 20";
	l_fstring.insert_range(l_fstring.length(), "C# is awesome.", string::range{ 2, 14 });
	EXPECT_TRUE("C++ 20 is awesome." == l_fstring);
}


TEST(fstring, front_back)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	FE::fstring<_TEST_FSTRING_LENGTH_>::value_type l_buffer[3] = "\0";
	string::concatenate<FE::fstring<_TEST_FSTRING_LENGTH_>::value_type>(l_buffer, 3, { l_fstring.front(), l_fstring.back() });

	EXPECT_EQ(0, strcmp(l_buffer, "F."));
}


TEST(fstring, c_str)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_TRUE(::FE::algorithm::string::compare("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));

	EXPECT_TRUE(::FE::algorithm::string::compare("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.c_str()));
}


TEST(fstring, begin_end)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_>::value_type l_buffer[_TEST_FSTRING_LENGTH_] = "\0";
	
	FE::var::index_t l_idx = 0;
	for (auto character = l_fstring.begin(); character < l_fstring.end(); ++character)
	{
		character < l_fstring.end();
		l_buffer[l_idx] = *character;
		++l_idx;
	}

	EXPECT_TRUE(l_fstring == l_buffer);
}


TEST(fstring, capacity_clear_and_is_empty)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.";

	EXPECT_EQ(l_fstring.capacity(), _TEST_FSTRING_LENGTH_);

	l_fstring.clear();

	EXPECT_EQ(l_fstring.is_empty(), true);
}


TEST(fstring, push_pop_back)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template";
	l_fstring.push_back('.');

	EXPECT_EQ(0, strcmp("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));

	EXPECT_EQ(l_fstring.pop_back(), '.');
}


TEST(fstring, concatenation)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a";
	l_fstring += " fixed sized string class template.";

	EXPECT_EQ(0, strcmp("FE::fstring<_UNIT_TEST_FSTRING_LENGTH_> is a fixed sized string class template.", l_fstring.data()));
}


TEST(fstring, starts_with)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_substring = "FE";

	EXPECT_TRUE(l_fstring.starts_with(l_substring));

	EXPECT_TRUE(l_fstring.starts_with("FE::"));

	EXPECT_TRUE(l_fstring.starts_with('F'));

	EXPECT_FALSE(l_fstring.starts_with('E'));
}


TEST(fstring, ends_with)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_substring = "template.";

	EXPECT_TRUE(l_fstring.ends_with(l_substring));

	EXPECT_TRUE(l_fstring.ends_with("template."));

	EXPECT_TRUE(l_fstring.ends_with('.'));

	EXPECT_FALSE(l_fstring.ends_with("%d"));
}


TEST(fstring, contains)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_substring = "string";

	EXPECT_TRUE(l_fstring.contains(l_substring));
			
	EXPECT_TRUE(l_fstring.contains("a string class template."));
			
	EXPECT_TRUE(l_fstring.contains('i'));

	EXPECT_FALSE(l_fstring.contains('?'));
}


TEST(fstring, substr)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_another = l_fstring.substr(index_t{ 24 }, count_t{ 5 });
	EXPECT_TRUE(l_another == "class");
}


TEST(fstring, copy)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_>::value_type l_buffer[20] = "\0";
	l_fstring.copy(l_buffer, capacity_t{20}, count_t{ 5 }, index_t{ 24 });
	EXPECT_EQ(0, strcmp(l_buffer, "class"));
}


TEST(fstring, find)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_substring = "fstring";

	std::optional<string::range> l_search_result = l_fstring.find(l_substring);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_EQ(0, string::compare_ranged(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	l_substring = "string";
	l_search_result.reset();
	l_search_result = *(l_fstring.find(l_substring, 10));

	EXPECT_EQ(0, string::compare_ranged(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));
}


TEST(fstring, rfind)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_substring = "string class";

	std::optional<string::range> l_search_result = l_fstring.rfind(l_substring);
	EXPECT_TRUE(l_search_result.has_value());

	EXPECT_EQ(0, string::compare_ranged(l_fstring.data(), *l_search_result, l_substring.data(), string::range{0, l_substring.length()}));


	std::optional<algorithm::string::range> l_result2 = l_fstring.rfind('t', FE::index_t{10});

	EXPECT_EQ(l_fstring[l_result2->_begin], 't');
}


TEST(fstring, count_chars)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "FE::fstring is a string class template.";

	EXPECT_EQ((l_fstring.count_chars('s'))->_match_count, 5);

	index_t l_from = 20;
	EXPECT_EQ((l_fstring.count_chars('s', l_from))->_match_count, 2);
}


TEST(fstring, swap)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_first_fstring = "ABC";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_second_fstring = "CBA";

	l_first_fstring.swap(l_second_fstring);

	EXPECT_TRUE(l_first_fstring == "CBA");
}


TEST(fstring, erase)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_first_fstring = "FE::fstring is a fixed-sized string class template.";
	l_first_fstring.erase(index_t{ 17 }, count_t{ 12 });

	EXPECT_TRUE(l_first_fstring == "FE::fstring is a string class template.");
}


TEST(fstring, append)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "COD Modern Warfare is my favorite ";
	l_fstring.append(3, 'A');
	EXPECT_TRUE(l_fstring == "COD Modern Warfare is my favorite AAA");


	FE::fstring<_TEST_FSTRING_LENGTH_> l_second_fstring = " shooter game.";
	l_fstring += l_second_fstring;
	EXPECT_TRUE(l_fstring == "COD Modern Warfare is my favorite AAA shooter game.");




	l_second_fstring = "Another my favorite ";
	l_second_fstring.append(l_fstring, 34, 3);
	EXPECT_TRUE(l_second_fstring == "Another my favorite AAA");


	l_second_fstring.append(" title is ", 0, 6);
	EXPECT_TRUE(l_second_fstring == "Another my favorite AAA title");


	l_second_fstring += " is Tom Clancy's";
	EXPECT_TRUE(l_second_fstring == "Another my favorite AAA title is Tom Clancy's");


	char l_string[] = " Ghost Recon: ";
	l_second_fstring.append(FE::const_iterator<FE::contiguous_iterator<char>>{l_string}, FE::const_iterator<FE::contiguous_iterator<char>>{l_string + 14});
	EXPECT_TRUE(l_second_fstring == "Another my favorite AAA title is Tom Clancy's Ghost Recon: ");


	l_second_fstring.append({'F', 'u', 't', 'u', 'r', 'e', ' ', 'S', 'o', 'l', 'd', 'i', 'e', 'r', '.'});
	EXPECT_TRUE(l_second_fstring == "Another my favorite AAA title is Tom Clancy's Ghost Recon: Future Soldier.");
}


TEST(fstring, append_range)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "Design patterns are";
	l_fstring.append_range("They are not silver bullets.", string::range{8, 28});
	EXPECT_TRUE(l_fstring == "Design patterns are not silver bullets.");
}


TEST(fstring, replace)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "Java";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_other = "ellyfish";
	l_fstring.replace(1, 3, l_other);
	EXPECT_TRUE(l_fstring == "Jellyfish");


	FE::fstring<_TEST_FSTRING_LENGTH_> l_javachip = "Javachip";
	l_fstring.replace(1, 4, l_javachip, 1, 3);
	EXPECT_TRUE(l_fstring == "Javafish");


	l_fstring.replace(4, 4, "fish & chips", 12);
	EXPECT_TRUE(l_fstring == "Javafish & chips");


	l_fstring.replace(1, 9, "arvis");
	EXPECT_TRUE(l_fstring == "Jarvis chips");

	
	l_fstring = "boh!";
	l_fstring.replace(1, 1, 'a',2);
	EXPECT_TRUE(l_fstring == "baah!");


	l_fstring = "C#";
	l_fstring.replace(1, 1, { '+', '+' });
	EXPECT_TRUE(l_fstring == "C++");
	

	FE::fstring<_TEST_FSTRING_LENGTH_> l_carbon = "Carbon";
	l_fstring.replace(1, 3, l_carbon.cbegin() + 1, l_carbon.cend());
	EXPECT_TRUE(l_fstring == "Carbon");
}


TEST(fstring, replace_with_range)
{
	FE::fstring<_TEST_FSTRING_LENGTH_> l_fstring = "Javascript";
	FE::fstring<_TEST_FSTRING_LENGTH_> l_other = "Typescript";

	l_fstring.replace_with_range(0, 4, l_other, string::range{ 0, 4 });
	EXPECT_TRUE(l_fstring == "Typescript");


	l_fstring = "x86 assembly";
	l_fstring.replace_with_range(3, 1, "-64 bit", string::range{ 0, 4 });
	EXPECT_TRUE(l_fstring == "x86-64 assembly");

	l_other = "an avx-512 SIMD instruction";
	l_fstring.replace_with_range(8, 7, l_other, string::range{4, 10});
	EXPECT_TRUE(l_fstring == "x86-64 avx-512");
}




void std_string_construction_and_destruction(benchmark::State& state_p) noexcept
{
	for (auto _ : state_p)
	{
		std::string l_string = "string performance competition";
		benchmark::DoNotOptimize(l_string);
	}
}
BENCHMARK(std_string_construction_and_destruction);


void fstring_construction_and_destruction(benchmark::State& state_p) noexcept
{
	for (auto _ : state_p)
	{
		FE::fstring<64> l_string = "string performance competition";
		benchmark::DoNotOptimize(l_string);
	}
}
BENCHMARK(fstring_construction_and_destruction);




void std_string_assignment(benchmark::State& state_p) noexcept
{
	std::string l_string;
	benchmark::DoNotOptimize(l_string);

	for (auto _ : state_p)
	{
		l_string = "string performance competition";
	}
}
BENCHMARK(std_string_assignment);


void fstring_assignment(benchmark::State& state_p) noexcept
{
	FE::fstring<64> l_string;
	benchmark::DoNotOptimize(l_string);

	for (auto _ : state_p)
	{
		l_string = "string performance competition";
	}
}
BENCHMARK(fstring_assignment);



void std_string_find(benchmark::State& state_p) noexcept
{
	std::string l_string = "You can run, but you can't hide.";
	benchmark::DoNotOptimize(l_string);

	for (auto _ : state_p)
	{
		auto l_result = l_string.find("but");
		benchmark::DoNotOptimize(l_result);
	}
}
BENCHMARK(std_string_find);


void fstring_find(benchmark::State& state_p) noexcept
{
	FE::fstring<64> l_string = "You can run, but you can't hide.";
	benchmark::DoNotOptimize(l_string);

	for (auto _ : state_p)
	{
		auto l_result = l_string.find("but");
		benchmark::DoNotOptimize(l_result);
	}
}
BENCHMARK(fstring_find);














TEST(farray, all)
{
	{
		FE::farray<const char*, 64> l_array;
		l_array.push_back("Pizza");
		
		EXPECT_TRUE(FE::algorithm::string::compare(l_array.back(), "Pizza"));
		l_array.pop_back();
	}
}


TEST(array, constructor_and_destructor)
{
	{
		FE::array<FE::string> l_array;
	}

	{
		FE::array<FE::string> l_array(2, "A bottle of water");
		EXPECT_TRUE(l_array[0] == "A bottle of water");
		EXPECT_TRUE(l_array[1] == "A bottle of water");
	}

	{
		std::initializer_list<FE::string> l_initializer_list = {"A", "bottle", "of", "water"};
		FE::array<FE::string> l_array(l_initializer_list.begin(), l_initializer_list.end());
		
		EXPECT_TRUE(l_array[0] == "A");
		EXPECT_TRUE(l_array[1] == "bottle");
		EXPECT_TRUE(l_array[2] == "of");
		EXPECT_TRUE(l_array[3] == "water");

	}

	{
		FE::array<FE::string> l_array(2, "A bottle of water");
		FE::array<FE::string> l_another_array = l_array;
		EXPECT_TRUE(l_another_array[0] == "A bottle of water");
		EXPECT_TRUE(l_another_array[1] == "A bottle of water");
	}

	{
		FE::array<FE::string> l_array(2, "A bottle of water");
		FE::array<FE::string> l_another_array = std::move(l_array);
		EXPECT_TRUE(l_another_array[0] == "A bottle of water");
		EXPECT_TRUE(l_another_array[1] == "A bottle of water");
	}

	{
		FE::array<FE::string> l_array = { "A", "bottle", "of", "water" };
		EXPECT_TRUE(l_array[0] == "A");
		EXPECT_TRUE(l_array[1] == "bottle");
		EXPECT_TRUE(l_array[2] == "of");
		EXPECT_TRUE(l_array[3] == "water");
	}

	{
		FE::array<FE::string> l_array(2, "A bottle of water");
		FE::array<FE::string> l_another_array;
		l_another_array = l_array;
		EXPECT_TRUE(l_another_array[0] == "A bottle of water");
		EXPECT_TRUE(l_another_array[1] == "A bottle of water");
	}

	{
		FE::array<FE::string> l_array(2, "A bottle of water");
		FE::array<FE::string> l_another_array;
		l_another_array = std::move(l_array);
		EXPECT_TRUE(l_another_array[0] == "A bottle of water");
		EXPECT_TRUE(l_another_array[1] == "A bottle of water");
	}

	{
		FE::array<FE::string> l_array;
		l_array = { "A", "bottle", "of", "water" };
		EXPECT_TRUE(l_array[0] == "A");
		EXPECT_TRUE(l_array[1] == "bottle");
		EXPECT_TRUE(l_array[2] == "of");
		EXPECT_TRUE(l_array[3] == "water");
	}
}




TEST(array, Element_access)
{
	{
		FE::array<FE::string> l_array;
		l_array.reserve(2);
		l_array.assign(2, "A bottle of water");

		EXPECT_TRUE(l_array[0] == "A bottle of water");
		EXPECT_TRUE(l_array[1] == "A bottle of water");
	}

	{
		std::initializer_list<FE::string> l_initializer_list = { "A", "bottle", "of", "water" };
		FE::array<FE::string> l_array;
		l_array.reserve(8);
		l_array.assign(l_initializer_list.begin(), l_initializer_list.end());

		EXPECT_TRUE(l_array[0] == "A");
		EXPECT_TRUE(l_array[1] == "bottle");
		EXPECT_TRUE(l_array[2] == "of");
		EXPECT_TRUE(l_array[3] == "water");
	}

	{
		FE::array<FE::string> l_array;
		l_array.reserve(8);
		l_array.assign({ "A", "bottle", "of", "water" });

		EXPECT_TRUE(l_array[0] == "A");
		EXPECT_TRUE(l_array[1] == "bottle");
		EXPECT_TRUE(l_array[2] == "of");
		EXPECT_TRUE(l_array[3] == "water");

	}

	{
		FE::array<FE::string> l_array = { "A", "bottle", "of", "water" };

		FE::array<FE::string> l_another_array;
		l_another_array.reserve(8);
		l_another_array.assign_range(l_array.make_range(FE::index_t{ 1 }, FE::index_t{ 4 }));


		EXPECT_TRUE(l_another_array.front() == "bottle");
		EXPECT_TRUE(l_another_array[1] == "of");
		EXPECT_TRUE(l_another_array.back() == "water");
		EXPECT_TRUE(l_another_array.data()[0] == "bottle");
	}
}




TEST(array, Iterators)
{
	{
		FE::array<FE::string> l_array = { "A", "bottle", "of", "water" };
		std::initializer_list<FE::string> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto value : l_array)
		{
			EXPECT_TRUE(value == *l_l_initializer_list_iterator);
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<FE::string> l_array = { "A", "bottle", "of", "water" };
		std::initializer_list<FE::string> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.cbegin(); it != l_array.cend(); ++it)
		{
			EXPECT_TRUE(*it == *l_l_initializer_list_iterator);
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<FE::string> l_array = { "water", "of", "bottle", "A" };
		std::initializer_list<FE::string> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.rbegin(); it != l_array.rend(); ++it)
		{
			EXPECT_TRUE(*it == *l_l_initializer_list_iterator);
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<FE::string> l_array = { "water", "of", "bottle", "A" };
		std::initializer_list<FE::string> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.crbegin(); it != l_array.crend(); ++it)
		{
			EXPECT_TRUE(*it == *l_l_initializer_list_iterator);
			++l_l_initializer_list_iterator;
		}
	}
}




TEST(array, Capacity)
{
	{
		FE::array<FE::string> l_array = { "water", "of", "bottle", "A" };
		EXPECT_FALSE(l_array.is_empty());

		EXPECT_EQ(l_array.size(), 4);

		l_array.reserve(10);
		EXPECT_EQ(l_array.capacity(), 10);

		l_array.extend(6);
		EXPECT_EQ(l_array.capacity(), 16);

		l_array.shrink_to_fit();
		EXPECT_EQ(l_array.capacity(), 4);
	}
}




TEST(array, Modifiers)
{
	{
		{
			FE::array<FE::string> l_another_array = { "Christmas" };
			l_another_array.extend(2);
			l_another_array.emplace_back("Tree");
			EXPECT_TRUE(l_another_array[1] == "Tree");

			l_another_array.emplace_back("s");
			EXPECT_TRUE(l_another_array.back() == "s");
		}

	
		{
			FE::array<FE::string> l_array = { "Bye" };
			l_array.resize(16);
			EXPECT_FALSE(l_array.is_empty());

			FE::array<FE::string> l_another_array = { "Hi", ", ", "world", "!"};
			l_array.append_range(l_another_array.make_range(1, l_another_array.size()));
			EXPECT_TRUE(l_array[0] == "Bye");
			EXPECT_TRUE(l_array[1] == ", ");
			EXPECT_TRUE(l_array[2] == "world");
			EXPECT_TRUE(l_array[3] == "!");
			
			EXPECT_TRUE(l_array.back() == "!");
			l_array.pop_back();

			l_array.resize(1);
			EXPECT_EQ(l_array.size(), 1);
			EXPECT_EQ(l_array.capacity(), 1);
		}
	}
}






TEST(array, TrivialConstructorAndDestructor)
{
	using namespace FE;
	{
		FE::array<character*> l_array;
	}

	{
		FE::array<character*> l_array(2, "A bottle of water");
		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "A bottle of water"));
	}

	{
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		FE::array<character*> l_array(l_initializer_list.begin(), l_initializer_list.end());

		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_array[2], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_array[3], "water"));

	}

	{
		FE::array<character*> l_array(2, "A bottle of water");
		FE::array<character*> l_another_array = l_array;
		EXPECT_TRUE(algorithm::string::compare(l_another_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array[1], "A bottle of water"));
	}

	{
		FE::array<character*> l_array(2, "A bottle of water");
		FE::array<character*> l_another_array = std::move(l_array);
		EXPECT_TRUE(algorithm::string::compare(l_another_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array[1], "A bottle of water"));
	}

	{
		FE::array<character*> l_array = { "A", "bottle", "of", "water" };
		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_array[2], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_array[3], "water"));
	}

	{
		FE::array<character*> l_array(2, "A bottle of water");
		FE::array<character*> l_another_array;
		l_another_array = l_array;
		EXPECT_TRUE(algorithm::string::compare(l_another_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array[1], "A bottle of water"));
	}

	{
		FE::array<character*> l_array(2, "A bottle of water");
		FE::array<character*> l_another_array;
		l_another_array = std::move(l_array);
		EXPECT_TRUE(algorithm::string::compare(l_another_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array[1], "A bottle of water"));
	}

	{
		FE::array<character*> l_array;
		l_array = { "A", "bottle", "of", "water" };
		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_array[2], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_array[3], "water"));
	}
}




TEST(array, TrivialElementAccess)
{
	using namespace FE;
	{
		FE::array<character*> l_array;
		l_array.reserve(2);
		l_array.assign(2, "A bottle of water");

		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A bottle of water"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "A bottle of water"));
	}

	{
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		FE::array<character*> l_array;
		l_array.reserve(8);
		l_array.assign(l_initializer_list.begin(), l_initializer_list.end());

		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_array[2], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_array[3], "water"));
	}

	{
		FE::array<character*> l_array;
		l_array.reserve(8);
		l_array.assign({ "A", "bottle", "of", "water" });

		EXPECT_TRUE(algorithm::string::compare(l_array[0], "A"));
		EXPECT_TRUE(algorithm::string::compare(l_array[1], "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_array[2], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_array[3], "water"));

	}

	{
		FE::array<character*> l_array = { "A", "bottle", "of", "water" };

		FE::array<character*> l_another_array;
		l_another_array.reserve(8);
		l_another_array.assign_range(l_array.make_range(FE::index_t{ 1 }, FE::index_t{ 4 }));


		EXPECT_TRUE(algorithm::string::compare(l_another_array.front(), "bottle"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array[1], "of"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array.back(), "water"));
		EXPECT_TRUE(algorithm::string::compare(l_another_array.data()[0], "bottle"));
	}
}




TEST(array, TrivialIterators)
{
	using namespace FE;
	{
		FE::array<character*> l_array = { "A", "bottle", "of", "water" };
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto value : l_array)
		{
			EXPECT_TRUE(algorithm::string::compare(value, *l_l_initializer_list_iterator));
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<character*> l_array = { "A", "bottle", "of", "water" };
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.cbegin(); it != l_array.cend(); ++it)
		{
			EXPECT_TRUE(algorithm::string::compare(*it, *l_l_initializer_list_iterator));
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<character*> l_array = { "water", "of", "bottle", "A" };
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.rbegin(); it != l_array.rend(); ++it)
		{
			EXPECT_TRUE(algorithm::string::compare(*it, *l_l_initializer_list_iterator));
			++l_l_initializer_list_iterator;
		}
	}


	{
		FE::array<character*> l_array = { "water", "of", "bottle", "A" };
		std::initializer_list<character*> l_initializer_list = { "A", "bottle", "of", "water" };
		auto l_l_initializer_list_iterator = l_initializer_list.begin();

		for (auto it = l_array.crbegin(); it != l_array.crend(); ++it)
		{
			EXPECT_TRUE(algorithm::string::compare(*it, *l_l_initializer_list_iterator));
			++l_l_initializer_list_iterator;
		}
	}
}




TEST(array, TrivialCapacity)
{
	using namespace FE;
	{
		FE::array<character*> l_array = { "water", "of", "bottle", "A" };
		EXPECT_FALSE(l_array.is_empty());

		EXPECT_EQ(l_array.size(), 4);

		l_array.reserve(10);
		EXPECT_EQ(l_array.capacity(), 10);

		l_array.extend(6);
		EXPECT_EQ(l_array.capacity(), 16);

		l_array.shrink_to_fit();
		EXPECT_EQ(l_array.capacity(), 4);
	}
}




TEST(array, TrivialModifiers)
{
	using namespace FE;
	{
		{
			FE::array<character*> l_another_array = { "Christmas", "Tree" };
			l_another_array.extend(1);
			l_another_array.emplace_back("s");
			EXPECT_TRUE(algorithm::string::compare(l_another_array.back(), "s"));
		}


		{
			FE::array<character*> l_array = { "Bye" };
			l_array.resize(16);
			EXPECT_FALSE(l_array.is_empty());

			FE::array<character*> l_another_array = { "Hi", ", ", "world", "!" };
			l_array.append_range(l_another_array.make_range(1, l_another_array.size()));
			EXPECT_TRUE(algorithm::string::compare(l_array[0], "Bye"));
			EXPECT_TRUE(algorithm::string::compare(l_array[1], ", "));
			EXPECT_TRUE(algorithm::string::compare(l_array[2], "world"));
			EXPECT_TRUE(algorithm::string::compare(l_array[3], "!"));

			EXPECT_TRUE(algorithm::string::compare(l_array.back(), "!"));
			l_array.pop_back();

			l_array.resize(1);
			EXPECT_EQ(l_array.size(), 1);
			EXPECT_EQ(l_array.capacity(), 1);
		}
	}
}