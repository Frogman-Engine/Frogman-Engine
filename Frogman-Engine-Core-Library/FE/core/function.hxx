#ifndef _FE_CORE_FUNCTION_HXX_
#define _FE_CORE_FUNCTION_HXX_
#include "prerequisite_symbols.h"
#include "algorithm/string.hxx"
#include <functional>


BEGIN_NAMESPACE(FE)


enum struct RETURN_TYPE : bool
{
    _VOID = false,
    _NON_VOID = true
};


struct task_base
{
    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept = 0;
};


template<typename P0>
struct one_arg
{
    using first_argument_type = P0;

    first_argument_type _param0;


    constexpr one_arg() noexcept {}
    _FORCE_INLINE_ one_arg(first_argument_type param0_p) noexcept : _param0(param0_p) {}
    constexpr ~one_arg() noexcept {}
};

template<typename P0, typename P1 = P0>
struct two_args : public one_arg<P0>
{
    using second_argument_type = P1;
    using base_type = one_arg<P0>;

    second_argument_type _param1;

    
    constexpr two_args() noexcept {}
    _FORCE_INLINE_ two_args(typename base_type::first_argument_type param0_p, second_argument_type param1_p) noexcept : base_type(param0_p), _param1(param1_p) {}
    constexpr ~two_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1>
struct three_args : public two_args<P0, P1>
{
    using third_argument_type = P2;
    using base_type = two_args<P0, P1>;

    third_argument_type _param2;


    constexpr three_args() noexcept {}
    _FORCE_INLINE_ three_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, third_argument_type param2_p) noexcept : base_type(param0_p, param1_p), _param2(param2_p) {}
    constexpr ~three_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2>
struct four_args : public three_args<P0, P1, P2>
{
    using fourth_argument_type = P3;
    using base_type = three_args<P0, P1, P2>;

    fourth_argument_type _param3;


    constexpr four_args() noexcept {}
    _FORCE_INLINE_ four_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, fourth_argument_type param3_p) noexcept : base_type(param0_p, param1_p, param2_p), _param3(param3_p) {}
    constexpr ~four_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3>
struct five_args : public four_args<P0, P1, P2, P3>
{
    using fifth_argument_type = P4;
    using base_type = four_args<P0, P1, P2, P3>;

    fifth_argument_type _param4;


    constexpr five_args() noexcept {}
    _FORCE_INLINE_ five_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, fifth_argument_type param4_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p), _param4(param4_p) {}
    constexpr ~five_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3, typename P5 = P4>
struct six_args : public five_args<P0, P1, P2, P3, P4>
{
    using sixth_argument_type = P5;
    using base_type = five_args<P0, P1, P2, P3, P4>;

    sixth_argument_type _param5;


    constexpr six_args() noexcept {}
    _FORCE_INLINE_ six_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, typename base_type::fifth_argument_type param4_p, sixth_argument_type param5_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p, param4_p), _param5(param5_p) {}
    constexpr ~six_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3, typename P5 = P4, typename P6 = P5>
struct seven_args : public six_args<P0, P1, P2, P3, P4, P5>
{
    using seventh_argument_type = P6;
    using base_type = six_args<P0, P1, P2, P3, P4, P5>;

    seventh_argument_type _param6;


    constexpr seven_args() noexcept {}
    _FORCE_INLINE_ seven_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, typename base_type::fifth_argument_type param4_p, typename base_type::sixth_argument_type param5_p, seventh_argument_type param6_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p, param4_p, param5_p), _param6(param6_p) {}
    constexpr ~seven_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3, typename P5 = P4, typename P6 = P5, typename P7 = P6>
struct eight_args : public seven_args<P0, P1, P2, P3, P4, P5, P6>
{
    using eighth_argument_type = P7;
    using base_type = seven_args<P0, P1, P2, P3, P4, P5, P6>;

    eighth_argument_type _param7;


