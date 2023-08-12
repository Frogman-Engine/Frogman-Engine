#ifndef _FE_CORE_TYPES_H_
#define _FE_CORE_TYPES_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/configuration.h>
#include "macros/attributes.h"
#include <any>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <string>
#include <typeinfo>
#include <type_traits>
#pragma warning(push)
#pragma warning(disable: 4530) // disable no-exception warnings


#ifdef _VISUAL_STUDIO_CPP_
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#endif


BEGIN_NAMESPACE(FE)


typedef const bool boolean; // primitive types are const by default

typedef const char character;  // primitive types are const by default
typedef const signed char schar; // primitive types are const by default
typedef const unsigned char uchar; // primitive types are const by default
typedef const wchar_t wchar; // primitive types are const by default


#ifdef _HAS_CXX20_
typedef const char8_t UTF8; // primitive types are const by default
#endif

typedef const char16_t UTF16; // primitive types are const by default
typedef const char32_t UTF32; // primitive types are const by default


typedef const float float32; // primitive types are const by default
typedef const double float64; // primitive types are const by default


typedef const bool binary; // primitive types are const by default
typedef const ::std::uint8_t byte; // primitive types are const by default
typedef const ::std::uint16_t word; // primitive types are const by default
typedef const ::std::uint32_t dword; // primitive types are const by default
typedef const ::std::uint64_t qword; // primitive types are const by default


typedef const ::std::int8_t int8; // primitive types are const by default
typedef const ::std::uint8_t uint8; // primitive types are const by default
typedef const ::std::int16_t int16; // primitive types are const by default
typedef const ::std::uint16_t uint16; // primitive types are const by default
typedef const ::std::int32_t int32; // primitive types are const by default
typedef const ::std::uint32_t uint32; // primitive types are const by default
typedef const ::std::int64_t int64; // primitive types are const by default
typedef const ::std::uint64_t uint64; // primitive types are const by default


