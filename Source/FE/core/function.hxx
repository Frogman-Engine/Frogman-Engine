#ifndef _FE_CORE_FUNCTION_HXX_
#define _FE_CORE_FUNCTION_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "algorithm/string.hxx"
#define PASS_RETURN_BUFFER(return_buffer) &return_buffer




BEGIN_NAMESPACE(FE)


template<typename T>
class buffer final
{
    thread_local static T tl_s_rvalue_buffer;
    
public:
    using value_type = T;
    using reference = T&;
    using rvalue_reference = T&&;

    static void set(rvalue_reference rvalue_p) noexcept
    {
        tl_s_rvalue_buffer = std::move(rvalue_p);
    }

    static reference set_and_get(rvalue_reference rvalue_p) noexcept
    {
        tl_s_rvalue_buffer = std::move(rvalue_p);
        return tl_s_rvalue_buffer;
    }

    static reference get() noexcept
    {
        return tl_s_rvalue_buffer;
    }
};

template<typename T>
thread_local T buffer<T>::tl_s_rvalue_buffer;


template<typename F>
class function final
{
public:
    function() noexcept = delete;
    ~function() noexcept = delete;
};

template<typename R, typename ...arguments>
class function<R(arguments...)> final
{
    R(*m_function_ptr)(arguments...);

public:
    using function_type = decltype(m_function_ptr);
    using return_type = R;

    constexpr function() noexcept : m_function_ptr() {}
    constexpr ~function() noexcept {}

    constexpr function(function_type function_ptr_p) noexcept : m_function_ptr(function_ptr_p) {}
    constexpr function(const function& other_cref_p) noexcept : m_function_ptr(other_cref_p.m_function_ptr) {}
    constexpr function(function&& rvalue_p) noexcept : m_function_ptr(rvalue_p.m_function_ptr) { rvalue_p.m_function_ptr = nullptr; }

    _FORCE_INLINE_ R operator()(arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_function_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_ptr));
        return this->m_function_ptr(arguments_ref_p...);
    }

    constexpr function& operator=(function_type function_ptr_p) noexcept
    {
        this->m_function_ptr = function_ptr_p;
        return *this;
    }

    constexpr function& operator=(const function& other_cref_p) noexcept
    {
        this->m_function_ptr = other_cref_p.m_function_ptr;
        return *this;
    }

    constexpr function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_ptr = rvalue_p.m_function_ptr;
        rvalue_p.m_function_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_function_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const function& other_cref_p) noexcept
    {
        return (this->m_function_ptr == other_cref_p.m_function_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const function& other_cref_p) noexcept
    {
        return (this->m_function_ptr != other_cref_p.m_function_ptr) ? true : false;
    }
};

template<typename ...arguments>
class function<void(arguments...)> final
{
    void(*m_function_ptr)(arguments...);

public:
    using function_type = decltype(m_function_ptr);
    using return_type = void;

    constexpr function() noexcept : m_function_ptr() {}
    constexpr ~function() noexcept {}

    constexpr function(function_type function_ptr_p) noexcept : m_function_ptr(function_ptr_p) {}
    constexpr function(const function& other_cref_p) noexcept : m_function_ptr(other_cref_p.m_function_ptr) {}
    constexpr function(function&& rvalue_p) noexcept : m_function_ptr(rvalue_p.m_function_ptr) { rvalue_p.m_function_ptr = nullptr; }

    _FORCE_INLINE_ void operator()(arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_function_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_ptr));
        this->m_function_ptr(arguments_ref_p...);
    }

    constexpr function& operator=(function_type function_ptr_p) noexcept
    {
        this->m_function_ptr = function_ptr_p;
        return *this;
    }

    constexpr function& operator=(const function& other_cref_p) noexcept
    {
        this->m_function_ptr = other_cref_p.m_function_ptr;
        return *this;
    }

    constexpr function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_ptr = rvalue_p.m_function_ptr;
        rvalue_p.m_function_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_function_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const function& other_cref_p) noexcept
    {
        return (this->m_function_ptr == other_cref_p.m_function_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const function& other_cref_p) noexcept
    {
        return (this->m_function_ptr != other_cref_p.m_function_ptr) ? true : false;
    }
};




template<class C, typename F>
class method final
{
public:
    method() noexcept = delete;
    ~method() noexcept = delete;
};

