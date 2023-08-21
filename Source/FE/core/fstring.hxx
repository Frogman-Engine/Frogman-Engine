#ifndef _FE_CORE_FSTRING_HXX_
#define _FE_CORE_FSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "algorithm/string.hxx"
#include "iterator.hxx"
#include <FE/core/memory.hxx>
#include "heap_memory.hpp"


BEGIN_NAMESPACE(FE)


template<typename char_type, uint64 string_max_capacity>
class fixed_sized_string 
{
    static_assert(FE::is_char<char_type>::value == true, "char_type is not a valid character type.");
    static_assert(FE::is_trivially_constructible_and_destructible<char_type>::value == FE::TYPE_TRIVIALITY::_TRIVIAL, "char_type is not a valid character type.");
   
    char_type m_fstring[string_max_capacity];
    var::uint64 m_string_length;

public:
    using value_type = char_type;
    using size_type = var::uint64;
    using length_type = var::uint64;
    using difference_type = var::ptrdiff_t;
    using reference = char_type&;
    using const_reference = const char_type&;
    using pointer = char_type*;
    using const_pointer = const char_type*;
    using iterator = FE::iterator<FE::contiguous_iterator<char_type>>;
    using const_iterator = FE::const_iterator<FE::contiguous_iterator<char_type>>;
    using reverse_iterator = FE::reverse_iterator<FE::contiguous_iterator<char_type>>;
    using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<char_type>>;


    _CONSTEXPR_ _FORCE_INLINE_ fixed_sized_string() noexcept
        : m_fstring{ _NULL_ }, m_string_length() {}

