#ifndef _FE_CORE_ALGORITHM_UTILITY_HXX_
#define _FE_CORE_ALGORITHM_UTILITY_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.h>
#include <FE/core/debug.h>
#include <FE/core/private/strlen.h>
#include <bitset>


#define CHAR_TO_INT(c) (c - '0')




BEGIN_NAMESPACE(FE::algorithm::utility)


template<typename T>
_FORCE_INLINE_ constexpr void swap(T& first_in_out_ref_p, T& second_in_out_ref_p) noexcept
{
	T l_temporary = ::std::move(first_in_out_ref_p);

	first_in_out_ref_p = ::std::move(second_in_out_ref_p);
	second_in_out_ref_p = ::std::move(l_temporary);
}


_MAYBE_UNUSED_ constexpr int8 _ASCII_CODE_ZERO_ = 48;
_MAYBE_UNUSED_ constexpr int8 _ASCII_CODE_NINE_ = 57;


template<typename integral_type>
struct integral_info
{
    static_assert(std::is_integral<integral_type>::value == true, "static assertion failed: The template argument integral_type is not an integral type.");
    integral_type _value = 0;
    var::uint8 _digit_length = 0;
};

template<typename real_type>
struct real_info
{
    static_assert(std::is_floating_point<real_type>::value == true, "static assertion failed: The template argument real_type is not a floating point type.");
    real_type _value = 0;
    var::uint8 _total_length = 0;
    var::uint8 _integral_part_length = 0;
    var::uint8 _real_part_length = 0;
};


template<typename unsigned_integral_type, typename char_type>
_FORCE_INLINE_ integral_info<unsigned_integral_type> string_to_uint(const char_type* const integral_string_ptrc_p) noexcept
{
    static_assert(std::is_unsigned<unsigned_integral_type>::value == true, "static assertion failed: the template argument unsigned_integral_type is not an unsigned integral type.");
    static_assert(FE::is_character<char_type>::value == true, "static assertion failed: the template argument char_type is not a character type.");

    const char_type* l_integral_string_ptr = integral_string_ptrc_p;
    unsigned_integral_type l_result = 0;

    while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
    {
        l_result *= 10;
        l_result += static_cast<unsigned_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
        ++l_integral_string_ptr;
    }

    return integral_info<unsigned_integral_type>{l_result, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptrc_p)};
}

template<typename unsigned_integral_type, typename char_type>
_FORCE_INLINE_ constexpr integral_info<unsigned_integral_type> constexpr_string_to_uint(const char_type* const integral_string_ptrc_p) noexcept
{
    static_assert(std::is_unsigned<unsigned_integral_type>::value == true, "static assertion failed: the template argument unsigned_integral_type is not an unsigned integral type.");
    static_assert(FE::is_character<char_type>::value == true, "static assertion failed: the template argument char_type is not a character type.");

    const char_type* l_integral_string_ptr = integral_string_ptrc_p;
    unsigned_integral_type l_result = 0;

    while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
    {
        l_result *= 10;
        l_result += static_cast<unsigned_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
        ++l_integral_string_ptr;
    }

    return integral_info<unsigned_integral_type>{l_result, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptrc_p)};
}


template<typename signed_integral_type, typename char_type>
_FORCE_INLINE_ integral_info<signed_integral_type> string_to_int(const char_type* integral_string_ptr_p) noexcept
{
    static_assert(std::is_signed<signed_integral_type>::value == true, "static assertion failed: the template argument signed_integral_type is not a signed integral type.");
    static_assert(FE::is_character<char_type>::value == true, "static assertion failed: the template argument char_type is not a character type.");

    const char_type* l_integral_string_ptr = integral_string_ptr_p;
    signed_integral_type l_result = 0;

    if (*l_integral_string_ptr == '-')
    {
        ++l_integral_string_ptr;
        ++integral_string_ptr_p;

        while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
        {
            l_result *= 10;
            l_result += static_cast<signed_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
            ++l_integral_string_ptr;
        }

        return integral_info<signed_integral_type>{l_result * -1, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptr_p)};
    }


    while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
    {
        l_result *= 10;
        l_result += static_cast<signed_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
        ++l_integral_string_ptr;
    }

    return integral_info<signed_integral_type>{l_result, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptr_p)};
}