template<class C, typename R, typename ...arguments>
class method<C, R(arguments...) const> final
{
    R(C::* m_method_ptr)(arguments...) const;

public:
    using method_type = decltype(m_method_ptr);
    using return_type = R;
    using class_type = C;

    constexpr method() noexcept : m_method_ptr() {}
    constexpr ~method() noexcept {}

    constexpr method(method_type method_ptr_p) noexcept : m_method_ptr(method_ptr_p) {}
    constexpr method(const method& other_cref_p) noexcept : m_method_ptr(other_cref_p.m_method_ptr) {}
    constexpr method(method&& rvalue_p) noexcept : m_method_ptr(rvalue_p.m_method_ptr) { rvalue_p.m_method_ptr = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_ref_p, arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_method_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_ptr));
        return (instance_ref_p.*this->m_method_ptr)(arguments_ref_p...);
    }

    constexpr method& operator=(method_type method_ptr_p) noexcept
    {
        this->m_method_ptr = method_ptr_p;
        return *this;
    }

    constexpr method& operator=(const method& other_cref_p) noexcept
    {
        this->m_method_ptr = other_cref_p.m_method_ptr;
        return *this;
    }

    constexpr method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_ptr = rvalue_p.m_method_ptr;
        rvalue_p.m_method_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_method_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr == other_cref_p.m_method_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr != other_cref_p.m_method_ptr) ? true : false;
    }
};

template<class C, typename ...arguments>
class method<C, void(arguments...) const> final
{
    void(C::* m_method_ptr)(arguments...) const;

public:
    using method_type = decltype(m_method_ptr);
    using return_type = void;
    using class_type = C;

    constexpr method() noexcept : m_method_ptr() {}
    constexpr ~method() noexcept {}

    constexpr method(method_type method_ptr_p) noexcept : m_method_ptr(method_ptr_p) {}
    constexpr method(const method& other_cref_p) noexcept : m_method_ptr(other_cref_p.m_method_ptr) {}
    constexpr method(method&& rvalue_p) noexcept : m_method_ptr(rvalue_p.m_method_ptr) { rvalue_p.m_method_ptr = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_ref_p, arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_method_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_ptr));
        (instance_ref_p.*this->m_method_ptr)(arguments_ref_p...);
    }

    constexpr method& operator=(method_type method_ptr_p) noexcept
    {
        this->m_method_ptr = method_ptr_p;
        return *this;
    }

    constexpr method& operator=(const method& other_cref_p) noexcept
    {
        this->m_method_ptr = other_cref_p.m_method_ptr;
        return *this;
    }

    constexpr method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_ptr = rvalue_p.m_method_ptr;
        rvalue_p.m_method_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_method_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr == other_cref_p.m_method_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr != other_cref_p.m_method_ptr) ? true : false;
    }
};

template<class C, typename R, typename ...arguments>
class method<C, R(arguments...)> final
{
    R(C::* m_method_ptr)(arguments...);

public:
    using method_type = decltype(m_method_ptr);
    using return_type = R;
    using class_type = C;

    constexpr method() noexcept : m_method_ptr() {}
    constexpr ~method() noexcept {}

    constexpr method(method_type method_ptr_p) noexcept : m_method_ptr(method_ptr_p) {}
    constexpr method(const method& other_cref_p) noexcept : m_method_ptr(other_cref_p.m_method_ptr) {}
    constexpr method(method&& rvalue_p) noexcept : m_method_ptr(rvalue_p.m_method_ptr) { rvalue_p.m_method_ptr = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_ref_p, arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_method_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_ptr));
        return (instance_ref_p.*this->m_method_ptr)(arguments_ref_p...);
    }

    constexpr method& operator=(method_type method_ptr_p) noexcept
    {
        this->m_method_ptr = method_ptr_p;
        return *this;
    }

    constexpr method& operator=(const method& other_cref_p) noexcept
    {
        this->m_method_ptr = other_cref_p.m_method_ptr;
        return *this;
    }

    constexpr method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_ptr = rvalue_p.m_method_ptr;
        rvalue_p.m_method_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_method_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr == other_cref_p.m_method_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr != other_cref_p.m_method_ptr) ? true : false;
    }
};

template<class C, typename ...arguments>
class method<C, void(arguments...)> final
{
    void(C::* m_method_ptr)(arguments...);

public:
    using method_type = decltype(m_method_ptr);
    using return_type = void;
    using class_type = C;

