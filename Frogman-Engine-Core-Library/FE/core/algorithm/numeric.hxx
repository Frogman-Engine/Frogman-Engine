#ifndef _FE_CORE_ALGORITHM_NUMERIC_HXX_
#define _FE_CORE_ALGORITHM_NUMERIC_HXX_
#pragma warning(push)
#pragma warning(disable: 4244)
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "FE/core/types.h"
#include "FE/core/debug.h"
#include <FE/core/private/strlen.h>
#include <cstdio>




BEGIN_NAMESPACE(FE::algorithm::numeric)


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


END_NAMESPACE

#pragma warning(pop)
#endif
