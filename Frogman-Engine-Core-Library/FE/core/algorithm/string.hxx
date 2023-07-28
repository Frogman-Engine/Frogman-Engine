#ifndef _FE_CORE_ALGORITHM_STRING_HXX_
#define _FE_CORE_ALGORITHM_STRING_HXX_
#pragma warning(push)
#pragma warning(disable: 4702)
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/algorithm/numeric.hxx>
#include <FE/core/iterator.hxx>
#include <FE/core/optional.hxx>
// Visual Studio v143 C++20 compiler has a bug in release build mode. The compiler options are /WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy- /GT /MT /Gy /GL /arch:AVX
// has_value() returns true even if search_very_last_substring returns std::nullopt.
#include <utility>
#include <bitset>




#define _MAX_NUMERIC_STRING_LENGTH_ 512
#define _256_BYTES_BIT_COUNT_ 2048




BEGIN_NAMESPACE(FE::algorithm::string)


_MAYBE_UNUSED_ constexpr int8 _ASCII_a_ = 97;
_MAYBE_UNUSED_ constexpr int8 _ASCII_z_ = 122;

_MAYBE_UNUSED_ constexpr int8 _ASCII_A_ = 65;
_MAYBE_UNUSED_ constexpr int8 _ASCII_Z_ = 90;
_MAYBE_UNUSED_ constexpr int8 _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ = 32;
_MAYBE_UNUSED_ constexpr int8 _ASCII_CODE_ZERO_ = 48;


struct range
{
    var::index_t _begin;
    var::index_t _end;
};

template<typename char_type>
struct char_count
{
    char_type _target_data;
    count_t _match_count;
};

template<typename char_type>
struct char_search_result
{
    char_type _target_data;
    index_t _target_data_location;
};


template <typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ int_type string_to_integer(char_type* cstr_ptr_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(cstr_ptr_p == nullptr, "DETECTED NULLPTR: cstr_ptr_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ constexpr int_type string_to_integer(const char_type* cstr_ptr_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(cstr_ptr_p == nullptr, "DETECTED NULLPTR: cstr_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(str_ptrc_p == nullptr, "DETECTED NULLPTR: str_ptrc_p is nullptr.");

    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*str_ptrc_p == _NULL_)
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != _NULL_) _LIKELY_ {}

    return (l_iterator_ptr - str_ptrc_p);
}