    constexpr method() noexcept : m_method_ptr() {}
    constexpr ~method() noexcept {}

    constexpr method(method_type method_ptr_p) noexcept : m_method_ptr(method_ptr_p) {}
    constexpr method(const method& other_cref_p) noexcept : m_method_ptr(other_cref_p.m_method_ptr) {}
    constexpr method(method&& rvalue_p) noexcept : m_method_ptr(rvalue_p.m_method_ptr) { rvalue_p.m_method_ptr = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_ref_p, arguments& ...arguments_ref_p) noexcept
    {
        FE_ASSERT(this->m_method_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_ptr));
        (instance_ref_p.*this->m_method_ptr)(arguments_ref_p...);
    }

    constexpr method& operator=(method_type method_ptr_p) noexcept
    {
        this->m_method_ptr = method_ptr_p;
        return *this;
    }

    constexpr method& operator=(const method& other_cref_p) noexcept
    {
        this->m_method_ptr = other_cref_p.m_method_ptr;
        return *this;
    }

    constexpr method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_ptr = rvalue_p.m_method_ptr;
        rvalue_p.m_method_ptr = nullptr;
        return *this;
    }

    constexpr operator bool() noexcept
    {
        return (this->m_method_ptr == nullptr) ? false : true;
    }

    constexpr var::boolean operator==(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr == other_cref_p.m_method_ptr) ? true : false;
    }

    constexpr var::boolean operator!=(const method& other_cref_p) noexcept
    {
        return (this->m_method_ptr != other_cref_p.m_method_ptr) ? true : false;
    }
};




enum struct ARGUMENTS_COUNT
{
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 =3,
    _4 = 4,
    _5 = 5,
    _6 = 6,
    _7 = 7,
    _8 = 8,
    _9 = 9,
    _10 = 10
};


template<typename first, typename second, typename third, typename fourth, typename fifth, typename sixth, typename seventh, typename eighth, typename ninth, typename tenth>
struct arguments;

template<>
struct arguments<void, void, void, void, void, void, void, void, void, void> 
{
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_0;
};

template<typename first>
struct arguments<first, void, void, void, void, void, void, void, void, void>
{
    using first_type = first;

    first _first;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_1;
    
    _FORCE_INLINE_ arguments() noexcept = default;
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : _first(arguments_ref_p._first) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : _first(std::move(arguments_p._first)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        this->_first = arguments_ref_p._first;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        this->_first = std::move(arguments_p._first);
        return *this;
    }
};

template<typename first, typename second>
struct arguments<first, second, void, void, void, void, void, void, void, void> : public arguments<first, void, void, void, void, void, void, void, void, void>
{
    using base_type = arguments<first, void, void, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = second;

    second_type _second;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_2;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _second() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _second(arguments_ref_p._second) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _second(std::move(arguments_p._second)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_second = arguments_ref_p._second;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_second = std::move(arguments_p._second);
        return *this;
    }
};

template<typename first, typename second, typename third>
struct arguments<first, second, third, void, void, void, void, void, void, void> : public arguments<first, second, void, void, void, void, void, void, void, void>
{
    using base_type = arguments<first, second, void, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second;
    using third_type = third;

