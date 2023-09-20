#ifndef _FE_CORE_FSTRING_HXX_
#define _FE_CORE_FSTRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/char_traits.hxx>
#include <FE/core/heap_memory.hpp>
#include <FE/core/iterator.hxx>
#include <FE/core/memory.hxx>
#pragma warning (push)
#pragma warning (disable: 6386)
#pragma warning (disable: 26800)




BEGIN_NAMESPACE(FE)


template<typename CharT, uint64 Capacity, class Traits = FE::char_traits<CharT>>
class fixed_sized_string final
{
    FE_STATIC_ASSERT(FE::is_char<CharT>::value == false, "static assertion failed: the template argument CharT is not a valid character type.");
    FE_STATIC_ASSERT(std::is_class<Traits>::value == false, "static assertion failed: the template argument traits is not a class or a struct type.");
    FE_STATIC_ASSERT((std::is_same<CharT, Traits::value_type>::value == false), "static assertion failed: enforcing traits' value_type to be equivalent to CharT. The template parameter CharT must be identical to traits::value_type.");


public:
    using traits_type = Traits;
    using value_type = CharT;
    using size_type = var::uint64;
    using length_type = var::uint64;
    using difference_type = var::ptrdiff_t;
    using reference = CharT&;
    using const_reference = const CharT&;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using iterator = FE::iterator<FE::contiguous_iterator<CharT>>;
    using const_iterator = FE::const_iterator<FE::contiguous_iterator<CharT>>;
    using reverse_iterator = FE::reverse_iterator<FE::contiguous_iterator<CharT>>;
    using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<CharT>>;


private:
    CharT m_fstring[Capacity];
    length_type m_string_length;


public:
    _FORCE_INLINE_ fixed_sized_string() noexcept
        : m_fstring{ _NULL_ }, m_string_length() {}

    _FORCE_INLINE_ fixed_sized_string(const CharT* const string_p) noexcept 
        : m_fstring{ _NULL_ }, m_string_length(algorithm::string::string_length<CharT>(string_p))
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        FE_ASSERT(this->m_string_length >= Capacity, "${%s@0}: the input string length exceeds the max string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));

        algorithm::string::copy_string( this->m_fstring, Capacity, string_p, this->m_string_length);
    }

    _FORCE_INLINE_ fixed_sized_string(const fixed_sized_string& other_p) noexcept
        : m_fstring{ _NULL_ }, m_string_length(other_p.m_string_length)
    {
        if (other_p.m_string_length == 0)
        {
            return;
        }

        algorithm::string::copy_string(this->m_fstring, Capacity, other_p.m_fstring, Capacity);
    }

    _FORCE_INLINE_ fixed_sized_string(fixed_sized_string&& rvalue_p) noexcept
        : m_fstring{ _NULL_ }, m_string_length(rvalue_p.m_string_length)
    {
        algorithm::string::copy_string(this->m_fstring, Capacity, rvalue_p.m_fstring, Capacity);
        *(rvalue_p.m_fstring) = _NULL_;
        rvalue_p.m_string_length = 0;
    }