template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr var::uint64 string_length(const char_type* const str_ptrc_p) noexcept 
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(str_ptrc_p == nullptr, "DETECTED NULLPTR: str_ptrc_p is nullptr.");

    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*str_ptrc_p == _NULL_)
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != _NULL_) {}

    return (l_iterator_ptr - str_ptrc_p);
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_FORCE_INLINE_ void copy_string(char_type* const destination_out_ptrc_p, capacity_t destination_size_p, const char_type* const source_ptrc_p, capacity_t source_size_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(destination_out_ptrc_p == nullptr, "NULLPTR DETECTED: destination_out_ptrc_p is nullptr.");
    FE_ASSERT(source_ptrc_p == nullptr, "NULLPTR DETECTED: source_ptrc_p is nullptr.");


    FE_ASSERT(destination_size_p < source_size_p, "MEMORY BOUNDARY CHECK FAILURE: the source_count_p is greater than the destination_count_p");

    if(source_size_p != 0)
    { 
        std::memcpy(destination_out_ptrc_p, source_ptrc_p, source_size_p * sizeof(char_type));
    }
    destination_out_ptrc_p[source_size_p] = static_cast<char_type>('\0');
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void capitalize_string(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_buffer_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_buffer_ptr_p is nullptr.");


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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_buffer_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_buffer_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.");
    FE_ASSERT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.");
    FE_ASSERT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.");
    FE_ASSERT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.");
    FE_ASSERT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
_NODISCARD_ _FORCE_INLINE_ _CONSTEXPR23_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(destination_out_ptrc_p == nullptr, "NULLPTR DETECTED: destination_out_ptrc_p is nullptr.");
    FE_ASSERT(source_ptrc_p == nullptr, "NULLPTR DETECTED: source_ptrc_p is nullptr.");

    FE_ASSERT(destination_total_count_p < source_total_count_p, "MEMORY BOUNDARY CHECK FAILURE: the source_total_count_p is greater than the destination_total_count_p");

    length_t l_destination_string_length = algorithm::string::string_length<char_type>(destination_out_ptrc_p);
 
    std::memcpy(destination_out_ptrc_p + l_destination_string_length, source_ptrc_p, source_total_count_p * sizeof(char_type));
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.");
    FE_ASSERT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_ptr_p is nullptr.");

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
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_ptrc_p == nullptr, "NULLPTR DETECTED: in_out_string_ptrc_p is nullptr.");

    var::index_t l_start = 0;
    var::index_t l_end = string_length(in_out_string_ptrc_p);

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


/*  
This function can be useful when a string needs to be hashed during compile time.
TIP: collaborate this function with switch cases.
*/
template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ constexpr var::uint64 hash_string(const char_type* const string_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");

    length_t l_string_length = string_length(string_ptrc_p);

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
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_very_first_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");

    const char_type* l_string_ptr = string_ptrc_p;
    while (*l_string_ptr != static_cast<char_type>('\0'))
    {
        if (*l_string_ptr == target_char_p)
        {
            return char_search_result<char_type>{*l_string_ptr, static_cast<index_t>(l_string_ptr - string_ptrc_p) };
        }
        ++l_string_ptr;
    }
        
    return char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_very_last_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rbegin = string_ptrc_p + (string_length(string_ptrc_p)-1);
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rend = string_ptrc_p - 1;

    while (l_string_rbegin != l_string_rend)
    {
        if (*l_string_rbegin == target_char_p)
        {
            return char_search_result<char_type>{*l_string_rbegin, static_cast<index_t>(l_string_rbegin.operator->() - string_ptrc_p) };
        }
        ++l_string_rbegin;
    }

    return char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ char_count<char_type> count_chars(char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.");

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

    return char_count<char_type>{l_target_char_buffer, l_match_count};
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr char_count<char_type> count_chars(const char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.");

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

    return char_count<char_type>{l_target_char_buffer, l_match_count};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_very_first_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
    FE_ASSERT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.");

    const char_type* l_string_ptr = string_ptrc_p;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_length(string_ptrc_p);
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);
 
    FE_ASSERT(l_target_substring_length > l_string_length, "CRITICAL ERROR: the l_target_substring_length is greater than or equal to the string length of string_ptrc_p");

    var::index_t l_string_idx = 0;
    while (*l_target_substring_ptr != static_cast<char_type>('\0') && l_string_idx < l_string_length)
    {
        if (*l_string_ptr == *l_target_substring_ptr)
        {
            ++l_string_ptr;
            ++l_target_substring_ptr;
            continue;
        }
        ++l_string_ptr;
        l_target_substring_ptr = target_substring_ptrc_p;
        ++l_string_idx;
    }

    index_t l_begin = (l_string_ptr - string_ptrc_p) - (l_target_substring_ptr - target_substring_ptrc_p);
    index_t l_end = l_string_ptr - string_ptrc_p;

    if (compare_ranged_strings(string_ptrc_p, range{ l_begin, l_end }, target_substring_ptrc_p, range{ 0, l_target_substring_length }))
    {
        return std::move(range(l_begin, l_end));
    }

    return FE::nullopt;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_very_last_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
    FE_ASSERT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.");

    length_t l_string_length = string_length(string_ptrc_p);
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_crbegin(string_ptrc_p + (l_string_length - 1));

    const FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crbegin_read_only(target_substring_ptrc_p + (l_target_substring_length - 1));
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crbegin = l_target_substring_crbegin_read_only;

    const FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crend_read_only(target_substring_ptrc_p - 1);

    var::index_t l_string_idx = 0;
    while (l_target_substring_crbegin != l_target_substring_crend_read_only && l_string_idx < l_string_length)
    {
        if (*l_string_crbegin == *l_target_substring_crbegin)
        {
            ++l_string_crbegin;
            ++l_target_substring_crbegin;
            continue;
        }
        ++l_string_crbegin;
        l_target_substring_crbegin = l_target_substring_crbegin_read_only;
        ++l_string_idx;
    }

    index_t l_begin = (l_string_crbegin.operator->() - string_ptrc_p) + 1;
    index_t l_end = ((l_string_crbegin.operator->() + l_target_substring_length) - string_ptrc_p) + 1;

    if ( compare_ranged_strings(string_ptrc_p, range{ l_begin, l_end }, target_substring_ptrc_p, range{0, l_target_substring_length}) )
    {
        return  std::move(range(l_begin, l_end));
    }

    return FE::nullopt;
}




template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_very_first_char_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");
    
    const char_type* l_string_ptr = string_ptrc_p + string_range_p._begin;
    while (*l_string_ptr != static_cast<char_type>('\0'))
    {
        if (*l_string_ptr == target_char_p)
        {
            return char_search_result<char_type>{*l_string_ptr, static_cast<index_t>(l_string_ptr - string_ptrc_p) };
        }
        ++l_string_ptr;
    }

    return char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_very_last_char_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
   FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
   FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
   FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rbegin = string_ptrc_p + (string_range_p._end - 1);
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rend = string_ptrc_p + (string_range_p._begin - 1);

    while (l_string_rbegin != l_string_rend)
    {
        if (*l_string_rbegin == target_char_p)
        {
            return char_search_result<char_type>{*l_string_rbegin, static_cast<index_t>(l_string_rbegin.operator->() - string_ptrc_p) };
        }
        ++l_string_rbegin;
    }

    return char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ char_count<char_type> count_all_corresponding_chars_within_range(char_type* string_ptr_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
    FE_ASSERT(string_length(string_ptr_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");

    var::count_t l_match_count = 0;
    string_ptr_p += string_range_p._begin;

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

    return char_count<char_type>{l_target_char_buffer, l_match_count};
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr char_count<char_type> count_all_corresponding_chars_within_range(const char_type* string_ptr_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
    FE_ASSERT(string_length(string_ptr_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");

    var::count_t l_match_count = 0;
    string_ptr_p += string_range_p._begin;

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

    return char_count<char_type>{l_target_char_buffer, l_match_count};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_very_first_substring_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
    FE_ASSERT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.");
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");

    const char_type* l_string_ptr = string_ptrc_p + string_range_p._begin;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_range_p._end - string_range_p._begin;
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);

    FE_ASSERT(l_target_substring_length > l_string_length, "CRITICAL ERROR: the l_target_substring_length is greater than or equal to the string length of string_ptrc_p");

    var::index_t l_string_idx = 0;
    while (*l_target_substring_ptr != static_cast<char_type>('\0') && l_string_idx < l_string_length)
    {
        if (*l_string_ptr == *l_target_substring_ptr)
        {
            ++l_string_ptr;
            ++l_target_substring_ptr;
            continue;
        }
        ++l_string_ptr;
        l_target_substring_ptr = target_substring_ptrc_p;
        ++l_string_idx;
    }

    index_t l_begin = (l_string_ptr - string_ptrc_p) - (l_target_substring_ptr - target_substring_ptrc_p);
    index_t l_end = l_string_ptr - string_ptrc_p;

    if (compare_ranged_strings(string_ptrc_p, range{l_begin, l_end}, target_substring_ptrc_p, range{0, l_target_substring_length}))
    {
        return  std::move(range(l_begin, l_end));
    }

    return FE::nullopt;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_very_last_substring_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.");
    FE_ASSERT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.");
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "INVALID RANGE DETECTED: string_range_p._end cannot be greater than the length of string_ptrc_p.");

    length_t l_string_length = string_range_p._end - string_range_p._begin;
    length_t l_target_substring_length = algorithm::string::string_length(target_substring_ptrc_p);

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_crbegin(string_ptrc_p + (l_string_length - 1));

    const FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crbegin_read_only(target_substring_ptrc_p + (l_target_substring_length - 1));
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crbegin = l_target_substring_crbegin_read_only;

    const FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_target_substring_crend_read_only(target_substring_ptrc_p - 1);

    var::index_t l_string_idx = 0;
    while (l_target_substring_crbegin != l_target_substring_crend_read_only && l_string_idx < l_string_length)
    {
        if (*l_string_crbegin == *l_target_substring_crbegin)
        {
            ++l_string_crbegin;
            ++l_target_substring_crbegin;
            continue;
        }
        ++l_string_crbegin;
        l_target_substring_crbegin = l_target_substring_crbegin_read_only;
        ++l_string_idx;
    }

    index_t l_begin = (l_string_crbegin.operator->() - string_ptrc_p) + 1;
    index_t l_end = ((l_string_crbegin.operator->() + l_target_substring_length) - string_ptrc_p) + 1;

    if (compare_ranged_strings(string_ptrc_p, range{ l_begin, l_end }, target_substring_ptrc_p, range{ 0, l_target_substring_length }))
    {
        return  std::move(range(l_begin, l_end));
    }

    return FE::nullopt;
}




template<typename char_type, typename int_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ int_type char_to_integer(char_type target_char_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    static_assert(::std::is_integral<int_type>::value == true, "typename int_type is not an integer");

    return static_cast<int_type>(target_char_p) - 48;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void concatenate_strings(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, ::std::initializer_list<const char_type* const>&& strings_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    ABORT_IF(out_string_buffer_ptrc_p == nullptr, "NULLPTR DETECTED: out_string_buffer_ptrc_p is nullptr.");

    var::size_t l_current_begin_index = algorithm::string::string_length(out_string_buffer_ptrc_p);

    for (var::size_t i = 0; i < strings_p.size(); ++i)
    {
        size_t l_string_length_buffer = algorithm::string::string_length(strings_p.begin()[i]);

        ABORT_IF(string_buffer_size_p <= l_current_begin_index, "MEMORY BOUNDARY CHECK FAILURES: the string_buffer_size_p is smaller or equal to the l_current_begin_index");

        std::memcpy(out_string_buffer_ptrc_p + l_current_begin_index, strings_p.begin()[i], l_string_length_buffer * sizeof(char_type));
        l_current_begin_index += l_string_length_buffer;
    }
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void concatenate_characters(char_type* const out_string_buffer_ptrc_p, _MAYBE_UNUSED_ size_t string_buffer_size_p, ::std::initializer_list<const char_type>&& chars_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(out_string_buffer_ptrc_p == nullptr, "NULLPTR DETECTED: out_string_buffer_ptrc_p is nullptr.");

    var::length_t l_string_buffer_length = algorithm::string::string_length(out_string_buffer_ptrc_p);

    FE_ASSERT(string_buffer_size_p <= chars_p.size() + l_string_buffer_length, "MEMORY BOUNDARY CHECK FAILURE: The total input string length exceeds the destination string buffer capacity.");
    
    ::memcpy(out_string_buffer_ptrc_p + l_string_buffer_length, chars_p.begin(), sizeof(char_type) * chars_p.size());
}




template<typename char_type>
_FORCE_INLINE_ void int_to_string(char_type* const string_out_ptrc_p, _MAYBE_UNUSED_ length_t input_string_capacity_p, var::int64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");
    FE_ASSERT(value_p == FE::_MIN_VALUE_<var::int64>, "NaCN ERROR: value_p is not a calculatable number");

    var::int8 l_integral_digits = numeric::count_integral_digit_length<var::int64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p < 0)
    {
        l_is_negative = true;
        value_p *= -1;
        ++l_integral_digits;
    }
    else if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    FE_ASSERT(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

    var::int8 l_idx = l_integral_digits - 1;
    while (value_p > 0)
    {
        string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
        value_p /= 10;
        --l_idx;
    }


    if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

    string_out_ptrc_p[l_integral_digits] = _NULL_;
}

template<typename char_type>
_FORCE_INLINE_ constexpr void constexpr_int_to_string(char_type* const string_out_ptrc_p, _MAYBE_UNUSED_ length_t input_string_capacity_p, var::int64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = numeric::count_integral_digit_length<var::int64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p < 0)
    {
        l_is_negative = true;
        value_p *= -1;
        ++l_integral_digits;
    }
    else if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    FE_ASSERT(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

    var::int8 l_idx = l_integral_digits - 1;
    while (value_p > 0)
    {
        string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
        value_p /= 10;
        --l_idx;
    }


    if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

    string_out_ptrc_p[l_integral_digits] = _NULL_;
}


template<typename char_type>
_FORCE_INLINE_ void uint_to_string(char_type* const string_out_ptrc_p, _MAYBE_UNUSED_ length_t input_string_capacity_p, var::uint64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = numeric::count_integral_digit_length<var::uint64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    FE_ASSERT(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

    var::int8 l_idx = l_integral_digits - 1;
    while (value_p > 0)
    {
        string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
        value_p /= 10;
        --l_idx;
    }


    if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

    string_out_ptrc_p[l_integral_digits] = _NULL_;
}

template<typename char_type>
_FORCE_INLINE_ constexpr void constexpr_uint_to_string(char_type* const string_out_ptrc_p, _MAYBE_UNUSED_ length_t input_string_capacity_p, var::uint64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = numeric::count_integral_digit_length<var::uint64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    FE_ASSERT(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

    var::int8 l_idx = l_integral_digits - 1;
    while (value_p > 0)
    {
        string_out_ptrc_p[l_idx] = _ASCII_CODE_ZERO_ + (value_p % 10);
        value_p /= 10;
        --l_idx;
    }


    if (l_is_negative) { *string_out_ptrc_p = static_cast<char_type>('-'); }

    string_out_ptrc_p[l_integral_digits] = _NULL_;
}


template<typename char_type>
_FORCE_INLINE_ void float_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, float64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    int_to_string<char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<var::int64>(value_p));

    var::uint64 l_integral_part_string_length = internal::strlen<char_type>(string_out_ptrc_p);
    string_out_ptrc_p[l_integral_part_string_length] = '.';
    ++l_integral_part_string_length;

    var::float64 l_floating_point = value_p - static_cast<float64>(static_cast<var::int64>(value_p));
    while (0 != (l_floating_point - static_cast<var::int64>(l_floating_point)))
    {
        l_floating_point *= 10.0f;
    }

    FE_ASSERT(input_string_capacity_p <= (numeric::count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "MEMORY BOUNDRY CHECK FAILURE: the digit length of the integral part exceeds the output string buffer capacity");

    int_to_string<char_type>(string_out_ptrc_p + l_integral_part_string_length, input_string_capacity_p, static_cast<var::int64>(l_floating_point));
}

template<typename char_type>
_FORCE_INLINE_ constexpr void constexpr_float_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, float64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    FE_ASSERT(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    constexpr_int_to_string<char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<int64>(value_p));

    var::uint64 l_integral_part_string_length = internal::strlen<char_type>(string_out_ptrc_p);
    string_out_ptrc_p[l_integral_part_string_length] = '.';
    ++l_integral_part_string_length;

    var::float64 l_floating_point = value_p - static_cast<float64>(static_cast<var::int64>(value_p));
    while (0 != (l_floating_point - static_cast<var::int64>(l_floating_point)))
    {
        l_floating_point *= 10;
    }

    FE_ASSERT(input_string_capacity_p <= (numeric::count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "MEMORY BOUNDRY CHECK FAILURE: the digit length of the integral part exceeds the output string buffer capacity");

    constexpr_int_to_string<char_type>(string_out_ptrc_p + l_integral_part_string_length, input_string_capacity_p, static_cast<var::int64>(l_floating_point));
}


template<typename char_type>
_FORCE_INLINE_ const char_type* boolean_to_string(boolean value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");

    return (value_p == true) ? static_cast<const char_type*>("true") : static_cast <const char_type*>("false");
}

template<typename char_type>
_FORCE_INLINE_ constexpr const char_type* constexpr_boolean_to_string(boolean value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");

    return (value_p == true) ? static_cast<const char_type*>("true") : static_cast <const char_type*>("false");
}


template <typename char_type, typename T>
_FORCE_INLINE_ void any_object_binary_representation(char_type* const dest_buffer_ptrc_p, capacity_t dest_buffer_capacity_p, T& object_ref_p)
{
    constexpr count_t l_required_bit_count = (sizeof(T) * 8) + sizeof(T);
    FE_ASSERT(dest_buffer_capacity_p < l_required_bit_count, "ERROR: The input buffer capacity is insufficient to store the binary representation of the subject");
    char_type l_buffer[l_required_bit_count] = { 0 };
    char_type* l_buffer_ptr = static_cast<char_type*>(l_buffer);

    byte* l_ptr = reinterpret_cast<byte*>(&object_ref_p);

    std::bitset<8> l_binary_representation = *l_ptr;
    for (var::size_t i = 0; i != sizeof(T); ++i)
    {
        *l_buffer_ptr = (l_binary_representation[0] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[1] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[2] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[3] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[4] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[5] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[6] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = (l_binary_representation[7] + 48);
        ++l_buffer_ptr;
        *l_buffer_ptr = '\n';

        ++l_ptr;
        l_binary_representation = *l_ptr;
        ++l_buffer_ptr;
    }

    std::memcpy(dest_buffer_ptrc_p, l_buffer, l_required_bit_count * sizeof(char_type));
}


template<typename char_type, typename T>
_FORCE_INLINE_ const char_type* any_primitive_to_string(T value_p) noexcept 
{
    static_assert(FE::is_primitive<T>::value == true, "static assertion failed: T must be a primitive type.");

    if constexpr (FE::is_boolean<T>::value)
    {
        thread_local static char_type tl_s_buffer[8] = "\0";
        std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));
        return boolean_to_string<char_type>(value_p);
    }
    else if constexpr (FE::is_character<T>::value)
    {
        thread_local static char_type tl_s_buffer[2] = "\0";
        tl_s_buffer[0] = value_p;
        tl_s_buffer[1] = _NULL_;
        return tl_s_buffer;
    }
    else if constexpr (std::is_unsigned<T>::value && std::is_integral<T>::value)
    {
        thread_local static char_type tl_s_buffer[_MAX_NUMERIC_STRING_LENGTH_] = "\0";
        std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));
        uint_to_string<char_type>(tl_s_buffer, _MAX_NUMERIC_STRING_LENGTH_, value_p);
        return tl_s_buffer;
    }
    else if constexpr (std::is_signed<T>::value && std::is_integral<T>::value)
    {
        thread_local static char_type tl_s_buffer[_MAX_NUMERIC_STRING_LENGTH_] = "\0";
        std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));
        int_to_string<char_type>(tl_s_buffer, _MAX_NUMERIC_STRING_LENGTH_, value_p);
        return tl_s_buffer;
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        thread_local static char_type tl_s_buffer[_MAX_NUMERIC_STRING_LENGTH_] = "\0";
        std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));
        float_to_string<char_type>(tl_s_buffer, _MAX_NUMERIC_STRING_LENGTH_, value_p);
        return tl_s_buffer;
    }
    else if constexpr (FE::is_c_style_constant_string<T>::value)
    {
        return value_p;
    }
    else if constexpr (std::is_pointer<T>::value)
    {
        thread_local static char_type tl_s_buffer[_MAX_NUMERIC_STRING_LENGTH_] = "\0";
        std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));
        std::snprintf(tl_s_buffer, _MAX_NUMERIC_STRING_LENGTH_, "%p", value_p);
        return tl_s_buffer;
    }
    else if constexpr (FE::is_nullptr<T>::value)
    {
        return static_cast<const char_type*>("nullptr");
    }
}


