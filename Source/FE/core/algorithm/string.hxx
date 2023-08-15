#ifndef _FE_CORE_ALGORITHM_STRING_HXX_
#define _FE_CORE_ALGORITHM_STRING_HXX_
#pragma warning(push)
#pragma warning(disable: 4702)
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/iterator.hxx>
#include <FE/core/optional.hxx>
// Visual Studio v143 C++20 compiler has a bug in release build mode. The compiler options are /WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy- /GT /MT /Gy /GL /arch:AVX
// has_value() returns true even if search_very_last_substring returns std::nullopt.




BEGIN_NAMESPACE(FE::algorithm::string)


template<typename char_type>
struct char_count
{
    char_type _target_data;
    count_t _match_count;
};


template<typename char_type>
_NODISCARD_ _FORCE_INLINE_ char_count<char_type> count_chars(char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ constexpr char_count<char_type> count_chars(const char_type* string_ptr_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptr_p), nullptr);

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




_MAYBE_UNUSED_ constexpr int8 _ASCII_a_ = 97;
_MAYBE_UNUSED_ constexpr int8 _ASCII_z_ = 122;

_MAYBE_UNUSED_ constexpr int8 _ASCII_A_ = 65;
_MAYBE_UNUSED_ constexpr int8 _ASCII_Z_ = 90;
_MAYBE_UNUSED_ constexpr int8 _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_ = 32;


template<typename char_type>
_FORCE_INLINE_ void capitalize(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_buffer_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(in_out_string_buffer_ptr_p), nullptr);

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
_FORCE_INLINE_ char_type capitalize(const char_type char_value_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");

    if (_ASCII_a_ <= static_cast<uint8>(char_value_p) && static_cast<uint8>(char_value_p) <= _ASCII_z_)
    {
        return static_cast<char_type>(static_cast<int16>(char_value_p) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
    }

    return char_value_p;
}


template<typename char_type>
_FORCE_INLINE_ void to_lowercase(char_type* in_out_string_buffer_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_buffer_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(in_out_string_buffer_ptr_p), nullptr);

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
_FORCE_INLINE_ char_type to_lowercase(const char_type char_value_p) noexcept
{
    static_assert(sizeof(char_type) <= sizeof(UTF32), "char_type is not a valid character type");

    if (_ASCII_A_ <= static_cast<uint8>(char_value_p) && static_cast<uint8>(char_value_p) <= _ASCII_Z_)
    {
        return static_cast<char_type>(static_cast<int16>(char_value_p) + _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_);
    }

    return char_value_p;
}




template<typename char_type>
_FORCE_INLINE_ void capitalize_every_first_letter_of_words(char_type* in_out_string_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(in_out_string_ptr_p), nullptr);

    if ((*in_out_string_ptr_p != static_cast<char_type>(' ')) || (*in_out_string_ptr_p != static_cast<char_type>('_')))
    {
        *in_out_string_ptr_p = static_cast<int16>(*in_out_string_ptr_p) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
    }

    while (*in_out_string_ptr_p != static_cast<char_type>('\0'))
    {
        if (((*in_out_string_ptr_p == static_cast<char_type>(' ')) && (in_out_string_ptr_p[1] != static_cast<char_type>(' '))) ||
            ((*in_out_string_ptr_p == static_cast<char_type>('_')) && (in_out_string_ptr_p[1] != static_cast<char_type>('_'))))
        {
            if (((_ASCII_A_ <= in_out_string_ptr_p[1]) && (in_out_string_ptr_p[1] <= _ASCII_Z_))
                || ((_ASCII_a_ <= in_out_string_ptr_p[1]) && (in_out_string_ptr_p[1] <= _ASCII_z_)))
            {
                in_out_string_ptr_p[1] = static_cast<int16>(in_out_string_ptr_p[1]) - _ASCII_GAP_BETWEEN_UPPERCASE_and_lowercase_;
            }
        }
        ++in_out_string_ptr_p;
    }
}




template <typename char_type>
_FORCE_INLINE_ void copy_string(char_type* const destination_out_ptrc_p, capacity_t destination_size_p, const char_type* const source_ptrc_p, capacity_t source_size_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(destination_out_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(destination_out_ptrc_p), nullptr);
    FE_ASSERT(source_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(source_ptrc_p), nullptr);

    FE_ASSERT(destination_size_p < source_size_p, "${%s@0}: the ${%s@2} is greater than ${%s@1}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(destination_size_p), TO_STRING(source_size_p), &destination_size_p, &source_size_p);

    if (source_size_p != 0) _UNLIKELY_
    {
        std::memcpy(destination_out_ptrc_p, source_ptrc_p, source_size_p * sizeof(char_type));
    }
    destination_out_ptrc_p[source_size_p] = static_cast<char_type>('\0');
}




template <typename char_type>
_NODISCARD_ _FORCE_INLINE_ var::uint64 string_length(char_type* const str_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(str_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(str_ptrc_p), nullptr);

    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*str_ptrc_p == _NULL_)
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != _NULL_) _LIKELY_ {}

    return (l_iterator_ptr - str_ptrc_p);
}

