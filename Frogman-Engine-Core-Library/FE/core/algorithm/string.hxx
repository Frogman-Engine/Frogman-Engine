#ifndef _FE_CORE_ALGORITHM_STRING_HXX_
#define _FE_CORE_ALGORITHM_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/heap_utilization.hpp>
#include <FE/core/containers/stack.hxx>
#include <array>
#include <optional>
#include <utility>


BEGIN_NAMESPACE(FE::algorithm::string)


_MAYBE_UNUSED_ static constexpr uint8 _ASCII_a_ = 97;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_z_ = 122;

_MAYBE_UNUSED_ static constexpr uint8 _ASCII_A_ = 65;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_Z_ = 90;
_MAYBE_UNUSED_ static constexpr uint8 _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ = 32;


struct string_range
{
    var::index_t _begin;
    var::index_t _end;
};


template<typename char_type>
struct target_char_count
{
    char_type _target_data;
    count_t _match_count;
};

template<typename char_type>
struct target_char_search_result
{
    char_type _target_data;
    index_t _target_data_location;
};


template <typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ int_type ascii_number_to_integer(char_type* cstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(cstr_ptr_p == nullptr, "ERROR: cstr_ptr_p is nullptr.");

    var::int16 l_sign = 1;
    if (*cstr_ptr_p == static_cast<const char_type>('-')) { l_sign = -1; }
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        ++cstr_ptr_p;
    }
    --cstr_ptr_p;

    int_type l_result = 0;
    int_type l_multiplier = 1;
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        l_result += static_cast<int_type>(*cstr_ptr_p - static_cast < const char_type>('0')) * l_multiplier;
        l_multiplier *= 10;
        --cstr_ptr_p;
    }
    return l_sign * l_result;
}

