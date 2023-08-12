#ifndef _FE_CORE_HASH_HXX_
#define _FE_CORE_HASH_HXX_
#pragma warning(push)
#pragma warning(disable: 4702)
#include <city.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/algorithm/string.hxx>
#include "random.hxx"




BEGIN_NAMESPACE(FE)


enum struct HASH_INPUT_DATA_TYPE : uint8
{
	_ADDRESS = 0,
	_STRING = 1,
	_BINARY = 2
};


template<typename T>
_FORCE_INLINE_ constexpr HASH_INPUT_DATA_TYPE evaluate_hash_input_data_type()
{
	if constexpr (FE::is_c_style_constant_string<T>::value == true)
	{
		return HASH_INPUT_DATA_TYPE::_STRING;
	}
	else if constexpr (std::is_pointer<T>::value == true)
	{
		return HASH_INPUT_DATA_TYPE::_ADDRESS;
	}

	return HASH_INPUT_DATA_TYPE::_BINARY;
}


template<typename T, HASH_INPUT_DATA_TYPE hash_input_data_type = FE::evaluate_hash_input_data_type<T>()>
struct hash
{
	hash() noexcept = delete;
	~hash() noexcept = delete;
};


struct hash_base
{
	static inline FE::random_integer<var::uint64> s_random_integer{0, FE::_MAX_VALUE_<var::uint64>};
protected:
	static uint64 s_seed;
};


template<typename T>
struct hash<T, HASH_INPUT_DATA_TYPE::_ADDRESS> final : public hash_base
{
	using base = hash_base;
	using output_type = var::uintptr_t;
	using input_type = T;

	_FORCE_INLINE_ output_type operator()(input_type value_p) const noexcept
	{
		return CityHash64WithSeed((const char*)value_p, sizeof(input_type), s_seed);
	}
};

template<typename T>
struct hash<T, HASH_INPUT_DATA_TYPE::_STRING> final : public hash_base
{
	using base = hash_base;
	using output_type = var::uint64;
	using input_type = T;
	
	_FORCE_INLINE_ output_type operator()(input_type value_p) const noexcept
	{
		
		return CityHash64WithSeed((const char*)value_p, sizeof(typename std::remove_pointer<T>::type) * algorithm::string::string_length(value_p), s_seed);
	}
};

template<typename T>
struct hash<T, HASH_INPUT_DATA_TYPE::_BINARY> final : public hash_base
{
	using base = hash_base;
	using output_type = var::uint64;
	using input_type = T;

	_FORCE_INLINE_ output_type operator()(input_type& value_p) const noexcept
	{
		return CityHash64WithSeed((const char*)(&value_p), sizeof(input_type), s_seed);
	}
};


END_NAMESPACE
#pragma warning(pop)
#endif