    _FORCE_INLINE_ fixed_sized_string& operator=(const CharT* const string_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));

        this->m_string_length = algorithm::string::string_length<CharT>(string_p);
        FE_ASSERT(this->m_string_length >= Capacity, "${%s@0}: the input string length exceeds the max string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));

        algorithm::string::copy_string(this->m_fstring, Capacity, string_p, this->m_string_length);
        return *this;
    }

    _FORCE_INLINE_ fixed_sized_string& operator=(const fixed_sized_string& other_p) noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        this->m_string_length = other_p.m_string_length;
        algorithm::string::copy_string(this->m_fstring, Capacity, other_p.m_fstring, Capacity);
        return *this;
    }

    _FORCE_INLINE_ fixed_sized_string& operator=(fixed_sized_string&& rvalue_p) noexcept
    {
        if (rvalue_p.m_string_length == 0)
        {
            return *this;
        }

        algorithm::string::copy_string(this->m_fstring, Capacity, rvalue_p.m_fstring, Capacity);
        *(rvalue_p.m_fstring) = _NULL_;
        this->m_string_length = rvalue_p.m_string_length;
        rvalue_p.m_string_length = 0;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ CharT& operator[](index_t index_p) noexcept
    {
        FE_ASSERT(index_p >= this->m_string_length, "${%s@0}: index out of boundary.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        return this->m_fstring[index_p];
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(size_type count_p, CharT value_p) noexcept
    {
        FE_ASSERT(count_p >= Capacity, "${%s@0}: ${%s@1} exceeds fixed sized string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY), TO_STRING(count_p));
        Traits::assign(this->m_fstring, count_p, value_p);
        this->m_string_length = count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const fixed_sized_string& other_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: ${%s@1} cannot be greater than or equal to ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING(input_begin_p), TO_STRING(input_end_p));

        if (other_p.m_string_length == 0)
        {
            return *this;
        }
    
        return this->assign(other_p.m_fstring, input_begin_p, input_end_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const CharT* const string_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        Traits::assign(string_info<CharT>{this->m_fstring, _NULL_, Capacity}, string_p, input_begin_p, input_end_p);
        this->m_string_length = input_end_p - input_begin_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const CharT* const string_p, size_type size_to_assign_p) noexcept
    {
        FE_ASSERT(size_to_assign_p == 0, "${%s@0}: {%s@1} is zero.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(size_to_assign_p));
        FE_ASSERT(string_p == nullptr, "${%s@0}: {%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        FE_ASSERT(size_to_assign_p >= Capacity, "ERROR: size_to_assign_p exceeds fixed sized string capacity.");
       
        Traits::assign(string_info<CharT>{this->m_fstring, _NULL_, Capacity}, string_p, size_to_assign_p);
        this->m_string_length = size_to_assign_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign(const_iterator input_begin_p, const_iterator input_end_p) noexcept
    {
        FE_STATIC_ASSERT((std::is_same<const_iterator::value_type, value_type>::value == false), "static assertion failed: const_iterator::value_type is not equal to value_type.");

        FE_ASSERT(input_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_begin_p));
        FE_ASSERT(input_end_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_end_p));

        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: ${%s@1} must be smaller than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(input_begin_p), TO_STRING(input_end_p));
        FE_ASSERT((input_end_p - input_begin_p) >= Capacity, "${%s@0}: input string range length exceeds fixed sized string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        
        Traits::assign(string_info<CharT>{this->m_fstring, _NULL_, Capacity}, input_begin_p, input_end_p);
        this->m_string_length = input_end_p - input_begin_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string&  assign(std::initializer_list<const CharT>&& initializer_list) noexcept
    {
        FE_ASSERT(initializer_list.size() >= Capacity, "ERROR: initializer_list.size() exceeds the string capacity.");
        FE_ASSERT(initializer_list.size() == 0, "${%s@0}: {%s@1} is an empty initializer_list.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(initializer_list));
       
        algorithm::string::concatenate_characters(this->m_fstring, Capacity, std::move(initializer_list));
        this->m_string_length = initializer_list.size();
        this->m_fstring[this->m_string_length] = _NULL_;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign_range(const_iterator input_iterator_begin_p, algorithm::string::range input_string_range_p) noexcept
    {
        return this->assign(*input_iterator_begin_p, input_string_range_p._begin, input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign_range(const fixed_sized_string& other_p, algorithm::string::range input_string_range_p) noexcept
    {
        return this->assign(other_p, input_string_range_p._begin, input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& assign_range(const CharT* const string_p, algorithm::string::range input_string_range_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: {%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return this->assign(string_p, input_string_range_p._begin, input_string_range_p._end);
    }


    _CONSTEXPR20_ _FORCE_INLINE_ CharT front() const noexcept { return *this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ CharT back() const noexcept { return this->m_fstring[this->m_string_length - 1]; }
    _CONSTEXPR20_ _FORCE_INLINE_ CharT* data() const noexcept { return const_cast<CharT*>(this->m_fstring); }
    _CONSTEXPR20_ _FORCE_INLINE_ const CharT* c_str() const noexcept { return this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ std::basic_string<CharT> std_str() noexcept { return this->m_fstring; }

    _CONSTEXPR20_ _FORCE_INLINE_ iterator begin() const noexcept { return this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ iterator end() const noexcept { return this->m_fstring + this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ reverse_iterator rbegin() const noexcept { return this->m_fstring + (this->m_string_length - 1); }
    _CONSTEXPR20_ _FORCE_INLINE_ reverse_iterator rend() const noexcept { return this->m_fstring - 1; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_iterator cbegin() const noexcept { return this->m_fstring; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_iterator cend() const noexcept { return this->m_fstring + this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept { return this->m_fstring + (this->m_string_length - 1); }
    _CONSTEXPR20_ _FORCE_INLINE_ const_reverse_iterator crend() const noexcept { return this->m_fstring - 1; }

    _NODISCARD_ _CONSTEXPR20_ _FORCE_INLINE_ boolean is_empty() const noexcept { return (this->m_string_length == 0) ? true : false; }

    _CONSTEXPR20_ _FORCE_INLINE_ length_type length() const noexcept { return this->m_string_length; }
    _CONSTEXPR20_ _FORCE_INLINE_ length_type max_length() const noexcept { return Capacity; }
    _CONSTEXPR20_ _FORCE_INLINE_ size_type capacity() const noexcept { return Capacity; }

    _CONSTEXPR20_ _FORCE_INLINE_ void clear() noexcept 
    {
        this->m_fstring[0] = _NULL_;
        this->m_string_length = 0;
    }
   

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, size_type count_p, CharT value_p) noexcept
    {
        FE_ASSERT(this_position_p >= Capacity, "ERROR: position_p cannot be greater than the string capacity.");
        FE_ASSERT(count_p == 0, "ERROR: insert() operation was not successful. size_type count_p was zero.");
        FE_ASSERT((this->m_string_length + count_p) >= Capacity, "ERROR: fixed sized string capacity overflowed.");

        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, count_p, value_p);
        this->m_string_length += count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, const CharT* const string_p) noexcept
    {
        FE_ASSERT(this_position_p >= Capacity, "${%s@0}: position_p cannot be greater than the string capacity.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(string_p == nullptr, "${%s@0}: the input string is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        
        size_type l_inout_string_length = algorithm::string::string_length(string_p);
        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, string_p, l_inout_string_length);
        this->m_string_length += l_inout_string_length;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, const fixed_sized_string& other_p) noexcept
    {
        FE_ASSERT(this_position_p >= Capacity, "${%s@0}: ${%s@1} cannot be greater than the ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY), TO_STRING(this_position_p), TO_STRING(Capacity));
        FE_ASSERT((this->m_string_length + other_p.m_string_length) >= Capacity, "${%s@0}: fixed sized string capacity overflowed.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));

        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, other_p.m_fstring, other_p.m_string_length);
        this->m_string_length += other_p.m_string_length;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, const fixed_sized_string& other_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        FE_ASSERT(this_position_p >= Capacity, "${%s@0}: ${%s@1} cannot be greater than the ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY), TO_STRING(this_position_p), TO_STRING(Capacity));
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING(input_begin_p), TO_STRING(input_end_p));

        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, other_p.m_fstring, input_begin_p, input_end_p);
        this->m_string_length += input_end_p - input_begin_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, const CharT* const string_p, size_type input_begin_p, size_type input_end_p) noexcept
    {
        FE_ASSERT(this_position_p >= Capacity, "${%s@0}: ${%s@1} cannot be greater than the ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY), TO_STRING(this_position_p), TO_STRING(Capacity));
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING(input_begin_p), TO_STRING(input_end_p));
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));

        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, string_p, input_begin_p, input_end_p);
        this->m_string_length += input_end_p - input_begin_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert(size_type this_position_p, std::initializer_list<const CharT>&& initializer_list_p) noexcept
    {
        FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}: initializer_list_p is empty.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE));
        FE_ASSERT((this->m_string_length + initializer_list_p.size()) >= Capacity, "${%s@0}: fixed sized string capacity overflowed.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));

        Traits::insert(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, std::move(initializer_list_p));
        this->m_string_length += initializer_list_p.size();
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert_range(size_type this_index_p, const_iterator input_iterator_begin_p, algorithm::string::range input_string_range_p)  noexcept
    {
        return this->insert(this_index_p, *input_iterator_begin_p, input_string_range_p._begin, input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert_range(size_type this_index_p, const fixed_sized_string& other_p, algorithm::string::range input_string_range_p)  noexcept
    {
        return this->insert(this_index_p, other_p, input_string_range_p._begin, input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& insert_range(size_type this_index_p, const CharT* const cstr_p, algorithm::string::range input_string_range_p)  noexcept
    {
        return this->insert(this_index_p, cstr_p, input_string_range_p._begin, input_string_range_p._end);
    }
    

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& erase(size_type index_p = 0, size_type count_p = 1) noexcept
    {
        FE_ASSERT(Capacity < (index_p + count_p), "${%s@0}: fixed sized string capacity overflowed.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(count_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(count_p));

        Traits::erase(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, index_p, count_p);
        this->m_string_length -= count_p;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ void push_back(const CharT value_p) noexcept
    {
        FE_ASSERT(this->m_string_length >= Capacity, "${%s0}: out of capacity", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        this->m_fstring[this->m_string_length] = value_p;
        ++this->m_string_length;
        this->m_fstring[this->m_string_length] = _NULL_;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ CharT pop_back() noexcept
    {
        FE_ASSERT(this->m_string_length == 0, "${%s0}: Unable to pop an empty fstring", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        const CharT l_return_value = this->back();
        --this->m_string_length;
        this->m_fstring[this->m_string_length] = _NULL_;
        return l_return_value;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(size_type input_count_p, CharT value_p) noexcept
    {
        FE_ASSERT(input_count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(this->max_length() < (this->m_string_length + input_count_p), "${%s0}: cannot append ${%ld@1} character(s) to the fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), &input_count_p);

        Traits::append(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, input_count_p, value_p);
        this->m_string_length += input_count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const fixed_sized_string& other_p) noexcept
    {
        return this->operator+=(other_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const CharT* const string_p) noexcept
    {
        return this->operator+=(string_p);
    }
    

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const fixed_sized_string& other_p, size_type input_position_p, size_type input_count_p = 1) noexcept
    {
        FE_ASSERT(input_count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(this->capacity() < (this->m_string_length + input_count_p), "${%s0}: cannot append another fstring that exceeds the capacity of a caller fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT(other_p.m_string_length < (input_count_p + input_position_p), "${%s0}: out of input fstring index boundary.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

        Traits::append(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, other_p.m_fstring, input_position_p, input_count_p);
        this->m_string_length += input_count_p;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const CharT* string_p, size_type input_position_p, size_type input_count_p = 1) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        FE_ASSERT(input_count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(this->capacity() < (this->m_string_length + input_count_p), "${%s0}: cannot append another fstring that exceeds the capacity of a caller fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

        Traits::append(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, string_p, input_position_p, input_count_p);
        this->m_string_length += input_count_p;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const CharT* string_p, size_type input_count_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        FE_ASSERT(input_count_p == 0, "${%s0}: ${%s1} is zero", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(this->capacity() < (this->m_string_length + input_count_p), "${%s0}: cannot append another fstring that exceeds the capacity of a caller fstring.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

        Traits::append(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, string_p, input_count_p);
        this->m_string_length += input_count_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(const_iterator input_begin_p, const_iterator input_end_p) noexcept
    {
        FE_STATIC_ASSERT((std::is_same<const_iterator::value_type, value_type>::value == false), "static assertion failed: const_iterator::value_type is not equal to value_type.");
        FE_ASSERT(input_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_begin_p));
        FE_ASSERT(input_end_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_end_p));
        FE_ASSERT(input_begin_p >= input_end_p, "${%s@0}: input_position_p must not be greater than input_count_p.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        FE_ASSERT((input_end_p - input_begin_p) + this->m_string_length >= Capacity, "${%s@0}: input string range length exceeds fixed sized string capacity.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
        
        Traits::append(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, input_begin_p, input_end_p);
        this->m_string_length += input_end_p - input_begin_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append(std::initializer_list<const CharT>&& initializer_list_p) noexcept
    {
        FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}: The initializer_list is empty.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE));
        FE_ASSERT(this->max_length() < initializer_list_p.size() + this->m_string_length, "${%s@0}: initializer_list_p is too large to take the contents.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        
        algorithm::string::concatenate_characters(this->data() + this->m_string_length, this->max_length(), std::move(initializer_list_p));
        this->m_string_length += initializer_list_p.size();
        this->m_fstring[this->m_string_length] = _NULL_;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append_range(const_iterator input_iterator_begin_p, algorithm::string::range input_string_range_p) noexcept
    {  
        return this->append(input_iterator_begin_p + input_string_range_p._begin, input_iterator_begin_p + input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append_range(const fixed_sized_string& other_p, algorithm::string::range input_string_range_p) noexcept
    {
        return this->append(other_p, input_string_range_p._begin, input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& append_range(const CharT* const string_p, algorithm::string::range input_string_range_p) noexcept
    {
        return this->append(string_p, input_string_range_p._begin, input_string_range_p._end);
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const fixed_sized_string& other_p) noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        this->m_string_length += other_p.m_string_length;
        algorithm::string::string_concatenation<CharT>(this->m_fstring, Capacity, other_p.m_fstring, other_p.m_string_length);
        this->m_fstring[this->m_string_length] = _NULL_;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const CharT* const string_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));

        length_type l_input_string_length = algorithm::string::string_length<CharT>(string_p);
        algorithm::string::string_concatenation<CharT>(this->m_fstring, Capacity, string_p, l_input_string_length);
        this->m_string_length += l_input_string_length;
        this->m_fstring[this->m_string_length] = _NULL_;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& operator+=(const CharT value_p) noexcept
    {
        algorithm::string::string_concatenation<CharT>(this->m_fstring, Capacity, &value_p, 1);
        this->m_string_length += 1;
        this->m_fstring[this->m_string_length] = _NULL_;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const fixed_sized_string& other_p) const noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return false;
        }

        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, other_p.m_string_length},
            other_p.data(), algorithm::string::range{0, other_p.m_string_length }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const CharT value_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, 1},
            & value_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean starts_with(const CharT* const string_p) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@0} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));

        length_t l_substring_length = algorithm::string::string_length(string_p);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{0, l_substring_length},
            string_p, algorithm::string::range{ 0, l_substring_length }
        );
    }


    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const fixed_sized_string& other_p) const noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return false;
        }

        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{this->m_string_length - other_p.m_string_length, this->m_string_length},
            other_p.data(), algorithm::string::range{ 0, other_p.m_string_length }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const CharT value_p) const noexcept
    {
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{this->m_string_length - 1, this->m_string_length},
            & value_p, algorithm::string::range{ 0, 1 }
        );
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean ends_with(const CharT* const string_p) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        length_t l_substring_length = algorithm::string::string_length(string_p);
        return algorithm::string::compare_ranged_strings(this->m_fstring, algorithm::string::range{this->m_string_length - l_substring_length, this->m_string_length},
            string_p, algorithm::string::range{ 0, l_substring_length }
        );
    }


    _CONSTEXPR20_ _FORCE_INLINE_  boolean contains(const fixed_sized_string& other_p) const noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return false;
        }

        return (algorithm::string::search_first_substring(this->m_fstring, other_p.m_fstring)).has_value();
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean contains(const CharT value_p) const noexcept
    {
        std::optional<algorithm::string::char_info<CharT>> l_target_search_result = algorithm::string::search_first_char(this->m_fstring, value_p);
        return l_target_search_result.has_value();
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean contains(const CharT* const string_p) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return (algorithm::string::search_first_substring(this->m_fstring, string_p)).has_value();
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, const fixed_sized_string& other_p) noexcept
    {
        FE_ASSERT(((this->m_string_length + other_p.m_string_length) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        FE_ASSERT(this_position_p > this->m_string_length, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this_position_p), TO_STRING(this->m_string_length));

        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        
        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, other_p.m_fstring, other_p.m_string_length);
        this->m_string_length = (this->m_string_length + other_p.m_string_length) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, const fixed_sized_string& other_p, size_type other_position_p, size_type other_count_p) noexcept
    {
        FE_ASSERT(((this->m_string_length + other_count_p) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        FE_ASSERT(this_position_p > this->m_string_length, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this_position_p), TO_STRING(this->m_string_length));
        FE_ASSERT(other_position_p > other_p.m_string_length, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(other_position_p), TO_STRING(other_p.m_string_length));

        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        FE_ASSERT(other_count_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(other_count_p));

        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, other_p.m_fstring + other_position_p, other_count_p);
        this->m_string_length = (this->m_string_length + other_p.m_string_length) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, const CharT* const string_p, size_type input_count_p) noexcept
    {
        FE_ASSERT(input_count_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(((this->m_string_length + input_count_p) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        
        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, string_p, input_count_p);
        this->m_string_length = (this->m_string_length + input_count_p) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, const CharT* const string_p) noexcept
    {
        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        
        size_type l_input_length = algorithm::string::string_length(string_p);
        FE_ASSERT(((this->m_string_length + l_input_length) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));

        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, string_p, l_input_length);
        this->m_string_length = (this->m_string_length + l_input_length) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, const CharT value_p, size_type input_count_p) noexcept
    {
        FE_ASSERT(input_count_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_count_p));
        FE_ASSERT(((this->m_string_length + input_count_p) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        
        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, value_p, input_count_p);
        this->m_string_length = (this->m_string_length + input_count_p) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type this_position_p, size_type this_count_to_replace_p, std::initializer_list<const CharT>&& initializer_list_p) noexcept
    {
        size_type l_input_size = initializer_list_p.size();

        FE_ASSERT(((this->m_string_length + l_input_size) - this_count_to_replace_p) > this->max_length(), "${%s@0}: failed to replace.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_CAPACITY));
        FE_ASSERT(this_count_to_replace_p == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_count_to_replace_p));
        FE_ASSERT(l_input_size == 0, "${%s@0}: ${%s@1} is zero.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(initializer_list_p.size()));

        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, this_position_p, this_count_to_replace_p, std::move(initializer_list_p));
        this->m_string_length = (this->m_string_length + l_input_size) - this_count_to_replace_p;
        return *this;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace(size_type first_index_p, size_type last_index_p, const_iterator input_first_p, const_iterator input_last_p) noexcept
    {
        FE_ASSERT(input_first_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_first_p));
        FE_ASSERT(input_last_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(input_last_p));
        FE_ASSERT(input_first_p > input_last_p, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_first_p), TO_STRING(input_last_p));
       
        size_type l_input_size = input_last_p - input_first_p;
        size_type l_this_count_to_replace = last_index_p - first_index_p;

        Traits::replace(string_info<CharT>{this->m_fstring, this->m_string_length, Capacity}, first_index_p, last_index_p, input_first_p, input_last_p);
        this->m_string_length = (this->m_string_length + l_input_size) - l_this_count_to_replace;
        return *this;
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace_with_range(size_type this_index_p, size_type this_count_to_replace_p, const_iterator input_iterator_begin_p, algorithm::string::range input_string_range_p) noexcept
    {
        FE_ASSERT(input_iterator_begin_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(cstr_ptrc_p));
        FE_ASSERT(input_string_range_p._begin >= input_string_range_p._end, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_string_range_p._begin), TO_STRING(input_string_range_p._end));
        FE_ASSERT(this_index_p > this->max_length(), "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_index_p), TO_STRING(this->max_length()));

        return this->replace(this_index_p, this_count_to_replace_p, input_iterator_begin_p + input_string_range_p._begin, input_iterator_begin_p + input_string_range_p._end);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace_with_range(size_type this_index_p, size_type this_count_to_replace_p, const fixed_sized_string& other_p, algorithm::string::range input_string_range_p) noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return *this;
        }

        FE_ASSERT(input_string_range_p._begin >= input_string_range_p._end, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_string_range_p._begin), TO_STRING(input_string_range_p._end));
        FE_ASSERT(this_index_p > this->max_length(), "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_index_p), TO_STRING(this->max_length()));

        return this->replace(this_index_p, this_count_to_replace_p, other_p, input_string_range_p._begin, input_string_range_p._end - input_string_range_p._begin);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string& replace_with_range(size_type this_index_p, size_type this_count_to_replace_p, const CharT* const string_p, algorithm::string::range input_string_range_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        FE_ASSERT(input_string_range_p._begin >= input_string_range_p._end, "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(input_string_range_p._begin), TO_STRING(input_string_range_p._end));
        FE_ASSERT(this_index_p > this->max_length(), "${%s@0}: ${%s@1} must not be greater than ${%s@2}.", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), TO_STRING(this_index_p), TO_STRING(this->max_length()));

        return this->replace(this_index_p, this_count_to_replace_p, string_p + input_string_range_p._begin, input_string_range_p._end - input_string_range_p._begin);
    }


    _CONSTEXPR20_ _FORCE_INLINE_ fixed_sized_string substr(size_type position_p, size_type count_p) const noexcept
    {
        fixed_sized_string l_tmp;
        l_tmp.assign(*this, position_p, position_p + count_p);
        return std::move(l_tmp);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ void copy(CharT* const dest_out_buffer_p, size_t buffer_capacity_p, size_type count_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(dest_out_buffer_p == nullptr, "${%s@0}: dest_out_buffer_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(count_p > this->m_string_length, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(count_p), TO_STRING(this->m_string_length));
        
        algorithm::string::copy_string(dest_out_buffer_p, buffer_capacity_p, this->m_fstring + position_p, count_p);
    }


    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> find(const fixed_sized_string& other_p, size_type position_p = 0) const noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return std::nullopt;
        }

        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: ${%s@1} cannot be greater than ${%s@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(position_p), TO_STRING(this->m_string_length));

        return this->find(other_p.m_fstring, position_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> find(const CharT* const string_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: string_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));
        
        std::optional<algorithm::string::range> l_result = algorithm::string::search_first_substring(this->m_fstring + position_p, string_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ algorithm::string::char_info<CharT> find(const CharT value_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));
        
        algorithm::string::char_info l_result = algorithm::string::search_first_char(this->m_fstring + position_p, value_p);
        l_result->_begin += position_p;
        l_result->_end += position_p;
        return l_result;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> rfind(const fixed_sized_string& other_p, size_type position_p = 0) const noexcept
    {
        if (other_p.m_string_length == 0)
        {
            return std::nullopt;
        }

        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));

        return this->rfind(other_p.m_fstring, position_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::range> rfind(const CharT* const string_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: string_p is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));
        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));

        return algorithm::string::search_last_substring_within_range(this->m_fstring, algorithm::string::range{0, position_p}, string_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::char_info<CharT>> rfind(const CharT value_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));

        return algorithm::string::search_last_char_within_range(this->m_fstring, algorithm::string::range{0, position_p}, value_p);;
    }

    _CONSTEXPR20_ _FORCE_INLINE_ std::optional<algorithm::string::char_count<CharT>> count_chars(const CharT value_p, size_type position_p = 0) const noexcept
    {
        FE_ASSERT(position_p > this->m_string_length, "${%s@0}: position_p cannot be greater than ${%s@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(this->m_string_length));

        return algorithm::string::count_chars(this->m_fstring + position_p, value_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ void swap(fixed_sized_string& in_out_other_p) noexcept
    {
        fixed_sized_string l_temp = std::move(*this);
        *this = std::move(in_out_other_p);
        in_out_other_p = std::move(l_temp);
    }
          
    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator==(const fixed_sized_string& other_p) const noexcept
    {
        return this->operator==(other_p.m_fstring);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator==(const CharT* const string_p) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return algorithm::string::string_comparison(this->m_fstring, string_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator!=(const fixed_sized_string& other_p) const noexcept
    {
        return this->operator!=(other_p.m_fstring);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ boolean operator!=(const CharT* const string_p) const noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return !algorithm::string::string_comparison(this->m_fstring, string_p);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator==(const CharT* const string_p, const fixed_sized_string& fstring_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return algorithm::string::string_comparison(string_p, fstring_p.m_fstring);
    }

    _CONSTEXPR20_ _FORCE_INLINE_ friend boolean operator!=(const CharT* const string_p, const fixed_sized_string& fstring_p) noexcept
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        return !algorithm::string::string_comparison(string_p, fstring_p.m_fstring);
    }
};


template<uint64 Capacity>
using fstring = FE::fixed_sized_string<char, Capacity>;

template<uint64 Capacity>
using ufstring = FE::fixed_sized_string<var::uchar, Capacity>;

template<uint64 Capacity>
using sfstring = FE::fixed_sized_string<var::schar, Capacity>;

template<uint64 Capacity>
using fwstring = FE::fixed_sized_string<var::wchar, Capacity>;

#ifdef _HAS_CXX20_
template<uint64 Capacity>
using fstring8 = FE::fixed_sized_string<var::UTF8, Capacity>;
#endif

template<uint64 Capacity>
using fstring16 = FE::fixed_sized_string<var::UTF16, Capacity>;

template<uint64 Capacity>
using fstring32 = FE::fixed_sized_string<var::UTF32, Capacity>;


END_NAMESPACE;
#pragma warning (pop)
#endif