typedef const ::std::size_t size_t; // primitive types are const by default 
typedef const ::std::size_t length_t; // primitive types are const by default 
typedef const ::std::size_t index_t; // primitive types are const by default
typedef const ::std::size_t count_t; // primitive types are const by default
typedef const ::std::size_t capacity_t; // primitive types are const by default
typedef const ::std::ptrdiff_t ptrdiff_t; // primitive types are const by default
typedef const ::std::intptr_t intptr_t; // primitive types are const by default
typedef const ::std::uintptr_t uintptr_t; // primitive types are const by default


	// variable types
	namespace var 
	{
		typedef bool boolean;
		static_assert(::std::atomic<boolean>::is_always_lock_free == true, "std::atomic is not compatible with boolean.");
		static_assert(sizeof(boolean) == 1, "The size of boolean must be one byte.");

		typedef char character;
		static_assert(::std::atomic<character>::is_always_lock_free == true, "std::atomic is not compatible with character.");
		static_assert(sizeof(character) == 1, "The size of character must be one byte.");

		typedef signed char schar;
		static_assert(::std::atomic<schar>::is_always_lock_free == true, "std::atomic is not compatible with schar.");
		static_assert(sizeof(schar) == 1, "The size of schar must be one byte.");

		typedef unsigned char uchar;
		static_assert(::std::atomic<uchar>::is_always_lock_free == true, "std::atomic is not compatible with uchar.");
		static_assert(sizeof(uchar) == 1, "The size of uchar must be one byte.");

		typedef wchar_t wchar;
		static_assert(::std::atomic<wchar>::is_always_lock_free == true, "std::atomic is not compatible with wchar.");
		static_assert(sizeof(wchar) <= 4, "The size of wchar must be less than or equal to four bytes.");

#ifdef _HAS_CXX20_
		typedef char8_t UTF8;
		static_assert(::std::atomic<UTF8>::is_always_lock_free == true, "std::atomic is not compatible with UTF8.");
		static_assert(sizeof(UTF8) <= 1, "The size of UTF8 must be one byte.");
#endif

		typedef char16_t UTF16;
		static_assert(::std::atomic<UTF16>::is_always_lock_free == true, "std::atomic is not compatible with UTF16.");
		static_assert(sizeof(UTF16) == 2, "The size of UTF16 must be two bytes.");

		typedef char32_t UTF32;
		static_assert(::std::atomic<UTF32>::is_always_lock_free == true, "std::atomic is not compatible with UTF32.");
		static_assert(sizeof(UTF32) == 4, "The size of UTF32 must be four bytes.");

		typedef float float32;
		static_assert(::std::atomic<float32>::is_always_lock_free == true, "std::atomic is not compatible with float32.");
		static_assert(sizeof(float32) == 4, "The size of float32 must be four bytes.");

		typedef double float64;
		static_assert(::std::atomic<float64>::is_always_lock_free == true, "std::atomic is not compatible with float64.");
		static_assert(sizeof(float64) == 8, "The size of float64 must be eight bytes.");

		typedef bool binary;
		static_assert(sizeof(binary) == 1, "The size of binary must be one byte.");

		typedef ::std::uint8_t byte;
		typedef ::std::uint16_t word; // primitive types are const by default
		typedef ::std::uint32_t dword; // primitive types are const by default
		typedef ::std::uint64_t qword; // primitive types are const by default

		typedef ::std::int8_t int8;
		static_assert(::std::atomic<int8>::is_always_lock_free == true, "std::atomic is not compatible with int8.");
		static_assert(sizeof(int8) == 1, "The size of int8 must be one byte.");

		typedef ::std::uint8_t uint8;
		static_assert(::std::atomic<uint8>::is_always_lock_free == true, "std::atomic is not compatible with uint8.");
		static_assert(sizeof(uint8) == 1, "The size of uint8 must be one byte.");

		typedef ::std::int16_t int16;
		static_assert(::std::atomic<int16>::is_always_lock_free == true, "std::atomic is not compatible with int16.");
		static_assert(sizeof(int16) == 2, "The size of int16 must be two bytes.");

		typedef ::std::uint16_t uint16;
		static_assert(::std::atomic<uint16>::is_always_lock_free == true, "std::atomic is not compatible with uint16.");
		static_assert(sizeof(uint16) == 2, "The size of uint16 must be two bytes.");

		typedef ::std::int32_t int32;
		static_assert(::std::atomic<int32>::is_always_lock_free == true, "std::atomic is not compatible with int32.");
		static_assert(sizeof(int32) == 4, "The size of int32 must be four bytes.");

		typedef ::std::uint32_t uint32;
		static_assert(::std::atomic<uint32>::is_always_lock_free == true, "std::atomic is not compatible with uint32.");
		static_assert(sizeof(uint32) == 4, "The size of uint32 must be four bytes.");

		typedef ::std::int64_t int64;
		static_assert(::std::atomic<int64>::is_always_lock_free == true, "std::atomic is not compatible with int64.");
		static_assert(sizeof(int64) == 8, "The size of int64 must be eight bytes.");

		typedef ::std::uint64_t uint64;
		static_assert(::std::atomic<uint64>::is_always_lock_free == true, "std::atomic is not compatible with uint64.");
		static_assert(sizeof(uint64) == 8, "The size of uint64 must be eight bytes.");

		typedef ::std::size_t size_t;
		typedef ::std::size_t length_t;
		typedef ::std::size_t index_t;
		typedef ::std::size_t count_t;
		typedef ::std::size_t capacity_t;
		typedef ::std::ptrdiff_t ptrdiff_t;
		typedef ::std::intptr_t intptr_t;
		typedef ::std::uintptr_t uintptr_t;
	}


	template <typename T>
	constexpr inline auto _MAX_VALUE_ = ::std::numeric_limits<T>::max();

	template <typename T>
	constexpr inline auto _MIN_VALUE_ = ::std::numeric_limits<T>::min();

