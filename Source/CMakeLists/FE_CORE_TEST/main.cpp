// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

#include <FE/core/prerequisites.h>
#include <FE/framework/framework.hpp>
#include <FE/core/block_pool.hxx>
#include <FE/miscellaneous/private/macro_restrictions.h>


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
class test final : public FE::framework::application
{
public:
	test(FE::size_t function_table_size_p)
	{
		s_function_table->reserve(function_table_size_p);
	}

private:
	virtual bool set_up(_MAYBE_UNUSED_ int argc_p, _MAYBE_UNUSED_ char** argv_p) override final
	{
		testing::InitGoogleTest(&argc_p, argv_p);

		if (argv_p == nullptr)
		{
			char l_arg0_default[] = "benchmark";
			char* l_args_default = l_arg0_default;

			argc_p = 1;
			argv_p = &l_args_default;
		}
		benchmark::Initialize(&argc_p, argv_p);
		FE_EXPECT(benchmark::ReportUnrecognizedArguments(argc_p, argv_p), false, "Expectation Failed: Unrecognized Benchmark Arguments Detected.");

		return _FE_SUCCESS_;
	}
	
	virtual int run(_MAYBE_UNUSED_ int argc_p, _MAYBE_UNUSED_ char** argv_p) override final
	{

		let int32 l_exit_code = RUN_ALL_TESTS();
		std::cerr << "\n\n";
		benchmark::RunSpecifiedBenchmarks();
		std::cerr << "\n\n";
		return l_exit_code;
	}

	virtual void clean_up() override final
	{
		benchmark::Shutdown();
	}

public:
	virtual ~test() override
	{

	}
};




FE::framework::application::initializer_t g_init = FE::framework::application::create_application
(
	[]()
	{
		constexpr FE::size_t l_function_table_size = 128;
		return _CREATE_AN_APP_ test(l_function_table_size);
	}
);