template<typename char_type, typename T>
_FORCE_INLINE_ void any_primitive_to_string(char_type* const dest_buffer_ptrc_p, capacity_t dest_buffer_capacity_p, T value_p) noexcept 
{
    static_assert(FE::is_primitive<T>::value == true, "static assertion failed: T must be a primitive type.");

    if constexpr (FE::is_boolean<T>::value)
    {
        const char_type* const l_result_ptrc = boolean_to_string<char_type>(value_p);
        copy_string(dest_buffer_ptrc_p, dest_buffer_capacity_p, l_result_ptrc, internal::strlen(l_result_ptrc));
    }
    else if constexpr (FE::is_character<T>::value)
    {
        dest_buffer_ptrc_p[0] = value_p;
        dest_buffer_ptrc_p[1] = _NULL_;
    }
    else if constexpr (std::is_unsigned<T>::value && std::is_integral<T>::value)
    {
        uint_to_string<char_type>(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p);
    }
    else if constexpr (std::is_signed<T>::value && std::is_integral<T>::value)
    {
        int_to_string<char_type>(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p);
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        float_to_string<char_type>(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p);
    }
    else if constexpr (FE::is_c_style_constant_string<T>::value)
    {
        copy_string(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p, internal::strlen(value_p));
    }
    else if constexpr (std::is_pointer<T>::value)
    {
        std::snprintf(dest_buffer_ptrc_p, dest_buffer_capacity_p, "%p", value_p);
    }
    else if constexpr (FE::is_nullptr<T>::value)
    {
        dest_buffer_ptrc_p[0] = 'n';
        dest_buffer_ptrc_p[1] = 'u';
        dest_buffer_ptrc_p[2] = 'l';
        dest_buffer_ptrc_p[3] = 'l';
        dest_buffer_ptrc_p[4] = 'p';
        dest_buffer_ptrc_p[5] = 't';
        dest_buffer_ptrc_p[6] = 'r';
        dest_buffer_ptrc_p[7] = '\0';
    }
}