template<typename signed_integral_type, typename char_type>
_FORCE_INLINE_ constexpr integral_info<signed_integral_type> constexpr_string_to_int(const char_type* integral_string_ptr_p) noexcept
{
    static_assert(std::is_signed<signed_integral_type>::value == true, "static assertion failed: the template argument signed_integral_type is not a signed integral type.");
    static_assert(FE::is_character<char_type>::value == true, "static assertion failed: the template argument char_type is not a character type.");

    const char_type* l_integral_string_ptr = integral_string_ptr_p;
    signed_integral_type l_result = 0;

    if (*l_integral_string_ptr == '-')
    {
        ++l_integral_string_ptr;
        ++integral_string_ptr_p;

        while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
        {
            l_result *= 10;
            l_result += static_cast<signed_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
            ++l_integral_string_ptr;
        }

        return integral_info<signed_integral_type>{l_result * -1, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptr_p)};
    }


    while ((*l_integral_string_ptr >= FE::algorithm::utility::_ASCII_CODE_ZERO_) && (*l_integral_string_ptr <= FE::algorithm::utility::_ASCII_CODE_NINE_))
    {
        l_result *= 10;
        l_result += static_cast<signed_integral_type>(CHAR_TO_INT(*l_integral_string_ptr));
        ++l_integral_string_ptr;
    }

    return integral_info<signed_integral_type>{l_result, static_cast<var::uint8>(l_integral_string_ptr - integral_string_ptr_p)};
}




template<typename char_type>
_FORCE_INLINE_ bool string_to_boolean(const char_type* const string_ptrc_p) noexcept
{
    const char_type* string_ptr = string_ptrc_p;

    const char_type* l_s_true_ptr = "true";
    const char_type* l_s_false_ptr = "false";


    switch (*string_ptr)
    {
    case 't':
        while ((*l_s_true_ptr == *string_ptr) && (*l_s_true_ptr != '\0'))
        {
            ++l_s_true_ptr;
            ++string_ptr;
        }
        ABORT_IF((string_ptr - string_ptrc_p) != 4, "ERROR: The calculation cannot be done properly. The input string is not \"true\".");
        return true;

    case 'f':
        while ((*l_s_false_ptr == *string_ptr) && (*l_s_false_ptr != '\0'))
        {
            ++l_s_false_ptr;
            ++string_ptr;
        }
        ABORT_IF((string_ptr - string_ptrc_p) != 5, "ERROR: The calculation cannot be done properly. The input string is not \"false\".");
        return false;

    default:
        ABORT_IF(true, "ERROR: The calculation cannot be done properly. The input string is neither \"true\" nor \"false\".");
        break;
    }
}

template<typename char_type>
_FORCE_INLINE_ constexpr bool constexpr_string_to_boolean(const char_type* const string_ptrc_p) noexcept
{
    const char_type* string_ptr = string_ptrc_p;

    const char_type* l_s_true_ptr = "true";
    const char_type* l_s_false_ptr = "false";


    switch (*string_ptr)
    {
    case 't':
        while ((*l_s_true_ptr == *string_ptr) && (*l_s_true_ptr != '\0'))
        {
            ++l_s_true_ptr;
            ++string_ptr;
        }
        ABORT_IF((string_ptr - string_ptrc_p) != 4, "ERROR: The calculation cannot be done properly. The input string is not \"true\".");
        return true;

    case 'f':
        while ((*l_s_false_ptr == *string_ptr) && (*l_s_false_ptr != '\0'))
        {
            ++l_s_false_ptr;
            ++string_ptr;
        }
        ABORT_IF((string_ptr - string_ptrc_p) != 5, "ERROR: The calculation cannot be done properly. The input string is not \"false\".");
        return false;

    default:
        ABORT_IF(true, "ERROR: The calculation cannot be done properly. The input string is neither \"true\" nor \"false\".");
        break;
    }
}




