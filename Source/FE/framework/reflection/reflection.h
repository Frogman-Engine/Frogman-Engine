﻿#ifndef _FE_FRAMEWORK_REFLECTION_HPP_
#define _FE_FRAMEWORK_REFLECTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
<<<<<<< HEAD
#include <FE/core/do_once.hxx>
#include <FE/core/function.hxx>
#include <FE/core/string.hxx>
#include <FE/core/type_traits.hxx>

#include <FE/framework/reflection/function.hpp>
#include <FE/framework/reflection/property.hpp>


/*
Frogman Engine serialization & deserialization system supports:
	1. Plain old data serialization & deserialization. O
	2. Non-trivial object serialization & deserialization. O
	3. Fixed-sized non-trivial instance array serialization & deserialization. O
	4. Fixed-sized plain old data array serialization & deserialization. O

	5. Serializing & deserializing plain old data pointed by FE smart array pointer O
	6. Serializing & deserializing Non-trivial data pointed by FE smart array pointer O

	7. Plain old data Container serialization & deserialization. O
	8. non-trivial Container serialization & deserialization. O

    9. Base type serialization & deserialization. O
   10. Components' base types serialization & deserialization. O
NOTE:
	Unregistered non Frogman Engine native types without begin() end() methods cannot be serialized nor deserialized. It will result in compilation failure.
*/
=======
#include <FE/core/type_traits.hxx>
#include <FE/core/string.hxx>

#include <FE/framework/reflection/function_table.hpp>
#include <FE/framework/reflection/variable_map.hpp>


>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948


#ifdef FE_CLASS_HAS_A_BASE
	#error FE_CLASS_HAS_A_BASE is a reserved Frogman Engine macro keyword.
#else
#define FE_CLASS_HAS_A_BASE(base_class) \
<<<<<<< HEAD
public: \
using base_type = base_class; \
private:
=======
using base_type = base_class; \
using base_type2 = void; 
#endif


#ifdef FE_CLASS_HAS_BASES
	#error FE_CLASS_HAS_BASES is a reserved Frogman Engine macro keyword.
#else
#define FE_CLASS_HAS_BASES(base_class, base_class2) \
using base_type = base_class; \
using base_type2 = base_class2; 
#endif


#ifdef FE_CLASS_HAS_NO_BASE
	#error FE_CLASS_HAS_NO_BASE is a reserved Frogman Engine macro keyword.
#else
#define FE_CLASS_HAS_NO_BASE() \
using base_type = void; \
using base_type2 = void; 
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
#endif


#ifdef REGISTER_FE_CLASS
	#error REGISTER_FE_CLASS is a reserved Frogman Engine macro keyword.
#else
#define REGISTER_FE_CLASS(class_name) \
public: \
<<<<<<< HEAD
using is_reflectable = decltype(true); \
=======
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
class class_meta_data \
{ \
public: \
	using type = class_name; \
<<<<<<< HEAD
=======
	using base_type = typename class_name::base_type; \
	using base_type2 = typename class_name::base_type2; \
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
}; \
private:
#endif


#ifdef REGISTER_FE_METHOD
	#error REGISTER_FE_METHOD is a reserved Frogman Engine macro keyword.
#else
/*Parameter order:
1st - method name
2nd - method attributes[ EX: void(void) ]
3rd and so on - arguments buffer type[ EX: FE::string, var::length_t ] 
*/
#define REGISTER_FE_METHOD(namespace, method_name, ...) \
class method_reflection_##method_name \
{ \
public: \
	_FORCE_INLINE_ method_reflection_##method_name() noexcept \
	{ \
<<<<<<< HEAD
		FE_DO_ONCE(_DO_ONCE_PER_APP_EXECUTION_, ::FE::framework::reflection::function::register_task<::FE::cpp_style_task<class_meta_data::type, __VA_ARGS__, typename FE::method<class_meta_data::type, __VA_ARGS__>::arguments_type>>(get_signature(), &class_meta_data::type::method_name)); \
=======
		FE_DO_ONCE(_DO_ONCE_AT_APP_EXECUTION_, ::FE::framework::reflection::function_table::register_task<::FE::cpp_style_task<class_meta_data::type, __VA_ARGS__, typename FE::method<class_meta_data::type, __VA_ARGS__>::arguments_type>>(get_signature(), &class_meta_data::type::method_name)); \
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
	} \
	static ::FE::string get_signature() noexcept \
	{ \
		::FE::string l_full_signature = #__VA_ARGS__; \
		auto l_result = l_full_signature.rfind("("); \
		if(l_full_signature[l_result->_begin - 1] != ' ') \
		{ \
		    l_full_signature.extend(1); \
		    l_full_signature.insert(l_result->_begin, " "); \
		} \
		::FE::string l_signature = #namespace; \
		l_signature.extend(::FE::algorithm::string::length(#method_name) + 2); \
		l_signature += "::"; \
		l_signature += #method_name; \
		l_full_signature.extend(l_signature.length()); \
		l_result = l_full_signature.rfind("("); \
		l_full_signature.insert(l_result->_begin, l_signature.c_str()); \
		if(l_full_signature.back() != ')') \
		{ \
		    l_result = l_full_signature.find(")"); \
			l_full_signature.erase(l_result->_end, l_full_signature.length() - l_result->_end); \
		} \
		return l_full_signature; \
	} \
<<<<<<< HEAD
}; \
_NO_UNIQUE_ADDRESS_ method_reflection_##method_name method_reflection_instance_##method_name;
=======
} _NO_UNIQUE_ADDRESS_ method_reflection_instance_##method_name;
>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
#endif


#ifdef REGISTER_FE_PROPERTY
	#error REGISTER_FE_PROPERTY is a reserved Frogman Engine macro keyword.
#else
#define REGISTER_FE_PROPERTY(property_name)  \
class property_reflection_##property_name \
{ \
public: \
	_FORCE_INLINE_ property_reflection_##property_name(typename class_meta_data::type* const this_p) noexcept \
	{ \
<<<<<<< HEAD
		FE_DO_ONCE(_DO_ONCE_PER_APP_EXECUTION_, ::FE::framework::reflection::property::register_property<typename class_meta_data::type, decltype(property_name)>(*this_p, this_p->property_name, #property_name)); \
	} \
}; \
_NO_UNIQUE_ADDRESS_ property_reflection_##property_name property_reflection_instance_##property_name = this;
#endif


namespace FE::framework::reflection
{
	_FORCE_INLINE_ void initialize() noexcept
	{
		FE::framework::reflection::function::initialize();
		FE::framework::reflection::property::initialize();
	}

	_FORCE_INLINE_ void clean_up() noexcept
	{
		FE::framework::reflection::property::clean_up();
		FE::framework::reflection::function::clean_up();
	}
}

=======
		FE_DO_ONCE(_DO_ONCE_AT_APP_EXECUTION_, ::FE::framework::reflection::variable_map::register_property<typename class_meta_data::type, decltype(property_name)>(*this_p, this_p->property_name, #property_name)); \
	} \
} _NO_UNIQUE_ADDRESS_ property_reflection_instance_##property_name = this;
#endif

>>>>>>> 19ea598051b1a13a8ae6b12b0447f686f156f948
#endif