    constexpr eight_args() noexcept {}
    _FORCE_INLINE_ eight_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, typename base_type::fifth_argument_type param4_p, typename base_type::sixth_argument_type param5_p, typename base_type::seventh_argument_type param6_p, eighth_argument_type param7_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p, param4_p, param5_p, param6_p), _param7(param7_p) {}
    constexpr ~eight_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3, typename P5 = P4, typename P6 = P5, typename P7 = P6, typename P8 = P7>
struct nine_args : public eight_args<P0, P1, P2, P3, P4, P5, P6, P7>
{
    using nineth_argument_type = P8;
    using base_type = eight_args<P0, P1, P2, P3, P4, P5, P6, P7>;

    nineth_argument_type _param8;

    constexpr nine_args() noexcept {}
    _FORCE_INLINE_ nine_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, typename base_type::fifth_argument_type param4_p, typename base_type::sixth_argument_type param5_p, typename base_type::seventh_argument_type param6_p, typename base_type::eighth_argument_type param7_p, nineth_argument_type param8_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p, param4_p, param5_p, param6_p, param7_p), _param8(param8_p) {}
    constexpr ~nine_args() noexcept {}
};

template<typename P0, typename P1 = P0, typename P2 = P1, typename P3 = P2, typename P4 = P3, typename P5 = P4, typename P6 = P5, typename P7 = P6, typename P8 = P7, typename P9 = P8>
struct ten_args : public nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8>
{
    using tenth_argument_type = P9;
    using base_type = nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8>;

    tenth_argument_type _param9;

    constexpr ten_args() noexcept {}
    _FORCE_INLINE_ ten_args(typename base_type::first_argument_type param0_p, typename base_type::second_argument_type param1_p, typename base_type::third_argument_type param2_p, typename base_type::fourth_argument_type param3_p, typename base_type::fifth_argument_type param4_p, typename base_type::sixth_argument_type param5_p, typename base_type::seventh_argument_type param6_p, typename base_type::eighth_argument_type param7_p, typename base_type::nineth_argument_type param8_p, tenth_argument_type param9_p) noexcept : base_type(param0_p, param1_p, param2_p, param3_p, param4_p, param5_p, param6_p, param7_p, param8_p), _param9(param9_p) {}
    constexpr ~ten_args() noexcept {}
};




struct void_function : public task_base
{
    ::std::function<void(void)> _function;


    using function_type = decltype(_function);
  

    _FORCE_INLINE_ void_function() noexcept = default;
    void_function(function_type function_p) noexcept : _function(function_p) {}

    void_function(void_function& other_ref_p) noexcept : _function(other_ref_p._function) {}
    void_function(void_function&& rvalue_p) noexcept : _function(rvalue_p._function) {}


    _FORCE_INLINE_ void_function& operator=(void_function& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        return *this;
    }

    _FORCE_INLINE_ void_function& operator=(void_function&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function();

        return RETURN_TYPE::_VOID;
    }
};

template<class T>
struct void_method : public task_base
{
    ::std::function<void(T)> _method;
    T* _object;


    using function_type = decltype(_method);


