#ifndef _FE_CORE_ALGORITHM_STRING_HXX_
#define _FE_CORE_ALGORITHM_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/iterator.hxx>
#include <FE/core/memory>
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
    FE_EXIT(cstr_ptr_p == nullptr, "DETECTED NULLPTR: cstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(cstr_ptr_p == nullptr, "DETECTED NULLPTR: cstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(str_ptrc_p == nullptr, "DETECTED NULLPTR: str_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(str_ptrc_p == nullptr, "DETECTED NULLPTR: str_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const string_range lstr_range_p, char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const string_range lstr_range_p, const char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const string_range lstr_range_p, char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const string_range lstr_range_p, const char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(destination_out_ptrc_p == nullptr, "NULLPTR DETECTED: destination_out_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(source_ptrc_p == nullptr, "NULLPTR DETECTED: source_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);


    FE_EXIT(destination_count_p < source_count_p, "MEMORY BOUNDARY CHECK FAILURE: the source_count_p is greater than the destination_count_p", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

    if(source_count_p != 0)
    { 
        FE::unaligned_memcpy(destination_out_ptrc_p, destination_count_p, sizeof(char_type), source_ptrc_p, source_count_p, sizeof(char_type));
    }
    destination_out_ptrc_p[source_count_p] = static_cast<char_type>('\0');
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void capitalize_string(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(in_out_string_buffer_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_buffer_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);


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
    FE_EXIT(in_out_string_buffer_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_buffer_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptr_p == nullptr, "NULLPTR DETECTED: lstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptr_p == nullptr, "NULLPTR DETECTED: rstr_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const string_range lstr_range_p, char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const string_range lstr_range_p, const char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const string_range lstr_range_p, char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ _CONSTEXPR23_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const string_range lstr_range_p, const char_type* const rstr_ptrc_p, const string_range rstr_range_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(destination_out_ptrc_p == nullptr, "NULLPTR DETECTED: destination_out_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(source_ptrc_p == nullptr, "NULLPTR DETECTED: source_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

    FE_EXIT(destination_total_count_p < source_total_count_p, "MEMORY BOUNDARY CHECK FAILURE: the source_total_count_p is greater than the destination_total_count_p", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

    length_t l_destination_string_length = algorithm::string::string_length<char_type>(destination_out_ptrc_p);

    FE::unaligned_memcpy(destination_out_ptrc_p + l_destination_string_length, destination_total_count_p, sizeof(char_type), source_ptrc_p, source_total_count_p, sizeof(char_type));
}


template <typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(lstr_ptrc_p == nullptr, "NULLPTR DETECTED: lstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(rstr_ptrc_p == nullptr, "NULLPTR DETECTED: rstr_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(in_out_string_ptr_p == nullptr, "NULLPTR DETECTED: in_out_string_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(in_out_string_ptrc_p == nullptr, "NULLPTR DETECTED: in_out_string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ target_char_search_result<char_type> search_very_first_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rbegin = string_ptrc_p + (string_length(string_ptrc_p)-1);
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rend = string_ptrc_p - 1;

    while (l_string_rbegin != l_string_rend)
    {
        if (*l_string_rbegin == target_char_p)
        {
            return target_char_search_result<char_type>{*l_string_rbegin, static_cast<index_t>(l_string_rbegin.operator->() - string_ptrc_p) };
        }
        ++l_string_rbegin;
    }

    return target_char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_count<char_type> count_all_corresponding_chars(char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
_NODISCARD_ _FORCE_INLINE_ constexpr target_char_count<char_type> count_all_corresponding_chars(const char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

    const char_type* l_string_ptr = string_ptrc_p;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_length(string_ptrc_p);
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);
 
    FE_EXIT(l_target_substring_length > l_string_length, "CRITICAL ERROR: the l_target_substring_length is greater than or equal to the string length of string_ptrc_p", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

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

    if (compare_ranged_strings(string_ptrc_p, string_range{ l_begin, l_end }, target_substring_ptrc_p, string_range{ 0, l_target_substring_length }))
    {
        return  std::make_optional<string_range>(l_begin, l_end);
    }

    return ::std::nullopt;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_::std::optional<string_range> search_very_last_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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

    if ( compare_ranged_strings(string_ptrc_p, string_range{ l_begin, l_end }, target_substring_ptrc_p, string_range{0, l_target_substring_length}) )
    {
        return  std::make_optional<string_range>(l_begin, l_end);
    }

    return ::std::nullopt;
}




template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_search_result<char_type> search_very_first_char_within_range(const char_type* const string_ptrc_p, const string_range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

    const char_type* l_string_ptr = string_ptrc_p + string_range_p._begin;
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
_NODISCARD_ _FORCE_INLINE_ target_char_search_result<char_type> search_very_last_char_within_range(const char_type* const string_ptrc_p, const string_range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rbegin = string_ptrc_p + (string_range_p._end - 1);
    FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>> l_string_rend = string_ptrc_p + (string_range_p._begin - 1);

    while (l_string_rbegin != l_string_rend)
    {
        if (*l_string_rbegin == target_char_p)
        {
            return target_char_search_result<char_type>{*l_string_rbegin, static_cast<index_t>(l_string_rbegin.operator->() - string_ptrc_p) };
        }
        ++l_string_rbegin;
    }

    return target_char_search_result<char_type>{};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ target_char_count<char_type> count_all_corresponding_chars_within_range(char_type* string_ptr_p, const string_range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

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

    return target_char_count<char_type>{l_target_char_buffer, l_match_count};
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_ constexpr target_char_count<char_type> count_all_corresponding_chars_within_range(const char_type* string_ptr_p, const string_range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptr_p == nullptr, "NULLPTR DETECTED: string_ptr_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

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

    return target_char_count<char_type>{l_target_char_buffer, l_match_count};
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_::std::optional<string_range> search_very_first_substring_within_range(const char_type* const string_ptrc_p, const string_range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);
    FE_EXIT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

    const char_type* l_string_ptr = string_ptrc_p + string_range_p._begin;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_range_p._end - string_range_p._begin;
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);

    FE_EXIT(l_target_substring_length > l_string_length, "CRITICAL ERROR: the l_target_substring_length is greater than or equal to the string length of string_ptrc_p", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);

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

    if (compare_ranged_strings(string_ptrc_p, string_range{l_begin, l_end}, target_substring_ptrc_p, string_range{0, l_target_substring_length}))
    {
        return  std::make_optional<string_range>(l_begin, l_end);
    }

    return ::std::nullopt;
}


template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_NODISCARD_ _FORCE_INLINE_::std::optional<string_range> search_very_last_substring_within_range(const char_type* const string_ptrc_p, const string_range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(string_ptrc_p == nullptr, "NULLPTR DETECTED: string_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
    FE_EXIT(string_range_p._begin > string_range_p._end, "INVALID RANGE DETECTED: string_range_p._begin cannot be greater than string_range_p._end.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);
    FE_EXIT(target_substring_ptrc_p == nullptr, "NULLPTR DETECTED: target_substring_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

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

    if (compare_ranged_strings(string_ptrc_p, string_range{ l_begin, l_end }, target_substring_ptrc_p, string_range{ 0, l_target_substring_length }))
    {
        return  std::make_optional<string_range>(l_begin, l_end);
    }

    return ::std::nullopt;
}




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
    ABORT_IF(out_string_buffer_ptrc_p == nullptr, "NULLPTR DETECTED: out_string_buffer_ptrc_p is nullptr.");

    var::size_t l_current_begin_index = algorithm::string::string_length(out_string_buffer_ptrc_p);

    for (var::size_t i = 0; i < strings_p.size(); ++i)
    {
        size_t l_string_length_buffer = algorithm::string::string_length(strings_p.begin()[i]);

        ABORT_IF(string_buffer_size_p <= l_current_begin_index, "MEMORY BOUNDARY CHECK FAILURES: the string_buffer_size_p is smaller or equal to the l_current_begin_index");

        ::FE::unaligned_memcpy(out_string_buffer_ptrc_p + l_current_begin_index, string_buffer_size_p, sizeof(char_type), strings_p.begin()[i], l_string_length_buffer, sizeof(char_type));
        l_current_begin_index += l_string_length_buffer;
    }
}

template<typename char_type>
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
_FORCE_INLINE_ void concatenate_characters(char_type* const out_string_buffer_ptrc_p, _MAYBE_UNUSED_ size_t string_buffer_size_p, ::std::initializer_list<const char_type>&& strings_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");
    FE_EXIT(out_string_buffer_ptrc_p == nullptr, "NULLPTR DETECTED: out_string_buffer_ptrc_p is nullptr.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

    var::length_t l_string_buffer_length = algorithm::string::string_length(out_string_buffer_ptrc_p);

    FE_EXIT(string_buffer_size_p <= strings_p.size() + l_string_buffer_length, "MEMORY BOUNDARY CHECK FAILURE: The total input string length exceeds the destination string buffer capacity.", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE);
    
    ::memcpy(out_string_buffer_ptrc_p + l_string_buffer_length, strings_p.begin(), sizeof(char_type) * strings_p.size());
}


END_NAMESPACE
#endif 
