#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <FE/core/function.hxx>
#include <FE/framework/reflection/reflection.h>
#include <FE/framework/framework.hpp>

// std
#include <cstring>


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

class framework_test : public FE::framework::application_base
{
	virtual bool set_up(int argc_p, char** argv_p) override
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
		FE_ABORT_IF(benchmark::ReportUnrecognizedArguments(argc_p, argv_p) == true, "Failed to meet the expectation: Unrecognized Benchmark Arguments Detected.");
		return true;
	}

	virtual int run(_MAYBE_UNUSED_ int argc_p, _MAYBE_UNUSED_ char** argv_p) override
	{
		FE::int32 l_exit_code = RUN_ALL_TESTS();
		std::cerr << "\n\n";
		benchmark::RunSpecifiedBenchmarks();
		std::cerr << "\n\n";
		return l_exit_code;
	}

	virtual void clean_up() override
	{
    	benchmark::Shutdown();
	}
};

CONFIGURE_A_FROGMAN_ENGINE_PROJECT()

return new framework_test;

END_OF_THE_FROGMAN_ENGINE_PROJECT_CONFIGURATION()




BEGIN_NAMESPACE(test)
class object
{ 
	FE_CLASS_HAS_NO_BASE();
	REGISTER_FE_CLASS(test::object);

	REGISTER_FE_PROPERTY(m_speed);
	_MAYBE_UNUSED_ var::float64 m_speed;

	REGISTER_FE_PROPERTY(m_direction);
	_MAYBE_UNUSED_ var::float64 m_direction;

	REGISTER_FE_PROPERTY(m_health);
	_MAYBE_UNUSED_ var::float64 m_health;

	REGISTER_FE_PROPERTY(m_integers);
	_MAYBE_UNUSED_ var::int32 m_integers[4];

	REGISTER_FE_PROPERTY(m_name); 
	var::character* m_name;

public:
	object() noexcept : m_speed(), m_direction(), m_health(), m_integers(), m_name(new var::character('\0')) {}
	object(FE::float64 speed_p, FE::float64 direction_p, FE::float64 health_p) noexcept : m_speed(speed_p), m_direction(direction_p), m_health(health_p), m_integers{1, 2, 3, 4}, m_name(new var::character('J')) {}

	REGISTER_FE_METHOD(test::object, initialize, std::string (void));
	std::string initialize() { return "object initialized"; }

	REGISTER_FE_METHOD(test::object, do_as_what_i_say, std::string(FE::length_t));
	std::string do_as_what_i_say(FE::length_t guess_its_size_p) noexcept
	{
		std::string s = "unsafe operations";
		if (s.size() != guess_its_size_p)
		{
			s = "you've failed to guess.";
		}
		return s; 
	}

	FE::float64 get_speed() const noexcept { return this->m_speed; }
	FE::float64 get_direction() const noexcept { return this->m_direction; }
	FE::float64 get_health() const noexcept { return this->m_health; }

	FE::int32* get_integers() const noexcept { return this->m_integers; }
	FE::character* get_name() const noexcept { return this->m_name; }
};
END_NAMESPACE

TEST(reflection, method_and_property)
{
	test::object l_object(10, 90, 100);
	std::any l_result = FE::framework::reflection::function_table::invoke_method(l_object, "std::string test::object::initialize(void)");
	EXPECT_TRUE(l_result.has_value());
	{
		std::string l_actual_result = std::any_cast<std::string>(l_result);
		EXPECT_TRUE(l_actual_result == "object initialized");
	}
	

	FE::arguments<var::length_t> l_args;
	l_args._first = 16;
	
	l_result = ::FE::framework::reflection::function_table::invoke_method(l_object, l_object.method_reflection_instance_do_as_what_i_say.get_signature(), std::move(l_args));
	EXPECT_TRUE(l_result.has_value());
	{
		std::string l_actual_result = std::any_cast<std::string>(l_result);
		EXPECT_TRUE(l_actual_result == "you've failed to guess.");
	}

	FE::framework::reflection::variable_map::serialize<test::object>("Frogman-Engine-Tests/FE-Tests/Unit-Tests/FE.framework.reflection/serialized", "test-object.froggy", l_object);

	test::object l_new_object;
	FE::framework::reflection::variable_map::deserialize<test::object>("Frogman-Engine-Tests/FE-Tests/Unit-Tests/FE.framework.reflection/serialized", "test-object.froggy", l_new_object);

	EXPECT_EQ(l_object.get_speed(), l_new_object.get_speed());
	EXPECT_EQ(l_object.get_direction(), l_new_object.get_direction());
	EXPECT_EQ(l_object.get_health(), l_new_object.get_health());

	FE::int32 l_integers[4] = {1, 2, 3, 4};
	EXPECT_EQ(std::memcmp(l_new_object.get_integers(), l_object.get_integers(), sizeof(l_integers)), 0);

	EXPECT_EQ(*l_object.get_name(), *l_new_object.get_name()); 
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

	auto l_result = FE::framework::reflection::function_table::invoke_function(l_function_signature);

	_MAYBE_UNUSED_ FE::task_base* l_fn = FE::framework::reflection::function_table::retrieve(l_function_signature);

	EXPECT_TRUE(std::any_cast<FE::boolean>(l_result));
}


void FE_function_table_invocation_overhead_benchmark(benchmark::State& state_p) noexcept
{
	FE::string l_function_signature = "bool JesusLovesYou() noexcept";
	for(auto _ : state_p)
	{
		FE::framework::reflection::function_table::invoke_function(l_function_signature);
	}
}
BENCHMARK(FE_function_table_invocation_overhead_benchmark);