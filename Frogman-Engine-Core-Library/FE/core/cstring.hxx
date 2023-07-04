#ifndef _FE_CORE_CSTRING_HXX_
#define _FE_CORE_CSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "algorithm/string.hxx"
#include "algorithm/utility.hxx"
#include "iterator.hxx"
#include <cstring>
#include <optional>


BEGIN_NAMESPACE(FE)


template< typename char_type = char >
#if _HAS_CXX20_ == 1
    requires character_type<char_type>
#endif
class compile_time_constant_string final
{
    static_assert(sizeof(char_type) <= sizeof(int32), "char_type is not a valid character type");

public:
    typedef const char_type* value_type;
    typedef char_type buffer_type;
    typedef var::uint64 length_type;

private:
    ::std::optional<const char_type*> m_string;

public:
    constexpr compile_time_constant_string() noexcept {}
    _CONSTEXPR20_ ~compile_time_constant_string() noexcept {}

    template <typename T>
    constexpr compile_time_constant_string(T* c_style_read_only_string_ptr_p) noexcept
    {
        FE_ASSERT(typeid(decltype(c_style_read_only_string_ptr_p)).name() != typeid(const char_type*).name(), "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.", _ASSERTED_LOCATION_);
        this->m_string.emplace(c_style_read_only_string_ptr_p); 
    }
    constexpr compile_time_constant_string(compile_time_constant_string<char_type>& other_ref_p) noexcept { this->m_string.emplace(*other_ref_p.m_string); }
    constexpr compile_time_constant_string(compile_time_constant_string<char_type>&& move_p) noexcept { this->m_string.emplace(*move_p.m_string); }

    template <typename T>
    constexpr compile_time_constant_string<char_type>& operator=(T* c_style_read_only_string_ptr_p) noexcept
    {
        FE_ASSERT(typeid(decltype(c_style_read_only_string_ptr_p)).name() != typeid(const char_type*).name(), "ERROR: char* nor any another non-const char_type* types cannot be assigned to a cstring instance.", _ASSERTED_LOCATION_);

        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(c_style_read_only_string_ptr_p);

        return *this;
    }
    constexpr compile_time_constant_string<char_type>& operator=(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*other_ref_p.m_string);

