#ifndef _FE_CORE_PRIVATE_STRLEN_H_
#define _FE_CORE_PRIVATE_STRLEN_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/types.hxx>


namespace FE::internal
{
    template<typename char_type>
    _NODISCARD_ _CONSTEXPR_ _FORCE_INLINE_ FE::var::uint64 strlen(const char_type* const str_ptrc_p) noexcept
    {
        const char_type* l_iterator_ptr = str_ptrc_p;

        if (*str_ptrc_p == _NULL_)
        {
            return 0;
        }

        while (*(++l_iterator_ptr) != _NULL_) _LIKELY_ {}

        return (l_iterator_ptr - str_ptrc_p);
    }
}

#endif