#ifndef _FE_CORE_MATH_HXX_
#define _FE_CORE_MATH_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"


BEGIN_NAMESPACE(FE)


template<typename T>
_FORCE_INLINE_ constexpr T abs(T value_p) noexcept
{
	static_assert(sizeof(T), "T is not a float nor an integer type.");

	if(value_p < static_cast<T>(0))
	{
		return value_p * static_cast<T>(-1);
	}

	return value_p;
}

template<typename T>
_FORCE_INLINE_ constexpr T select_greatest(const T& a_cref_p, const T& b_cref_p) noexcept
{
	if (a_cref_p > b_cref_p)
	{
		return a_cref_p;
	}

	return b_cref_p;
}

template<typename T>
_FORCE_INLINE_ constexpr T select_smallest(const T& a_cref_p, const T& b_cref_p) noexcept
{
	if (a_cref_p < b_cref_p)
	{
		return a_cref_p;
	}

	return b_cref_p;
}

// It compares two floating point values to determine whether they are within the tolerance range.
_FORCE_INLINE_ constexpr boolean is_it_nearly_equal(float64 A_p, float64 B_p, var::float64 tolerance_p) noexcept
{
	if (tolerance_p < FE::_ACCURATE_MINIMUM_FLOAT_VALUE_)
	{
		tolerance_p = FE::_ACCURATE_MINIMUM_FLOAT_VALUE_;
	}
	if (A_p + tolerance_p >= B_p && B_p >= A_p - tolerance_p)
	{
		return true;
	}
	return false;
}


END_NAMESPACE
#endif