template<typename float_type, typename char_type>
_FORCE_INLINE_ real_info<float_type> string_to_float(const char_type* float_string_ptr_p) noexcept
{
    integral_info<var::int64> l_integral_part_info = string_to_int<var::int64>(float_string_ptr_p);

    if (*float_string_ptr_p == '-')
    {
        ++float_string_ptr_p;
        float_string_ptr_p += (l_integral_part_info._digit_length + 1);
        integral_info<var::uint64> l_real_part_info = string_to_uint<var::uint64>(float_string_ptr_p);

        float_type l_integral_part = static_cast<float_type>(l_integral_part_info._value);
        float_type l_real_part = static_cast<float_type>(l_real_part_info._value);

        for (var::int32 i = 0; i < l_real_part_info._digit_length; ++i)
        {
            l_real_part /= 10.0f;
        }
        return real_info<float_type>{l_integral_part - l_real_part, static_cast<var::uint8>(l_integral_part_info._digit_length + l_real_part_info._digit_length + 1), l_integral_part_info._digit_length, l_real_part_info._digit_length};
    }
    

    float_string_ptr_p += (l_integral_part_info._digit_length + 1);
    integral_info<var::uint64> l_real_part_info = string_to_uint<var::uint64>(float_string_ptr_p);

    float_type l_integral_part = static_cast<float_type>(l_integral_part_info._value);
    float_type l_real_part = static_cast<float_type>(l_real_part_info._value);

    for (var::int32 i = 0; i < l_real_part_info._digit_length; ++i)
    {
        l_real_part /= 10.0f;
    }
    return real_info<float_type>{l_integral_part + l_real_part, static_cast<var::uint8>(l_integral_part_info._digit_length + l_real_part_info._digit_length + 1), l_integral_part_info._digit_length, l_real_part_info._digit_length};
}

template<typename float_type, typename char_type>
_FORCE_INLINE_ constexpr real_info<float_type> constexpr_string_to_float(const char_type* float_string_ptr_p) noexcept
{
    integral_info<var::int64> l_integral_part_info = string_to_int<var::int64>(float_string_ptr_p);

    if (*float_string_ptr_p == '-')
    {
        ++float_string_ptr_p;
        float_string_ptr_p += (l_integral_part_info._digit_length + 1);
        integral_info<var::uint64> l_real_part_info = string_to_uint<var::uint64>(float_string_ptr_p);

        float_type l_integral_part = static_cast<float_type>(l_integral_part_info._value);
        float_type l_real_part = static_cast<float_type>(l_real_part_info._value);

        for (var::int32 i = 0; i < l_real_part_info._digit_length; ++i)
        {
            l_real_part /= 10.0f;
        }
        return real_info<float_type>{l_integral_part - l_real_part, static_cast<var::uint8>(l_integral_part_info._digit_length + l_real_part_info._digit_length + 1), l_integral_part_info._digit_length, l_real_part_info._digit_length};
    }


    float_string_ptr_p += (l_integral_part_info._digit_length + 1);
    integral_info<var::uint64> l_real_part_info = string_to_uint<var::uint64>(float_string_ptr_p);

    float_type l_integral_part = static_cast<float_type>(l_integral_part_info._value);
    float_type l_real_part = static_cast<float_type>(l_real_part_info._value);

    for (var::int32 i = 0; i < l_real_part_info._digit_length; ++i)
    {
        l_real_part /= 10.0f;
    }
    return real_info<float_type>{l_integral_part + l_real_part, static_cast<var::uint8>(l_integral_part_info._digit_length + l_real_part_info._digit_length + 1), l_integral_part_info._digit_length, l_real_part_info._digit_length};
}




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




#define _MAX_NUMERIC_STRING_LENGTH_ 512
#define _256_BYTES_BIT_COUNT_ 2048
#define _16_BYTES_BIT_COUNT_ 128


