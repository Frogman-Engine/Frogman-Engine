#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

#include <FE/function.hxx>
#include <FE/framework/reflection/reflection.h>

#include <FE/framework/atom_base.hpp>

// std
#include <string>


#include <glm/vec3.hpp>




struct plain_old_data
{
	FE_CLASS(plain_old_data);

	FE_PROPERTY(_a);
	var::int32 _a;

	FE_PROPERTY(_b);
	var::float32 _b;

	FE_PROPERTY(_c);
	var::uint16 _c;
};

struct pod_with_array
{
	var::int32 _a;
	var::float32 _b;
	var::uint16 _c;
	var::uint32 _d[10];
};

struct object_with_string
{
	FE_CLASS(object_with_string);

	FE_PROPERTY(_a);
	std::string _a;
};

struct object_with_vector
{
	FE_CLASS(object_with_vector);

	FE_PROPERTY(_a);
	std::vector<std::string> _a;
};

class object : public object_with_vector
{
	FE_CLASS_HAS_A_BASE(object_with_vector);
	FE_CLASS(object);
	
	FE_PROPERTY(m_text);
	std::string m_text;
public:
	object() {  };
	object(const std::string& text_p) : m_text(text_p) {/* std::cerr << method_reflection_instance_get_text.get_signature();*/ }

	FE_METHOD(object, get_text, FE::ASCII* (void) const);
	FE::ASCII* get_text() const
	{
		return this->m_text.c_str();
	}
};

TEST(reflection, POD_serialization)
{
	plain_old_data l_pod;
	l_pod._a = 1;
	l_pod._b = 2.0f;
	l_pod._c = 3;

	FE::framework::reflection_system::access()._property_reflection.serialize(std::filesystem::current_path(), FE_TEXT(serialized_pod.bin), l_pod);

	plain_old_data l_new_pod;
	FE::framework::reflection_system::access()._property_reflection.deserialize(std::filesystem::current_path(), FE_TEXT(serialized_pod.bin), l_new_pod);

	EXPECT_EQ(l_pod._a, l_new_pod._a);
	EXPECT_EQ(l_pod._b, l_new_pod._b);
	EXPECT_EQ(l_pod._c, l_new_pod._c);
}

TEST(reflection, object_with_string_serialization)
{
	object_with_string l_str;
	l_str._a = "Hello World";

	FE::framework::reflection_system::access()._property_reflection.serialize(std::filesystem::current_path(), FE_TEXT(serialized_strings.bin), l_str);

	object_with_string l_new_str;
	FE::framework::reflection_system::access()._property_reflection.deserialize(std::filesystem::current_path(), FE_TEXT(serialized_strings.bin), l_new_str);

	EXPECT_STREQ(l_str._a.data(), l_new_str._a.data());
}

TEST(reflection, object_with_vector_serialization)
{
	object_with_vector l_strs;
	l_strs._a.push_back("Hello World");
	l_strs._a.push_back("Bye World");

	FE::framework::reflection_system::access()._property_reflection.serialize(std::filesystem::current_path(), FE_TEXT(serialized_strings.bin), l_strs);

	object_with_vector l_new_strs;
	FE::framework::reflection_system::access()._property_reflection.deserialize(std::filesystem::current_path(), FE_TEXT(serialized_strings.bin), l_new_strs);

	EXPECT_STREQ(l_strs._a[0].data(), l_new_strs._a[0].data());
	EXPECT_STREQ(l_strs._a[1].data(), l_new_strs._a[1].data());
}

TEST(reflection, method_call)
{
	object l_object("Jesus Loves You!");
	FE::ASCII* l_msg = FE::framework::reflection_system::access()._method_reflection.invoke<FE::ASCII*>(l_object, "FE::ASCII* object::get_text(void) const");
	EXPECT_STREQ(l_msg, "Jesus Loves You!");
}