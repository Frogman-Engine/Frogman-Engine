#ifndef _FE_CORE_TYPES_H_
#define _FE_CORE_TYPES_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#pragma warning(disable : 4455)
#include "../miscellaneous/configuration.h"
#include "macros/attributes.h"
#include "macros/macro_definitions.h"
#include <any>
#include <atomic>
#include <climits>
#include <cstring>
#include <limits>
#include <string>
#include <typeinfo>
#include <type_traits>


#if _VISUAL_STUDIO_CPP_ == 1 
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#endif


BEGIN_NAMESPACE(FE)


template <typename T>
constexpr T max_value() noexcept
{
	return ::std::numeric_limits<T>::max();
}

template <typename T>
constexpr T min_value() noexcept
{
	return ::std::numeric_limits<T>::max();
}


typedef const bool boolean; // primitive types are const by default

typedef const signed char schar; // primitive types are const by default
typedef const unsigned char uchar; // primitive types are const by default
typedef const wchar_t wchar; // primitive types are const by default


#if _HAS_CXX20_ == 1
typedef const char8_t char8; // primitive types are const by default
#endif


typedef const char16_t char16; // primitive types are const by default
typedef const char32_t char32; // primitive types are const by default


typedef const float float32; // primitive types are const by default
typedef const double float64; // primitive types are const by default


typedef const bool binary; // primitive types are const by default
typedef const signed char sbyte; // primitive types are const by default
typedef const unsigned char ubyte; // primitive types are const by default
typedef const signed char int8; // primitive types are const by default
typedef const unsigned char uint8; // primitive types are const by default
typedef const signed short int16; // primitive types are const by default
typedef const unsigned short uint16; // primitive types are const by default
typedef const signed int int32; // primitive types are const by default
typedef const unsigned int uint32; // primitive types are const by default
typedef const signed long long int64; // primitive types are const by default
typedef const unsigned long long uint64; // primitive types are const by default


typedef const ::std::size_t size_t; // primitive types are const by default 
typedef const ::std::size_t length_t; // primitive types are const by default 
typedef const ::std::size_t index_t; // primitive types are const by default
typedef const ::std::size_t count_t; // primitive types are const by default
typedef const ::std::size_t capacity_t; // primitive types are const by default
typedef const ::std::ptrdiff_t ptrdiff_t; // primitive types are const by default


#if _HAS_CXX20_ == 1
template <typename T>
concept integral_type = sizeof(T) <= 8;

