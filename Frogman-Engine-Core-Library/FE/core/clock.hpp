#ifndef _FE_CORE_CLOCK_HPP_
#define _FE_CORE_CLOCK_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <chrono>
#include <memory>
#include "prerequisite_symbols.h"


BEGIN_NAMESPACE(FE)


class clock final
{
public:
    using char_type = char;

    // const char* FE::clock::get_current_local_time() noexcept;
    _MAYBE_UNUSED_ static constexpr int _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_ = 64;

private:
    ::std::chrono::steady_clock::time_point m_starting_point;
    ::std::chrono::steady_clock::time_point m_ending_point;
    ::std::chrono::duration<var::float64> m_delta_time;

public:
    constexpr clock() noexcept : m_starting_point(), m_ending_point(), m_delta_time() {}
    constexpr ~clock() noexcept {}

    _FORCE_INLINE_ void start_clock() noexcept { this->m_starting_point = ::std::chrono::steady_clock::now(); }
    _FORCE_INLINE_ void end_clock() noexcept { this->m_ending_point = ::std::chrono::steady_clock::now(); }

    _FORCE_INLINE_ var::float64 get_delta_time() noexcept
    {
        this->m_delta_time = this->m_ending_point - this->m_starting_point;
        return this->m_delta_time.count();
    }

    const char_type* get_current_local_time() noexcept;
};


END_NAMESPACE
#endif