template <typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr int_type ascii_number_to_integer(const char_type* cstr_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(cstr_ptr_p == nullptr, "ERROR: cstr_ptr_p is nullptr.");

    var::int16 l_sign = 1;
    if (*cstr_ptr_p == static_cast<const char_type>('-')) { l_sign = -1; }
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        ++cstr_ptr_p;
    }
    --cstr_ptr_p;

    int_type l_result = 0;
    int_type l_multiplier = 1;
    while (*cstr_ptr_p >= static_cast<const char_type>('0') && *cstr_ptr_p <= static_cast<const char_type>('9') && *cstr_ptr_p != static_cast<const char_type>('\0'))
    {
        l_result += static_cast<int_type>(*cstr_ptr_p - static_cast <const char_type>('0')) * l_multiplier;
        l_multiplier *= 10;
        --cstr_ptr_p;
    }
    return l_sign * l_result;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::uint64 string_length(char_type* const str_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(str_ptrc_p == nullptr, "ERROR: str_ptrc_p is nullptr.");

    const char_type* l_iterator_ptr = str_ptrc_p;

    switch (*str_ptrc_p)
    {
    case  '\0':
        return 0;


    default:
        break;
    }

    while (*(++l_iterator_ptr) != static_cast<char_type>('\0')) _LIKELY_ {}

    return (l_iterator_ptr - str_ptrc_p);
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::uint64 string_length(const char_type* const str_ptrc_p) noexcept 
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(str_ptrc_p == nullptr, "ERROR: str_ptrc_p is nullptr.");

    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*str_ptrc_p == '\0')
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != static_cast<char_type>('\0')) {}

    return (l_iterator_ptr - str_ptrc_p);
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, string_range lstr_range_p, char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_lstr_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_rstr_length = rstr_range_p._end - rstr_range_p._begin;

    if ((l_lstr_length != l_rstr_length) || (l_lstr_length == 0))
    {
        return false;
    }

    const char_type* l_lstr_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_rstr_ptr = rstr_ptrc_p + rstr_range_p._begin;


    var::count_t l_character_match_count = 0;
    while ((l_character_match_count < l_lstr_length) && (*l_lstr_ptr == *l_rstr_ptr))
    {
        ++l_character_match_count;
        ++l_lstr_ptr;
        ++l_rstr_ptr;
    }

    if (l_character_match_count == l_lstr_length)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, string_range lstr_range_p, const char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_lstr_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_rstr_length = rstr_range_p._end - rstr_range_p._begin;

    if ((l_lstr_length != l_rstr_length) || (l_lstr_length == 0))
    {
        return false;
    }

    const char_type* l_lstr_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_rstr_ptr = rstr_ptrc_p + rstr_range_p._begin;


    var::count_t l_character_match_count = 0;
    while ((l_character_match_count < l_lstr_length) && (*l_lstr_ptr == *l_rstr_ptr))
    {
        ++l_character_match_count;
        ++l_lstr_ptr;
        ++l_rstr_ptr;
    }

    if (l_character_match_count == l_lstr_length)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, string_range lstr_range_p, char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_lstr_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_rstr_length = rstr_range_p._end - rstr_range_p._begin;

    if ((l_lstr_length != l_rstr_length) || (l_lstr_length == 0))
    {
        return false;
    }

    const char_type* l_lstr_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_rstr_ptr = rstr_ptrc_p + rstr_range_p._begin;


    var::count_t l_character_match_count = 0;
    while ((l_character_match_count < l_lstr_length) && (*l_lstr_ptr == *l_rstr_ptr))
    {
        ++l_character_match_count;
        ++l_lstr_ptr;
        ++l_rstr_ptr;
    }

    if (l_character_match_count == l_lstr_length)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, string_range lstr_range_p, const char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_lstr_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_rstr_length = rstr_range_p._end - rstr_range_p._begin;

    if ((l_lstr_length != l_rstr_length) || (l_lstr_length == 0))
    {
        return false;
    }

    const char_type* l_lstr_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_rstr_ptr = rstr_ptrc_p + rstr_range_p._begin;


    var::count_t l_character_match_count = 0;
    while ((l_character_match_count < l_lstr_length) && (*l_lstr_ptr == *l_rstr_ptr))
    {
        ++l_character_match_count;
        ++l_lstr_ptr;
        ++l_rstr_ptr;
    }

    if (l_character_match_count == l_lstr_length)
    {
        return true;
    }

    return false;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void copy_string(char_type* const destination_out_ptrc_p, count_t destination_count_p, const char_type* const source_ptrc_p, count_t source_count_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(destination_out_ptrc_p == nullptr, "ERROR: destination_out_ptrc_p is nullptr.");
    ABORT_IF(source_ptrc_p == nullptr, "ERROR: source_ptrc_p is nullptr.");


    ABORT_IF(destination_count_p < source_count_p, "CRITICAL ERROR: the source_count_p is greater than the destination_count_p");

    FE::memcpy_s(destination_out_ptrc_p, destination_count_p, sizeof(char_type), source_ptrc_p, source_count_p, sizeof(char_type));
    destination_out_ptrc_p[source_count_p] = static_cast<char_type>('\0');
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void capitalize_string(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(in_out_string_buffer_ptr_p == nullptr, "ERROR: in_out_string_buffer_ptr_p is nullptr.");


    while (*in_out_string_buffer_ptr_p != static_cast<char_type>('\0'))
    {
        if ((_ASCII_a_ <= static_cast<uint8>(*in_out_string_buffer_ptr_p) && static_cast<uint8>(*in_out_string_buffer_ptr_p) <= _ASCII_z_))
        {
            *in_out_string_buffer_ptr_p = static_cast<char_type>(static_cast<int16>(*in_out_string_buffer_ptr_p) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
        }
        ++in_out_string_buffer_ptr_p;
    }
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ char_type capitalize_character(const char_type char_value_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");

    if (_ASCII_a_ <= static_cast<uint8>(char_value_p) && static_cast<uint8>(char_value_p) <= _ASCII_z_)
    {
        return static_cast<char_type>(static_cast<int16>(char_value_p) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
    }

    return char_value_p;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void to_lowercase(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(in_out_string_buffer_ptr_p == nullptr, "ERROR: in_out_string_buffer_ptr_p is nullptr.");

    while (*in_out_string_buffer_ptr_p != static_cast<char_type>('\0'))
    {
        if ((_ASCII_A_ <= static_cast<uint8>(*in_out_string_buffer_ptr_p) && static_cast<uint8>(*in_out_string_buffer_ptr_p) <= _ASCII_Z_))
        {
            *in_out_string_buffer_ptr_p = static_cast<char_type>(static_cast<int16>(*in_out_string_buffer_ptr_p) + _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
        }
        ++in_out_string_buffer_ptr_p;
    }
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ char_type to_lowercase(const char_type char_value_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");

    if (_ASCII_A_ <= static_cast<uint8>(char_value_p) && static_cast<uint8>(char_value_p) <= _ASCII_Z_)
    {
        return static_cast<char_type>(static_cast<int16>(char_value_p) + _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
    }

    return char_value_p;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(const char_type* lstr_ptr_p, char_type* rstr_ptr_p) noexcept 
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptr_p == nullptr, "ERROR: lstr_ptr_p is nullptr.");
    ABORT_IF(rstr_ptr_p == nullptr, "ERROR: rstr_ptr_p is nullptr.");

    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(char_type* lstr_ptr_p, const char_type* rstr_ptr_p) noexcept 
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptr_p == nullptr, "ERROR: lstr_ptr_p is nullptr.");
    ABORT_IF(rstr_ptr_p == nullptr, "ERROR: rstr_ptr_p is nullptr.");

    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(char_type* lstr_ptr_p, char_type* rstr_ptr_p) noexcept 
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptr_p == nullptr, "ERROR: lstr_ptr_p is nullptr.");
    ABORT_IF(rstr_ptr_p == nullptr, "ERROR: rstr_ptr_p is nullptr.");

    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean string_comparison(const char_type* lstr_ptr_p, const char_type* rstr_ptr_p) noexcept 
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptr_p == nullptr, "ERROR: lstr_ptr_p is nullptr.");
    ABORT_IF(rstr_ptr_p == nullptr, "ERROR: rstr_ptr_p is nullptr.");

    while ((*lstr_ptr_p != static_cast<char_type>('\0')) && (*lstr_ptr_p == *rstr_ptr_p))
    {
        ++lstr_ptr_p;
        ++rstr_ptr_p;
    }

    if (!(*lstr_ptr_p - *rstr_ptr_p))
    {
        return true;
    }

    return false;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, string_range lstr_range_p, char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }
   
    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, string_range lstr_range_p, const char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, string_range lstr_range_p, char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ _CONSTEXPR23_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, string_range lstr_range_p, const char_type* const rstr_ptrc_p, string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void string_concatenation(char_type* const destination_out_ptrc_p, count_t destination_total_count_p, const char_type* const source_ptrc_p, count_t source_total_count_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(destination_out_ptrc_p == nullptr, "ERROR: destination_out_ptrc_p is nullptr.");
    ABORT_IF(source_ptrc_p == nullptr, "ERROR: source_ptrc_p is nullptr.");

    ABORT_IF(destination_total_count_p < source_total_count_p, "CRITICAL ERROR: the source_total_count_p is greater than the destination_total_count_p");

    length_t l_destination_string_length = algorithm::string::string_length<char_type>(destination_out_ptrc_p);

    FE::memcpy_s(destination_out_ptrc_p + l_destination_string_length, destination_total_count_p, sizeof(char_type), source_ptrc_p, source_total_count_p, sizeof(char_type));
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(char_type* const lstr_ptrc_p, const char_type* const rstr_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, const char_type* const rstr_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(lstr_ptrc_p == nullptr, "ERROR: lstr_ptrc_p is nullptr.");
    ABORT_IF(rstr_ptrc_p == nullptr, "ERROR: rstr_ptrc_p is nullptr.");

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize_character(*l_left_string_ptr) == string::capitalize_character(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
    {
        ++l_left_string_ptr;
        ++l_right_string_ptr;
    }

    if (*l_left_string_ptr == *l_right_string_ptr)
    {
        return true;
    }

    return false;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void capitalize_every_first_letter_of_words(char_type* in_out_string_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(in_out_string_ptr_p == nullptr, "ERROR: in_out_string_ptr_p is nullptr.");

    if ((*in_out_string_ptr_p != static_cast<char_type>(' ')) || (*in_out_string_ptr_p != static_cast<char_type>('_')))
    {
        *in_out_string_ptr_p = static_cast<int16>(*in_out_string_ptr_p) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
    }

    while (*in_out_string_ptr_p != static_cast<char_type>('\0'))
    {
        if (((*in_out_string_ptr_p == static_cast<char_type>(' ')) && (in_out_string_ptr_p[1] != static_cast<char_type>(' '))) ||
            ((*in_out_string_ptr_p == static_cast<char_type>('_')) && (in_out_string_ptr_p[1] != static_cast<char_type>('_'))))
        {
            if ( ((_ASCII_A_ <= in_out_string_ptr_p[1]) && (in_out_string_ptr_p[1] <= _ASCII_Z_))
                || ((_ASCII_a_ <= in_out_string_ptr_p[1]) && (in_out_string_ptr_p[1] <= _ASCII_z_)) )
            {
                in_out_string_ptr_p[1] = static_cast<int16>(in_out_string_ptr_p[1]) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
            }
        }
        ++in_out_string_ptr_p;
    }
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void invert_string(char_type* const in_out_string_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(in_out_string_ptrc_p == nullptr, "ERROR: in_out_string_ptrc_p is nullptr.");

    var::index_t l_start = 0;
    var::index_t l_end = algorithm::string::string_length(in_out_string_ptrc_p);

    char_type l_temporary = static_cast<char_type>('\0');
    while ( l_start < l_end )
    {
        l_temporary = in_out_string_ptrc_p[l_start];
        --l_end;
        in_out_string_ptrc_p[l_start] = in_out_string_ptrc_p[l_end];
        in_out_string_ptrc_p[l_end] = l_temporary;
        ++l_start;
    }
}


/*  This function can be useful when a string needs to be hashed during compile time.
    TIP: collaborate this function with switch cases.
*/
template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ constexpr var::uint64 hash_string(const char_type* const string_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptrc_p == nullptr, "ERROR: string_ptrc_p is nullptr.");

    uint64 l_string_length = algorithm::string::string_length(string_ptrc_p);

    if (l_string_length == 0)
    {
        return 0;
    }

    var::uint64 l_hash = 0;
    for (var::uint64 i = 0; i < l_string_length; ++i)
    {
        l_hash = (l_hash * l_hash * l_hash) + string_ptrc_p[i];
    }

    return l_hash;
}
#define SWITCH(string_p) switch( ::FE::algorithm::string::hash_string(string_p) )
#define CASE(string_p) case ::FE::algorithm::string::hash_string(string_p)


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_search_result<char_type> search_very_first_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptrc_p == nullptr, "ERROR: string_ptrc_p is nullptr.");

    const char_type* l_string_ptr = string_ptrc_p;
    while (*l_string_ptr != static_cast<char_type>('\0'))
    {
        if (*l_string_ptr == target_char_p)
        {
            return target_char_search_result<char_type>{*l_string_ptr, static_cast<index_t>(l_string_ptr - string_ptrc_p) };
        }
        ++l_string_ptr;
    }
        
    return target_char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_search_result<char_type> search_very_last_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptrc_p == nullptr, "ERROR: string_ptrc_p is nullptr.");

    var::index_t l_target_char_location = 0;

    const char_type* l_string_ptr = string_ptrc_p;
    while (*l_string_ptr != static_cast<char_type>('\0'))
    {
        if (*l_string_ptr == target_char_p)
        {
            l_target_char_location = l_string_ptr - string_ptrc_p;
        }
        ++l_string_ptr;
    }

    return target_char_search_result<char_type>{ string_ptrc_p[l_target_char_location], l_target_char_location};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_count<char_type> search_all_corresponding_characters(char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptr_p == nullptr, "ERROR: string_ptr_p is nullptr.");

    var::count_t l_match_count = 0;

    while (*string_ptr_p != static_cast<char_type>('\0'))
    {
        if (target_char_p == *string_ptr_p)
        {
            ++l_match_count;
        }
        ++string_ptr_p;
    }

    char_type l_target_char_buffer = static_cast<char_type>('\0');

    if (l_match_count != 0)
    {
        l_target_char_buffer = target_char_p;
    }

    return target_char_count<char_type>{l_target_char_buffer, l_match_count};
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr target_char_count<char_type> search_all_corresponding_characters(const char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptr_p == nullptr, "ERROR: string_ptr_p is nullptr.");

    var::count_t l_match_count = 0;

    while (*string_ptr_p != static_cast<char_type>('\0'))
    {
        if (target_char_p == *string_ptr_p)
        {
            ++l_match_count;
        }
        ++string_ptr_p;
    }

    char_type l_target_char_buffer = static_cast<char_type>('\0');

    if (l_match_count != 0)
    {
        l_target_char_buffer = target_char_p;
    }

    return target_char_count<char_type>{l_target_char_buffer, l_match_count};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ ::std::optional<string_range> search_very_first_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptrc_p == nullptr, "ERROR: string_ptrc_p is nullptr.");
    ABORT_IF(target_substring_ptrc_p == nullptr, "ERROR: target_substring_ptrc_p is nullptr.");

    const char_type* l_string_ptr = string_ptrc_p;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;

    length_t l_target_substring_length = string::string_length(target_substring_ptrc_p);

    ABORT_IF(l_target_substring_length >= string::string_length(string_ptrc_p), "CRITICAL ERROR: the l_target_substring_length is greater than or equal to the string length of string_ptrc_p");

    while (*l_target_substring_ptr != static_cast<char_type>('\0'))
    {
        if (*l_string_ptr == *l_target_substring_ptr)
        {
            ++l_string_ptr;
            ++l_target_substring_ptr;
            continue;
        }
        ++l_string_ptr;
        l_target_substring_ptr = target_substring_ptrc_p;
    }

    if (l_target_substring_ptr[-1] == l_string_ptr[-1])
    {
        index_t l_begin = (l_string_ptr - string_ptrc_p) - l_target_substring_length;
        index_t l_end = l_string_ptr - string_ptrc_p;

        return  std::make_optional<string_range>(l_begin, l_end);
    }

    return ::std::nullopt;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_IN_DEVELOPMENT_ _NODISCARD_ _FORCE_INLINE_::std::optional<string_range> search_very_last_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(string_ptrc_p == nullptr, "ERROR: string_ptrc_p is nullptr.");
    ABORT_IF(target_substring_ptrc_p == nullptr, "ERROR: target_substring_ptrc_p is nullptr.");

    length_t l_string_length = algorithm::string::string_length(string_ptrc_p);
    length_t l_target_letters_length = algorithm::string::string_length(target_substring_ptrc_p);

    const char_type* l_string_ptr = string_ptrc_p + l_string_length;

    if (l_string_length < l_target_letters_length) { return ::std::nullopt; }

    var::count_t l_match_count = 0;
    for (; *target_substring_ptrc_p != static_cast<char_type>('\0'); --l_string_ptr)
    {
        if (*l_string_ptr == *target_substring_ptrc_p)
        {
            for (l_match_count = 0; (l_string_ptr[l_match_count] == target_substring_ptrc_p[l_match_count]) && (l_string_ptr[l_match_count] != '\0'); ++l_match_count) {}
            if (l_match_count == l_target_letters_length) { return ::std::optional<string_range>(string_range{ static_cast<var::index_t>(l_string_ptr - string_ptrc_p), static_cast<var::index_t>((l_string_ptr - string_ptrc_p) + l_match_count) }); }
        }
    }

    return ::std::nullopt;


    //length_t l_string_length = algorithm::string::string_length(string_ptrc_p);
    //length_t l_target_substring_length = algorithm::string::string_length(target_substring_ptrc_p);

    //ABORT_IF(l_target_substring_length >= l_string_length, "CRITICAL ERROR: l_target_substring_length is greater than or equal to the l_string_length");

    //const char_type* const l_string_end_ptrc = string_ptrc_p + l_string_length;
    //const char_type* l_target_substring_begin_ptr = target_substring_ptrc_p;

    //const char_type* l_string_rbegin_ptr = l_string_end_ptrc - 1;
    //const char_type* const l_string_rend_ptrc = string_ptrc_p - 1;
}


// search_very_first_substring_within_range
// search_very_last_substring_within_range

// search_very_first_character_within_range
// search_very_last_character_within_range
// search_all_corresponding_characters_within_range


template<typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ int_type ascii_character_number_to_int(char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    static_assert(::std::is_integral<int_type>::value == true, "typename int_type is not an integer");


    return static_cast<int_type>(target_char_p) - 48;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void concatenate_strings(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, ::std::initializer_list<const char_type* const>&& strings_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(out_string_buffer_ptrc_p == nullptr, "ERROR: out_string_buffer_ptrc_p is nullptr.");

    var::size_t l_current_begin_index = algorithm::string::string_length(out_string_buffer_ptrc_p);

    for (var::size_t i = 0; i < strings_p.size(); ++i)
    {
        size_t l_string_length_buffer = algorithm::string::string_length(strings_p.begin()[i]);

        ABORT_IF(string_buffer_size_p <= l_current_begin_index, "CRITICAL ERROR: the string_buffer_size_p is smaller or equal to the l_current_begin_index");

        ::FE::memcpy_s(out_string_buffer_ptrc_p + l_current_begin_index, string_buffer_size_p, sizeof(char_type), strings_p.begin()[i], l_string_length_buffer, sizeof(char_type));
        l_current_begin_index += l_string_length_buffer;
    }
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void concatenate_characters(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, ::std::initializer_list<const char_type>&& strings_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    ABORT_IF(out_string_buffer_ptrc_p == nullptr, "ERROR: out_string_buffer_ptrc_p is nullptr.");

    var::length_t l_string_buffer_length = algorithm::string::string_length(out_string_buffer_ptrc_p);

    ABORT_IF(string_buffer_size_p <= strings_p.size() + l_string_buffer_length, "CRITICAL ERROR: The total input string length exceeds the destination string buffer capacity");
    
    ::memcpy(out_string_buffer_ptrc_p + l_string_buffer_length, strings_p.begin(), sizeof(char_type) * strings_p.size());
}


END_NAMESPACE
#endif 
