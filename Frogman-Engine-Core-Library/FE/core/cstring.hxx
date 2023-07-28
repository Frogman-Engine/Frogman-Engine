#ifndef _FE_CORE_CSTRING_HXX_
#define _FE_CORE_CSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "algorithm/utility.hxx"
#include <cstring>


BEGIN_NAMESPACE(FE)


template< typename char_type = char >
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
class compile_time_constant_string final
{
    static_assert(FE::is_character<char_type>::value == true, "char_type is not a valid character type");
    static_assert(FE::is_trivially_constructible_and_destructible<char_type>::_VALUE_ == FE::OBJECT_TRIVIALITY::_TRIVIAL, "char_type is not a valid character type");

public:
    using value_type = const char_type*;
    using buffer_type = char_type;
    using const_iterator = FE::const_iterator<FE::contiguous_iterator<const char_type>>;
    using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<const char_type>>;

private:
    ::std::optional<const char_type*> m_string;

public:
    constexpr _FORCE_INLINE_ compile_time_constant_string() noexcept {}
    _CONSTEXPR20_ _FORCE_INLINE_ ~compile_time_constant_string() noexcept {}

    template <typename T>
    _FORCE_INLINE_ constexpr compile_time_constant_string(T* c_style_read_only_string_ptr_p) noexcept
    {
        static_assert(FE::is_c_style_constant_string<T*>::value == true, "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.");

        this->m_string.emplace(c_style_read_only_string_ptr_p); 
    }
    _FORCE_INLINE_ constexpr compile_time_constant_string(compile_time_constant_string<char_type>& other_ref_p) noexcept { this->m_string.emplace(*other_ref_p.m_string); }
    _FORCE_INLINE_  constexpr compile_time_constant_string(compile_time_constant_string<char_type>&& move_p) noexcept { this->m_string.emplace(*move_p.m_string); }

    template <typename T>
    _FORCE_INLINE_ constexpr compile_time_constant_string<char_type>& operator=(T* c_style_read_only_string_ptr_p) noexcept
    {
        static_assert(FE::is_c_style_constant_string<T*>::value == true, "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.");

        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(c_style_read_only_string_ptr_p);

        return *this;
    }
    _FORCE_INLINE_ constexpr compile_time_constant_string<char_type>& operator=(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*other_ref_p.m_string);