template<typename char_type>
_FORCE_INLINE_ void int_to_string(char_type* const string_out_ptrc_p, _MAYBE_UNUSED_ length_t input_string_capacity_p, var::int64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");
    ABORT_IF(value_p == FE::_MIN_VALUE_<var::int64>, "NaCN ERROR: value_p is not a calculatable number");

    var::int8 l_integral_digits = count_integral_digit_length<var::int64>(value_p);
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

    ABORT_IF(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

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
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = count_integral_digit_length<var::int64>(value_p);
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

    ABORT_IF(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

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
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = count_integral_digit_length<var::uint64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    ABORT_IF(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

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
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    var::int8 l_integral_digits = count_integral_digit_length<var::uint64>(value_p);
    var::boolean l_is_negative = false;

    if (value_p == 0)
    {
        string_out_ptrc_p[0] = '0';
        string_out_ptrc_p[1] = '\0';
        return;
    }

    ABORT_IF(input_string_capacity_p <= l_integral_digits, "MEMORY BOUNDRY CHECK FAILURE: the digit length of an integer exceeds the output string buffer capacity");

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
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    int_to_string<char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<var::int64>(value_p));

    var::uint64 l_integral_part_string_length = internal::strlen<char_type>(string_out_ptrc_p);
    string_out_ptrc_p[l_integral_part_string_length] = '.';
    ++l_integral_part_string_length;

    var::float64 l_floating_point = value_p - static_cast<float64>(static_cast<var::int64>(value_p));
    while (0 != (l_floating_point - static_cast<var::int64>(l_floating_point)))
    {
        l_floating_point *= 10.0f;
    }

    ABORT_IF(input_string_capacity_p <= (count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "MEMORY BOUNDRY CHECK FAILURE: the digit length of the integral part exceeds the output string buffer capacity");

    int_to_string<char_type>(string_out_ptrc_p + l_integral_part_string_length, input_string_capacity_p, static_cast<var::int64>(l_floating_point));
}

template<typename char_type>
_FORCE_INLINE_ constexpr void constexpr_float_to_string(char_type* const string_out_ptrc_p, length_t input_string_capacity_p, float64 value_p) noexcept
{
    static_assert(FE::is_character<char_type>::value, "an illegal type of value_p assigned to the template argument char_type");
    ABORT_IF(string_out_ptrc_p == nullptr, "NULLPTR DETECTED: string_out_ptrc_p is nullptr.");

    constexpr_int_to_string<char_type>(string_out_ptrc_p, input_string_capacity_p, static_cast<int64>(value_p));

    var::uint64 l_integral_part_string_length = internal::strlen<char_type>(string_out_ptrc_p);
    string_out_ptrc_p[l_integral_part_string_length] = '.';
    ++l_integral_part_string_length;

    var::float64 l_floating_point = value_p - static_cast<float64>(static_cast<var::int64>(value_p));
    while (0 != (l_floating_point - static_cast<var::int64>(l_floating_point)))
    {
        l_floating_point *= 10;
    }

    ABORT_IF(input_string_capacity_p <= (count_integral_digit_length<var::int64>(l_floating_point) + l_integral_part_string_length), "MEMORY BOUNDRY CHECK FAILURE: the digit length of the integral part exceeds the output string buffer capacity");

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
    ABORT_IF(dest_buffer_capacity_p < l_required_bit_count, "ERROR: The input buffer capacity is insufficient to store the binary representation of the subject");
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
        uint64 l_length = internal::strlen(l_result_ptrc);
        std::memcpy(dest_buffer_ptrc_p, l_result_ptrc, l_length * sizeof(char_type));
        dest_buffer_ptrc_p[l_length] = '\0';
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
        uint64 l_length = internal::strlen(value_p);
        uint64 l_bytes_to_copy = l_length * sizeof(char_type);
        if (dest_buffer_capacity_p < l_bytes_to_copy) _UNLIKELY_{ std::abort(); }
        std::memcpy(dest_buffer_ptrc_p, value_p, l_bytes_to_copy);
        dest_buffer_ptrc_p[l_length] = '\0';
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


END_NAMESPACE
#endif