    third_type _third;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_3;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _third() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _third(arguments_ref_p._third) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _third(std::move(arguments_p._third)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_third = arguments_ref_p._third;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_third = std::move(arguments_p._third);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth>
struct arguments<first, second, third, fourth, void, void, void, void, void, void> : public arguments<first, second, third, void, void, void, void, void, void, void>
{
    using base_type = arguments<first, second, third, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = fourth;

    fourth_type _fourth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_4;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _fourth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _fourth(arguments_ref_p._fourth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _fourth(std::move(arguments_p._fourth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_fourth = arguments_ref_p._fourth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fourth = std::move(arguments_p._fourth);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth, typename fifth>
struct arguments<first, second, third, fourth, fifth, void, void, void, void, void> : public arguments<first, second, third, fourth, void, void, void, void, void, void>
{
    using base_type = arguments<first, second, third, fourth, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = fifth;

    fifth_type _fifth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_5;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _fifth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _fifth(arguments_ref_p._fifth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _fifth(std::move(arguments_p._fifth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_fifth = arguments_ref_p._fifth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fifth = std::move(arguments_p._fifth);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth, typename fifth, typename sixth>
struct arguments<first, second, third, fourth, fifth, sixth, void, void, void, void> : public arguments<first, second, third, fourth, fifth, void, void, void, void, void>
{
    using base_type = arguments<first, second, third, fourth, fifth, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = sixth;

    sixth_type _sixth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_6;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _sixth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _sixth(arguments_ref_p._sixth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _sixth(std::move(arguments_p._sixth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_sixth = arguments_ref_p._sixth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_sixth = std::move(arguments_p._sixth);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth, typename fifth, typename sixth, typename seventh>
struct arguments<first, second, third, fourth, fifth, sixth, seventh, void, void, void> : public arguments<first, second, third, fourth, fifth, sixth, void, void, void, void>
{
    using base_type = arguments<first, second, third, fourth, fifth, sixth, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = seventh;

    seventh_type _seventh;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_7;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _seventh() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _seventh(arguments_ref_p._seventh) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _seventh(std::move(arguments_p._seventh)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_seventh = arguments_ref_p._seventh;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_seventh = std::move(arguments_p._seventh);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth, typename fifth, typename sixth, typename seventh, typename eighth>
struct arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, void, void> : public arguments<first, second, third, fourth, fifth, sixth, seventh, void, void, void>
{
    using base_type = arguments<first, second, third, fourth, fifth, sixth, seventh, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = eighth;

    eighth_type _eighth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_8;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _eighth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _eighth(arguments_ref_p._eighth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _eighth(std::move(arguments_p._eighth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_eighth = arguments_ref_p._eighth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_eighth = std::move(arguments_p._eighth);
        return *this;
    }
};

template<typename first, typename second, typename third, typename fourth, typename fifth, typename sixth, typename seventh, typename eighth, typename ninth>
struct arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, void> : public  arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, void, void>
{
    using base_type = arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = typename base_type::eighth_type;
    using ninth_type = ninth;

    ninth_type _ninth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_9;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _ninth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _ninth(arguments_ref_p._ninth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _ninth(std::move(arguments_p._ninth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_ninth = arguments_ref_p._ninth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_ninth = std::move(arguments_p._ninth);
        return *this;
    }
};


template<typename first = void, typename second = void, typename third = void, typename fourth = void, typename fifth = void, typename sixth = void, typename seventh = void, typename eighth = void, typename ninth = void, typename tenth = void>
struct arguments : public arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, void>
{
    using base_type = arguments<first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = typename base_type::eighth_type;
    using ninth_type = typename base_type::ninth_type;
    using tenth_type = tenth;

    tenth_type _tenth;
    static constexpr inline ARGUMENTS_COUNT arguments_count = ARGUMENTS_COUNT::_10;

    _FORCE_INLINE_ arguments() noexcept : base_type(), _tenth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ arguments(arguments& arguments_ref_p) noexcept : base_type(arguments_ref_p), _tenth(arguments_ref_p._tenth) {};
    _FORCE_INLINE_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _tenth(std::move(arguments_p._tenth)) {};

    _FORCE_INLINE_ arguments& operator=(arguments& arguments_ref_p) noexcept
    {
        base_type::operator=(arguments_ref_p);
        this->_tenth = arguments_ref_p._tenth;
        return *this;
    }

    _FORCE_INLINE_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_tenth = std::move(arguments_p._tenth);
        return *this;
    }
};




struct task_base
{
    _NODISCARD_ virtual void operator()(_MAYBE_UNUSED_ void* out_return_buffer_ptr_p = nullptr) noexcept = 0;
};


template<class C, typename task_impl, typename R = void, typename ...arguments>
struct cpp_style_task_base : public task_base
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using class_type = C;
    using task_impl_type = task_impl;
    using task_type = FE::method<C, task_impl_type>;

    FE::arguments<arguments...> _arguments;
    task_type _method;
    C* _instance_ptr;

protected:
    _FORCE_INLINE_ cpp_style_task_base() noexcept = default;
    _FORCE_INLINE_ ~cpp_style_task_base() noexcept = default;

    _FORCE_INLINE_ cpp_style_task_base(task_type task_p) noexcept : _method(task_p) {}
    _FORCE_INLINE_ cpp_style_task_base(cpp_style_task_base& cpp_style_task_base_ref_p) noexcept : _arguments(cpp_style_task_base_ref_p._arguments), _method(cpp_style_task_base_ref_p._method) {}
    _FORCE_INLINE_ cpp_style_task_base(cpp_style_task_base&& rvalue_p) noexcept : _arguments(std::move(rvalue_p._arguments)), _method(rvalue_p._method) { rvalue_p._method = nullptr; }

    _FORCE_INLINE_ cpp_style_task_base& operator=(task_type task_p) noexcept
    {
        this->_method = task_p;
        return *this;
    }

    _FORCE_INLINE_ cpp_style_task_base& operator=(cpp_style_task_base& cpp_style_task_base_ref_p) noexcept
    {
        this->_arguments = cpp_style_task_base_ref_p._arguments;
        this->_method = cpp_style_task_base_ref_p._method;
        this->_instance_ptr = cpp_style_task_base_ref_p._instance_ptr;
        return *this;
    }

    _FORCE_INLINE_ cpp_style_task_base& operator=(cpp_style_task_base&& rvalue_p) noexcept
    {
        this->_arguments = std::move(rvalue_p._arguments);

        this->_method = rvalue_p._method;
        rvalue_p._method = nullptr;

        this->_instance_ptr = rvalue_p._instance_ptr;
        rvalue_p._instance_ptr = nullptr;
        return *this;
    }

public:
    _NODISCARD_ virtual void operator()(_MAYBE_UNUSED_ void* out_return_buffer_ptr_p) noexcept override
    {
        FE_ASSERT(out_return_buffer_ptr_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(out_return_buffer_ptr_p));
        FE_ASSERT(this->_instance_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->_instance_ptr));

        if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_0)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_1)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_2)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_3)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_4)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_5)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_6)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_7)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_8)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_9)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_10)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth, this->_arguments._tenth);
            return;
        }
    }
};

template<class C, typename task_impl, typename ...arguments>
struct cpp_style_task_base<C, task_impl, void, arguments...> : public task_base 
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using class_type = C;
    using task_impl_type = task_impl;
    using task_type = FE::method<C, task_impl_type>;

    FE::arguments<arguments...> _arguments;
    task_type _method;
    C* _instance_ptr;

protected:
    _FORCE_INLINE_ cpp_style_task_base() noexcept = default;
    _FORCE_INLINE_ ~cpp_style_task_base() noexcept = default;

    _FORCE_INLINE_ cpp_style_task_base(task_type task_p) noexcept : _method(task_p) {}
    _FORCE_INLINE_ cpp_style_task_base(cpp_style_task_base& cpp_style_task_base_ref_p) noexcept : _arguments(cpp_style_task_base_ref_p._arguments), _method(cpp_style_task_base_ref_p._method) {}
    _FORCE_INLINE_ cpp_style_task_base(cpp_style_task_base&& rvalue_p) noexcept : _arguments(std::move(rvalue_p._arguments)), _method(rvalue_p._method) { rvalue_p._method = nullptr; }

    _FORCE_INLINE_ cpp_style_task_base& operator=(task_type task_p) noexcept
    {
        this->_method = task_p;
        return *this;
    }

    _FORCE_INLINE_ cpp_style_task_base& operator=(cpp_style_task_base& cpp_style_task_base_ref_p) noexcept
    {
        this->_arguments = cpp_style_task_base_ref_p._arguments;
        this->_method = cpp_style_task_base_ref_p._method;
        this->_instance_ptr = cpp_style_task_base_ref_p._instance_ptr;
        return *this;
    }

    _FORCE_INLINE_ cpp_style_task_base& operator=(cpp_style_task_base&& rvalue_p) noexcept
    {
        this->_arguments = std::move(rvalue_p._arguments);

        this->_method = rvalue_p._method;
        rvalue_p._method = nullptr; 

        this->_instance_ptr = rvalue_p._instance_ptr;
        rvalue_p._instance_ptr = nullptr;
        return *this;
    }

public:
    _NODISCARD_ virtual void operator()(_MAYBE_UNUSED_ void* out_return_buffer_ptr_p = nullptr) noexcept override
    {
        FE_ASSERT(this->_instance_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->_instance_ptr));

        if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_0)
        {
            this->_method(*this->_instance_ptr);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_1)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_2)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_3)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_4)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_5)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_6)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_7)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_8)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_9)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_10)
        {
            this->_method(*this->_instance_ptr, this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth, this->_arguments._tenth);
            return;
        }
    }
};




