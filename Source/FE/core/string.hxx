#ifndef _FE_CORE_STRING_HXX_
#define _FE_CORE_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "allocator.hxx"
#include "algorithm/string.hxx"
#include "iterator.hxx"


BEGIN_NAMESPACE(FE)


template< typename char_type = char, class allocator = FE::scalable_aligned_allocator<char_type>, typename integral_length_type = var::uint32>
#if _HAS_CXX20 == 1
    requires character_type<char_type>
#endif
class basic_string final
{
    static_assert(FE::is_character<char_type>::value == true, "char_type is not a valid character type");
    static_assert(FE::is_trivially_constructible_and_destructible<char_type>::_VALUE_ == FE::OBJECT_TRIVIALITY::_TRIVIAL, "char_type is not a valid character type");
    static_assert(std::is_class<allocator>::value == true, "allocator is not a valid class nor struct type");
    static_assert(std::is_integral<integral_length_type>::value, "length_type is not a valid integral type");

public:
    using value_type = char_type;
    using allocator_type = allocator;
    using size_type = integral_length_type;
    using length_type = integral_length_type;
    using difference_type = var::ptrdiff_t;
    using reference = char_type&;
    using const_reference = const char_type&;
    using pointer = char_type*;
    using const_pointer = const char_type*;
    using iterator = FE::iterator<FE::contiguous_iterator<char_type>>;
    using const_iterator = FE::const_iterator<FE::contiguous_iterator<char_type>>;
    using reverse_iterator = FE::reverse_iterator<FE::contiguous_iterator<char_type>>;
    using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<char_type>>;
   
private:
    value_type* m_string_ptr;
    length_type m_string_length;
    size_type m_capacity;

public:
    _FORCE_INLINE_ constexpr basic_string() noexcept : m_string_ptr(), m_string_length(), m_capacity() {}
    _FORCE_INLINE_ constexpr ~basic_string() noexcept {}

    _FORCE_INLINE_ basic_string(const basic_string& other_cref_p) noexcept : m_string_ptr(), m_string_length(other_cref_p.m_string_length), m_capacity(other_cref_p.m_capacity) {}
    _FORCE_INLINE_ basic_string(basic_string&& rvalue_reference_p) noexcept : m_string_ptr(rvalue_reference_p.m_string_ptr), m_string_length(rvalue_reference_p.m_string_length), m_capacity(rvalue_reference_p.m_capacity) 
    {
        rvalue_reference_p.m_string_ptr = nullptr;
        rvalue_reference_p.m_string_length = 0;
        rvalue_reference_p.m_capacity = 0;
    }
};


using string = basic_string<var::character, var::uint32>;
using article = basic_string<var::character, var::uint64>;
using ustring = basic_string<var::uchar, var::uint32>;
using uarticle = basic_string<var::uchar, var::uint64>;
using sstring = basic_string<var::schar, var::uint32>;
using sarticle = basic_string<var::schar, var::uint64>;

using wstring = basic_string<var::wchar, var::uint32>;
using warticle = basic_string<var::wchar, var::uint64>;

#ifdef _HAS_CXX20_
using string8 = basic_string<var::UTF8, var::uint32>;
using article8 = basic_string<var::UTF8, var::uint64>;
#endif

using string16 = basic_string<var::UTF16, var::uint32>;
using article16 = basic_string<var::UTF16, var::uint64>;

using string32 = basic_string<var::UTF32, var::uint32>;
using article32 = basic_string<var::UTF32, var::uint64>;


END_NAMESPACE
#endif
