#ifndef _FE_CORE_STRING_HXX_
#define _FE_CORE_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/allocator.hxx>
#include <FE/core//algorithm/string.hxx>
#include <FE/core/iterator.hxx>
#include <FE/core/smart_pointers/exclusive_ptr.hxx>




BEGIN_NAMESPACE(FE)


template< typename char_type = char, class allocator = FE::scalable_aligned_allocator<char_type>>
class basic_string final
{
    static_assert(FE::is_char<char_type>::value == true, "char_type is not a valid character type");
    static_assert(FE::is_trivially_constructible_and_destructible<char_type>::value == FE::TYPE_TRIVIALITY::_TRIVIAL, "char_type is not a valid character type");
    static_assert(std::is_class<allocator>::value == true, "allocator is not a valid class nor struct type");

public:
    using value_type = char_type;
    using allocator_type = allocator;
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
   
private:
    FE::exclusive_ptr<value_type[], allocator> m_string;
    length_type m_string_length;

public:
    _CONSTEXPR20_ _FORCE_INLINE_ basic_string() noexcept : m_string(), m_string_length() {}
    _CONSTEXPR20_ _FORCE_INLINE_ ~basic_string() noexcept {}
};


using string = basic_string<var::character, var::uint64>;
using ustring = basic_string<var::uchar, var::uint64>;
using sstring = basic_string<var::schar, var::uint64>;

using wstring = basic_string<var::wchar, var::uint64>;

#ifdef _HAS_CXX20_
using string8 = basic_string<var::UTF8, var::uint64>;
#endif

using string16 = basic_string<var::UTF16, var::uint64>;
using string32 = basic_string<var::UTF32, var::uint64>;


END_NAMESPACE
#endif