template<class C, typename R = void, typename ...arguments>
struct cpp_style_task 
{
    cpp_style_task() noexcept = delete;
    ~cpp_style_task() noexcept = delete;
};

template<class C, typename R, typename ...arguments>
struct cpp_style_task<C, R(arguments...)> : public cpp_style_task_base<C, R(arguments...), R, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");
   
    using base_type = cpp_style_task_base<C, R(arguments...), arguments...>;
};

template<class C, typename ...arguments>
struct cpp_style_task<C, void(arguments...)> : public cpp_style_task_base<C, void(arguments...), void, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, void(arguments...), arguments...>;
};

template<class C, typename R, typename ...arguments>
struct cpp_style_task<C, R(arguments&...)> : public cpp_style_task_base<C, R(arguments&...), R, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, R(arguments&...), arguments...>;

};

template<class C, typename ...arguments>
struct cpp_style_task<C, void(arguments&...)> : public cpp_style_task_base<C, void(arguments&...), void, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, void(arguments&...), arguments...>;
};


template<class C, typename R, typename ...arguments>
struct cpp_style_task<C, R(arguments...) const> : public cpp_style_task_base<C, R(arguments...) const, R, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, R(arguments...) const, arguments...>;
};

template<class C, typename ...arguments>
struct cpp_style_task<C, void(arguments...) const> : public cpp_style_task_base<C, void(arguments...) const, void, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, void(arguments...) const, arguments...>;
};

