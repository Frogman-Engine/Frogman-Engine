﻿#ifndef _FE_CORE_RANDOM_HXX_
#define _FE_CORE_RANDOM_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/types.hxx>

// std
#include <optional>
#include <random>




BEGIN_NAMESPACE(FE)


template <typename T>
class random_integer final
{
    static_assert(std::is_integral<T>::value == true, "typename T is not an integral type");

    std::optional<std::mt19937_64> m_value_generator;
    std::optional<std::uniform_int_distribution<T>> m_uniform_int_distribution;

public:
    using value_type = T;

    random_integer() noexcept : m_value_generator(::std::mt19937_64{ static_cast<var::uint64>(time(NULL)) }) {}
    _FE_CONSTEXPR20_ ~random_integer() noexcept {}

    _FE_FORCE_INLINE_ T ranged_random_integer(T min_range_p, T max_range_p) noexcept
    {
        this->m_uniform_int_distribution.emplace(min_range_p, max_range_p);
        return (*this->m_uniform_int_distribution)(*this->m_value_generator);
    }
};


template <typename T>
class random_float final
{
    static_assert(::std::is_floating_point<T>::value == true, "typename T is not a floating point type");

    std::optional<::std::mt19937_64> m_value_generator;
    std::optional<::std::uniform_real_distribution<T>> m_uniform_real_distribution;

public:
    using value_type = T;

    random_float() noexcept : m_value_generator(::std::mt19937_64{ static_cast<var::uint64>(time(NULL)) }) {}
    _FE_CONSTEXPR20_ ~random_float() noexcept {};

    _FE_FORCE_INLINE_ T ranged_random_float(T min_range_p, T max_range_p) noexcept
    {
        this->m_uniform_real_distribution.emplace(min_range_p, max_range_p);
        return (*this->m_uniform_real_distribution)(*this->m_value_generator);
    }
};



END_NAMESPACE
#endif
