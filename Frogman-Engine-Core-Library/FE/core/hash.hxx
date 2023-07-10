#ifndef _HASH_HXX_
#define _HASH_HXX_
#include <city.h> // Copyright 2011, Google Inc. All rights reserved. City Hash is Google's intellectual property.

#include "prerequisite_symbols.h" // Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "algorithm/string.hxx"


BEGIN_NAMESPACE(FE)


template<typename T>
class hash
{
public:
	typedef const char* byte_array_ptr_t;
	typedef T value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		if constexpr (::std::is_pointer<T>::value == true)
		{
			return (var::uint64)value_p;
		}

		return CityHash64((byte_array_ptr_t)&value_p, sizeof(value_type));
	}
};

template<>
class hash<const char*>
{
public:
	typedef const char* byte_array_ptr_t;
	typedef const char* value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		return CityHash64((byte_array_ptr_t)value_p, algorithm::string::string_length(value_p));
	}
};

template<>
class hash<const wchar_t*>
{
public:
	typedef const char* byte_array_ptr_t;
	typedef const wchar_t* value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		return CityHash64((byte_array_ptr_t)value_p, algorithm::string::string_length(value_p) * sizeof(wchar_t));
	}
};

#if _HAS_CXX20_ == 1
template<>
class hash<const char8_t*>
{
public:
	typedef const char* byte_array_ptr_t;
	typedef const char8_t* value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		return CityHash64((byte_array_ptr_t)value_p, algorithm::string::string_length(value_p) * sizeof(char8_t));
	}
};
#endif

template<>
class hash<const char16_t*>
{
public:
	typedef const char* byte_array_ptr_t;
	typedef const char16_t* value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		return CityHash64((byte_array_ptr_t)value_p, algorithm::string::string_length(value_p) * sizeof(char16_t));
	}
};

template<>
class hash<const char32_t*>
{
public:
	typedef const char* byte_array_ptr_t;
	typedef const char32_t* value_type;

	_FORCE_INLINE_ var::uint64 operator()(value_type value_p) noexcept
	{
		return CityHash64((byte_array_ptr_t)value_p, algorithm::string::string_length(value_p) * sizeof(char32_t));
	}
};

END_NAMESPACE
#endif