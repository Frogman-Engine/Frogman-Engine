
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <FE/core/function.hxx>
#include <FE/framework/reflection/reflection.h>



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



class object
{
	REGISTER_FE_CLASS(object);

public:
	REGISTER_FE_METHOD(initialize, const char* (void));
	const char* initialize() { return "object initialized"; }

	REGISTER_FE_METHOD(do_as_what_i_say, std::string(std::string, FE::length_t), FE::FORWARD_DATA::_AS_RVALUE_REF, std::string, FE::var::length_t);
	std::string do_as_what_i_say(std::string input_p, FE::length_t guess_its_size_p) noexcept
	{
		if (input_p.size() != guess_its_size_p)
		{
			input_p = "you've failed to guess.";
		}
		return std::move(input_p); 
	}
};

TEST(reflection, method)
{

	object l_object;
	FE::task_base* l_task = FE::framework::application_base::get_function_table().invoke_method(l_object, "const char* object::reflection::initialize(void)");
	std::any l_result = std::move(l_task->get_result());
	EXPECT_TRUE(l_result.has_value());
	{
		const char* l_actual_result = std::any_cast<const char*>(l_result);
		EXPECT_STREQ(l_actual_result, "object initialized");
	}
	

	FE::arguments<std::string, FE::var::length_t> l_args;
	l_args._first = "unsafe operations";
	l_args._second = 16;
	
	l_task = FE::framework::application_base::get_function_table().invoke_method(l_object, l_object.reflection_do_as_what_i_say_instance.get_signature(), std::move(l_args));
	l_result = std::move(l_task->get_result());
	EXPECT_TRUE(l_result.has_value());
	{
		std::string l_actual_result = std::any_cast<std::string>(l_result);
		EXPECT_STREQ(l_actual_result.c_str(), "you've failed to guess.");
	}
}


bool JesusLovesYou() noexcept
{
	//std::cout << "Jesus loves you!" << std::endl;
	return true;
}

// https://learn.microsoft.com/en-us/cpp/build/reference/gf-eliminate-duplicate-strings?view=msvc-170
TEST(reflection, function)
{
	FE::framework::function_table l_table;
	l_table.register_task<FE::c_style_task<bool(void)>>("bool JesusLovesYou() noexcept", &JesusLovesYou);
	EXPECT_TRUE(l_table.check_presence("bool JesusLovesYou() noexcept"));

	l_table.invoke_function("bool JesusLovesYou() noexcept");
	auto l_fn = l_table.retrieve("bool JesusLovesYou() noexcept");
	auto l_result = l_fn->get_result();
	EXPECT_TRUE(l_result.has_value());
	
	_DISCARD_ auto l_actual_result = std::any_cast<FE::boolean>(l_result);
	EXPECT_TRUE(l_actual_result);
}


void FE_function_table_invocation_overhead_benchmark(benchmark::State& state_p) noexcept
{
	FE::framework::function_table l_table;
	l_table.register_task<FE::c_style_task<bool(void)>>("bool JesusLovesYou() noexcept", &JesusLovesYou);

	for(auto _ : state_p)
	{
		l_table.invoke_function("bool JesusLovesYou() noexcept");
	}
	_DISCARD_ auto l_actual_result = std::any_cast<bool>(l_table.retrieve("bool JesusLovesYou() noexcept")->get_result());
}

BENCHMARK(FE_function_table_invocation_overhead_benchmark);