template<class C, typename R, typename ...arguments>
struct cpp_style_task<C, R(arguments&...) const> : public cpp_style_task_base<C, R(arguments&...) const, R, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, R(arguments&...) const, arguments...>;

};

template<class C, typename ...arguments>
struct cpp_style_task<C, void(arguments&...) const> : public cpp_style_task_base<C, void(arguments&...) const, void, arguments...>
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

    using base_type = cpp_style_task_base<C, void(arguments&...) const, arguments...>;
};








template<typename task_impl, typename R = void, typename ...arguments>
struct c_style_task_base : public task_base
{
    using task_impl_type = task_impl;
    using task_type = FE::function<task_impl_type>;

    FE::arguments<arguments...> _arguments;
    task_type _function;

protected:
    _FORCE_INLINE_ c_style_task_base() noexcept = default;
    _FORCE_INLINE_ ~c_style_task_base() noexcept = default;

    _FORCE_INLINE_ c_style_task_base(task_type task_p) noexcept : _function(task_p) {}
    _FORCE_INLINE_ c_style_task_base(c_style_task_base& c_style_task_base_ref_p) noexcept : _arguments(c_style_task_base_ref_p._arguments), _function(c_style_task_base_ref_p._function) {}
    _FORCE_INLINE_ c_style_task_base(c_style_task_base&& rvalue_p) noexcept : _arguments(std::move(rvalue_p._arguments)), _function(rvalue_p._function) { rvalue_p._function = nullptr; }

    _FORCE_INLINE_ c_style_task_base& operator=(task_type task_p) noexcept
    {
        this->_function = task_p;
        return *this;
    }

    _FORCE_INLINE_ c_style_task_base& operator=(c_style_task_base& c_style_task_base_ref_p) noexcept
    {
        this->_arguments = c_style_task_base_ref_p._arguments;
        this->_function = c_style_task_base_ref_p._function;
        return *this;
    }

    _FORCE_INLINE_ c_style_task_base& operator=(c_style_task_base&& rvalue_p) noexcept
    {
        this->_arguments = std::move(rvalue_p._arguments);

        this->_function = rvalue_p._function;
        rvalue_p._function = nullptr;
        return *this;
    }

public:
    _NODISCARD_ virtual void operator()(_MAYBE_UNUSED_ void* out_return_buffer_ptr_p) noexcept override
    {
        FE_ASSERT(out_return_buffer_ptr_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(out_return_buffer_ptr_p));

        if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_0)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function();
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_1)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_2)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_3)
        {
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_4)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_5)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_6)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_7)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_8)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_9)                                        
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth);
            return;                                                                                                        
        }                                                                                                                  
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_10)                                       
        {                                                                                                                  
            *static_cast<R*>(out_return_buffer_ptr_p) = this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth, this->_arguments._tenth);
            return;
        }
    }
};

template<typename task_impl, typename ...arguments>
struct c_style_task_base<task_impl, void, arguments...> : public task_base
{
    using task_impl_type = task_impl;
    using task_type = FE::function<task_impl_type>;

