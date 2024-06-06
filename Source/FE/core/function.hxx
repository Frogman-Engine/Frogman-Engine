#ifndef _FE_CORE_FUNCTION_HXX_
#define _FE_CORE_FUNCTION_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/type_traits.hxx>

// std
#include <any>




BEGIN_NAMESPACE(FE)

using void_t = var::uint8;

enum struct FORWARD_DATA : boolean
{
    _AS_LVALUE_REF = true,
    _AS_RVALUE_REF = false
};


template<class C, typename TaskImpl, FORWARD_DATA ArgumentsForwardingMode = FE::FORWARD_DATA::_AS_RVALUE_REF, typename ...ArgumentsBufferTypes>
class cpp_style_task;

template<typename TaskImpl, FORWARD_DATA ArgumentsForwardingMode = FE::FORWARD_DATA::_AS_RVALUE_REF, typename ...ArgumentsBufferTypes>
class c_style_task;


template<typename F, FORWARD_DATA ArgumentsForwardingMode = FE::FORWARD_DATA::_AS_RVALUE_REF>
class function;

template<typename R, typename ...Arguments>
class function<R(Arguments...), FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class c_style_task;

    R(*m_function_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = false;

    using function_type = decltype(m_function_pointer);
    using return_type = R;

    _FORCE_INLINE_ _CONSTEXPR20_ function() noexcept : m_function_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~function() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ function(function_type function_p) noexcept : m_function_pointer(function_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(const function& other_p) noexcept : m_function_pointer(other_p.m_function_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(function&& rvalue_p) noexcept : m_function_pointer(rvalue_p.m_function_pointer) { rvalue_p.m_function_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_function_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_pointer));
        return this->m_function_pointer(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function_type function_p) noexcept
    {
        this->m_function_pointer = function_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(const function& other_p) noexcept
    {
        this->m_function_pointer = other_p.m_function_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_pointer = rvalue_p.m_function_pointer;
        rvalue_p.m_function_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_function_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const function& other_p) const noexcept
    {
        return (this->m_function_pointer == other_p.m_function_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const function& other_p) const noexcept
    {
        return (this->m_function_pointer != other_p.m_function_pointer) ? true : false;
    }
};

template<typename ...Arguments>
class function<void(Arguments...), FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class c_style_task;

    void(*m_function_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = true;

    using function_type = decltype(m_function_pointer);
    using return_type = void;

    _FORCE_INLINE_ _CONSTEXPR20_ function() noexcept : m_function_pointer() {}
    ~function() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ function(function_type function_p) noexcept : m_function_pointer(function_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(const function& other_p) noexcept : m_function_pointer(other_p.m_function_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(function&& rvalue_p) noexcept : m_function_pointer(rvalue_p.m_function_pointer) { rvalue_p.m_function_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_function_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_pointer));
        this->m_function_pointer(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function_type function_p) noexcept
    {
        this->m_function_pointer = function_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(const function& other_p) noexcept
    {
        this->m_function_pointer = other_p.m_function_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_pointer = rvalue_p.m_function_pointer;
        rvalue_p.m_function_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_function_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const function& other_p) const noexcept
    {
        return (this->m_function_pointer == other_p.m_function_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const function& other_p) const noexcept
    {
        return (this->m_function_pointer != other_p.m_function_pointer) ? true : false;
    }
};




template<typename R, typename ...Arguments>
class function<R(Arguments...), FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class c_style_task;

    R(*m_function_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = false;

    using function_type = decltype(m_function_pointer);
    using return_type = R;

    _FORCE_INLINE_ _CONSTEXPR20_ function() noexcept : m_function_pointer() {}
    ~function() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ function(function_type function_ptr_p) noexcept : m_function_pointer(function_ptr_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(const function& other_cref_p) noexcept : m_function_pointer(other_cref_p.m_function_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(function&& rvalue_p) noexcept : m_function_pointer(rvalue_p.m_function_pointer) { rvalue_p.m_function_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_function_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_pointer));
        return this->m_function_pointer(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function_type function_p) noexcept
    {
        this->m_function_pointer = function_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(const function& other_p) noexcept
    {
        this->m_function_pointer = other_p.m_function_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_pointer = rvalue_p.m_function_pointer;
        rvalue_p.m_function_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_function_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const function& other_p) const noexcept
    {
        return (this->m_function_pointer == other_p.m_function_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const function& other_p) const noexcept
    {
        return (this->m_function_pointer != other_p.m_function_pointer) ? true : false;
    }
};

template<typename ...Arguments>
class function<void(Arguments...), FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class c_style_task;

    void(*m_function_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = true;

    using function_type = decltype(m_function_pointer);
    using return_type = void;

    _FORCE_INLINE_ _CONSTEXPR20_ function() noexcept : m_function_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~function() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ function(function_type function_p) noexcept : m_function_pointer(function_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(const function& other_p) noexcept : m_function_pointer(other_p.m_function_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ function(function&& rvalue_p) noexcept : m_function_pointer(rvalue_p.m_function_pointer) { rvalue_p.m_function_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_function_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_function_pointer));
        this->m_function_pointer(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function_type function_p) noexcept
    {
        this->m_function_pointer = function_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(const function& other_p) noexcept
    {
        this->m_function_pointer = other_p.m_function_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ function& operator=(function&& rvalue_p) noexcept
    {
        this->m_function_pointer = rvalue_p.m_function_pointer;
        rvalue_p.m_function_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_function_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const function& other_p) const noexcept
    {
        return (this->m_function_pointer == other_p.m_function_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const function& other_p) const noexcept
    {
        return (this->m_function_pointer != other_p.m_function_pointer) ? true : false;
    }
};




template<class C, typename F, FORWARD_DATA ArgumentsForwardingMode = FE::FORWARD_DATA::_AS_RVALUE_REF>
class method;

template<class C, typename R, typename ...Arguments>
class method<C, R(Arguments...) const, FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    R(C::* m_method_pointer)(Arguments...) const;

public:
    static constexpr inline boolean has_void_return_type = false;

    using method_type = decltype(m_method_pointer);
    using return_type = R;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_p, Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        return (instance_p.*this->m_method_pointer)(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename ...Arguments>
class method<C, void(Arguments...) const, FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    void(C::* m_method_pointer)(Arguments...) const;

public:
    static constexpr inline boolean has_void_return_type = true;

    using method_type = decltype(m_method_pointer);
    using return_type = void;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_p, Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        (instance_p.*this->m_method_pointer)(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename R, typename ...Arguments>
class method<C, R(Arguments...), FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    R(C::* m_method_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = false;

    using method_type = decltype(m_method_pointer);
    using return_type = R;
    using class_type = C;

    constexpr _FORCE_INLINE_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_p, Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        return (instance_p.*this->m_method_pointer)(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename ...Arguments>
class method<C, void(Arguments...), FE::FORWARD_DATA::_AS_LVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    void(C::* m_method_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = true;

    using method_type = decltype(m_method_pointer);
    using return_type = void;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_p, Arguments& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        (instance_p.*this->m_method_pointer)(arguments_p...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};


template<class C, typename R, typename ...Arguments>
class method<C, R(Arguments...) const, FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    R(C::* m_method_pointer)(Arguments...) const;

public:
    static constexpr inline boolean has_void_return_type = false;

    using method_type = decltype(m_method_pointer);
    using return_type = R;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_p, Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        return (instance_p.*this->m_method_pointer)(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename ...Arguments>
class method<C, void(Arguments...) const, FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    void(C::* m_method_pointer)(Arguments...) const;

public:
    static constexpr inline boolean has_void_return_type = true;

    using method_type = decltype(m_method_pointer);
    using return_type = void;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_p, Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        (instance_p.*this->m_method_pointer)(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename R, typename ...Arguments>
class method<C, R(Arguments...), FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    R(C::* m_method_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = false;

    using method_type = decltype(m_method_pointer);
    using return_type = R;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
     _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ R operator()(class_type& instance_p, Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        return (instance_p.*this->m_method_pointer)(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ var::boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ var::boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};

template<class C, typename ...Arguments>
class method<C, void(Arguments...), FE::FORWARD_DATA::_AS_RVALUE_REF> final
{
    template<class c, typename task_impl, FORWARD_DATA arguments_forwarding_mode, typename ...arguments_buffer_types>
    friend class cpp_style_task;

    void(C::* m_method_pointer)(Arguments...);

public:
    static constexpr inline boolean has_void_return_type = true;

    using method_type = decltype(m_method_pointer);
    using return_type = void;
    using class_type = C;

    _FORCE_INLINE_ _CONSTEXPR20_ method() noexcept : m_method_pointer() {}
    _CONSTEXPR23_ _FORCE_INLINE_ ~method() noexcept {}

    _FORCE_INLINE_ _CONSTEXPR20_ method(method_type method_p) noexcept : m_method_pointer(method_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(const method& other_p) noexcept : m_method_pointer(other_p.m_method_pointer) {}
    _FORCE_INLINE_ _CONSTEXPR20_ method(method&& rvalue_p) noexcept : m_method_pointer(rvalue_p.m_method_pointer) { rvalue_p.m_method_pointer = nullptr; }

    _FORCE_INLINE_ void operator()(class_type& instance_p, Arguments&& ...arguments_p) noexcept
    {
        FE_ASSERT(this->m_method_pointer == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_method_pointer));
        (instance_p.*this->m_method_pointer)(std::forward<Arguments>(arguments_p)...);
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method_type method_p) noexcept
    {
        this->m_method_pointer = method_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(const method& other_p) noexcept
    {
        this->m_method_pointer = other_p.m_method_pointer;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ method& operator=(method&& rvalue_p) noexcept
    {
        this->m_method_pointer = rvalue_p.m_method_pointer;
        rvalue_p.m_method_pointer = nullptr;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ operator bool() const noexcept
    {
        return this->m_method_pointer != nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ var::boolean operator==(const method& other_p) const noexcept
    {
        return (this->m_method_pointer == other_p.m_method_pointer) ? true : false;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ var::boolean operator!=(const method& other_p) const noexcept
    {
        return (this->m_method_pointer != other_p.m_method_pointer) ? true : false;
    }
};




enum struct ARGUMENTS_COUNT : uint8
{
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
    _5 = 5,
    _6 = 6,
    _7 = 7,
    _8 = 8,
    _9 = 9,
    _10 = 10
};

template<typename First = void, typename Second = void, typename Third = void, typename Fourth = void, typename Fifth = void, typename Sixth = void, typename Seventh = void, typename Eighth = void, typename Ninth = void, typename Tenth = void>
struct arguments;

template<>
struct arguments<void, void, void, void, void, void, void, void, void, void> 
{
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_0;
};

template<typename First>
struct arguments<First, void, void, void, void, void, void, void, void, void>
{
    using first_type = First;

    First _first;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_1;
    
    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept = default;
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : _first(arguments_p._first) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : _first(std::move(arguments_p._first)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        this->_first = arguments_p._first;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        this->_first = std::move(arguments_p._first);
        return *this;
    }
};

template<typename First, typename Second>
struct arguments<First, Second, void, void, void, void, void, void, void, void> : public arguments<First, void, void, void, void, void, void, void, void, void>
{
    using base_type = arguments<First, void, void, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = Second;

    second_type _second;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_2;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _second() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _second(arguments_p._second) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _second(std::move(arguments_p._second)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_second = arguments_p._second;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_second = std::move(arguments_p._second);
        return *this;
    }
};

template<typename First, typename Second, typename Third>
struct arguments<First, Second, Third, void, void, void, void, void, void, void> : public arguments<First, Second, void, void, void, void, void, void, void, void>
{
    using base_type = arguments<First, Second, void, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::Second;
    using third_type = Third;

    third_type _third;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_3;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _third() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _third(arguments_p._third) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _third(std::move(arguments_p._third)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_third = arguments_p._third;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_third = std::move(arguments_p._third);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth>
struct arguments<First, Second, Third, Fourth, void, void, void, void, void, void> : public arguments<First, Second, Third, void, void, void, void, void, void, void>
{
    using base_type = arguments<First, Second, Third, void, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = Fourth;

    fourth_type _fourth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_4;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _fourth() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _fourth(arguments_p._fourth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _fourth(std::move(arguments_p._fourth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fourth = arguments_p._fourth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fourth = std::move(arguments_p._fourth);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth, typename Fifth>
struct arguments<First, Second, Third, Fourth, Fifth, void, void, void, void, void> : public arguments<First, Second, Third, Fourth, void, void, void, void, void, void>
{
    using base_type = arguments<First, Second, Third, Fourth, void, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = Fifth;

    fifth_type _fifth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_5;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _fifth() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _fifth(arguments_p._fifth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _fifth(std::move(arguments_p._fifth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fifth = arguments_p._fifth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_fifth = std::move(arguments_p._fifth);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth, typename Fifth, typename Sixth>
struct arguments<First, Second, Third, Fourth, Fifth, Sixth, void, void, void, void> : public arguments<First, Second, Third, Fourth, Fifth, void, void, void, void, void>
{
    using base_type = arguments<First, Second, Third, Fourth, Fifth, void, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = Sixth;

    sixth_type _sixth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_6;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _sixth() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _sixth(arguments_p._sixth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _sixth(std::move(arguments_p._sixth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_sixth = arguments_p._sixth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_sixth = std::move(arguments_p._sixth);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth, typename Fifth, typename Sixth, typename Seventh>
struct arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, void, void, void> : public arguments<First, Second, Third, Fourth, Fifth, Sixth, void, void, void, void>
{
    using base_type = arguments<First, Second, Third, Fourth, Fifth, Sixth, void, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = Seventh;

    seventh_type _seventh;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_7;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _seventh() {};
    _CONSTEXPR23_ _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _seventh(arguments_p._seventh) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _seventh(std::move(arguments_p._seventh)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_seventh = arguments_p._seventh;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_seventh = std::move(arguments_p._seventh);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth, typename Fifth, typename Sixth, typename Seventh, typename Eighth>
struct arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, void, void> : public arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, void, void, void>
{
    using base_type = arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, void, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = Eighth;

    eighth_type _eighth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_8;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _eighth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _eighth(arguments_p._eighth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _eighth(std::move(arguments_p._eighth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_eighth = arguments_p._eighth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_eighth = std::move(arguments_p._eighth);
        return *this;
    }
};

template<typename First, typename Second, typename Third, typename Fourth, typename Fifth, typename Sixth, typename Seventh, typename Eighth, typename Ninth>
struct arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, void> : public  arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, void, void>
{
    using base_type = arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, void, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = typename base_type::eighth_type;
    using ninth_type = Ninth;

    ninth_type _ninth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_9;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _ninth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _ninth(arguments_p._ninth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _ninth(std::move(arguments_p._ninth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_ninth = arguments_p._ninth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_ninth = std::move(arguments_p._ninth);
        return *this;
    }
};


template<typename First, typename Second, typename Third, typename Fourth, typename Fifth, typename Sixth, typename Seventh, typename Eighth, typename Ninth, typename Tenth>
struct arguments : public arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, void>
{
    using base_type = arguments<First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, void>;
    using first_type = typename base_type::first_type;
    using second_type = typename base_type::second_type;
    using third_type = typename base_type::third_type;
    using fourth_type = typename base_type::fourth_type;
    using fifth_type = typename base_type::fifth_type;
    using sixth_type = typename base_type::sixth_type;
    using seventh_type = typename base_type::seventh_type;
    using eighth_type = typename base_type::eighth_type;
    using ninth_type = typename base_type::ninth_type;
    using tenth_type = Tenth;

    tenth_type _tenth;
    static constexpr inline ARGUMENTS_COUNT count = ARGUMENTS_COUNT::_10;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments() noexcept : base_type(), _tenth() {};
    _FORCE_INLINE_ ~arguments() noexcept = default;

    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments& arguments_p) noexcept : base_type(arguments_p), _tenth(arguments_p._tenth) {};
    _FORCE_INLINE_ _CONSTEXPR20_ arguments(arguments&& arguments_p) noexcept : base_type(std::move(arguments_p)), _tenth(std::move(arguments_p._tenth)) {};

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_tenth = arguments_p._tenth;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ arguments& operator=(arguments&& arguments_p) noexcept
    {
        base_type::operator=(arguments_p);
        this->_tenth = std::move(arguments_p._tenth);
        return *this;
    }
};




class task_base
{
public:
    task_base() noexcept = default;

    virtual ~task_base() {};

    virtual void operator()(void) noexcept = 0;

    // Caller must ensure the class type correctness. It has no effect for c_style_tasks.
	virtual void set_instance(void* const target_instance_p) noexcept = 0;

	// Caller must ensure that the types and size of the arguments are correct.
    virtual void set_arguments(void* arguments_p, _MAYBE_UNUSED_ size_t size_in_bytes_p) noexcept = 0;

	// Checks if the function pointer is nullptr.
    virtual boolean is_null(void) const noexcept = 0;

	// Returns the result of the task.
    virtual std::any get_result() const noexcept = 0;
};




template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
class cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...> : public task_base
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

public:
    using class_type = C;
    using task_impl_type = TaskImpl;
    using task_type = FE::method<class_type, task_impl_type, FE::FORWARD_DATA::_AS_RVALUE_REF>;
    using arguments_buffer_type = FE::arguments<ArgumentsBufferTypes...>;
    using return_type = typename FE::remove_const_reference<typename FE::method<class_type, task_impl_type, FE::FORWARD_DATA::_AS_RVALUE_REF>::return_type>::type;
    using task_result_buffer_type = typename FE::conditional_type<std::is_void<return_type>::value, void_t, return_type>::type;

    typename task_type::method_type _method;

private:
    class_type* m_instance;

    thread_local static arguments_buffer_type tl_s_arguments_buffer;
    thread_local static task_result_buffer_type tl_s_task_result;

public:
    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task() noexcept : _method() {}
    virtual ~cpp_style_task() noexcept override {};

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(typename task_type::method_type task_p) noexcept : _method(task_p), m_instance() {}
    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(cpp_style_task& other_p) noexcept : _method(other_p._method), m_instance(other_p.m_instance) {}
    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(cpp_style_task&& rvalue_p) noexcept : _method(rvalue_p._method), m_instance(rvalue_p.m_instance)
    {
        rvalue_p._method = nullptr;
        rvalue_p.m_instance = nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(typename task_type::method_type task_p) noexcept
    {
        this->_method = task_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(cpp_style_task& other_p) noexcept
    {
        this->_method = other_p._method;
        this->m_instance = other_p.m_instance;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(cpp_style_task&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        rvalue_p._method = nullptr;

        this->m_instance = rvalue_p.m_instance;
        rvalue_p.m_instance = nullptr;
        return *this;
    }

    virtual void operator()(void) noexcept override
    {
        FE_ASSERT(this->m_instance == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_instance));

        if constexpr (task_type::has_void_return_type == true)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {   
                (m_instance->*_method)();
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                (m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth), std::forward<typename arguments_buffer_type::_tenth>(tl_s_arguments_buffer._tenth));
                return;
            }
        }
        else if constexpr (task_type::has_void_return_type == false)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                tl_s_task_result = std::move((m_instance->*_method)());
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                tl_s_task_result = std::move((m_instance->*_method)(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth), std::forward<typename arguments_buffer_type::_tenth>(tl_s_arguments_buffer._tenth)));
                return;
            }
        }
    }


    virtual void set_instance(void* const instance_p) noexcept override
    {
        FE_ASSERT(instance_p == nullptr, "The target instance is null!");
		this->m_instance = static_cast<class_type*>(instance_p);
    }


    virtual void set_arguments(void* arguments_p, _MAYBE_UNUSED_ size_t size_in_bytes_p) noexcept override
    {
		FE_ASSERT(arguments_p == nullptr, "The arguments are null!");
		FE_ASSERT(size_in_bytes_p == 0, "The size of the arguments is 0!");

        if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
		{
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");
			
            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
		}
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");
			
            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
		}

        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");
            
            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
		}
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fourth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");
			
            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
        {
            FE_ASSERT((sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type)) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
		}
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

			tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

			tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
		}
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

			tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

			tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

			tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

			tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

			tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

			tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

			tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
		}
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

			tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

			tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

			tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

			tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

			tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
        }
		else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
		{
			FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) + sizeof(typename arguments_buffer_type::tenth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

			tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

			tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

			tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

			tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

			tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

			tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

			tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

			tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

			tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
			arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::ninth_type);

			tl_s_arguments_buffer._tenth = std::move(*static_cast<typename arguments_buffer_type::tenth_type*>(arguments_p));
		}
    }


    virtual boolean is_null(void) const noexcept override
    {
        if (!this->_method)
        {
            return true;
        }

        if (this->m_instance == nullptr)
        {
            return true;
        }

        return false;
    }

    virtual std::any get_result() const noexcept override
    {
        return std::move(tl_s_task_result);
    }
};

template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::arguments_buffer_type cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::tl_s_arguments_buffer;

template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::task_result_buffer_type cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::tl_s_task_result;


template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
class cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...> : public task_base
{
    static_assert(std::is_class<C>::value == true, "C must be a class or a struct type.");

public:
    using class_type = C;
    using task_impl_type = TaskImpl;
    using task_type = FE::method<class_type, task_impl_type, FE::FORWARD_DATA::_AS_LVALUE_REF>;
    using arguments_buffer_type = FE::arguments<ArgumentsBufferTypes...>;
    using return_type = typename FE::remove_const_reference<typename FE::method<class_type, task_impl_type, FE::FORWARD_DATA::_AS_LVALUE_REF>::return_type>::type;
    using task_result_buffer_type = typename FE::conditional_type<std::is_void<return_type>::value, void_t, return_type>::type;

    typename task_type::method_type _method;

private:
    class_type* m_instance;

    thread_local static arguments_buffer_type tl_s_arguments_buffer;
    thread_local static task_result_buffer_type tl_s_task_result;

public:
    _FORCE_INLINE_ cpp_style_task() noexcept : _method(), m_instance() {}
    virtual ~cpp_style_task() noexcept override {};

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(typename task_type::method_type task_p) noexcept : _method(task_p), m_instance() {}
    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(cpp_style_task& other_p) noexcept : _method(other_p._method), m_instance(other_p.m_instance) {}
    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task(cpp_style_task&& rvalue_p) noexcept : _method(rvalue_p._method), m_instance(rvalue_p.m_instance) 
    {
        rvalue_p._method = nullptr;
        rvalue_p.m_instance = nullptr;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(typename task_type::method_type task_p) noexcept
    {
        this->_method = task_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(cpp_style_task& other_p) noexcept
    {
        this->_method = other_p._method;
        this->m_instance = other_p.m_instance;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ cpp_style_task& operator=(cpp_style_task&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        rvalue_p._method = nullptr;

        this->m_instance = rvalue_p.m_instance;
        rvalue_p.m_instance = nullptr;
        return *this;
    }

    virtual void operator()(void) noexcept override
    {
        FE_ASSERT(this->m_instance == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_instance));

        if constexpr (task_type::has_void_return_type == true)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                (m_instance->*_method)();
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                (m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth, tl_s_arguments_buffer._tenth);
                return;
            }
        }
        else if constexpr (task_type::has_void_return_type == false)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                tl_s_task_result = std::move((m_instance->*_method)());
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                *tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                tl_s_task_result = std::move((m_instance->*_method)(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth, tl_s_arguments_buffer._tenth));
                return;
            }
        }
    }


    virtual void set_instance(void* const instance_p) noexcept override
    {
        FE_ASSERT(instance_p == nullptr, "The target instance is null!");
        this->m_instance = static_cast<class_type*>(instance_p);
    }


    virtual void set_arguments(void* arguments_p, _MAYBE_UNUSED_ size_t size_in_bytes_p) noexcept override
    {
        FE_ASSERT(arguments_p == nullptr, "The arguments are null!");
        FE_ASSERT(size_in_bytes_p == 0, "The size of the arguments is 0!");

        if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
        }

        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fourth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
        {
            FE_ASSERT((sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type)) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) + sizeof(typename arguments_buffer_type::tenth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::ninth_type);

            tl_s_arguments_buffer._tenth = std::move(*static_cast<typename arguments_buffer_type::tenth_type*>(arguments_p));
        }
    }


    virtual boolean is_null(void) const noexcept override
    {
        if (!this->_method)
        {
            return true;
        }

        if (this->m_instance == nullptr)
        {
            return true;
        }

        return false;
    }

    virtual std::any get_result() const noexcept override
    {
        return std::move(tl_s_task_result);
    }
};

template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::arguments_buffer_type cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::tl_s_arguments_buffer;

template<class C, typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::task_result_buffer_type cpp_style_task<C, TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::tl_s_task_result;




template<typename TaskImpl, typename ...ArgumentsBufferTypes>
class c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...> : public task_base
{
public:
    using task_impl_type = TaskImpl;
    using task_type = FE::function<task_impl_type, FE::FORWARD_DATA::_AS_RVALUE_REF>;
    using arguments_buffer_type = FE::arguments<ArgumentsBufferTypes...>;
    using return_type = typename FE::remove_const_reference<typename FE::function<task_impl_type, FE::FORWARD_DATA::_AS_RVALUE_REF>::return_type>::type;
    using task_result_buffer_type = typename FE::conditional_type<std::is_void<return_type>::value, void_t, return_type>::type;

    typename task_type::function_type _function;

private:
    thread_local static arguments_buffer_type tl_s_arguments_buffer;
    thread_local static task_result_buffer_type tl_s_task_result;

public:
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task() noexcept : _function() {}
    virtual ~c_style_task() noexcept override {};

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(typename task_type::function_type task_p) noexcept : _function(task_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(c_style_task& other_p) noexcept : _function(other_p._function) {}
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(c_style_task&& rvalue_p) noexcept : _function(rvalue_p._function) { rvalue_p._function = nullptr; }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(typename task_type::function_type task_p) noexcept
    {
        this->_function = task_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(c_style_task& other_p) noexcept
    {        
        this->_function = other_p._function;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(c_style_task&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        rvalue_p._function = nullptr;
        return *this;
    }

    virtual void operator()(void) noexcept override
    {
        if constexpr (task_type::has_void_return_type == true)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                this->_function();
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth), std::forward<typename arguments_buffer_type::_tenth>(tl_s_arguments_buffer._tenth));
                return;
            }
        }
        else if constexpr (task_type::has_void_return_type == false)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                tl_s_task_result = std::move(this->_function());
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                *tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth)));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                tl_s_task_result = std::move(this->_function(std::forward<typename arguments_buffer_type::first_type>(tl_s_arguments_buffer._first), std::forward<typename arguments_buffer_type::second_type>(tl_s_arguments_buffer._second), std::forward<typename arguments_buffer_type::third_type>(tl_s_arguments_buffer._third), std::forward<typename arguments_buffer_type::fourth_type>(tl_s_arguments_buffer._fourth), std::forward<typename arguments_buffer_type::fifth_type>(tl_s_arguments_buffer._fifth), std::forward<typename arguments_buffer_type::sixth_type>(tl_s_arguments_buffer._sixth), std::forward<typename arguments_buffer_type::seventh_type>(tl_s_arguments_buffer._seventh), std::forward<typename arguments_buffer_type::Eighth>(tl_s_arguments_buffer._eighth), std::forward<typename arguments_buffer_type::_ninth>(tl_s_arguments_buffer._ninth), std::forward<typename arguments_buffer_type::_tenth>(tl_s_arguments_buffer._tenth)));
                return;
            }
        }
    }


    virtual void set_arguments(void* arguments_p, _MAYBE_UNUSED_ size_t size_in_bytes_p) noexcept override
    {
        FE_ASSERT(arguments_p == nullptr, "The arguments are null!");
        FE_ASSERT(size_in_bytes_p == 0, "The size of the arguments is 0!");

        if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
        }

        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fourth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
        {
            FE_ASSERT((sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type)) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) + sizeof(typename arguments_buffer_type::tenth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::ninth_type);

            tl_s_arguments_buffer._tenth = std::move(*static_cast<typename arguments_buffer_type::tenth_type*>(arguments_p));
        }
    }


    virtual boolean is_null(void) const noexcept override
    {
        if (!this->_function)
        {
            return true;
        }

        return false;
    }

    virtual std::any get_result() const noexcept override
    {
        return std::move(tl_s_task_result);
    }

    virtual void set_instance(void* const) noexcept override {};
};

template<typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::arguments_buffer_type c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::tl_s_arguments_buffer;

template<typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::task_result_buffer_type c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_RVALUE_REF, ArgumentsBufferTypes...>::tl_s_task_result;


template<typename TaskImpl, typename ...ArgumentsBufferTypes>
class c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...> : public task_base
{
public:
    using task_impl_type = TaskImpl;
    using task_type = FE::function<task_impl_type, FE::FORWARD_DATA::_AS_LVALUE_REF>;
    using arguments_buffer_type = FE::arguments<ArgumentsBufferTypes...>;
    using return_type = typename FE::remove_const_reference<typename FE::function<task_impl_type, FE::FORWARD_DATA::_AS_LVALUE_REF>::return_type>::type;
    using task_result_buffer_type = typename FE::conditional_type<std::is_void<return_type>::value, void_t, return_type>::type;

    typename task_type::function_type _function;

private:
    thread_local static arguments_buffer_type tl_s_arguments_buffer;
    thread_local static task_result_buffer_type tl_s_task_result;

public:
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task() noexcept : _function() {}
    virtual ~c_style_task() noexcept override {};

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(typename task_type::function_type task_p) noexcept : _function(task_p) {}
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(c_style_task& other_p) noexcept : _function(other_p._function) {}
    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task(c_style_task&& rvalue_p) noexcept : _function(rvalue_p._function) { rvalue_p._function = nullptr; }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(typename task_type::function_type task_p) noexcept
    {
        this->_function = task_p;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(c_style_task& other_p) noexcept
    {
        this->_function = other_p._function;
        return *this;
    }

    _FORCE_INLINE_ _CONSTEXPR20_ c_style_task& operator=(c_style_task&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        rvalue_p._function = nullptr;
        return *this;
    }

    virtual void operator()(void) noexcept override
    {
        if constexpr (task_type::has_void_return_type == true)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                this->_function();
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                this->_function(tl_s_arguments_buffer._first);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth);
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth, tl_s_arguments_buffer._tenth);
                return;
            }
        }
        else if constexpr (task_type::has_void_return_type == false)
        {
            if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_0)
            {
                tl_s_task_result = std::move(this->_function());
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
            {
                *tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth));
                return;
            }
            else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
            {
                tl_s_task_result = std::move(this->_function(tl_s_arguments_buffer._first, tl_s_arguments_buffer._second, tl_s_arguments_buffer._third, tl_s_arguments_buffer._fourth, tl_s_arguments_buffer._fifth, tl_s_arguments_buffer._sixth, tl_s_arguments_buffer._seventh, tl_s_arguments_buffer._eighth, tl_s_arguments_buffer._ninth, tl_s_arguments_buffer._tenth));
                return;
            }
        }
    }


    virtual void set_arguments(void* arguments_p, _MAYBE_UNUSED_ size_t size_in_bytes_p) noexcept override
    {
        FE_ASSERT(arguments_p == nullptr, "The arguments are null!");
        FE_ASSERT(size_in_bytes_p == 0, "The size of the arguments is 0!");

        if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_1)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_2)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_3)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_4)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fourth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_5)
        {
            FE_ASSERT((sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type)) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_6)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_7)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_8)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_9)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
        }
        else if constexpr (arguments_buffer_type::count == ARGUMENTS_COUNT::_10)
        {
            FE_ASSERT(sizeof(typename arguments_buffer_type::first_type) + sizeof(typename arguments_buffer_type::second_type) + sizeof(typename arguments_buffer_type::third_type) + sizeof(typename arguments_buffer_type::fifth_type) + sizeof(typename arguments_buffer_type::sixth_type) + sizeof(typename arguments_buffer_type::seventh_type) + sizeof(typename arguments_buffer_type::eighth_type) + sizeof(typename arguments_buffer_type::ninth_type) + sizeof(typename arguments_buffer_type::tenth_type) != size_in_bytes_p, "Input arguments buffer corruption detected: different size of types have been passed to the arguments buffer!");

            tl_s_arguments_buffer._first = std::move(*static_cast<typename arguments_buffer_type::first_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::first_type);

            tl_s_arguments_buffer._second = std::move(*static_cast<typename arguments_buffer_type::second_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::second_type);

            tl_s_arguments_buffer._third = std::move(*static_cast<typename arguments_buffer_type::third_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::third_type);

            tl_s_arguments_buffer._fourth = std::move(*static_cast<typename arguments_buffer_type::fourth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fourth_type);

            tl_s_arguments_buffer._fifth = std::move(*static_cast<typename arguments_buffer_type::fifth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::fifth_type);

            tl_s_arguments_buffer._sixth = std::move(*static_cast<typename arguments_buffer_type::sixth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::sixth_type);

            tl_s_arguments_buffer._seventh = std::move(*static_cast<typename arguments_buffer_type::seventh_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::seventh_type);

            tl_s_arguments_buffer._eighth = std::move(*static_cast<typename arguments_buffer_type::eighth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::eighth_type);

            tl_s_arguments_buffer._ninth = std::move(*static_cast<typename arguments_buffer_type::ninth_type*>(arguments_p));
            arguments_p = static_cast<var::byte*>(arguments_p) + sizeof(typename arguments_buffer_type::ninth_type);

            tl_s_arguments_buffer._tenth = std::move(*static_cast<typename arguments_buffer_type::tenth_type*>(arguments_p));
        }
    }


    virtual boolean is_null(void) const noexcept override
    {
        if (!this->_function)
        {
            return true;
        }

        return false;
    }

    virtual std::any get_result() const noexcept override
    {
        return std::move(tl_s_task_result);
    }

    virtual void set_instance(void* const) noexcept override {};
};

template<typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::arguments_buffer_type c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::tl_s_arguments_buffer;

template<typename TaskImpl, typename ...ArgumentsBufferTypes>
thread_local typename c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::task_result_buffer_type c_style_task<TaskImpl, FE::FORWARD_DATA::_AS_LVALUE_REF, ArgumentsBufferTypes...>::tl_s_task_result;


template <class FunctionSignature>
_FORCE_INLINE_ typename FE::function<FunctionSignature>::function_type function_cast(typename FE::function<FunctionSignature>::function_type lamda_p) noexcept
{
    return lamda_p;
}


END_NAMESPACE
#endif