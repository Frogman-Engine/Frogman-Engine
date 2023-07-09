#ifndef _FE_CORE_STRING_HXX_
#define _FE_CORE_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "allocator.hxx"
#include "algorithm/string.hxx"
#include "iterator.hxx"


ENABLE_TEST_FOR(basic_string);


BEGIN_NAMESPACE(FE)


template< typename char_type = char, typename max_length_type = var::uint32, class allocator = FE::scalable_aligned_allocator<char_type> >
#if _HAS_CXX20 == 1
    requires character_type<char_type>
#endif
class basic_string final
{
#if _VISUAL_STUDIO_CPP_ == 1
    ALLOW_ITS_FRIEND_TO_TEST(basic_string);
#endif

    static_assert(::std::is_integral<max_length_type>::value, "max_length_type is not a valid numeric type");
    static_assert(sizeof(char_type) <= sizeof(int32), "char_type is not a valid character type");

public:
    typedef char_type value_type;
    typedef allocator allocator_type;
    typedef char_type& reference;
    typedef const char_type& const_reference;
    typedef char_type* pointer;
    typedef const char_type* const_pointer;
    typedef max_length_type length_type;

private:
    char_type* m_string_ptr;
    length_type m_string_length;
    length_type m_total_string_length;

    static char_type s_null;

public:
    _FORCE_INLINE_ basic_string() noexcept : m_string_length(), m_total_string_length() {}

    _FORCE_INLINE_ ~basic_string() noexcept
    {

    }


    _FORCE_INLINE_ basic_string(const char_type* cstr_ptr_p) noexcept : m_string_length(::FE::algorithm::string::string_length<char_type>(cstr_ptr_p))
    {

    }


    _FORCE_INLINE_ basic_string(const basic_string<char_type, max_length_type, allocator>& copy_other_ref_p) noexcept
    {

    }