    _FORCE_INLINE_ fixed_sized_string(const char_type* const cstr_ptrc_p) noexcept 
        : m_fstring{ _NULL_ }, m_string_length(algorithm::string::string_length<char_type>(cstr_ptrc_p))
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        
        FE_ASSERT(this->m_string_length >= string_max_capacity, "CRITICAL ERROR: the input string length exceeds the max string capacity.");
        algorithm::string::copy_string( this->m_fstring, string_max_capacity, cstr_ptrc_p, this->m_string_length);
    }

    _FORCE_INLINE_ fixed_sized_string(const fixed_sized_string& other_cref_p) noexcept
        : m_fstring{ _NULL_ }, m_string_length(other_cref_p.m_string_length)
    {
        if (other_cref_p.m_string_length == 0)
        {
            return;
        }

        algorithm::string::copy_string(this->m_fstring, string_max_capacity, other_cref_p.m_fstring, string_max_capacity);
    }

    _FORCE_INLINE_ fixed_sized_string(fixed_sized_string&& rvalue_reference_p) noexcept
        : m_fstring{ _NULL_ }, m_string_length(rvalue_reference_p.m_string_length)
    {
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, rvalue_reference_p.m_fstring, string_max_capacity);
        UNALIGNED_MEMSET(rvalue_reference_p.m_fstring, _NULL_, rvalue_reference_p.m_string_length * sizeof(char_type));
        rvalue_reference_p.m_string_length = 0;
    }


    _FORCE_INLINE_ fixed_sized_string& operator=(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));

        this->m_string_length = algorithm::string::string_length<char_type>(cstr_ptrc_p);

        FE_ASSERT(this->m_string_length >= string_max_capacity, "CRITICAL ERROR: the input string length exceeds the max string capacity.");
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, cstr_ptrc_p, this->m_string_length);
        return *this;
    }

    _FORCE_INLINE_ fixed_sized_string& operator=(const fixed_sized_string& other_cref_p) noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return *this;
        }

        this->m_string_length = other_cref_p.m_string_length;
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, other_cref_p.m_fstring, string_max_capacity);
        return *this;
    }

    _FORCE_INLINE_ fixed_sized_string& operator=(fixed_sized_string&& rvalue_p) noexcept
    {
        if (rvalue_p.m_string_length == 0)
        {
            return *this;
        }

        algorithm::string::copy_string(this->m_fstring, string_max_capacity, rvalue_p.m_fstring, string_max_capacity);
        UNALIGNED_MEMSET(rvalue_p.m_fstring, _NULL_, rvalue_p.m_string_length * sizeof(char_type));
        this->m_string_length = rvalue_p.m_string_length;
        rvalue_p.m_string_length = 0;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ char_type& operator[](index_t idx_p) noexcept
    {
        FE_ASSERT(idx_p >= this->m_string_length, "CRITICAL ERROR: index out of boundary.");
        return this->m_fstring[idx_p];
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(size_type count_p, char_type value_p) noexcept
    {
        FE_ASSERT(count_p >= string_max_capacity, "ERROR: count_p exceeds fixed sized string capacity.");

        char_type* l_string_ptr = static_cast<char_type*>(this->m_fstring);
        for (var::length_t i = 0; i != count_p; ++i)
        {
             *l_string_ptr  = value_p;
             ++l_string_ptr;
        }
        this->m_string_length = count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const fixed_sized_string& other_cref_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return *this;
        }

        FE_ASSERT(input_begin_p >= input_end_p, "ERROR: input_begin_p cannot be greater than or equal to input_end_p.");
        size_type l_size_to_copy = input_end_p - input_begin_p;
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, other_cref_p.m_fstring + input_begin_p, l_size_to_copy);
        this->m_string_length = l_size_to_copy;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const char_type* const str_ptrc_p, size_type size_to_assign_p) noexcept
    {
        FE_ASSERT(size_to_assign_p == 0, "${%s@0}: {%s@1} is zero.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), TO_STRING(size_to_assign_p));
        FE_ASSERT(str_ptrc_p == nullptr, "${%s@0}: {%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(str_ptrc_p));
        FE_ASSERT(size_to_assign_p >= string_max_capacity, "ERROR: size_to_assign_p exceeds fixed sized string capacity.");
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, str_ptrc_p, size_to_assign_p);
        this->m_string_length = size_to_assign_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const_iterator input_begin_p, const_iterator input_end_p) noexcept
    {
        FE_ASSERT(input_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_begin_p));
        FE_ASSERT(input_end_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_end_p));

        FE_ASSERT(input_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_begin_p));
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: input_begin_p address value must be smaller than input_end_p address value.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT((input_end_p - input_begin_p) >= string_max_capacity, "${%s@0}: input string range length exceeds fixed sized string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        size_type l_size_to_copy = input_end_p - input_begin_p;
        algorithm::string::copy_string(this->m_fstring, string_max_capacity, input_begin_p.operator->(), input_end_p - input_begin_p);
        this->m_string_length = l_size_to_copy;
        return *this;
    }
    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string&  assign(std::initializer_list<const char_type>&& char_list_rvalue_p) noexcept
    {
        FE_ASSERT(char_list_rvalue_p.size() >= string_max_capacity, "ERROR: char_list_rvalue_p.size() exceeds fixed sized string capacity.");
        FE_ASSERT(char_list_rvalue_p.size() == 0, "${%s@0}: {%s@1} is an empty initializer_list.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), TO_STRING(char_list_rvalue_p));
        algorithm::string::concatenate_characters(this->m_fstring, string_max_capacity, std::move(char_list_rvalue_p));
        this->m_string_length = char_list_rvalue_p.size();
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ char_type front() const noexcept { return *this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ char_type back() const noexcept { return this->m_fstring[this->m_string_length - 1]; }

    // It returns a pointer to the data
    _CONSTEXPR20_ _FORCE_INLINE_ char_type* data() const noexcept { return const_cast<char_type*>(this->m_fstring); }

    // It returns a pointer to a traditional c-style read-only string
    _CONSTEXPR20_ _FORCE_INLINE_ const char_type* c_str() const noexcept { return this->m_fstring; }

    // It returns a standard string
    _CONSTEXPR20_ _FORCE_INLINE_ std::basic_string<char_type> std_str() noexcept { return this->m_fstring; }

    _CONSTEXPR20_ _FORCE_INLINE_ iterator begin() noexcept { return this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ iterator end() noexcept { return this->m_fstring + this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ reverse_iterator rbegin() noexcept { return this->m_fstring + (this->m_string_length - 1); }
    _CONSTEXPR20_ _FORCE_INLINE_ reverse_iterator rend() noexcept { return this->m_fstring - 1; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_iterator cbegin() noexcept { return this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_iterator cend() noexcept { return this->m_fstring + this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_reverse_iterator crbegin() noexcept { return this->m_fstring + (this->m_string_length - 1); }
    _CONSTEXPR20_ _FORCE_INLINE_ const_reverse_iterator crend() noexcept { return this->m_fstring - 1; }

    _NODISCARD_ _CONSTEXPR20_ _FORCE_INLINE_ boolean is_empty() const noexcept { return (this->m_string_length == 0) ? true : false; }

    _CONSTEXPR20_ _FORCE_INLINE_ length_type length() const noexcept { return this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ length_type max_length() const noexcept { return string_max_capacity; }
    _CONSTEXPR20_ _FORCE_INLINE_ size_type capacity() const noexcept { return string_max_capacity; }

    _CONSTEXPR20_ _FORCE_INLINE_ void clear() noexcept 
    {
        UNALIGNED_MEMSET(this->m_fstring, _NULL_, string_max_capacity * sizeof(char_type));
        this->m_string_length = 0;
    }
   

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, size_type count_p, char_type value_p) noexcept
    {
        FE_ASSERT(position_p >= string_max_capacity, "ERROR: position_p cannot be greater than the string capacity.");
        FE_ASSERT(count_p == 0, "WARNING: insert() operation was not successful. size_type count_p was zero.");
        FE_ASSERT((this->m_string_length + count_p) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + count_p), this->m_fstring + position_p, this->m_string_length - position_p);

        char_type* l_string_ptr = static_cast<char_type*>(this->m_fstring + position_p);
        for (var::length_t i = 0; i != count_p; ++i)
        {
            *l_string_ptr = value_p;
            ++l_string_ptr;
        }
        this->m_string_length += count_p;
        this->m_fstring[this->m_string_length] = static_cast<char_type>('\0');
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, const char_type* const str_ptrc_p) noexcept
    {
        FE_ASSERT(position_p >= string_max_capacity, "${%s@0}: position_p cannot be greater than the string capacity.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(str_ptrc_p == nullptr, "${%s@0}: the input string is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        
        length_type l_input_string_length = algorithm::string::string_length(str_ptrc_p);
        FE_ASSERT((this->m_string_length + l_input_string_length) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + l_input_string_length), this->m_fstring + position_p, this->m_string_length - position_p);
        UNALIGNED_MEMCPY(this->m_fstring + position_p, str_ptrc_p, l_input_string_length * sizeof(char_type));
        
        this->m_string_length += l_input_string_length;
        this->m_fstring[this->m_string_length] = static_cast<char_type>('\0');
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, const fixed_sized_string& other_cref_p) noexcept
    {
        FE_ASSERT(position_p >= string_max_capacity, "ERROR: position_p cannot be greater than the string capacity.");
        FE_ASSERT(other_cref_p.is_empty() == true, "ERROR: other_cref_p is an empty string object");

        length_type l_input_string_length = algorithm::string::string_length(other_cref_p.c_str());
        FE_ASSERT((this->m_string_length + l_input_string_length) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + l_input_string_length), this->m_fstring + position_p, this->m_string_length - position_p);
        UNALIGNED_MEMCPY(this->m_fstring + position_p, other_cref_p.c_str(), l_input_string_length * sizeof(char_type));

        this->m_string_length += l_input_string_length;
        this->m_fstring[this->m_string_length] = static_cast<char_type>('\0');
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, const fixed_sized_string& other_cref_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        FE_ASSERT(position_p >= string_max_capacity, "ERROR: position_p cannot be greater than the string capacity.");
        FE_ASSERT(input_begin_p >= input_end_p, "ERROR: input_begin_p cannot be greater than input_end_p.");
        FE_ASSERT(other_cref_p.is_empty() == true, "ERROR: other_cref_p is an empty string object");

        length_type l_input_string_length = input_end_p - input_begin_p;
        FE_ASSERT(l_input_string_length > algorithm::string::string_length(other_cref_p.c_str()), "ERROR: input_end_p - input_begin_p cannot be greater than str_ptrc_p string length.");

        FE_ASSERT((this->m_string_length + l_input_string_length) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + l_input_string_length), this->m_fstring + position_p, this->m_string_length - position_p);
        UNALIGNED_MEMCPY(this->m_fstring + position_p, other_cref_p.data() + input_begin_p, l_input_string_length * sizeof(char_type));

        this->m_string_length += l_input_string_length;
        this->m_fstring[this->m_string_length] = static_cast<char_type>('\0');
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, const char_type* const str_ptrc_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        FE_ASSERT(position_p >= string_max_capacity, "ERROR: position_p cannot be greater than the string capacity.");
        FE_ASSERT(input_begin_p >= input_end_p, "ERROR: input_begin_p cannot be greater than input_end_p.");
        FE_ASSERT(str_ptrc_p == nullptr, "ERROR: the input string is nullptr");

        length_type l_input_string_length = input_end_p - input_begin_p;
        FE_ASSERT(l_input_string_length > algorithm::string::string_length(str_ptrc_p), "ERROR: input_end_p - input_begin_p cannot be greater than str_ptrc_p string length.");

        FE_ASSERT((this->m_string_length + l_input_string_length) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + l_input_string_length), this->m_fstring + position_p, this->m_string_length - position_p);
        UNALIGNED_MEMCPY(this->m_fstring + position_p, str_ptrc_p + input_begin_p, l_input_string_length * sizeof(value_type));

        this->m_string_length += l_input_string_length;
        this->m_fstring[this->m_string_length] = static_cast<value_type>('\0');
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type position_p, std::initializer_list<const char_type>&& initializer_list_p) noexcept
    {
        FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}: initializer_list_p is empty.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
        FE_ASSERT((this->m_string_length + initializer_list_p.size()) >= string_max_capacity, "ERROR: fixed sized string capacity overflowed.");

        std::memmove(this->m_fstring + (position_p + initializer_list_p.size()), this->m_fstring + position_p, this->m_string_length - position_p);
        UNALIGNED_MEMSET(this->m_fstring + position_p, _NULL_, initializer_list_p.size() * sizeof(value_type));
        algorithm::string::concatenate_characters(this->m_fstring + position_p, string_max_capacity - position_p, std::move(initializer_list_p));
        this->m_string_length += initializer_list_p.size();
        this->m_fstring[this->m_string_length] = static_cast<value_type>('\0');
        return *this;
    }
    

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& erase(size_type index_p = 0, size_type count_p = 1) noexcept
    {
        FE_ASSERT(this->max_length() < (index_p + count_p), "${%s@0}: fixed sized string capacity overflowed.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(count_p == 0, "${%s@0}: fixed sized string capacity overflowed.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
       
        std::memmove(this->m_fstring + index_p, this->m_fstring + (index_p + count_p), (this->m_string_length - index_p) * sizeof(value_type));
        this->m_string_length -= count_p;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ void push_back(const char_type char_type_element_p) noexcept
    {
        FE_ASSERT(this->m_string_length >= string_max_capacity, "${%s0}: out of capacity", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        this->m_fstring[this->m_string_length] = char_type_element_p;
        ++this->m_string_length;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ char_type pop_back() noexcept
    {
        FE_ASSERT(this->m_string_length == 0, "${%s0}: Unable to pop an empty fstring", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        const char_type l_return_value = this->back();
        --this->m_string_length;
        this->m_fstring[this->m_string_length] = static_cast<const char_type>('\0');
        return l_return_value;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(size_type count_p, char_type char_p) noexcept
    {
        FE_ASSERT(count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), TO_STRING(count_p));
        FE_ASSERT(this->max_length() < (this->m_string_length + count_p), "${%s0}: cannot append ${%ld@1} character(s) to the fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), &count_p);

        value_type* l_begin_ptr = this->m_fstring + this->m_string_length;
        value_type* const l_end_ptrc = l_begin_ptr + count_p;

        while (l_begin_ptr != l_end_ptrc)
        {
            *l_begin_ptr = char_p;
            ++l_begin_ptr;
        }
        this->m_string_length += count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const fixed_sized_string& other_cref_p) noexcept
    {
        return this->operator+=(other_cref_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const fixed_sized_string& other_cref_p, size_type position_p, size_type count_p = 1) noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return *this;
        }

        FE_ASSERT(count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), TO_STRING(count_p));
        FE_ASSERT(this->max_length() < (this->m_string_length + count_p), "${%s0}: cannot append another fstring that exceeds the capacity of a caller fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(other_cref_p.length() < (count_p + position_p), "${%s0}: out of input fstring index boundary.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

        value_type* l_begin_ptr = this->m_fstring + this->m_string_length;
        value_type* const l_end_ptrc = l_begin_ptr + count_p;
        value_type* l_other_begin_ptr = other_cref_p.data() + position_p;

        while (l_begin_ptr != l_end_ptrc)
        {
            *l_begin_ptr = *l_other_begin_ptr;
            ++l_begin_ptr;
            ++l_other_begin_ptr;
        }
        this->m_string_length += count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const char_type* cstr_ptr_p, size_type count_p) noexcept
    {
        FE_ASSERT(cstr_ptr_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptr_p));
        FE_ASSERT(count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), TO_STRING(count_p));
        FE_ASSERT(this->max_length() < (this->m_string_length + count_p), "${%s0}: cannot append another fstring that exceeds the capacity of a caller fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
 
        value_type* l_begin_ptr = this->m_fstring + this->m_string_length;
        value_type* const l_end_ptrc = l_begin_ptr + count_p;

        while (l_begin_ptr != l_end_ptrc)
        {
            *l_begin_ptr = *cstr_ptr_p;
            ++l_begin_ptr;
            ++cstr_ptr_p;
        }
        this->m_string_length += count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const char_type* const cstr_ptrc_p) noexcept
    {
        return this->operator+=(cstr_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const_iterator input_begin_p, const_iterator input_end_p) noexcept
    {
        FE_ASSERT(input_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_begin_p));
        FE_ASSERT(input_end_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_end_p));
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: input_begin_p address value must be smaller than input_end_p address value.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT((input_end_p - input_begin_p) + this->m_string_length >= string_max_capacity, "${%s@0}: input string range length exceeds fixed sized string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        
        size_type l_input_size = input_end_p - input_begin_p;
        value_type* l_begin_ptr = this->m_fstring + this->m_string_length;
        value_type* const l_end_ptrc = l_begin_ptr + l_input_size;

        while (l_begin_ptr != l_end_ptrc)
        {
            *l_begin_ptr = *input_begin_p;
            ++l_begin_ptr;
            ++input_begin_p;
        }
        this->m_string_length += l_input_size;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(std::initializer_list<const char_type>&& initializer_list_p) noexcept
    {
        FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}: initializer_list_p is empty.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
        FE_ASSERT(this->max_length() < initializer_list_p.size() + this->m_string_length, "${%s@0}: initializer_list_p is too large to take the contents.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        algorithm::string::concatenate_characters(this->data() + this->m_string_length, this->max_length(), std::move(initializer_list_p));
        this->m_string_length += initializer_list_p.size();
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const fixed_sized_string& other_cref_p) noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return *this;
        }
        this->m_string_length += other_cref_p.m_string_length;
        algorithm::string::string_concatenation<char_type>(this->m_fstring, string_max_capacity, other_cref_p.m_fstring, other_cref_p.m_string_length);
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const char_type* const cstr_ptrc_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));

        length_type l_input_string_length = algorithm::string::string_length<char_type>(cstr_ptrc_p);
        algorithm::string::string_concatenation<char_type>(this->m_fstring, string_max_capacity, cstr_ptrc_p, l_input_string_length);
        this->m_string_length += l_input_string_length;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const char_type char_p) noexcept
    {
        algorithm::string::string_concatenation<char_type>(this->m_fstring, string_max_capacity, &char_p, 1);
        this->m_string_length += 1;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const fixed_sized_string& substring_cref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_cref_p.data());
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, l_substring_length},
            substring_cref_p.data(), algorithm::string::range{0, l_substring_length}
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const char_type target_character_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, 1},
            & target_character_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_ASSERT(substring_ptrc_p == nullptr, "${%s@0}: substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, l_substring_length},
            substring_ptrc_p, algorithm::string::range{ 0, l_substring_length }
        );
    }


    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const fixed_sized_string& substring_cref_p) const noexcept
    {
        length_t l_substring_length = algorithm::string::string_length(substring_cref_p.data());
        length_t l_this_string_length = algorithm::string::string_length(this->m_fstring);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{l_this_string_length - l_substring_length, l_this_string_length},
            substring_cref_p.data(), algorithm::string::range{ 0, l_substring_length }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const char_type target_character_p) const noexcept
    {
        length_t l_this_string_length = algorithm::string::string_length(this->m_fstring);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{l_this_string_length - 1, l_this_string_length},
            & target_character_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const char_type* const substring_ptrc_p) const noexcept
    {
        FE_ASSERT(substring_ptrc_p == nullptr, "${%s@0}: substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        length_t l_substring_length = algorithm::string::string_length(substring_ptrc_p);
        length_t l_this_string_length = algorithm::string::string_length(this->m_fstring);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{l_this_string_length - l_substring_length, l_this_string_length},
            substring_ptrc_p, algorithm::string::range{ 0, l_substring_length }
        );
    }


    _CONSTEXPR20_ _FORCE_INLINE_  boolean contains(fixed_sized_string& substring_ref_p) const noexcept
    {
        if (substring_ref_p.m_string_length == 0)
        {
            return false;
        }

        return (algorithm::string::search_first_substring(this->m_fstring, substring_ref_p.data())).has_value();
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean contains(const char_type target_character_p) const noexcept
    {
        algorithm::string::char_search_result<char_type> l_target_char_search_result = algorithm::string::search_first_char(this->m_fstring, target_character_p);
        return (l_target_char_search_result._target_data != static_cast<char_type>('\0')) ? true : false;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean contains(const char_type* const target_substring_ptrc_p) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        return (algorithm::string::search_first_substring(this->m_fstring, target_substring_ptrc_p)).has_value();
    }


    _CONSTEXPR20_ _FORCE_INLINE_ void copy(char_type* const in_out_buffer_ptrc_p, size_t in_out_buffer_capacity_p, size_type input_begin_p, size_type input_end_p) const noexcept
    {
        FE_ASSERT(in_out_buffer_ptrc_p == nullptr, "${%s@0}: in_out_buffer_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(input_begin_p >= input_end_p, "ERROR: input_end_p cannot be greater than or equal to input_end_p.");
        FE_ASSERT(input_end_p > algorithm::string::string_length(this->m_fstring), "ERROR: input_end_p cannot be greater than the left operand string length.");
        algorithm::string::copy_string(in_out_buffer_ptrc_p, in_out_buffer_capacity_p, this->m_fstring + input_begin_p, input_end_p - input_begin_p);
    }


    //replace


    _CONSTEXPR20_ _FORCE_INLINE_ FE::optional<algorithm::string::range> find(const fixed_sized_string& other_cref_p, size_type position_p = 0) const noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return FE::nullopt;
        }

        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        FE::optional<algorithm::string::range> l_result = algorithm::string::search_first_substring(this->m_fstring + position_p, other_cref_p.data());
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    _CONSTEXPR20_ _FORCE_INLINE_ FE::optional<algorithm::string::range> find(const char_type* const target_substring_ptrc_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        FE::optional<algorithm::string::range> l_result = algorithm::string::search_first_substring(this->m_fstring + position_p, target_substring_ptrc_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }
    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_search_result<char_type> find(const char_type target_character_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        algorithm::string::char_search_result l_result = algorithm::string::search_first_char(this->m_fstring + position_p, target_character_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ FE::optional<algorithm::string::range> rfind(const fixed_sized_string& other_cref_p, size_type position_p = 0) const noexcept
    {
        if (other_cref_p.m_string_length == 0)
        {
            return FE::nullopt;
        }

        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_substring_within_range(this->m_fstring, algorithm::string::range{0, position_p}, other_cref_p.data());
    }

    _CONSTEXPR20_ _FORCE_INLINE_ FE::optional<algorithm::string::range> rfind(const char_type* const target_substring_ptrc_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(target_substring_ptrc_p == nullptr, "${%s@0}: target_substring_ptrc_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_substring_within_range(this->m_fstring, algorithm::string::range{0, position_p}, target_substring_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_search_result<char_type> rfind(const char_type target_character_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::search_last_char_within_range(this->m_fstring, algorithm::string::range{0, position_p}, target_character_p);;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_count<char_type> count_chars(const char_type target_character_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > algorithm::string::string_length(this->m_fstring), "ERROR: position_p cannot be greater than the left operand string length.");
        return algorithm::string::count_chars(this->m_fstring + position_p, target_character_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ void swap(fixed_sized_string& second_ref_p) noexcept
    {
        fixed_sized_string<char_type, string_max_capacity> l_temp = std::move(*this);
        *this = std::move(second_ref_p);
        second_ref_p = std::move(l_temp);
    }
          
    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator==(const fixed_sized_string& other_cref_p)const noexcept
    {
        return algorithm::string::string_comparison(this->m_fstring, other_cref_p.m_fstring);
    }
    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator==(const char_type* const cstr_ptrc_p) const noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        return algorithm::string::string_comparison(this->m_fstring, cstr_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator!=(const fixed_sized_string& other_cref_p) const noexcept
    {
        return !algorithm::string::string_comparison(this->m_fstring, other_cref_p.m_fstring);
    }
    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator!=(const char_type* const cstr_ptrc_p) const noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        return !algorithm::string::string_comparison(this->m_fstring, cstr_ptrc_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator==(const char_type* const cstr_ptrc_p, const fixed_sized_string<char_type, string_max_capacity>& fstring_cref_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        return algorithm::string::string_comparison(cstr_ptrc_p, fstring_cref_p.m_fstring);
    }
    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator!=(const char_type* const cstr_ptrc_p, const fixed_sized_string<char_type, string_max_capacity>& fstring_cref_p) noexcept
    {
        FE_ASSERT(cstr_ptrc_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        return !algorithm::string::string_comparison(cstr_ptrc_p, fstring_cref_p.m_fstring);
    }
};


template<uint64 string_max_capacity>
using fstring = FE::fixed_sized_string<char, string_max_capacity>;
template<uint64 string_max_capacity>
using ufstring = FE::fixed_sized_string<var::uchar, string_max_capacity>;
template<uint64 string_max_capacity>
using sfstring = FE::fixed_sized_string<var::schar, string_max_capacity>;

template<uint64 string_max_capacity>
using fwstring = FE::fixed_sized_string<var::wchar, string_max_capacity>;

#ifdef _HAS_CXX20_
template<uint64 string_max_capacity>
using fstring8 = FE::fixed_sized_string<var::UTF8, string_max_capacity>;
#endif

template<uint64 string_max_capacity>
using fstring16 = FE::fixed_sized_string<var::UTF16, string_max_capacity>;

template<uint64 string_max_capacity>
using fstring32 = FE::fixed_sized_string<var::UTF32, string_max_capacity>;


END_NAMESPACE;
#endif