_MAYBE_UNUSED_	constexpr inline FE::int8 _INT8_MAX_ = _MAX_VALUE_<FE::int8>;
_MAYBE_UNUSED_	constexpr inline FE::int16 _INT16_MAX_ = _MAX_VALUE_<FE::int16>;
_MAYBE_UNUSED_	constexpr inline FE::int32 _INT32_MAX_ = _MAX_VALUE_<FE::int32>;
_MAYBE_UNUSED_	constexpr inline FE::int64 _INT64_MAX_ = _MAX_VALUE_<FE::int64>;
	
_MAYBE_UNUSED_	constexpr inline FE::uint8 _UINT8_MAX_ = _MAX_VALUE_<FE::uint8>;
_MAYBE_UNUSED_	constexpr inline FE::uint16 _UINT16_MAX_ = _MAX_VALUE_<FE::uint16>;
_MAYBE_UNUSED_	constexpr inline FE::uint32 _UINT32_MAX_ = _MAX_VALUE_<FE::uint32>;
_MAYBE_UNUSED_	constexpr inline FE::uint64 _UINT64_MAX_ = _MAX_VALUE_<FE::uint64>;

_MAYBE_UNUSED_	constexpr inline FE::float64 _ACCURATE_MINIMUM_FLOAT_VALUE_ = 0.000001f;

#define _NULL_ 0

_MAYBE_UNUSED_	constexpr inline FE::int8 _TRUE_ = 1;
_MAYBE_UNUSED_	constexpr inline FE::int8 _FALSE_ = 0;

_MAYBE_UNUSED_	constexpr inline FE::float32 _NULL_f_ = 0.0f;

_MAYBE_UNUSED_	constexpr inline FE::boolean _FOUND_ = true;
_MAYBE_UNUSED_	constexpr inline FE::boolean _NOT_FOUND_ = false;

_MAYBE_UNUSED_	constexpr inline FE::boolean _SUCCESSFUL_ = true;
_MAYBE_UNUSED_	constexpr inline FE::boolean _FAILED_ = false;

struct null {};


namespace internal
{
	template <bool compile_time_test_result, typename true_type, typename false_type>
	struct conditional_type {};

	template<typename true_type, typename false_type>
	struct conditional_type<true, true_type, false_type> { using type = true_type; };

	template<typename true_type, typename false_type>
	struct conditional_type<false, true_type, false_type> { using type = false_type; };
}

template <bool compile_time_test_result, typename true_type, typename false_type>
using conditional_type = internal::conditional_type< compile_time_test_result, true_type, false_type>;


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
struct is_character 
{
	_MAYBE_UNUSED_ static constexpr inline bool value = false;
};

template<>
struct is_character<character>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::character>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<schar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::schar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<uchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::uchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<wchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::wchar>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

#ifdef _HAS_CXX20_
template<>
struct is_character<UTF8>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::UTF8>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};
#endif

template<>
struct is_character<UTF16>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::UTF16>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<UTF32>
{
	_MAYBE_UNUSED_ static constexpr inline bool value = true;
};

template<>
struct is_character<var::UTF32>
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
	_MAYBE_UNUSED_ static constexpr inline bool value = ((FE::is_boolean<T>::value == true) || (FE::is_character<T>::value == true) || (std::is_integral<T>::value == true) || (std::is_floating_point<T>::value == true) || (FE::is_c_style_constant_string<T>::value == true) || (std::is_pointer<T>::value == true) || (FE::is_nullptr<T>::value == true));
};


enum struct TYPE_TRAIT : int8
{
	_UNDEFINED = -1,
	_PRIMITIVE = 0,
	_BOOLEAN = 1,
	_CHARACTER = 2,
	_SIGNED_INTEGER = 3,
	_UNSIGNED_INTEGER = 4,
	_FLOAT = 5,
	_C_STYLE_STRING = 6,
	_POINTER = 7,
	_NULLPTR = 8,
	_CLASS = 9,
	_FUNCTION = 10
};

