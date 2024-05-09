#ifndef _FE_CORE_TYPE_TRAITS_HXX_
#define _FE_CORE_TYPE_TRAITS_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.hxx>
#include <type_traits>

// std
#include <string>
#include <string_view>




BEGIN_NAMESPACE(FE)

template <typename T>
struct remove_const_reference { using type = typename std::remove_const<typename std::remove_reference<T>::type>::type; };

template <bool TestResult, typename TrueType, typename FalseType>
struct conditional_type {};

template<typename TrueType, typename FalseType>
struct conditional_type<true, TrueType, FalseType> { using type = TrueType; };

template<typename TrueType, typename FalseType>
struct conditional_type<false, TrueType, FalseType> { using type = FalseType; };


template<typename T>
struct is_c_style_constant_string
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_c_style_constant_string<character*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<schar*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<uchar*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<wchar*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef _HAS_CXX20_
template<>
struct is_c_style_constant_string<UTF8*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_c_style_constant_string<UTF16*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<UTF32*>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<character[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<schar[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<uchar[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<wchar[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef _HAS_CXX20_
template<>
struct is_c_style_constant_string<UTF8[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_c_style_constant_string<UTF16[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_c_style_constant_string<UTF32[]>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


template<typename T>
struct is_char
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_char<character>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::character>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<schar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::schar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<uchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::uchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<wchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::wchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef _HAS_CXX20_
template<>
struct is_char<UTF8>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::UTF8>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_char<UTF16>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::UTF16>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<UTF32>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_char<var::UTF32>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


template<typename T>
struct is_boolean
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_boolean<var::boolean>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_boolean<boolean>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


template<typename T>
struct is_nullptr
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_nullptr<std::nullptr_t>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


template<typename T>
struct is_primitive
{
	_MAYBE_UNUSED_ static constexpr inline bool value = ((FE::is_boolean<T>::value == true) || (FE::is_char<T>::value == true) || (std::is_integral<T>::value == true) || (std::is_floating_point<T>::value == true) || (FE::is_c_style_constant_string<T>::value == true) || (std::is_pointer<T>::value == true) || (FE::is_nullptr<T>::value == true));
};


template<typename T>
struct is_numeric
{
	_MAYBE_UNUSED_ static constexpr inline bool value = (((std::is_integral<T>::value == true) && (FE::is_boolean<T>::value == false)) || (std::is_floating_point<T>::value == true));
};

template<typename T>
struct is_function
{
	_MAYBE_UNUSED_ static constexpr inline bool value = (std::is_function<T>::value == true) || (std::is_member_function_pointer<T>::value == true);
};


enum struct TYPE_TRIVIALITY : boolean
{
	_TRIVIAL = true,
	_NOT_TRIVIAL = false
};

template <typename T>
struct is_trivial
{
	_MAYBE_UNUSED_ static constexpr inline TYPE_TRIVIALITY value = static_cast<TYPE_TRIVIALITY>(std::is_trivially_constructible<T>::value && std::is_trivially_destructible<T>::value);
};


template<typename T>
struct is_string_class
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_string_class<std::string>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_string_class<std::wstring>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef __cpp_lib_char8_t
template<>
struct is_string_class<std::u8string>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_string_class<std::u16string>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_string_class<std::u32string>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


template<>
struct is_string_class<std::string_view>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_string_class<std::wstring_view>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef __cpp_lib_char8_t
template<>
struct is_string_class<std::u8string_view>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_string_class<std::u16string_view>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_string_class<std::u32string_view>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};


END_NAMESPACE
#endif