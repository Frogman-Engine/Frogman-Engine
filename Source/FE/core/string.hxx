#ifndef _FE_CORE_STRING_HXX_
#define _FE_CORE_STRING_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/allocator.hxx>
#include <FE/core/char_traits.hxx>
#include <FE/core/iterator.hxx>
#include <FE/core/string_view.hxx>
#include <FE/core/smart_pointers/exclusive_ptr.hxx>
#pragma warning(push)
#pragma warning(disable: 26495)




BEGIN_NAMESPACE(FE)


template<typename CharT, boolean IsConst>
class basic_string_view;


template<typename CharT = char, class Allocator = FE::scalable_aligned_allocator<CharT>, class Traits = FE::char_traits<CharT>>
class basic_string final
{
    FE_STATIC_ASSERT(std::is_const<CharT>::value == true, "static assertion failed: the template argument CharT cannot be const.");
    FE_STATIC_ASSERT(FE::is_char<CharT>::value == false, "static assertion failed: the template argument CharT is not a valid character type.");
    FE_STATIC_ASSERT(std::is_class<Allocator>::value == false, "static assertion failed: the template argument Allocator is not a valid class nor struct type.");
    FE_STATIC_ASSERT(std::is_class<Traits>::value == false, "static assertion failed: the template argument traits is not a class or a struct type.");
    FE_STATIC_ASSERT((std::is_same<CharT, Allocator::value_type>::value == false), "static assertion failed: enforcing Allocator's value_type to be equivalent to CharT. The template parameter CharT must be identical to the value_type of the Allocator.");
    FE_STATIC_ASSERT((std::is_same<CharT, Traits::value_type>::value == false), "static assertion failed: enforcing traits' value_type to be equivalent to CharT. The template parameter CharT must be identical to traits::value_type.");
    FE_STATIC_ASSERT(Allocator::is_allocated_from_an_address_aligned_allocator == false, "static assertion failed: addresses allocated from the template argument Allocator must meet the hardware-specific SIMD Alignment requirements, or it must be aligned by power of two.");

public:
    using traits_type = Traits;
    using value_type = CharT;
    using allocator_type = Allocator;
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
    using smart_pointer = FE::exclusive_ptr<value_type[], Allocator>;

private:
    FE::exclusive_ptr<value_type[], Allocator> m_smart_string;
    length_type m_length;

public:
    _CONSTEXPR20_ basic_string() noexcept : m_smart_string(), m_length() {}
    _FORCE_INLINE_ ~basic_string() noexcept {}

    _CONSTEXPR20_ basic_string(size_type count_p, CharT value_p) noexcept : m_smart_string(FE::make_exclusive<value_type[], Allocator>(count_p)), m_length(count_p)
    {
        Traits::assign(this->m_smart_string.get(), count_p, value_p);
    }