        return *this;
    }
    constexpr compile_time_constant_string<char_type>& operator=(compile_time_constant_string<char_type>&& move_p) noexcept
    {
        if (this->m_string.has_value())
        {
            this->m_string.reset();
        }

        this->m_string.emplace(*move_p.m_string);

        return *this;
    }

    constexpr char_type at(index_t index_p) const noexcept
    {
        FE_ASSERT(index_p >= algorithm::string::string_length(*(this->m_string)), "ERROR: an input index value passed to at() exceeded the index boundary of a cstring instance.", _ASSERTED_LOCATION_);
        return (*this->m_string)[index_p];
    }
    constexpr char_type operator[](index_t index_p) const noexcept
    {
        FE_ASSERT(index_p >= algorithm::string::string_length(*(this->m_string)), "ERROR: an input index value passed to operator[]() exceeded the index boundary of a cstring instance.", _ASSERTED_LOCATION_);
        return (*this->m_string)[index_p];
    }

    constexpr char_type front() const noexcept { return *(*this->m_string); }
    constexpr char_type back() const noexcept { return  (*this->m_string)[algorithm::string::string_length(*this->m_string) - 1]; }

    // It returns a pointer to the data
    constexpr const char_type* data() const noexcept { return (*this->m_string); }

    // It returns a pointer to a traditional c-style read-only string
    constexpr const char_type* c_str() const noexcept { return *this->m_string; }

    // It returns a standard string
    constexpr ::std::basic_string<char_type> std_str() const noexcept { return *this->m_string; }

    constexpr iterator<contiguous_iterator<const char_type>> begin() const noexcept { return *this->m_string; }
    constexpr iterator<contiguous_iterator<const char_type>> end() const noexcept { return (*this->m_string) + algorithm::string::string_length(*this->m_string); }
    constexpr reverse_iterator<contiguous_iterator<const char_type>> rbegin() const noexcept { return (*this->m_string) + (algorithm::string::string_length(*this->m_string) - 1); }
    constexpr reverse_iterator<contiguous_iterator<const char_type>> rend() const noexcept { return (*this->m_string) - 1; }

    constexpr var::boolean is_empty() const noexcept { return !(this->m_string.has_value()); }
    constexpr var::size_t length() const noexcept { return algorithm::string::string_length<char_type>(*this->m_string); }
    constexpr var::uint64 max_length() const noexcept { return ::FE::max_value<var::uint64>(); }
    constexpr void clear() noexcept { this->m_string.reset(); }

    constexpr var::boolean starts_with(compile_time_constant_string<char_type>& substring_ref_p) const noexcept 
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        FE_ASSERT(algorithm::string::string_length(this->data()) < l_substring_length, "ERROR: The input target sub-string instance's length is greater than the left operand string", _ASSERTED_LOCATION_);
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{0, l_substring_length}, 
                                                            substring_ref_p.data(), algorithm::string::string_range{0, l_substring_length}
                                                            );
    }
    constexpr var::boolean starts_with(const char_type target_character_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{0, 1},
                                                            &target_character_p, algorithm::string::string_range{0, 1}
                                                            );
    }
    constexpr var::boolean starts_with(const char_type* const substring_ptrc_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        FE_ASSERT(algorithm::string::string_length(this->data()) < l_substring_length, "ERROR: The input target sub-string instance's length is greater than the left operand string", _ASSERTED_LOCATION_);
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{0, l_substring_length},
                                                            substring_ptrc_p, algorithm::string::string_range{0, l_substring_length}
                                                            );
    }

    constexpr var::boolean ends_with(compile_time_constant_string<char_type>& substring_ref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ref_p.data());
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        FE_ASSERT(l_this_string_length < l_substring_length, "ERROR: The input target sub-string instance's length is greater than the left operand string", _ASSERTED_LOCATION_);
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{l_this_string_length - l_substring_length, l_this_string_length},
                                                            substring_ref_p.data(), algorithm::string::string_range{0, l_substring_length}
                                                            );
    }
    constexpr var::boolean ends_with(const char_type target_character_p) const noexcept
    {
        length_t l_this_string_length = algorithm::string::string_length(this->data());
    
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{l_this_string_length - 1, l_this_string_length},
                                                            &target_character_p, algorithm::string::string_range{0, 1}
                                                            );
    }
    constexpr var::boolean ends_with(const char_type* const substring_ptrc_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        length_t l_this_string_length = algorithm::string::string_length(this->data());
        FE_ASSERT(l_this_string_length < l_substring_length, "ERROR: The input target sub-string instance's length is greater than the left operand string", _ASSERTED_LOCATION_);
        return algorithm::string::compare_ranged_strings(   this->data(), algorithm::string::string_range{l_this_string_length - l_substring_length, l_this_string_length},
                                                            substring_ptrc_p, algorithm::string::string_range{0, l_substring_length}
                                                            );
    }

    constexpr var::boolean contains(compile_time_constant_string<char_type>& substring_ref_p) const noexcept
    {
        return (algorithm::string::search_very_first_substring(this->data(), substring_ref_p.data())).has_value();
    }
    constexpr var::boolean contains(const char_type target_character_p) const noexcept
    {
        algorithm::string::target_char_search_result<char_type> l_target_char_search_result = algorithm::string::search_very_first_char(this->data(), target_character_p);
        return (l_target_char_search_result._target_data != static_cast<char_type>('\0')) ? true : false;
    }
    constexpr var::boolean contains(const char_type* const target_substring_ptrc_p) const noexcept
    {
        return (algorithm::string::search_very_first_substring(this->data(), target_substring_ptrc_p)).has_value();
    }

    constexpr void copy_substring(index_t begin_p, index_t end_p, char_type* const in_out_buffer_ptrc_p, size_t in_out_buffer_capacity_p) const noexcept
    {
        algorithm::string::copy_string(in_out_buffer_ptrc_p, in_out_buffer_capacity_p, *(this->m_string) + begin_p, end_p - begin_p);
    }

    constexpr ::std::optional<algorithm::string::string_range> find(compile_time_constant_string<char_type>& target_substring_ref_p, index_t position_p = 0) const noexcept
    {
        ::std::optional<algorithm::string::string_range> l_result = algorithm::string::search_very_first_substring(this->data() + position_p, target_substring_ref_p.data());
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    constexpr ::std::optional<algorithm::string::string_range> find(const char_type* const target_substring_ptrc_p, index_t position_p = 0) const noexcept
    {
        ::std::optional<algorithm::string::string_range> l_result = algorithm::string::search_very_first_substring(this->data() + position_p, target_substring_ptrc_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    constexpr algorithm::string::target_char_search_result<char_type> find(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        ::std::optional<algorithm::string::string_range> l_result = algorithm::string::search_very_first_char(this->data() + position_p, target_character_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    constexpr algorithm::string::target_char_count<char_type> find_all_corresponding_characters(const char_type target_character_p, index_t position_p = 0) const noexcept
    {
        return algorithm::string::search_all_corresponding_characters(this->data() + position_p, target_character_p);
    }

    static constexpr void swap(compile_time_constant_string<char_type>& first_ref_p, compile_time_constant_string<char_type>& second_ref_p) noexcept
    {
        compile_time_constant_string<char_type> l_temp = first_ref_p;
        first_ref_p = second_ref_p;
        second_ref_p = l_temp;
    }

    constexpr boolean operator==(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        return algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }
    constexpr boolean operator==(const char_type* const cstr_ptrc_p) noexcept
    {
        return algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    constexpr boolean operator!=(compile_time_constant_string<char_type>& other_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(*this->m_string, *other_ref_p.m_string);
    }
    constexpr boolean operator!=(const char_type* const cstr_ptrc_p) noexcept
    {
        return !algorithm::string::string_comparison(*this->m_string, cstr_ptrc_p);
    }

    friend constexpr boolean operator==(const char_type* const cstr_ptrc_p, compile_time_constant_string<char_type>& cstring_ref_p) noexcept
    {
        return algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }
    friend constexpr boolean operator!=(const char_type* const cstr_ptrc_p, compile_time_constant_string<char_type>& cstring_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(cstr_ptrc_p, *cstring_ref_p.m_string);
    }
};

using cstring = compile_time_constant_string<char>;
using ucstring = compile_time_constant_string<var::uchar>;
using scstring = compile_time_constant_string<var::schar>;
using wcstring = compile_time_constant_string<var::wchar>;

#if _HAS_CXX20 == 1
using cstring8 = compile_time_constant_string<var::char8>;
#endif

using cstring16 = compile_time_constant_string<var::char16>;
using cstring32 = compile_time_constant_string<var::char32>;

END_NAMESPACE
#endif