template <typename T>
concept character_type = sizeof(T) <= 4;
#endif


	// variable types
	namespace var 
	{
		typedef bool boolean;
		static_assert(::std::atomic<boolean>::is_always_lock_free == true, "std::atomic is not compatible with boolean.");
		static_assert(sizeof(boolean) == 1, "The size of boolean must be one byte.");

		typedef signed char schar;
		static_assert(::std::atomic<schar>::is_always_lock_free == true, "std::atomic is not compatible with schar.");
		static_assert(sizeof(schar) == 1, "The size of schar must be one byte.");

		typedef unsigned char uchar;
		static_assert(::std::atomic<uchar>::is_always_lock_free == true, "std::atomic is not compatible with uchar.");
		static_assert(sizeof(uchar) == 1, "The size of uchar must be one byte.");

		typedef wchar_t wchar;
		static_assert(::std::atomic<wchar>::is_always_lock_free == true, "std::atomic is not compatible with wchar.");
		static_assert(sizeof(wchar) <= 4, "The size of wchar must be less than or equal to four bytes.");

#if _HAS_CXX20_ == 1
		typedef char8_t char8;
		static_assert(::std::atomic<char8>::is_always_lock_free == true, "std::atomic is not compatible with char8.");
		static_assert(sizeof(char8) <= 1, "The size of char8 must be one byte.");
#endif

		typedef char16_t char16;
		static_assert(::std::atomic<char16>::is_always_lock_free == true, "std::atomic is not compatible with char16.");
		static_assert(sizeof(char16) == 2, "The size of char16 must be two bytes.");

		typedef char32_t char32;
		static_assert(::std::atomic<char32>::is_always_lock_free == true, "std::atomic is not compatible with char32.");
		static_assert(sizeof(char32) == 4, "The size of char32 must be four bytes.");

		typedef float float32;
		static_assert(::std::atomic<float32>::is_always_lock_free == true, "std::atomic is not compatible with float32.");
		static_assert(sizeof(float32) == 4, "The size of float32 must be four bytes.");

		typedef double float64;
		static_assert(::std::atomic<float64>::is_always_lock_free == true, "std::atomic is not compatible with float64.");
		static_assert(sizeof(float64) == 8, "The size of float64 must be eight bytes.");

		typedef bool binary;
		static_assert(sizeof(binary) == 1, "The size of binary must be one byte.");

		typedef signed char sbyte;
		static_assert(::std::atomic<sbyte>::is_always_lock_free == true, "std::atomic is not compatible with sbyte.");
		static_assert(sizeof(sbyte) == 1, "The size of sbyte must be one byte.");

		typedef unsigned char ubyte;
		static_assert(::std::atomic<ubyte>::is_always_lock_free == true, "std::atomic is not compatible with ubyte.");
		static_assert(sizeof(ubyte) == 1, "The size of ubyte must be one byte.");

		typedef signed char int8;
		static_assert(::std::atomic<int8>::is_always_lock_free == true, "std::atomic is not compatible with int8.");
		static_assert(sizeof(int8) == 1, "The size of int8 must be one byte.");

		typedef unsigned char uint8;
		static_assert(::std::atomic<uint8>::is_always_lock_free == true, "std::atomic is not compatible with uint8.");
		static_assert(sizeof(uint8) == 1, "The size of uint8 must be one byte.");

		typedef signed short int16;
		static_assert(::std::atomic<int16>::is_always_lock_free == true, "std::atomic is not compatible with int16.");
		static_assert(sizeof(int16) == 2, "The size of int16 must be two bytes.");

		typedef unsigned short uint16;
		static_assert(::std::atomic<uint16>::is_always_lock_free == true, "std::atomic is not compatible with uint16.");
		static_assert(sizeof(uint16) == 2, "The size of uint16 must be two bytes.");

		typedef signed int int32;
		static_assert(::std::atomic<int32>::is_always_lock_free == true, "std::atomic is not compatible with int32.");
		static_assert(sizeof(int32) == 4, "The size of int32 must be four bytes.");

		typedef unsigned int uint32;
		static_assert(::std::atomic<uint32>::is_always_lock_free == true, "std::atomic is not compatible with uint32.");
		static_assert(sizeof(uint32) == 4, "The size of uint32 must be four bytes.");

		typedef signed long long int64;
		static_assert(::std::atomic<int64>::is_always_lock_free == true, "std::atomic is not compatible with int64.");
		static_assert(sizeof(int64) == 8, "The size of int64 must be eight bytes.");

		typedef unsigned long long uint64;
		static_assert(::std::atomic<uint64>::is_always_lock_free == true, "std::atomic is not compatible with uint64.");
		static_assert(sizeof(uint64) == 8, "The size of uint64 must be eight bytes.");

		typedef ::std::size_t size_t;
		typedef ::std::size_t length_t;
		typedef ::std::size_t index_t;
		typedef ::std::size_t count_t;
		typedef ::std::size_t capacity_t;
		typedef ::std::ptrdiff_t ptrdiff_t;

		static_assert(sizeof(nullptr) == 8, "Your system's memory address model must be 64-bit.");
		typedef ::std::atomic_bool* ATOMIC_BYTE_PTR;

		typedef bool* BYTE_PTR;
		static_assert(::std::atomic<BYTE_PTR>::is_always_lock_free == true, "std::atomic is not compatible with  BYTE_PTR.");

		typedef unsigned short* WORD_PTR;
		static_assert(::std::atomic<WORD_PTR>::is_always_lock_free == true, "std::atomic is not compatible with  WORD_PTR.");

		typedef unsigned int* DWORD_PTR;
		static_assert(::std::atomic<DWORD_PTR>::is_always_lock_free == true, "std::atomic is not compatible with  DWORD_PTR.");

		typedef unsigned long long* QWORD_PTR;
		static_assert(::std::atomic<QWORD_PTR>::is_always_lock_free == true, "std::atomic is not compatible with  QWORD_PTR.");
	}

	typedef ::std::atomic_bool* const ATOMIC_BYTE_PTR;
	typedef bool* const BYTE_PTR;
	typedef unsigned short* const WORD_PTR;
	typedef unsigned int* const DWORD_PTR;
	typedef unsigned long long* const QWORD_PTR;


	_MAYBE_UNUSED_	constexpr FE::int8 _INT8_MAX_ = max_value<FE::int8>();
	_MAYBE_UNUSED_	constexpr FE::int16 _INT16_MAX_ = max_value<FE::int16>();
	_MAYBE_UNUSED_	constexpr FE::int32 _INT32_MAX_ = max_value<FE::int32>();
	_MAYBE_UNUSED_	constexpr FE::int64 _INT64_MAX_ = max_value<FE::int64>();
	
	_MAYBE_UNUSED_	constexpr FE::uint8 _UINT8_MAX_ = max_value<FE::uint8>();
	_MAYBE_UNUSED_	constexpr FE::uint16 _UINT16_MAX_ = max_value<FE::uint16>();
	_MAYBE_UNUSED_	constexpr FE::uint32 _UINT32_MAX_ = max_value<FE::uint32>();
	_MAYBE_UNUSED_	constexpr FE::uint64 _UINT64_MAX_ = max_value<FE::uint64>();

	_MAYBE_UNUSED_	constexpr FE::float64 _ACCURATE_MINIMUM_FLOAT_VALUE_ = 0.000001f;

	_MAYBE_UNUSED_	constexpr FE::int8 _NULL_ = 0;

	_MAYBE_UNUSED_	constexpr FE::int8 _TRUE_ = 1;
	_MAYBE_UNUSED_	constexpr FE::int8 _FALSE_ = 0;

	_MAYBE_UNUSED_	constexpr FE::float32 _NULL_f_ = 0.0f;

	_MAYBE_UNUSED_	constexpr FE::boolean _FOUND_ = true;
	_MAYBE_UNUSED_	constexpr FE::boolean _NOT_FOUND_ = false;

	_MAYBE_UNUSED_	constexpr FE::boolean _SUCCESSFUL_ = true;
	_MAYBE_UNUSED_	constexpr FE::boolean _FAILED_ = false;

template<typename A, typename B>
class auto_cast final
{
public:
	inline B cast_A_to_B(A object_p) noexcept { return (B)(object_p); }

	inline A cast_B_to_A(B object_p) noexcept { return (A)(object_p); }
};


#define IF_T_IS_NOT_TRIVIALLY_CONSTRUCTIBLE_AND_DESTRUCTIBLE(T, executable_code_lines) if constexpr (!std::is_trivially_constructible<T>::value || !std::is_trivially_destructible<T>::value) {executable_code_lines}


END_NAMESPACE

#if _VISUAL_STUDIO_CPP_ == 1
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif

#endif