        return *this;
    }
    _FORCE_INLINE_ constexpr compile_time_constant_string<char_type>& operator=(compile_time_constant_string<char_type>&& move_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*move_p.m_string);

        return *this;
    }

    _FORCE_INLINE_ constexpr char_type operator[](index_t index_p) const noexcept
    {
        FE_ASSERT(index_p >= algorithm::string::string_length(*(this->m_string)), "ERROR: an input index value passed to operator[]() exceeded the index boundary of a cstring instance.");
        return (*this->m_string)[index_p];
    }

    _FORCE_INLINE_ constexpr char_type front() const noexcept { return *(*this->m_string); }
    _FORCE_INLINE_ constexpr char_type back() const noexcept { return  (*this->m_string)[algorithm::string::string_length(*this->m_string) - 1]; }

    // It returns a pointer to the data
    _FORCE_INLINE_ constexpr const char_type* data() const noexcept { return (*this->m_string); }

    // It returns a pointer to a traditional c-style read-only string
    _FORCE_INLINE_ constexpr const char_type* c_str() const noexcept { return *this->m_string; }

    // It returns a standard string
    _FORCE_INLINE_ constexpr ::std::basic_string<char_type> std_str() const noexcept { return *this->m_string; }

    _FORCE_INLINE_ constexpr const_iterator cbegin() const noexcept { return *this->m_string; }
    _FORCE_INLINE_ constexpr const_iterator cend() const noexcept { return (*this->m_string) + algorithm::string::string_length(*this->m_string); }
    _FORCE_INLINE_ constexpr const_reverse_iterator crbegin() const noexcept { return (*this->m_string) + (algorithm::string::string_length(*this->m_string) - 1); }
    _FORCE_INLINE_ constexpr const_reverse_iterator crend() const noexcept { return (*this->m_string) - 1; }

    _FORCE_INLINE_ constexpr var::boolean is_empty() const noexcept { return !(this->m_string.has_value()); }
    _FORCE_INLINE_ constexpr var::size_t length() const noexcept { return algorithm::string::string_length<char_type>(*this->m_string); }
    _FORCE_INLINE_ constexpr var::uint64 max_length() const noexcept { return ::FE::_MAX_VALUE_<var::uint64>(); }
    _FORCE_INLINE_ constexpr void clear() noexcept { this->m_string.reset(); }

    _FORCE_INLINE_ constexpr var::boolean starts_with(compile_time_constant_string<char_type>& substring_ref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{0, l_substring_length}, 
                                                            substring_ref_p.data(), algorithm::string::range{0, l_substring_length}
                                                            );
    }
    _FORCE_INLINE_ constexpr var::boolean starts_with(const char_type target_character_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{0, 1},
                                                            &target_character_p, algorithm::string::range{0, 1}
                                                            );
    }
    _FORCE_INLINE_ constexpr var::boolean starts_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_EXIT(substring_ptrc_p == nullptr, "ERROR: substring_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);

        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{0, l_substring_length},
                                                            substring_ptrc_p, algorithm::string::range{0, l_substring_length}
                                                            );
    }

    _FORCE_INLINE_ constexpr var::boolean ends_with(compile_time_constant_string<char_type>& substring_ref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{l_this_string_length - l_substring_length, l_this_string_length},
                                                            substring_ref_p.data(), algorithm::string::range{0, l_substring_length}
                                                            );
    }
    _FORCE_INLINE_ constexpr var::boolean ends_with(const char_type target_character_p) const noexcept
    {
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{l_this_string_length - 1, l_this_string_length},
                                                            &target_character_p, algorithm::string::range{0, 1}
                                                            );
    }
    _FORCE_INLINE_ constexpr var::boolean ends_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_EXIT(substring_ptrc_p == nullptr, "ERROR: substring_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::range{l_this_string_length - l_substring_length, l_this_string_length},
                                                            substring_ptrc_p, algorithm::string::range{0, l_substring_length}
                                                            );
    }

    _FORCE_INLINE_  constexpr var::boolean contains(compile_time_constant_string<char_type>& substring_ref_p) const noexcept
    {
        return (algorithm::string::search_very_first_substring(this->data(), substring_ref_p.data())).has_value();
    }
    _FORCE_INLINE_ constexpr var::boolean contains(const char_type target_character_p) const noexcept
    {
        algorithm::string::char_search_result<char_type> l_target_char_search_result = algorithm::string::search_very_first_char(this->data(), target_character_p);
        return (l_target_char_search_result._target_data != static_cast<char_type>('\0')) ? true : false;
    }
    _FORCE_INLINE_ constexpr var::boolean contains(const char_type* const target_substring_ptrc_p) const noexcept
    {
        FE_EXIT(target_substring_ptrc_p == nullptr, "ERROR: target_substring_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        return (algorithm::string::search_very_first_substring(this->data(), target_substring_ptrc_p)).has_value();
    }

    _FORCE_INLINE_ constexpr void copy(char_type* const in_out_buffer_ptrc_p, size_t in_out_buffer_capacity_p, index_t begin_p, index_t end_p) const noexcept
    {
        FE_EXIT(in_out_buffer_ptrc_p == nullptr, "ERROR: in_out_buffer_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        FE_ASSERT(begin_p >= end_p, "ERROR: end_p cannot be greater than or equal to end_p.");
        FE_ASSERT(end_p > algorithm::string::string_length(this->data()), "ERROR: end_p cannot be greater than the left operand string length.");
        algorithm::string::copy_string(in_out_buffer_ptrc_p, in_out_buffer_capacity_p, *(this->m_string) + begin_p, end_p - begin_p);
    }

    _FORCE_INLINE_ constexpr FE::optional<algorithm::string::range> find(compile_time_constant_string<char_type>& target_substring_ref_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        FE::optional<algorithm::string::range> l_result = algorithm::string::search_very_first_substring(this->data() + position_p, target_substring_ref_p.data());
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    _FORCE_INLINE_ constexpr FE::optional<algorithm::string::range> find(const char_type* const target_substring_ptrc_p, index_t position_p = 0) const noexcept
    {
        FE_EXIT(target_substring_ptrc_p == nullptr, "ERROR: target_substring_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        FE::optional<algorithm::string::range> l_result = algorithm::string::search_very_first_substring(this->data() + position_p, target_substring_ptrc_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    _FORCE_INLINE_ constexpr algorithm::string::char_search_result<char_type> find(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        algorithm::string::char_search_result l_result = algorithm::string::search_very_first_char(this->data() + position_p, target_character_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _FORCE_INLINE_ constexpr FE::optional<algorithm::string::range> rfind(compile_time_constant_string<char_type>& target_substring_ref_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_very_last_substring_within_range(this->data(), algorithm::string::range{0, position_p}, target_substring_ref_p.data());
    }

    _FORCE_INLINE_ constexpr FE::optional<algorithm::string::range> rfind(const char_type* const target_substring_ptrc_p, index_t position_p = 0) const noexcept
    {
        FE_EXIT(target_substring_ptrc_p == nullptr, "ERROR: target_substring_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_very_last_substring_within_range(this->data(), algorithm::string::range{0, position_p}, target_substring_ptrc_p);
    }

    _FORCE_INLINE_ constexpr algorithm::string::char_search_result<char_type> rfind(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_very_last_char_within_range(this->data(), algorithm::string::range{0, position_p}, target_character_p);;
    }

    _FORCE_INLINE_ constexpr algorithm::string::char_count<char_type> count_chars(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->data()), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::count_chars(this->data() + position_p, target_character_p);
    }

    _FORCE_INLINE_ static constexpr void swap(compile_time_constant_string<char_type>& first_ref_p, compile_time_constant_string<char_type>& second_ref_p) noexcept
    {
        compile_time_constant_string<char_type> l_temp = first_ref_p;
        first_ref_p = second_ref_p;
        second_ref_p = l_temp;
    }

    _FORCE_INLINE_ constexpr boolean operator==(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        return algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }
    _FORCE_INLINE_ constexpr boolean operator==(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_EXIT(cstr_ptrc_p == nullptr, "ERROR: cstr_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        return algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    _FORCE_INLINE_ constexpr boolean operator!=(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }
    _FORCE_INLINE_ constexpr boolean operator!=(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_EXIT(cstr_ptrc_p == nullptr, "ERROR: cstr_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        return !algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    _FORCE_INLINE_ friend constexpr boolean operator==(const char_type* const cstr_ptrc_p, compile_time_constant_string<char_type>& cstring_ref_p) noexcept
    {
        FE_EXIT(cstr_ptrc_p == nullptr, "ERROR: cstr_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        return algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }
    _FORCE_INLINE_ friend constexpr boolean operator!=(const char_type* const cstr_ptrc_p, compile_time_constant_string<char_type>& cstring_ref_p) noexcept
    {
        FE_EXIT(cstr_ptrc_p == nullptr, "ERROR: cstr_ptrc_p is nullptr", FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR);
        return !algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }
};

using cstring = compile_time_constant_string<char>;
using ucstring = compile_time_constant_string<var::uchar>;
using scstring = compile_time_constant_string<var::schar>;
using wcstring = compile_time_constant_string<var::wchar>;

#if _HAS_CXX20 == 1
using cstring8 = compile_time_constant_string<var::UTF8>;
#endif

using cstring16 = compile_time_constant_string<var::UTF16>;
using cstring32 = compile_time_constant_string<var::UTF32>;

END_NAMESPACE
#endif
