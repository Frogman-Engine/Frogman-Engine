#ifndef _FE_FRAMEWORK_REFLECTION_HPP_
#define _FE_FRAMEWORK_REFLECTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/string.hxx>

#include <FE/framework/reflection/function_table.hpp>


#ifdef REGISTER_FE_CLASS
#error REGISTER_FE_CLASS is a reserved Frogman Engine macro keyword.
#endif
#define REGISTER_FE_CLASS(class_name) \
public: \
struct class_meta_data \
{ \
	using type = class_name; \
	static constexpr const char* name = #class_name; \
}; \
private:


#ifdef REGISTER_FE_METHOD
#error REGISTER_FE_METHOD is a reserved Frogman Engine macro keyword.
#endif
/*Parameter order:
1st - method name
2nd - method attributes[ EX: void(void) ]
3rd - arguments forwarding mode[ EX: FE::FORWARD_DATA::AS_RVALUE_REF ]
4th and so on - arguments buffer type[ EX: FE::string, var::length_t ] 
*/
#define REGISTER_FE_METHOD(namespace, method_name, ...) \
private: \
struct reflection_##method_name \
{ \
	reflection_##method_name() noexcept \
	{ \
		FE_DO_ONCE(_DO_ONCE_AT_APP_PROCESS_, ::FE::framework::function_table::register_task<::FE::cpp_style_task<class_meta_data::type, __VA_ARGS__>>(get_signature(), &class_meta_data::type::method_name)); \
	} \
public: \
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
}; public: reflection_##method_name reflection_instance_##method_name

#endif