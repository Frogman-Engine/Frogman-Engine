#ifndef _FE_FRAMEWORK_REFLECTION_HPP_
#define _FE_FRAMEWORK_REFLECTION_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/framework/framework.hpp>




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
#define REGISTER_FE_METHOD(method_name, ...) \
private: \
struct reflection_##method_name \
{ \
	reflection_##method_name() noexcept \
	{ \
		FE_DO_ONCE(_DO_ONCE_AT_APP_PROCESS_, ::FE::framework::method_signature_t signature = get_signature(); ::FE::framework::application::get_function_table().register_task<::FE::cpp_style_task<class_meta_data::type, __VA_ARGS__>>(std::move(signature), &class_meta_data::type::##method_name)); \
	} \
public: \
	static ::FE::framework::method_signature_t get_signature() noexcept \
	{ \
		::FE::framework::method_signature_t l_full_signature = __FUNCTION__; \
		::FE::framework::method_signature_t l_method_attribute = #__VA_ARGS__; \
		auto l_result = l_method_attribute.find(")"); \
		::FE::length_t l_unnecessary_part_length = l_method_attribute.length() - l_result->_end; \
		l_full_signature.extend(l_method_attribute.length()); \
		if (l_unnecessary_part_length != 0) \
		{ \
			l_method_attribute.erase(l_result->_end, l_unnecessary_part_length); \
		} \
		l_result = l_method_attribute.find("("); \
		l_full_signature.insert(0, l_method_attribute, 0, l_result->_begin); \
		auto l_namespace = l_full_signature.rfind("::"); \
		::FE::count_t l_count_to_replace = l_full_signature.length() - l_namespace->_begin; \
		::FE::count_t l_input_replacement_size = l_method_attribute.find(")")->_end - l_result->_begin; \
		l_full_signature.replace(l_namespace->_begin, l_count_to_replace, l_method_attribute, l_result->_begin, l_input_replacement_size); \
		l_full_signature.replace(l_full_signature.rfind("::reflection_")->_end - 1, 1, ':', 2); \
		return std::move(l_full_signature); \
	} \
}; public: reflection_##method_name reflection_##method_name##_instance

#endif