    _FORCE_INLINE_ basic_string(basic_string<char_type, max_length_type, allocator>&& move_p) noexcept
    {
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(const char_type* cstr_ptr_p) noexcept
    {
        return *this;
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(const basic_string<char_type, max_length_type, allocator>& copy_other_ref_p) noexcept
    {
        return *this;
    }


    _FORCE_INLINE_ basic_string<char_type, max_length_type, allocator>& operator=(basic_string<char_type, max_length_type, allocator>&& move_p) noexcept
    {
        return *this;
    }


    constexpr iterator<contiguous_iterator<char_type>> begin() const noexcept { return this->m_string_ptr; }
    constexpr iterator<contiguous_iterator<char_type>> end() const noexcept { return this->m_string_ptr + this->m_string_length; }

    constexpr iterator<contiguous_iterator<char_type>> rbegin() const noexcept { return this->m_string_ptr + (this->m_string_length - 1); }
    constexpr iterator<contiguous_iterator<char_type>> rend() const noexcept { return this->m_string_ptr - 1; }

    _FORCE_INLINE_ char_type front() const noexcept { return *this->m_string_ptr; }
    _FORCE_INLINE_ char_type back() const noexcept { return this->m_string_ptr[this->m_string_length - 1]; }

    _FORCE_INLINE_ length_type length() const noexcept { return this->m_string_length; }
    _FORCE_INLINE_ length_type capacity() const noexcept { return this->m_total_string_length; }
    constexpr length_type max_length() noexcept { return FE::max_value<length_type>(); }

    _FORCE_INLINE_ void reserve(length_type new_size_p) noexcept
    {
    }

    _FORCE_INLINE_ void shrink_to_fit() noexcept
    {

    }

    _FORCE_INLINE_ void insert(length_type index_p, const char_type* cstr_ptr_p) noexcept
    {

    }

    _FORCE_INLINE_ void insert(length_type index_p, const basic_string<char_type, max_length_type, allocator>& str_ref_p) noexcept
    {

    }

    _FORCE_INLINE_ void try_pop_at(length_type index_p) noexcept
    {

    }

    _FORCE_INLINE_ char_type try_pop_back() noexcept
    {

    }

    _FORCE_INLINE_ void clear() noexcept
    {

    }

    _FORCE_INLINE_ boolean is_empty() const noexcept
    {

    }


    _FORCE_INLINE_ char_type& operator[](length_type index_p) noexcept
    {
        return this->m_string_ptr[index_p];
    }

    _FORCE_INLINE_ length_type operator+=(char_type char_p) noexcept
    {

    }

    _FORCE_INLINE_ length_type operator+=(const char_type* cstr_ptr_p) noexcept
    {

    }

    _FORCE_INLINE_ length_type operator+=(const basic_string<char_type, max_length_type, allocator>& str_cref_p) noexcept
    {

    }

    // It returns a pointer to the data
    constexpr char_type* data() noexcept { return this->m_string_ptr; }

    // It returns a pointer to a traditional c-style read-only string
    constexpr const char_type* c_str() noexcept { return this->m_string_ptr; }

    // It returns a standard string
    constexpr ::std::basic_string<char_type> std_str() noexcept { return this->m_string_ptr; }


    boolean operator==(basic_string<char_type>& other_ref_p) noexcept
    {
        return algorithm::string::string_comparison(this->m_string_ptr, other_ref_p.m_string_ptr);
    }
    boolean operator==(const char_type* const cstr_ptrc_p) noexcept
    {
        return algorithm::string::string_comparison(this->m_string_ptr, cstr_ptrc_p);
    }

    boolean operator!=(basic_string<char_type>& other_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(this->m_string_ptr, other_ref_p.m_string_ptr);
    }
    boolean operator!=(const char_type* const cstr_ptrc_p) noexcept
    {
        return !algorithm::string::string_comparison(this->m_string_ptr, cstr_ptrc_p);
    }

    friend boolean operator==(const char_type* const cstr_ptrc_p, basic_string<char_type>& string_ref_p) noexcept
    {
        return algorithm::string::string_comparison(cstr_ptrc_p, string_ref_p.m_string_ptr);
    }
    friend boolean operator!=(const char_type* const cstr_ptrc_p, basic_string<char_type>& string_ref_p) noexcept
    {
        return !algorithm::string::string_comparison(cstr_ptrc_p, string_ref_p.m_string_ptr);
    }


    _FORCE_INLINE_ static void swap(basic_string<char_type, max_length_type, allocator>& left_ref_p, basic_string<char_type, max_length_type, allocator>& right_ref_p) noexcept
    {
        basic_string<char_type, max_length_type, allocator> l_temp = std::move(left_ref_p);
        left_ref_p = ::std::move(right_ref_p);
        right_ref_p = ::std::move(l_temp);
    }
};

template<typename char_type, typename max_length_type, class allocator>
#if _HAS_CXX20 == 1
    requires character_type<char_type>
#endif
char_type basic_string<char_type, max_length_type, allocator>::s_null = char_type('\0');


using string = basic_string<char, var::uint32>;
using article = basic_string<char, var::uint64>;
using ustring = basic_string<var::uchar, var::uint32>;
using uarticle = basic_string<var::uchar, var::uint64>;
using sstring = basic_string<var::schar, var::uint32>;
using sarticle = basic_string<var::schar, var::uint64>;

using wstring = basic_string<var::wchar, var::uint32>;
using warticle = basic_string<var::wchar, var::uint64>;

#if _HAS_CXX20_ == 1
using string8 = basic_string<var::char8, var::uint32>;
using article8 = basic_string<var::char8, var::uint64>;
#endif

using string16 = basic_string<var::char16, var::uint32>;
using article16 = basic_string<var::char16, var::uint64>;

using string32 = basic_string<var::char32, var::uint32>;
using article32 = basic_string<var::char32, var::uint64>;


END_NAMESPACE
#endif