template<typename T>
constexpr inline TYPE_TRAIT type_trait() noexcept
{
	if constexpr (FE::is_boolean<T>::value)
	{
		return TYPE_TRAIT::_BOOLEAN;
	}
	else if constexpr (FE::is_character<T>::value)
	{
		return TYPE_TRAIT::_CHARACTER;
	}
	else if constexpr (std::is_signed<T>::value)
	{
		return TYPE_TRAIT::_SIGNED_INTEGER;
	}
	else if constexpr (std::is_unsigned<T>::value)
	{
		return TYPE_TRAIT::_UNSIGNED_INTEGER;
	}
	else if constexpr (std::is_floating_point<T>::value)
	{
		return TYPE_TRAIT::_FLOAT;
	}
	else if constexpr (FE::is_c_style_constant_string<T>::value)
	{
		return TYPE_TRAIT::_C_STYLE_STRING;
	}
	else if constexpr (std::is_pointer<T>::value)
	{
		return TYPE_TRAIT::_POINTER;
	}
	else if constexpr (FE::is_nullptr<T>::value)
	{
		return TYPE_TRAIT::_NULLPTR;
	}
	else if constexpr (std::is_function<T>::value)
	{
		return TYPE_TRAIT::_FUNCTION;
	}

	return TYPE_TRAIT::_UNDEFINED;
}


enum struct OBJECT_TRIVIALITY : boolean
{
	_TRIVIAL = true,
	_NOT_TRIVIAL = false
};

template <typename T>
struct is_trivially_constructible_and_destructible
{
	_MAYBE_UNUSED_ static constexpr inline OBJECT_TRIVIALITY _VALUE_ = static_cast<OBJECT_TRIVIALITY>(std::is_trivially_constructible<T>::value && std::is_trivially_destructible<T>::value);
};


enum struct OBJECT_LIFECYCLE : boolean
{
	_CONSTRUCTED = true,
	_DESTRUCTED = false
};


template <typename T>
struct lazy_const
{
private:
	T _data;
	var::boolean _is_initialized;

public:
	constexpr lazy_const() noexcept : _data(), _is_initialized(false) {}
	constexpr lazy_const(T&& data_p) noexcept : _data(std::move(data_p)), _is_initialized(true) {}
	constexpr ~lazy_const() noexcept {};

	_FORCE_INLINE_ lazy_const(const lazy_const& other_cref_p) noexcept : _data(other_cref_p._data), _is_initialized(true) {}
	_FORCE_INLINE_ lazy_const(lazy_const&& rvalue_p) noexcept : _data(std::move(rvalue_p._data)), _is_initialized(true) {}

	_FORCE_INLINE_ lazy_const& operator=(T&& data_p) noexcept
	{
		if (this->_is_initialized == true)
		{
			::abort();
		}

		this->_data = std::move(data_p);
		this->_is_initialized = true;
		
		return *this;
	}

	_FORCE_INLINE_ lazy_const& operator=(const lazy_const& other_cref_p) noexcept
	{
		if (this->_is_initialized == true)
		{
			::abort();
		}

		this->_data = other_cref_p._data;
		this->_is_initialized = true;
		
		return *this;
	}

	_FORCE_INLINE_ lazy_const& operator=(lazy_const&& rvalue_p) noexcept
	{
		if constexpr (this->_is_initialized == true)
		{
			::abort();
		}

		this->_data = std::move(rvalue_p._data);
		this->_is_initialized = true;
		
		return *this;
	}

	_FORCE_INLINE_ const T& load() noexcept { return this->_data; }
};


#ifdef _HAS_CXX20_
template <typename T>
concept integral_type = std::is_integral<T>::value;

template <typename T>
concept character_type = FE::is_character<T>::value;
#endif


END_NAMESPACE


#ifdef _VISUAL_STUDIO_CPP_
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif


#pragma warning(pop)
#endif