template <typename char_type>
_NODISCARD_ _FORCE_INLINE_ constexpr var::uint64 string_length(const char_type* const str_ptrc_p) noexcept 
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(str_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(str_ptrc_p), nullptr);

    const char_type* l_iterator_ptr = str_ptrc_p;

    if (*str_ptrc_p == _NULL_)
    {
        return 0;
    }

    while (*(++l_iterator_ptr) != _NULL_) {}

    return (l_iterator_ptr - str_ptrc_p);
}




struct range
{
    var::index_t _begin;
    var::index_t _end;
};


template<typename char_type>
_NODISCARD_ _FORCE_INLINE_ char_count<char_type> count_chars_within_range(char_type* string_ptr_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptr_p), nullptr);
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: the ${%s@1} cannot be greater than ${%s@2}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end), &string_range_p._begin, &string_range_p._end);
    FE_ASSERT(string_length(string_ptr_p) > string_range_p._end, "${%s@0}: the ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_length(string_ptr_p)), TO_STRING(string_range_p._end));

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
_NODISCARD_ _FORCE_INLINE_ constexpr char_count<char_type> count_chars_within_range(const char_type* string_ptr_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptr_p), nullptr);
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: the ${%s@1} cannot be greater than ${%s@2}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end), &string_range_p._begin, &string_range_p._end);
    FE_ASSERT(string_length(string_ptr_p) > string_range_p._end, "${%s@0}: the ${%s@1} cannot be greater than ${%s@2}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_length(string_ptr_p)), TO_STRING(string_range_p._end), &string_length(string_ptr_p), &string_range_p._end);

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




template <typename char_type>
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(const char_type* lstr_ptr_p, char_type* rstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(char_type* lstr_ptr_p, const char_type* rstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean string_comparison(char_type* lstr_ptr_p, char_type* rstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean string_comparison(const char_type* lstr_ptr_p, const char_type* rstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean compare_ranged_strings(char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ constexpr var::boolean compare_ranged_strings(const char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(char_type* const lstr_ptrc_p, const char_type* const rstr_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(char_type* const lstr_ptrc_p, char_type* const rstr_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_string_comparison(const char_type* const lstr_ptrc_p, const char_type* const rstr_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    const char_type* l_left_string_ptr = lstr_ptrc_p;
    const char_type* l_right_string_ptr = rstr_ptrc_p;

    while (string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr) && *l_left_string_ptr != static_cast<char_type>('\0'))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr))
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
_NODISCARD_ _FORCE_INLINE_ var::boolean insensitive_ranged_string_comparison(char_type* const lstr_ptrc_p, const range lstr_range_p, char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr))
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
_NODISCARD_ _FORCE_INLINE_ _CONSTEXPR23_ var::boolean insensitive_ranged_string_comparison(const char_type* const lstr_ptrc_p, const range lstr_range_p, const char_type* const rstr_ptrc_p, const range rstr_range_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(lstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(lstr_ptr_p), nullptr);
    FE_ASSERT(rstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(rstr_ptr_p), nullptr);

    length_t l_left_string_length = lstr_range_p._end - lstr_range_p._begin;
    length_t l_right_string_length = rstr_range_p._end - rstr_range_p._begin;

    if (l_left_string_length != l_right_string_length)
    {
        return false;
    }

    const char_type* l_left_string_ptr = lstr_ptrc_p + lstr_range_p._begin;
    const char_type* l_right_string_ptr = rstr_ptrc_p + rstr_range_p._begin;

    const char_type* const l_end_of_left_string = lstr_ptrc_p + lstr_range_p._end;


    while (l_left_string_ptr != l_end_of_left_string && string::capitalize(*l_left_string_ptr) == string::capitalize(*l_right_string_ptr))
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
_FORCE_INLINE_ void string_concatenation(char_type* const destination_out_ptrc_p, count_t destination_total_count_p, const char_type* const source_ptrc_p, count_t source_total_count_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(destination_out_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(destination_out_ptrc_p), nullptr);
    FE_ASSERT(source_ptrc_p == nullptr, "${%s@0}: ${%s@1} is ${%p@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(source_ptrc_p), nullptr);

    FE_ASSERT(destination_total_count_p < source_total_count_p, "${%s@0}: the ${%s@2} cannot be greater than ${%s@1}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(destination_total_count_p), TO_STRING(source_total_count_p), &destination_total_count_p, &source_total_count_p);

    length_t l_destination_string_length = algorithm::string::string_length<char_type>(destination_out_ptrc_p);
 
    std::memcpy(destination_out_ptrc_p + l_destination_string_length, source_ptrc_p, source_total_count_p * sizeof(char_type));
}


template<typename char_type>
_FORCE_INLINE_ void concatenate_strings(char_type* const out_string_buffer_ptrc_p, size_t string_buffer_size_p, ::std::initializer_list<const char_type* const>&& strings_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
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
_FORCE_INLINE_ void concatenate_characters(char_type* const out_string_buffer_ptrc_p, _MAYBE_UNUSED_ size_t string_buffer_size_p, ::std::initializer_list<const char_type>&& chars_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(out_string_buffer_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(out_string_buffer_ptrc_p));

    var::length_t l_string_buffer_length = algorithm::string::string_length(out_string_buffer_ptrc_p);

    FE_ASSERT(string_buffer_size_p <= chars_p.size() + l_string_buffer_length, "${%s@0}: The total input string length exceeds the destination string buffer capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

    ::memcpy(out_string_buffer_ptrc_p + l_string_buffer_length, chars_p.begin(), sizeof(char_type) * chars_p.size());
}




template<typename char_type>
struct char_search_result
{
    char_type _target_data;
    index_t _target_data_location;
};


template<typename char_type>
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_first_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));

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
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_last_char(const char_type* const string_ptrc_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));

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
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_first_char_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end));
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "${%s@0}: ${%s@2} cannot be greater than the length of ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_length(string_ptrc_p)), TO_STRING(string_range_p._end));

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
_NODISCARD_ _FORCE_INLINE_ char_search_result<char_type> search_last_char_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end));
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "${%s@0}: ${%s@2} cannot be greater than the length of ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(string_length(string_ptrc_p)), TO_STRING(string_range_p._end));

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
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_first_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(target_substring_ptrc_p));

    const char_type* l_string_ptr = string_ptrc_p;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_length(string_ptrc_p);
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);
 
    FE_ASSERT(l_target_substring_length > l_string_length, "${%s@0}: the ${%s@1} is greater than to the string length of ${%s@2}. ${%s@1} was ${%lu@3}, and ${%s@2} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(l_target_substring_length), TO_STRING(l_string_length), &l_target_substring_length, &l_string_length);

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
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_last_substring(const char_type* const string_ptrc_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(target_substring_ptrc_p));

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
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_first_substring_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end));
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than the length of ${%s@2}.", TO_STRING(string_length(string_ptrc_p)), TO_STRING(string_range_p._end));

    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(target_substring_ptrc_p));

    const char_type* l_string_ptr = string_ptrc_p + string_range_p._begin;
    const char_type* l_target_substring_ptr = target_substring_ptrc_p;
    length_t l_string_length = string_range_p._end - string_range_p._begin;
    length_t l_target_substring_length = string_length(target_substring_ptrc_p);

    FE_ASSERT(l_target_substring_length > l_string_length, "${%s@0}: the ${%s@1} is greater than or equal to the string length of ${%s@2}", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(l_target_substring_length), TO_STRING(l_string_length));

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
_NODISCARD_ _FORCE_INLINE_ FE::optional<range> search_last_substring_within_range(const char_type* const string_ptrc_p, const range string_range_p, const char_type* const target_substring_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_range_p._begin > string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(string_range_p._begin), TO_STRING(string_range_p._end));
    FE_ASSERT(string_length(string_ptrc_p) < string_range_p._end, "${%s@0}: ${%s@1} cannot be greater than the length of ${%s@2}.", TO_STRING(string_length(string_ptrc_p)), TO_STRING(string_range_p._end));

    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_ptrc_p));
    FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(target_substring_ptrc_p));


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
_FORCE_INLINE_ int_type char_to_integer(char_type target_char_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    static_assert(::std::is_integral<int_type>::value == true, "typename int_type is not an integer");

    return static_cast<int_type>(target_char_p) - 48;
}


template <typename char_type, typename int_type>
_NODISCARD_ _FORCE_INLINE_ int_type string_to_integer(char_type* cstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(cstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptr_p));

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

template <typename char_type, typename int_type>
_NODISCARD_ _FORCE_INLINE_ constexpr int_type string_to_integer(const char_type* cstr_ptr_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(cstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptr_p));

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




template<typename char_type>
_FORCE_INLINE_ void invert_string(char_type* const in_out_string_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(in_out_string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptr_p));

    var::index_t l_start = 0;
    var::index_t l_end = string_length(in_out_string_ptrc_p);

    char_type l_temporary = static_cast<char_type>('\0');
    while (l_start < l_end)
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
TIP: use this function with switch cases.
*/
template<typename char_type>
_FORCE_INLINE_ constexpr var::uint64 hash_string(const char_type* const string_ptrc_p) noexcept
{
    static_assert(FE::is_char<char_type>::value, "char_type is not a valid character type");
    FE_ASSERT(string_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptr_p));

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




END_NAMESPACE
#pragma warning(pop)
#endif