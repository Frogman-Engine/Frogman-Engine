#ifndef _FE_CORE_RANDOM_HXX_
#define _FE_CORE_RANDOM_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include <optional>
#include <random>


BEGIN_NAMESPACE(FE)


template <typename T>
class random_int final
{
    static_assert(::std::is_integral<T>::value == true, "typename T is not an integral type");

private:
    ::std::optional<::std::mt19937_64> m_value_generator;
    ::std::optional<::std::uniform_int_distribution<T>> m_uniform_int_distribution;

public:
    typedef T value_type;

    random_int() noexcept = default;
    random_int(T min_range_p, T max_range_p) noexcept : m_value_generator(::std::mt19937_64{ static_cast<var::uint64>(time(NULL)) }), m_uniform_int_distribution(::std::uniform_int_distribution<T>{ min_range_p, max_range_p }) {}

    ~random_int() noexcept = default;


    T ranged_random_int() noexcept { return (*this->m_uniform_int_distribution)(*this->m_value_generator); }

    T ranged_random_int(T min_range_p, T max_range_p) noexcept
    {
        if (!this->m_value_generator)
        {
            this->m_value_generator.emplace(static_cast<var::uint64>(time(NULL)));
        }

        if (!this->m_uniform_int_distribution)
        {
            this->m_uniform_int_distribution.emplace(min_range_p, max_range_p);
        }

        return (*this->m_uniform_int_distribution)(*this->m_value_generator);
    }
};


template <typename T>
class random_float final
{
    static_assert(::std::is_floating_point<T>::value == true, "typename T is not a floating point type");

private:
    ::std::optional<::std::mt19937_64> m_value_generator;
    ::std::optional<::std::uniform_real_distribution<T>> m_uniform_real_distribution;

public:
    typedef T value_type;

    random_float() noexcept = default;
    random_float(T min_range_p, T max_range_p) noexcept : m_value_generator(::std::mt19937_64{ static_cast<var::uint64>(time(NULL)) }), m_uniform_real_distribution(::std::uniform_real_distribution<T>{ min_range_p, max_range_p }) {}

    ~random_float() noexcept = default;


    T ranged_random_float() noexcept { return (*this->m_uniform_real_distribution)(*this->m_value_generator); }

    T ranged_random_float(T min_range_p, T max_range_p) noexcept
    {
        if (!this->m_value_generator)
        {
            this->m_value_generator.emplace(static_cast<var::uint64>(time(NULL)));
        }

        if (!this->m_uniform_real_distribution)
        {
            this->m_uniform_real_distribution.emplace(min_range_p, max_range_p);
        }

        return (*this->m_uniform_real_distribution)(*this->m_value_generator);
    }
};



END_NAMESPACE
#endif
