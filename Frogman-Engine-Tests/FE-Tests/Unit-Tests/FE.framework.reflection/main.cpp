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
    FE::framework::reflection::function_table::initialize();
	FE::framework::reflection::variable_map::initialize();

	int32 l_exit_code = RUN_ALL_TESTS();
	std::cerr << "\n\n";
	benchmark::RunSpecifiedBenchmarks();
	std::cerr << "\n\n";
    benchmark::Shutdown();

	FE::framework::reflection::variable_map::clean_up();
	FE::framework::reflection::function_table::clean_up();
    return l_exit_code;
}


TEST(reflection, table_seg_fault)
{
	{
		_MAYBE_UNUSED_ robin_hood::unordered_map<FE::string, int, FE::hash<FE::string>> l_hash_map;
		std::cout << "static robin_hood::unordered_map<FE::string, int, FE::hash<FE::string>> l_hash_map;\n" 
				  << "   ^                                  ^\n" 
				  << "remove static                    FE::string uses a thread_local static reference table to manage its memory.\n"
				  << "NOTE: anything associated with the Frogman Engine smart pointers and references is not allowed to have static lifetime.\n";
		l_hash_map.emplace("bah", 0);
		EXPECT_TRUE(false);
	}
}


class object
{ 
	REGISTER_FE_CLASS(object);

	REGISTER_FE_PROPERTY(m_speed);
	var::float64 m_speed;

	REGISTER_FE_PROPERTY(m_direction);
	var::float64 m_direction;

	REGISTER_FE_PROPERTY(m_health);
	var::float64 m_health;

public:
	object() noexcept : m_speed(), m_direction(), m_health() {}

	REGISTER_FE_METHOD(object, initialize, std::string  (void));
	std::string initialize() { return "object initialized"; }

	REGISTER_FE_METHOD(object, do_as_what_i_say, std::string(FE::length_t), FE::FORWARD_DATA::_AS_RVALUE_REF, var::length_t);
	std::string do_as_what_i_say(FE::length_t guess_its_size_p) noexcept
	{
		std::string s = "unsafe operations";
		if (s.size() != guess_its_size_p)
		{
			s = "you've failed to guess.";
		}
		return s; 
	}
};


TEST(reflection, method)
{
	object l_object;
	FE::task_base* l_task = ::FE::framework::reflection::function_table::invoke_method(l_object, "std::string object::initialize(void)");
	std::any l_result = l_task->get_result();
	EXPECT_TRUE(l_result.has_value());
	{
		std::string l_actual_result = std::any_cast<std::string>(l_result);
		EXPECT_TRUE(l_actual_result == "object initialized");
	}
	

	FE::arguments<var::length_t> l_args;
	l_args._first = 16;
	
	l_task = ::FE::framework::reflection::function_table::invoke_method(l_object, l_object.method_reflection_instance_do_as_what_i_say.get_signature(), std::move(l_args));
	l_result = l_task->get_result();
	EXPECT_TRUE(l_result.has_value());
	{
		std::string l_actual_result = std::any_cast<std::string>(l_result);
		EXPECT_TRUE(l_actual_result == "you've failed to guess.");
	}
}


bool JesusLovesYou() noexcept
{
	return true;
}


// https://learn.microsoft.com/en-us/cpp/build/reference/gf-eliminate-duplicate-strings?view=msvc-170
TEST(reflection, function)
{
	FE::string l_function_signature = "bool JesusLovesYou() noexcept";
	FE::framework::reflection::function_table::register_task<FE::c_style_task<bool(void)>>(l_function_signature, &JesusLovesYou);
	EXPECT_TRUE(FE::framework::reflection::function_table::check_presence(l_function_signature));

	FE::framework::reflection::function_table::invoke_function(l_function_signature);

	auto l_fn = FE::framework::reflection::function_table::retrieve(l_function_signature);
	auto l_result = l_fn->get_result();
	EXPECT_TRUE(l_result.has_value());

	_DISCARD_ auto l_actual_result = std::any_cast<FE::boolean>(l_result);
	EXPECT_TRUE(l_actual_result);
}


void FE_function_table_invocation_overhead_benchmark(benchmark::State& state_p) noexcept
{
	FE::string l_function_signature = "bool JesusLovesYou() noexcept";
	for(auto _ : state_p)
	{
		FE::framework::reflection::function_table::invoke_function(l_function_signature);
	}
	_DISCARD_ auto l_actual_result = std::any_cast<bool>(FE::framework::reflection::function_table::retrieve(l_function_signature)->get_result());
}
BENCHMARK(FE_function_table_invocation_overhead_benchmark);