template<typename char_type, typename U>
_FORCE_INLINE_ const char_type* any_to_string(U& value_p) noexcept
{
    thread_local static char_type tl_s_buffer[_256_BYTES_BIT_COUNT_] = "\0";
    std::memset(tl_s_buffer, _NULL_, sizeof(char_type) * internal::strlen(tl_s_buffer));

    if constexpr (std::is_class< typename std::remove_reference< decltype(value_p) >::type >::value == true)
    {
        any_object_binary_representation(tl_s_buffer, _256_BYTES_BIT_COUNT_, value_p);
    }
    else if constexpr (FE::is_primitive< typename std::remove_reference< decltype(value_p) >::type >::value == true)
    {
        any_primitive_to_string(tl_s_buffer, _256_BYTES_BIT_COUNT_, value_p);
    }
    return tl_s_buffer;
}


template<typename char_type, typename U>
_FORCE_INLINE_ void any_to_string(char_type* const dest_buffer_ptrc_p, capacity_t dest_buffer_capacity_p, U& value_p) noexcept
{
    if constexpr (std::is_class< typename std::remove_reference< decltype(value_p) >::type >::value == true)
    {
        any_object_binary_representation(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p);
    }
    else if constexpr (FE::is_primitive< typename std::remove_reference< decltype(value_p) >::type >::value == true)
    {
        any_primitive_to_string(dest_buffer_ptrc_p, dest_buffer_capacity_p, value_p);
    }
}