    constexpr void_method() noexcept : _object() {}
    void_method(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method(function_type function_p, T* const object_ptrc_p) noexcept : _method(function_p), _object(object_ptrc_p) {}

    void_method(void_method& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object) {}
    void_method(void_method&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object) {}


    _FORCE_INLINE_ void_method& operator=(void_method& function_ref_p) noexcept
    {
        this->_method = function_ref_p._method;
        this->_object = function_ref_p._object;
        return *this;
    }

    _FORCE_INLINE_ void_method& operator=(void_method&& function_p) noexcept
    {
        this->_method = function_p._method;
        this->_object = function_p._object;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method(*_object);

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0>
struct void_function_with_1_arg : public task_base
{
    ::std::function<void(P0)> _function;
    FE::one_arg<P0> _parameters;

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_1_arg() noexcept {}
    void_function_with_1_arg(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_1_arg(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_1_arg(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_1_arg(void_function_with_1_arg& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_1_arg(void_function_with_1_arg&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_1_arg& operator=(void_function_with_1_arg& function_ref_p) noexcept
    {
        this->_function = function_ref_p._function;
        this->_parameters = function_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_1_arg& operator=(void_function_with_1_arg&& function_p) noexcept
    {
        this->_function = function_p._function;
        this->_parameters = function_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0>
struct void_method_with_1_arg : public task_base
{
    ::std::function<void(T, P0)> _method;
    T* _object;
    FE::one_arg<P0> _parameters;

    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_1_arg() noexcept : _object() {}
    void_method_with_1_arg(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_1_arg(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_1_arg(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_1_arg(function_type function_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(function_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_1_arg(void_method_with_1_arg& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_1_arg(void_method_with_1_arg&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_1_arg& operator=(void_method_with_1_arg& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_1_arg& operator=(void_method_with_1_arg&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0>
struct void_function_with_2_args : public task_base
{
    ::std::function<void(P0, P1)> _function;
    FE::two_args<P0, P1> _parameters;

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_2_args() noexcept {}
    void_function_with_2_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_2_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_2_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_2_args(void_function_with_2_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_2_args(void_function_with_2_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_2_args& operator=(void_function_with_2_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_2_args& operator=(void_function_with_2_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0>
struct void_method_with_2_args : public task_base
{
    ::std::function<void(T, P0, P1)> _method;
    T* _object;
    FE::two_args<P0, P1> _parameters;

    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_2_args() noexcept : _object() {}
    void_method_with_2_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_2_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_2_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_2_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_2_args(void_method_with_2_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_2_args(void_method_with_2_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_2_args& operator=(void_method_with_2_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_2_args& operator=(void_method_with_2_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0, typename P2 = P1>
struct void_function_with_3_args : public task_base
{
    ::std::function<void(P0, P1, P2)> _function;
    FE::three_args<P0, P1, P2> _parameters;

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_3_args() noexcept {}
    void_function_with_3_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_3_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_3_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_3_args(void_function_with_3_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_3_args(void_function_with_3_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_3_args& operator=(void_function_with_3_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_3_args& operator=(void_function_with_3_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0, typename P2 = P1>
struct void_method_with_3_args : public task_base
{
    ::std::function<void(T, P0, P1, P2)> _method;
    T* _object;
    FE::three_args<P0, P1, P2> _parameters;
    
    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_3_args() noexcept : _object() {}
    void_method_with_3_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_3_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_3_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_3_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_3_args(void_method_with_3_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_3_args(void_method_with_3_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_3_args& operator=(void_method_with_3_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_3_args& operator=(void_method_with_3_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2>
struct void_function_with_4_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3)> _function;
    FE::four_args<P0, P1, P2, P3> _parameters;

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_4_args() noexcept {}
    void_function_with_4_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_4_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_4_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_4_args(void_function_with_4_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_4_args(void_function_with_4_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_4_args& operator=(void_function_with_4_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_4_args& operator=(void_function_with_4_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2>
struct void_method_with_4_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3)> _method;
    T* _object;
    FE::four_args<P0, P1, P2, P3> _parameters;

    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_4_args() noexcept : _object() {}
    void_method_with_4_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_4_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_4_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_4_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_4_args(void_method_with_4_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_4_args(void_method_with_4_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_4_args& operator=(void_method_with_4_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_4_args& operator=(void_method_with_4_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3>
struct void_function_with_5_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4)> _function;
    FE::five_args<P0, P1, P2, P3, P4> _parameters;
    

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_5_args() noexcept {}
    void_function_with_5_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_5_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_5_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_5_args(void_function_with_5_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_5_args(void_function_with_5_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_5_args& operator=(void_function_with_5_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_5_args& operator=(void_function_with_5_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3>
struct void_method_with_5_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4)> _method;
    T* _object;
    FE::five_args<P0, P1, P2, P3, P4> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_5_args() noexcept : _object() {}
    void_method_with_5_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_5_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_5_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_5_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_5_args(void_method_with_5_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_5_args(void_method_with_5_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_5_args& operator=(void_method_with_5_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_5_args& operator=(void_method_with_5_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4>
struct void_function_with_6_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4, P5)> _function;
    FE::six_args<P0, P1, P2, P3, P4, P5> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_6_args() noexcept {}
    void_function_with_6_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_6_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_6_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_6_args(void_function_with_6_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_6_args(void_function_with_6_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_6_args& operator=(void_function_with_6_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_6_args& operator=(void_function_with_6_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4>
struct void_method_with_6_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4, P5)> _method;
    T* _object;
    FE::six_args<P0, P1, P2, P3, P4, P5> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);

    
    constexpr void_method_with_6_args() noexcept : _object() {}
    void_method_with_6_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_6_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_6_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_6_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_6_args(void_method_with_6_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_6_args(void_method_with_6_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_6_args& operator=(void_method_with_6_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_6_args& operator=(void_method_with_6_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5>
struct void_function_with_7_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4, P5, P6)> _function;
    FE::seven_args<P0, P1, P2, P3, P4, P5, P6> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_7_args() noexcept {}
    void_function_with_7_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_7_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_7_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_7_args(void_function_with_7_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_7_args(void_function_with_7_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_7_args& operator=(void_function_with_7_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_7_args& operator=(void_function_with_7_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5>
struct void_method_with_7_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4, P5, P6)> _method;
    T* _object;
    FE::seven_args<P0, P1, P2, P3, P4, P5, P6> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_7_args() noexcept : _object() {}
    void_method_with_7_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_7_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_7_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_7_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_7_args(void_method_with_7_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_7_args(void_method_with_7_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_7_args& operator=(void_method_with_7_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_7_args& operator=(void_method_with_7_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6>
struct void_function_with_8_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4, P5, P6, P7)> _function;
    FE::eight_args<P0, P1, P2, P3, P4, P5, P6, P7> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_8_args() noexcept {};
    void_function_with_8_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_8_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_8_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_8_args(void_function_with_8_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_8_args(void_function_with_8_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_8_args& operator=(void_function_with_8_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_8_args& operator=(void_function_with_8_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6>
struct void_method_with_8_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4, P5, P6, P7)> _method;
    T* _object;
    FE::eight_args<P0, P1, P2, P3, P4, P5, P6, P7> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_8_args() noexcept : _object() {}
    void_method_with_8_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_8_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_8_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_8_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_8_args(void_method_with_8_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_8_args(void_method_with_8_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_8_args& operator=(void_method_with_8_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_8_args& operator=(void_method_with_8_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7
        );

        return RETURN_TYPE::_VOID;
    }
};





template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7>
struct void_function_with_9_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4, P5, P6, P7, P8)> _function;
    FE::nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_9_args() noexcept {}
    void_function_with_9_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_9_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_9_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_9_args(void_function_with_9_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_9_args(void_function_with_9_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_9_args& operator=(void_function_with_9_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_9_args& operator=(void_function_with_9_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7>
struct void_method_with_9_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4, P5, P6, P7, P8)> _method;
    T* _object;
    FE::nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_9_args() noexcept : _object() {}
    void_method_with_9_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_9_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_9_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_9_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_9_args(void_method_with_9_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_9_args(void_method_with_9_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_9_args& operator=(void_method_with_9_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_9_args& operator=(void_method_with_9_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7, typename P9 = P8>
struct void_function_with_10_args : public task_base
{
    ::std::function<void(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> _function;
    FE::ten_args<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr void_function_with_10_args() noexcept {}
    void_function_with_10_args(function_type function_p) noexcept : _function(function_p) {}
    void_function_with_10_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    void_function_with_10_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    void_function_with_10_args(void_function_with_10_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    void_function_with_10_args(void_function_with_10_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ void_function_with_10_args& operator=(void_function_with_10_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_function_with_10_args& operator=(void_function_with_10_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8, _parameters._param9
        );

        return RETURN_TYPE::_VOID;
    }
};

template<class T, typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7, typename P9 = P8>
struct void_method_with_10_args : public task_base
{
    ::std::function<void(T, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> _method;
    T* _object;
    FE::ten_args<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> _parameters;
    

    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr void_method_with_10_args() noexcept : _object() {}
    void_method_with_10_args(function_type function_p) noexcept : _method(function_p), _object() {}
    void_method_with_10_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    void_method_with_10_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    void_method_with_10_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    void_method_with_10_args(void_method_with_10_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    void_method_with_10_args(void_method_with_10_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ void_method_with_10_args& operator=(void_method_with_10_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ void_method_with_10_args& operator=(void_method_with_10_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(_MAYBE_UNUSED_ void* out_return_ptr_p = nullptr, _MAYBE_UNUSED_ const char* const typename_str_ptrc_p = nullptr) noexcept override
    {
        _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8, _parameters._param9
        );

        return RETURN_TYPE::_VOID;
    }
};




template<typename return_type>
struct function : public task_base
{
    ::std::function<return_type(void)> _function;


    using function_type = decltype(_function);


    constexpr function() noexcept {}
    function(function_type function_p) noexcept : _function(function_p) {}

    function(function& other_ref_p) noexcept : _function(other_ref_p._function) {}
    function(function&& rvalue_p) noexcept : _function(rvalue_p._function) {}


    _FORCE_INLINE_ function& operator=(function& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        return *this;
    }

    _FORCE_INLINE_ function& operator=(function&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");
        
        *((return_type*)out_return_ptr_p) = _function();

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T>
struct method : public task_base
{
    ::std::function<return_type(T)> _method;
    T* _object;


    using function_type = decltype(_method);


    constexpr method() noexcept : _object() {}
    method(function_type function_p) noexcept : _method(function_p), _object() {}
    method(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method(function_type function_p, T* const object_ptrc_p) noexcept : _method(function_p), _object(object_ptrc_p) {}

    method(method& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object) {}
    method(method&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object) {}


    _FORCE_INLINE_ method& operator=(method& function_ref_p) noexcept
    {
        this->_method = function_ref_p._method;
        this->_object = function_ref_p._object;
        return *this;
    }

    _FORCE_INLINE_ method& operator=(method&& function_p) noexcept
    {
        this->_method = function_p._method;
        this->_object = function_p._object;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method(*_object);

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type, typename P0>
struct function_with_1_arg : public task_base
{
    ::std::function<return_type(P0)> _function;
    FE::one_arg<P0> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_1_arg() noexcept {}
    function_with_1_arg(function_type function_p) noexcept : _function(function_p) {}
    function_with_1_arg(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_1_arg(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_1_arg(function_with_1_arg& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_1_arg(function_with_1_arg&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_1_arg& operator=(function_with_1_arg& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_1_arg& operator=(function_with_1_arg&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T, typename P0>
struct method_with_1_arg : public task_base
{
    ::std::function<return_type(T, P0)> _method;
    T* _object;
    FE::one_arg<P0> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_1_arg() noexcept : _object() {}
    method_with_1_arg(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_1_arg(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_1_arg(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_1_arg(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_1_arg(method_with_1_arg& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_1_arg(method_with_1_arg&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_1_arg& operator=(method_with_1_arg& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_1_arg& operator=(method_with_1_arg&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type, typename P0, typename P1 = P0>
struct function_with_2_args : public task_base
{
    ::std::function<return_type(P0, P1)> _function;
    FE::two_args<P0, P1> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_2_args() noexcept {}
    function_with_2_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_2_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_2_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_2_args(function_with_2_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_2_args(function_with_2_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_2_args& operator=(function_with_2_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_2_args& operator=(function_with_2_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T, typename P0, typename P1 = P0>
struct method_with_2_args : public task_base
{
    ::std::function<return_type(T, P0, P1)> _method;
    T* _object;
    FE::two_args<P0, P1> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_2_args() noexcept : _object() {}
    method_with_2_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_2_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_2_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_2_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_2_args(method_with_2_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_2_args(method_with_2_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_2_args& operator=(method_with_2_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_2_args& operator=(method_with_2_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1>
struct function_with_3_args : public task_base
{
    ::std::function<return_type(P0, P1, P2)> _function;
    FE::three_args<P0, P1, P2> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_3_args() noexcept {}
    function_with_3_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_3_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_3_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_3_args(function_with_3_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_3_args(function_with_3_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_3_args& operator=(function_with_3_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_3_args& operator=(function_with_3_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }

    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1>
struct method_with_3_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2)> _method;
    T* _object;
    FE::three_args<P0, P1, P2> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_3_args() noexcept : _object() {}
    method_with_3_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_3_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_3_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_3_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_3_args(method_with_3_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_3_args(method_with_3_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_3_args& operator=(method_with_3_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_3_args& operator=(method_with_3_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2>
struct function_with_4_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3)> _function;
    FE::four_args<P0, P1, P2, P3> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_4_args() noexcept {}
    function_with_4_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_4_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_4_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_4_args(function_with_4_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_4_args(function_with_4_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_4_args& operator=(function_with_4_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_4_args& operator=(function_with_4_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2>
struct method_with_4_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3)> _method;
    T* _object;
    FE::four_args<P0, P1, P2, P3> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_4_args() noexcept : _object() {}
    method_with_4_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_4_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_4_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_4_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_4_args(method_with_4_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_4_args(method_with_4_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_4_args& operator=(method_with_4_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_4_args& operator=(method_with_4_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3>
struct function_with_5_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4)> _function;
    FE::five_args<P0, P1, P2, P3, P4> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_5_args() noexcept {}
    function_with_5_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_5_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_5_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_5_args(function_with_5_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_5_args(function_with_5_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_5_args& operator=(function_with_5_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_5_args& operator=(function_with_5_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3>
struct method_with_5_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4)> _method;
    T* _object;
    FE::five_args<P0, P1, P2, P3, P4> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_5_args() noexcept : _object() {}
    method_with_5_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_5_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_5_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_5_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_5_args(method_with_5_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_5_args(method_with_5_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_5_args& operator=(method_with_5_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_5_args& operator=(method_with_5_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4>
struct function_with_6_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4, P5)> _function;
    FE::six_args<P0, P1, P2, P3, P4, P5> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_6_args() noexcept {}
    function_with_6_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_6_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_6_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_6_args(function_with_6_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_6_args(function_with_6_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_6_args& operator=(function_with_6_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_6_args& operator=(function_with_6_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4>
struct method_with_6_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4, P5)> _method;
    T* _object;
    FE::six_args<P0, P1, P2, P3, P4, P5> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_6_args() noexcept : _object() {}
    method_with_6_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_6_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_6_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_6_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_6_args(method_with_6_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_6_args(method_with_6_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_6_args& operator=(method_with_6_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_6_args& operator=(method_with_6_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5>
struct function_with_7_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4, P5, P6)> _function;
    FE::seven_args<P0, P1, P2, P3, P4, P5, P6> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_7_args() noexcept {}
    function_with_7_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_7_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_7_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_7_args(function_with_7_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_7_args(function_with_7_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_7_args& operator=(function_with_7_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_7_args& operator=(function_with_7_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5>
struct method_with_7_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4, P5, P6)> _method;
    T* _object;
    FE::seven_args<P0, P1, P2, P3, P4, P5, P6> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_7_args() noexcept : _object() {}
    method_with_7_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_7_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_7_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_7_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_7_args(method_with_7_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_7_args(method_with_7_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_7_args& operator=(method_with_7_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_7_args& operator=(method_with_7_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6>
struct function_with_8_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4, P5, P6, P7)> _function;
    FE::eight_args<P0, P1, P2, P3, P4, P5, P6, P7> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_8_args() noexcept {}
    function_with_8_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_8_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_8_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_8_args(function_with_8_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_8_args(function_with_8_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_8_args& operator=(function_with_8_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_8_args& operator=(function_with_8_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6>
struct method_with_8_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4, P5, P6, P7)> _method;
    T* _object;
    FE::eight_args<P0, P1, P2, P3, P4, P5, P6, P7> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_8_args() noexcept : _object() {}
    method_with_8_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_8_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_8_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_8_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_8_args(method_with_8_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_8_args(method_with_8_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_8_args& operator=(method_with_8_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_8_args& operator=(method_with_8_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7
        );

        return RETURN_TYPE::_NON_VOID;
    }
};





template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7>
struct function_with_9_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4, P5, P6, P7, P8)> _function;
    FE::nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8> _parameters;
    

    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_9_args() noexcept {}
    function_with_9_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_9_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_9_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_9_args(function_with_9_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_9_args(function_with_9_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_9_args& operator=(function_with_9_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_9_args& operator=(function_with_9_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7>
struct method_with_9_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4, P5, P6, P7, P8)> _method;
    T* _object;
    FE::nine_args<P0, P1, P2, P3, P4, P5, P6, P7, P8> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_9_args() noexcept : _object() {}
    method_with_9_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_9_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_9_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_9_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_9_args(method_with_9_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_9_args(method_with_9_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_9_args& operator=(method_with_9_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_9_args& operator=(method_with_9_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8
        );

        return RETURN_TYPE::_NON_VOID;
    }
};




template<typename return_type,
    typename P0, typename P1 = P0,
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4,
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7, typename P9 = P8>
struct function_with_10_args : public task_base
{
    ::std::function<return_type(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> _function;
    FE::ten_args<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> _parameters;


    using function_type = decltype(_function);
    using parameter_package_type = decltype(_parameters);


    constexpr function_with_10_args() noexcept{}
    function_with_10_args(function_type function_p) noexcept : _function(function_p) {}
    function_with_10_args(parameter_package_type parameters_p) noexcept : _parameters(parameters_p) {}
    function_with_10_args(function_type function_p, parameter_package_type parameters_p) noexcept : _function(function_p), _parameters(parameters_p) {}

    function_with_10_args(function_with_10_args& other_ref_p) noexcept : _function(other_ref_p.function_p), _parameters(other_ref_p.parameters_p) {}
    function_with_10_args(function_with_10_args&& rvalue_p) noexcept : _function(rvalue_p.function_p), _parameters(rvalue_p.parameters_p) {}


    _FORCE_INLINE_ function_with_10_args& operator=(function_with_10_args& other_ref_p) noexcept
    {
        this->_function = other_ref_p._function;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ function_with_10_args& operator=(function_with_10_args&& rvalue_p) noexcept
    {
        this->_function = rvalue_p._function;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _function
        (
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8, _parameters._param9
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

template<typename return_type, class T,
    typename P0, typename P1 = P0, 
    typename P2 = P1, typename P3 = P2,
    typename P4 = P3, typename P5 = P4, 
    typename P6 = P5, typename P7 = P6,
    typename P8 = P7, typename P9 = P8>
struct method_with_10_args : public task_base
{
    ::std::function<return_type(T, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> _method;
    T* _object;
    FE::ten_args<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> _parameters;


    using function_type = decltype(_method);
    using parameter_package_type = decltype(_parameters);


    constexpr method_with_10_args() noexcept : _object() {}
    method_with_10_args(function_type function_p) noexcept : _method(function_p), _object() {}
    method_with_10_args(T* const object_ptrc_p) noexcept : _object(object_ptrc_p) {}
    method_with_10_args(parameter_package_type parameters_p) noexcept : _object(), _parameters(parameters_p) {}
    method_with_10_args(function_type rvalue_p, T* const object_ptrc_p, parameter_package_type parameters_p) noexcept : _method(rvalue_p), _object(object_ptrc_p), _parameters(parameters_p) {}

    method_with_10_args(method_with_10_args& other_ref_p) noexcept : _method(other_ref_p._method), _object(other_ref_p._object), _parameters(other_ref_p._parameters) {}
    method_with_10_args(method_with_10_args&& rvalue_p) noexcept : _method(rvalue_p._method), _object(rvalue_p._object), _parameters(rvalue_p._parameters) {}


    _FORCE_INLINE_ method_with_10_args& operator=(method_with_10_args& other_ref_p) noexcept
    {
        this->_method = other_ref_p._method;
        this->_object = other_ref_p._object;
        this->_parameters = other_ref_p._parameters;
        return *this;
    }

    _FORCE_INLINE_ method_with_10_args& operator=(method_with_10_args&& rvalue_p) noexcept
    {
        this->_method = rvalue_p._method;
        this->_object = rvalue_p._object;
        this->_parameters = rvalue_p._parameters;
        return *this;
    }


    _NODISCARD_ virtual RETURN_TYPE execute(void* out_return_ptr_p, const char* const typename_str_ptrc_p) noexcept override
    {
        FE_ASSERT(!::FE::algorithm::string::string_comparison<char>(typeid(return_type).name(), typename_str_ptrc_p), "ERROR: an ilegal type of data was passed");

        *((return_type*)out_return_ptr_p) = _method
        (
            *_object,
            _parameters._param0, _parameters._param1,
            _parameters._param2, _parameters._param3,
            _parameters._param4, _parameters._param5,
            _parameters._param6, _parameters._param7,
            _parameters._param8, _parameters._param9
        );

        return RETURN_TYPE::_NON_VOID;
    }
};

END_NAMESPACE
#endif // !_FE_CORE_TASK_HXX_
