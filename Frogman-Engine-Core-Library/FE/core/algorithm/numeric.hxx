#ifndef _FE_CORE_ALGORITHM_NUMERIC_HXX_
#define _FE_CORE_ALGORITHM_NUMERIC_HXX_
#pragma warning(push)
#pragma warning(disable: 4244)
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include "string.hxx"


BEGIN_NAMESPACE(FE::algorithm::numeric)


_MAYBE_UNUSED_ constexpr var::uint8 _ASCII_CODE_ZERO_ = 48;


template<typename integral_type>
_NODISCARD_ _FORCE_INLINE_ var::uint8 count_integral_digit_length(integral_type value_p) noexcept
{
	static_assert(::std::is_integral<integral_type>::value == true || ::std::is_floating_point<integral_type>::value == true, "the type of the template parameter integral_type is not numeric");

	var::int8 l_length_of_n = 0;
	if (value_p < 0)
	{
		for (; value_p <= static_cast<integral_type>(-10); value_p /= static_cast<integral_type>(10)) { ++l_length_of_n; }
		return ++l_length_of_n;
	}

	for (; value_p >= static_cast<integral_type>(10); value_p /= static_cast<integral_type>(10)) { ++l_length_of_n; }
	return ++l_length_of_n;
}

template<typename integral_type>
_NODISCARD_ _FORCE_INLINE_ constexpr var::uint8 constexpr_count_integral_digit_length(integral_type value_p) noexcept
{
	static_assert(::std::is_integral<integral_type>::value == true || ::std::is_floating_point<integral_type>::value == true, "the type of the template parameter integral_type is not numeric");

	var::int8 l_length_of_n = 0;
	if (value_p < 0)
	{
		for (; value_p <= static_cast<integral_type>(-10); value_p /= static_cast<integral_type>(10)) { ++l_length_of_n; }
		return ++l_length_of_n;
	}

	for (; value_p >= static_cast<integral_type>(10); value_p /= static_cast<integral_type>(10)) { ++l_length_of_n; }
	return ++l_length_of_n;
}


template<typename integral_type, typename char_type>
_FORCE_INLINE_ void convert_integer_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, integral_type value_p) noexcept
{
	static_assert(::std::is_integral<integral_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");
	ABORT_IF(string_out_ptrc_p == nullptr, "ERROR: string_out_ptrc_p is nullptr.");

	var::int8 l_integral_digits = numeric::count_integral_digit_length<integral_type>(value_p);
	var::boolean l_is_negative = false;

	if (value_p < 0)
	{
		l_is_negative = true;
		value_p = -value_p;
		++l_integral_digits;
	}

	ABORT_IF(input_string_capacity_p <= l_integral_digits, "CRITICAL ERROR: the digit length of an integer exceeds the output string buffer capacity");

	var::int8 l_idx = l_integral_digits - 1;
	while (value_p > 0)
	{
		string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
		value_p /= 10;
		--l_idx;
	}


	if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

	string_out_ptrc_p[l_integral_digits] = static_cast<char_type>('\0');
}

template<typename integral_type, typename char_type>
_FORCE_INLINE_ constexpr void constexpr_convert_integer_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, integral_type value_p) noexcept
{
	static_assert(::std::is_integral<integral_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");
	ABORT_IF(string_out_ptrc_p == nullptr, "ERROR: string_out_ptrc_p is nullptr.");

	var::int8 l_integral_digits = numeric::count_integral_digit_length<integral_type>(value_p);
	var::boolean l_is_negative = false;

	if (value_p < 0)
	{
		l_is_negative = true;
		value_p = -value_p;
		++l_integral_digits;
	}

	ABORT_IF(input_string_capacity_p <= l_integral_digits, "CRITICAL ERROR: the digit length of an integer exceeds the output string buffer capacity");

	var::int8 l_idx = l_integral_digits - 1;
	while (value_p > 0)
	{
		string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
		value_p /= 10;
		--l_idx;
	}


	if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

	string_out_ptrc_p[l_integral_digits] = static_cast<char_type>('\0');
}


template<typename float_type, typename char_type>
_FORCE_INLINE_ void convert_float_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, float_type value_p) noexcept
{
	static_assert(::std::is_floating_point<float_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");
	ABORT_IF(string_out_ptrc_p == nullptr, "ERROR: string_out_ptrc_p is nullptr.");

	numeric::convert_integer_to_string<var::int64, char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<var::int64>(value_p));
	
	var::uint64 l_integral_part_string_length = algorithm::string::string_length<char_type>(string_out_ptrc_p);
	string_out_ptrc_p[l_integral_part_string_length] = '.';
	++l_integral_part_string_length;

	float_type l_floating_point = value_p - static_cast<float_type>(static_cast<var::int64>(value_p));
	while (0 !=  (l_floating_point - static_cast<var::int64>(l_floating_point)) )
	{
		l_floating_point *= 10.0f;
	}

	ABORT_IF(input_string_capacity_p <= (numeric::count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "CRITICAL ERROR: the digit length of the integral part exceeds the output string buffer capacity");

	numeric::convert_integer_to_string<var::int64, char_type>(string_out_ptrc_p + l_integral_part_string_length, input_string_capacity_p, static_cast<var::int64>(l_floating_point));
}

template<typename float_type, typename char_type>
_FORCE_INLINE_ constexpr void constexpr_convert_float_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, float_type value_p) noexcept
{
	static_assert(::std::is_floating_point<float_type>::value == true, "an illegal type of value_p assigned to the template argument integral_type");
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");
	ABORT_IF(string_out_ptrc_p == nullptr, "ERROR: string_out_ptrc_p is nullptr.");

	numeric::constexpr_convert_integer_to_string<var::int64, char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<var::int64>(value_p));

	var::uint64 l_integral_part_string_length = algorithm::string::string_length<char_type>(string_out_ptrc_p);
	string_out_ptrc_p[l_integral_part_string_length] = '.';
	++l_integral_part_string_length;

	float_type l_floating_point = value_p - static_cast<float_type>(static_cast<var::int64>(value_p));
	while (0 != (l_floating_point - static_cast<var::int64>(l_floating_point)))
	{
		l_floating_point *= 10;
	}

	ABORT_IF(input_string_capacity_p <= (numeric::count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "CRITICAL ERROR: the digit length of the integral part exceeds the output string buffer capacity");

	numeric::constexpr_convert_integer_to_string<var::int64, char_type>(string_out_ptrc_p + l_integral_part_string_length, input_string_capacity_p, static_cast<var::int64>(l_floating_point));
}


template<typename char_type>
_FORCE_INLINE_ const char_type* convert_boolean_to_string(boolean value_p) noexcept
{
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");

	return (value_p == true) ? static_cast<const char_type*>("true") : static_cast <const char_type*>("false");
}

template<typename char_type>
_FORCE_INLINE_ constexpr const char_type* constexpr_convert_boolean_to_string(boolean value_p) noexcept
{
	static_assert(sizeof(char_type) <= sizeof(UTF32), "an illegal type of value_p assigned to the template argument char_type");

	return (value_p == true) ? static_cast<const char_type *>("true") : static_cast < const char_type*>("false");
}

END_NAMESPACE

#pragma warning(pop)
#endif