template <typename char_type, typename U = null_template_argument, typename ...arguments>
void format_string_recursive(char_type* return_buffer_ptr_p, const char_type* string_format_ptr_p, U first_p = null_template_argument{}, arguments&&... arguments_p)
{
    FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, internal::strlen(string_format_ptr_p) > _256_BYTES_BIT_COUNT_, buffer_overflow);
    FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, return_buffer_ptr_p == nullptr, is_return_buffer_ptr_p_nullptr);
    FE_CHECK_ONCE(_FN_LEVEL_THREAD_LOCAL_, string_format_ptr_p == nullptr, is_string_format_ptr_p_nullptr);
    constexpr static auto _FORMAT_SPECIFIER_LENGTH_ = 3;


    while (*string_format_ptr_p != '\0')
    {
        if ((*string_format_ptr_p == '{') && (string_format_ptr_p[1] == '%') && (string_format_ptr_p[2] == '}')) _UNLIKELY_
        {
            const char_type * l_result_ptrc = FE::algorithm::string::any_to_string<char_type, U>(first_p);
            int64 l_data_bytes_to_copy = internal::strlen(l_result_ptrc) * sizeof(char_type);
            std::memcpy(return_buffer_ptr_p, l_result_ptrc, l_data_bytes_to_copy);
            return_buffer_ptr_p += l_data_bytes_to_copy;
            string_format_ptr_p += _FORMAT_SPECIFIER_LENGTH_;
            format_string_recursive(return_buffer_ptr_p, string_format_ptr_p, arguments_p...);
            return;
        }
        else
        {
            *return_buffer_ptr_p = *string_format_ptr_p;
            ++return_buffer_ptr_p;
            ++string_format_ptr_p;
        }
    }
}


END_NAMESPACE
#pragma warning(pop)
#endif 