    FE::arguments<arguments...> _arguments;
    task_type _function;

protected:
    _FORCE_INLINE_ c_style_task_base() noexcept = default;
    _FORCE_INLINE_ ~c_style_task_base() noexcept = default;

    _FORCE_INLINE_ c_style_task_base(task_type task_p) noexcept : _function(task_p) {}
    _FORCE_INLINE_ c_style_task_base(c_style_task_base& c_style_task_base_ref_p) noexcept : _arguments(c_style_task_base_ref_p._arguments), _function(c_style_task_base_ref_p._function) {}
    _FORCE_INLINE_ c_style_task_base(c_style_task_base&& rvalue_p) noexcept : _arguments(std::move(rvalue_p._arguments)), _function(rvalue_p._function) { rvalue_p._function = nullptr; }

    _FORCE_INLINE_ c_style_task_base& operator=(task_type task_p) noexcept
    {
        this->_function = task_p;
        return *this;
    }

    _FORCE_INLINE_ c_style_task_base& operator=(c_style_task_base& c_style_task_base_ref_p) noexcept
    {
        this->_arguments = c_style_task_base_ref_p._arguments;
        this->_function = c_style_task_base_ref_p._function;
        return *this;
    }

    _FORCE_INLINE_ c_style_task_base& operator=(c_style_task_base&& rvalue_p) noexcept
    {
        this->_arguments = std::move(rvalue_p._arguments);

        this->_function = rvalue_p._function;
        rvalue_p._function = nullptr;
        return *this;
    }

public:
    _NODISCARD_ virtual void operator()(_MAYBE_UNUSED_ void* out_return_buffer_ptr_p = nullptr) noexcept override
    {
        if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_0)
        {
            this->_function();
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_1)
        {
            this->_function(this->_arguments._first);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_2)
        {
            this->_function(this->_arguments._first, this->_arguments._second);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_3)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_4)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_5)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_6)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_7)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_8)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_9)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth);
            return;
        }
        else if constexpr (this->_arguments.arguments_count == ARGUMENTS_COUNT::_10)
        {
            this->_function(this->_arguments._first, this->_arguments._second, this->_arguments._third, this->_arguments._fourth, this->_arguments._fifth, this->_arguments._sixth, this->_arguments._seventh, this->_arguments._eighth, this->_arguments._ninth, this->_arguments._tenth);
            return;
        }
    }
};




template<typename R = void, typename ...arguments>
struct c_style_task 
{
    c_style_task() noexcept = delete;
    ~c_style_task() noexcept = delete;
};

template<typename R, typename ...arguments>
struct c_style_task<R(arguments...)> : public c_style_task_base<R(arguments...), R, arguments...>
{
    using base_type = c_style_task_base<R(arguments...), arguments...>;
};

template<typename ...arguments>
struct c_style_task<void(arguments...)> : public c_style_task_base<void(arguments...), void, arguments...>
{
    using base_type = c_style_task_base<void(arguments...), arguments...>;
};

template<typename R, typename ...arguments>
struct c_style_task<R(arguments&...)> : public c_style_task_base<R(arguments&...), R, arguments...>
{
    using base_type = c_style_task_base<R(arguments&...), arguments...>;
};

template<typename ...arguments>
struct c_style_task<void(arguments&...)> : public c_style_task_base<void(arguments&...), void, arguments...>
{
    using base_type = c_style_task_base<void(arguments&...), arguments...>;
};


template<typename R, typename ...arguments>
struct c_style_task<R(arguments...) const> : public c_style_task_base<R(arguments...) const, R, arguments...>
{
    using base_type = c_style_task_base<R(arguments...) const, arguments...>;
};

template<typename ...arguments>
struct c_style_task<void(arguments...) const> : public c_style_task_base<void(arguments...) const, void, arguments...>
{
    using base_type = c_style_task_base<void(arguments...) const, arguments...>;
};

template<typename R, typename ...arguments>
struct c_style_task<R(arguments&...) const> : public c_style_task_base<R(arguments&...) const, R, arguments...>
{
    using base_type = c_style_task_base<R(arguments&...) const, arguments...>;
};

template<typename ...arguments>
struct c_style_task<void(arguments&...) const> : public c_style_task_base<void(arguments&...) const, void, arguments...>
{
    using base_type = c_style_task_base<void(arguments&...) const, arguments...>;
};


END_NAMESPACE
#endif