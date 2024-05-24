// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/type_traits.hxx>

// std
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>


/*
ls: lists all folders in the current working directory
ls filename: checks the presence of files with the specified name.
*/
int main()
{
    _MAYBE_UNUSED_ FE::remove_const_reference<const int&>::type i = 0;

    _MAYBE_UNUSED_ FE::conditional_type<false, int, float>::type false_type = 0.0f;

    assert(FE::is_c_style_constant_string<const char*>::value == true);
    assert(FE::is_char<FE::UTF16>::value == true);
    assert(FE::is_boolean<FE::boolean>::value == true);
    assert(FE::is_primitive<FE::float64>::value == true);
    assert(FE::is_numeric<FE::int64>::value == true);
    assert(FE::is_trivial<std::string>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL);
    assert(FE::is_string_class<std::string_view>::value == true);

    std::cout << "Compilation test of FE.core.type_traits source code is successful.\n";
    return 0;
}