    _CONSTEXPR20_ basic_string(const basic_string& other_p, size_type position_p) noexcept : m_smart_string(), m_length()
    {
        FE_ASSERT(position_p >= other_p.m_length, "${%s@0}: ${%s@1} was ${%lu@2}, and ${%s@3} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING(position_p), &position_p, TO_STRING(other_p.m_length), &other_p.m_length);

        if (other_p.m_length == 0)
        {
            return;
        }

        size_type l_input_string_length = other_p.m_length - position_p;
        this->m_smart_string.reset(FE::resize_to{ l_input_string_length });
        Traits::assign(string_info{ this->m_smart_string.get(), _NULL_, l_input_string_length}, other_p.m_smart_string.get() + position_p, l_input_string_length);
        this->m_length = l_input_string_length;
    }

    _CONSTEXPR20_ basic_string(basic_string&& rvalue_p, size_type position_p) noexcept : m_smart_string(), m_length()
    {
        FE_ASSERT(position_p >= rvalue_p.m_length, "${%s@0}: ${%s@1} was ${%lu@2}, and ${%s@3} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING(position_p), &position_p, TO_STRING(rvalue_p.m_length), &rvalue_p.m_length);

        if (rvalue_p.m_length == 0)
        {
            return;
        }

        size_type l_input_string_length = rvalue_p.m_length - position_p;
        std::memmove(rvalue_p.m_smart_string.get() + position_p, rvalue_p.m_smart_string.get(), sizeof(CharT) * l_input_string_length);
        rvalue_p.m_smart_string.get()[l_input_string_length] = _NULL_;
        this->m_smart_string.swap(rvalue_p.m_smart_string);
        this->m_length = l_input_string_length;

        rvalue_p.m_length = 0;
    }

    _CONSTEXPR20_ basic_string(const basic_string& other_p, size_type position_p, size_type count_p) noexcept : m_smart_string(), m_length()
    {
        FE_ASSERT((position_p + count_p) >= other_p.m_length, "${%s@0}: ${%s@1} was ${%lu@2}, and ${%s@3} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING((position_p + count_p)), &FE::buffer<size_type>::set_and_get(position_p + count_p), TO_STRING(other_p.m_length), &other_p.m_length);

        if (other_p.m_length == 0)
        {
            return;
        }

        this->m_smart_string.reset(FE::resize_to{ count_p });
        std::memcpy(this->m_smart_string.get(), other_p.m_smart_string.get() + position_p, sizeof(CharT) * count_p);
        this->m_length = count_p;
        this->m_smart_string.get()[count_p] = _NULL_;
    }

    _CONSTEXPR20_ basic_string(basic_string&& rvalue_p, size_type position_p, size_type count_p) noexcept : m_smart_string(), m_length()
    {
        FE_ASSERT((position_p + count_p) >= rvalue_p.m_length, "${%s@0}: ${%s@1} was ${%lu@2}, and ${%s@3} was ${%lu@4}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_ILLEGAL_POSITION), TO_STRING((position_p + count_p)), &FE::buffer<size_type>::set_and_get(position_p + count_p), TO_STRING(rvalue_p.m_length), &rvalue_p.m_length);

        if (rvalue_p.m_length == 0)
        {
            return;
        }

        std::memmove(rvalue_p.m_smart_string.get(), rvalue_p.m_smart_string.get() + position_p, sizeof(CharT) * count_p);
        this->m_smart_string.swap(rvalue_p.m_smart_string);
        this->m_length = count_p;
        this->m_smart_string.get()[count_p] = _NULL_;
    }

    _CONSTEXPR20_ basic_string(const CharT* const string_p, size_type count_p) noexcept : m_smart_string(FE::make_exclusive<CharT[], Allocator>(size_t{ count_p })), m_length(count_p)
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));
        FE_ASSERT(algorithm::string::string_length(string_p) < count_p, "${%s@0}: ${%s@1} is greater than the length of the input string. The input string length was ${%lu@2}, and ${%s@1} was ${%s@1}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(count_p), &FE::buffer<size_type>::set_and_get(algorithm::string::string_length(string_p)), &count_p);
        
        Traits::assign(string_info<CharT>{this->m_smart_string.get(), _NULL_, this->m_smart_string.size()}, string_p, count_p);
    }
  
    _CONSTEXPR20_ basic_string(const CharT* const string_p) noexcept : m_smart_string(FE::make_exclusive<CharT[], Allocator>(size_t{algorithm::string::string_length(string_p)})), m_length(this->m_smart_string.size())
    {
        FE_ASSERT(string_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(string_p));

        Traits::assign(string_info<CharT>{this->m_smart_string.get(), _NULL_, this->m_smart_string.size()}, string_p, this->m_smart_string.size());
    }
    
    _CONSTEXPR20_ _FORCE_INLINE_ basic_string(const basic_string& other_p) noexcept : m_smart_string(FE::make_exclusive<value_type[], Allocator>(other_p.m_smart_string.size())), m_length(other_p.m_length) { ALIGNED_MEMCPY(this->m_smart_string.get(), other_p.m_smart_string.get(), other_p.m_smart_string.size() * sizeof(value_type)); }
    _CONSTEXPR20_ _FORCE_INLINE_ basic_string(basic_string&& rvalue_p) noexcept : m_smart_string(std::move(rvalue_p.m_smart_string)), m_length(rvalue_p.m_length) { rvalue_p.m_length = 0; }


    _FORCE_INLINE_ CharT& operator[](index_t index_p) const noexcept
    {
        FE_ASSERT(index_p >= this->m_smart_string.size(), "${%s@0}: ${%s@1} was ${%lu@2}, and the string capacity was ${%lu@3}", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(index_p), &index_p, &FE::buffer<size_type>::set_and_get(this->m_smart_string.size()));
        return this->m_smart_string.get()[index_p];
    }

    _FORCE_INLINE_ CharT front() const noexcept { return *(this->m_smart_string.get()); }
    _FORCE_INLINE_ CharT back() const noexcept { return *((this->m_smart_string.get() + this->m_length) - 1); }
    _FORCE_INLINE_ CharT* data() const noexcept { return this->m_smart_string.get(); }
    _FORCE_INLINE_ const CharT* c_str() const noexcept { return this->m_smart_string.get(); }
    _FORCE_INLINE_ std::basic_string<CharT, FE::std_style::scalable_aligned_allocator<CharT>> std_str() const noexcept { return this->m_smart_string.get(); }
    _FORCE_INLINE_ operator basic_string_view<CharT>() const noexcept { return FE::basic_string_view<CharT>(this->m_smart_string); }


    _FORCE_INLINE_ iterator begin() const noexcept { return iterator{this->m_smart_string.get()}; }
    _FORCE_INLINE_ iterator end() const noexcept { return iterator{this->m_smart_string.get() + this->m_length}; }

    _FORCE_INLINE_ const_iterator cbegin() const noexcept { return const_iterator{this->m_smart_string.get()}; }
    _FORCE_INLINE_ const_iterator cend() const noexcept { return const_iterator{this->m_smart_string.get() + this->m_length}; }

    _FORCE_INLINE_ reverse_iterator rbegin() const noexcept { return reverse_iterator{(this->m_smart_string.get() + this->m_length) - 1}; }
    _FORCE_INLINE_ reverse_iterator rend() const noexcept { return reverse_iterator{this->m_smart_string.get() - 1}; }

    _FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{(this->m_smart_string.get() + this->m_length) - 1}; }
    _FORCE_INLINE_ const_reverse_iterator crend() const noexcept { return const_reverse_iterator{this->m_smart_string.get() - 1}; }

    _FORCE_INLINE_ boolean is_empty() const noexcept { return this->m_length == 0; }
    _FORCE_INLINE_ length_type length() const noexcept { return this->m_length; }
    _FORCE_INLINE_ length_type max_length() const noexcept { return FE::_MAX_VALUE_<length_type>; }

    // reserve
    _FORCE_INLINE_ length_type capacity() const noexcept { return this->m_smart_string.size(); }
    // shrink_to_fit

    _FORCE_INLINE_ void clear() noexcept 
    { 
        *(this->m_smart_string) = _NULL_;
        this->m_length = 0;
    }   

    // insert [impl from char_traits]
    // insert_range
    // erase [impl from char_traits]
    // push_back
    // pop_back
    // append [impl from char_traits]
    // append_range
    // operator +=
    // starts_with
    // ends_with
    // contains
    // replace [impl from char_traits]
    // replace_with_range
    // substr
    // copy
    // resize
    _FORCE_INLINE_ void swap(basic_string& other_p) noexcept
    {
        basic_string l_tmp_string = std::move(other_p);
        other_p = std::move(*this);
        *this = std::move(l_tmp_string);
    }
    // find [impl from char_traits]
    // rfind [impl from char_traits]
    // count_chars [impl from char_traits]

    template<typename CharT>
    _FORCE_INLINE_ boolean operator==(basic_string_view<CharT>& other_p) const noexcept
    {
        return algorithm::string::string_comparison(this->m_smart_string.get(), other_p.begin().operator->());
    }
    _FORCE_INLINE_ boolean operator==(const basic_string& other_p) const noexcept
    {
        return algorithm::string::string_comparison(this->m_smart_string.get(), other_p.m_smart_string.get());
    }
    _FORCE_INLINE_ boolean operator==(const CharT* const string_p) const noexcept
    {
        return algorithm::string::string_comparison(this->m_smart_string.get(), string_p);
    }
    _FORCE_INLINE_ friend boolean operator==(const CharT* const string_p, const basic_string& other_p) const noexcept
    {
        return algorithm::string::string_comparison(string_p, other_p.m_smart_string.get());
    }

    template<typename CharT>
    _FORCE_INLINE_ boolean operator!=(basic_string_view<CharT>& other_p) const noexcept
    {
        return !algorithm::string::string_comparison(this->m_smart_string.get(), other_p.begin().operator->());
    }
    _FORCE_INLINE_ boolean operator!=(const basic_string& other_p) const noexcept
    {
        return !algorithm::string::string_comparison(this->m_smart_string.get(), other_p.m_smart_string.get());
    }
    _FORCE_INLINE_ boolean operator!=(const CharT* const string_p) const noexcept
    {
        return !algorithm::string::string_comparison(this->m_smart_string.get(), string_p);
    }
    _FORCE_INLINE_ friend boolean operator!=(const CharT* const string_p, const basic_string& other_p) const noexcept
    {
        return !algorithm::string::string_comparison(string_p, other_p.m_smart_string.get());
    }
};


using string = basic_string<var::character>;
using ustring = basic_string<var::uchar>;
using sstring = basic_string<var::schar>;
using wstring = basic_string<var::wchar>;

#ifdef _HAS_CXX20_
using string8 = basic_string<var::UTF8>;
#endif

using string16 = basic_string<var::UTF16>;
using string32 = basic_string <var::UTF32>;


END_NAMESPACE
#pragma warning(pop)
#endif
