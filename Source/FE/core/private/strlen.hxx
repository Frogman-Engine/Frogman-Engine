#ifndef _FE_CORE_PRIVATE_STRLEN_HXX_
#define _FE_CORE_PRIVATE_STRLEN_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.hxx>


namespace FE::internal
{
    template<typename CharT>
    _NODISCARD_ _FORCE_INLINE_ _CONSTEXPR17_ uint64 strlen(const CharT* const str_p) noexcept
    {
        const CharT* l_iterator_pointer = str_p;

        if (*str_p == _FE_NULL_)
        {
            return 0;
        }

        while (*(++l_iterator_pointer) != _FE_NULL_) {}

        return (l_iterator_pointer - str_p);
    }
}

#endif