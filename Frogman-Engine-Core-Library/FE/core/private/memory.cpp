#include "memory.hpp"


BEGIN_NAMESPACE(FE)


#if _AVX512_ == true
void memcpy_with_avx512(void* const dest_ptrc_p, const void* const source_ptrc_p, size_t count_to_copy_p, size_t bytes_to_copy_p) noexcept
{
    typedef int16 bool16;
    constexpr static auto _BOTH_ARE_ALIGNED_ = 2;
    constexpr static auto _BOTH_ARE_UNALIGNED_ = 0;


    __m512i* const l_dest_ptrc = reinterpret_cast<__m512i*>(dest_ptrc_p);
    const __m512i* const l_source_ptrc = reinterpret_cast<const __m512i* const>(source_ptrc_p);

    bool16 l_is_dest_ptrc_p_aligned = (MODULO_BY_64(reinterpret_cast<uintptr_t>(dest_ptrc_p)) == 0);
    bool16 l_is_source_ptrc_p_aligned = (MODULO_BY_64(reinterpret_cast<uintptr_t>(source_ptrc_p)) == 0);

    size_t l_bytes_to_set = count_to_copy_p * bytes_to_copy_p;
    size_t l_leftover_bytes = MODULO_BY_64(l_bytes_to_set);
    size_t l_bytes_to_be_setted_with_avx512 = (l_bytes_to_set - l_leftover_bytes);

    var::size_t l_avx_operation_count = 0;
    if (l_bytes_to_be_setted_with_avx512 != 0)
    {
        l_avx_operation_count = DIVIDE_BY_64(l_bytes_to_be_setted_with_avx512);

        switch (l_is_dest_ptrc_p_aligned + l_is_source_ptrc_p_aligned)
        {
        case _BOTH_ARE_ALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm512_store_si512(l_dest_ptrc + executed_operation_count, _mm512_load_si512(l_source_ptrc + executed_operation_count));
            }

            break;


        case _BOTH_ARE_UNALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm512_storeu_si512(l_dest_ptrc + executed_operation_count, _mm512_loadu_si512(l_source_ptrc + executed_operation_count));
            }

            break;


        default:

            if (l_is_dest_ptrc_p_aligned == _TRUE_) // l_is_source_ptrc_p_aligned is always false at this point.
            {
                for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
                {
                    _mm512_store_si512(l_dest_ptrc + executed_operation_count, _mm512_loadu_si512(l_source_ptrc + executed_operation_count));
                }
            }
            else // l_is_source_ptrc_p_aligned is always true at this point.
            {
                for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
                {
                    _mm512_storeu_si512(l_dest_ptrc + executed_operation_count, _mm512_load_si512(l_source_ptrc + executed_operation_count));
                }
            }

            break;
        }
    }

    switch (l_leftover_bytes)
    {
    case 0:
        return;

    default:
        ::std::memcpy(l_dest_ptrc + l_avx_operation_count, l_source_ptrc + l_avx_operation_count, l_leftover_bytes);
        break;
    }
}

void memset_with_avx512(void* const dest_ptrc_p, int8 value_p, length_t count_to_set_p, size_t bytes_to_set_p) noexcept
{
    constexpr static auto _ALIGNED_ = 0;


    __m512i* const l_dest_ptrc = reinterpret_cast<__m512i*>(dest_ptrc_p);
    const __m512i l_value_to_be_assigned = _mm512_set1_epi8(value_p);

    size_t l_bytes_to_set = count_to_set_p * bytes_to_set_p;
    size_t l_leftover_bytes = MODULO_BY_64(l_bytes_to_set);
    size_t l_bytes_to_be_setted_with_avx512 = (l_bytes_to_set - l_leftover_bytes);

    var::size_t l_avx_operation_count = 0;
    if (l_bytes_to_be_setted_with_avx512 != 0)
    {
        l_avx_operation_count = DIVIDE_BY_64(l_bytes_to_be_setted_with_avx512);

        switch (MODULO_BY_64(reinterpret_cast<uintptr_t>(dest_ptrc_p)))
        {
        case _ALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm512_store_si512(l_dest_ptrc + executed_operation_count, l_value_to_be_assigned);
            }

            break;


        default:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm512_storeu_si512(l_dest_ptrc + executed_operation_count, l_value_to_be_assigned);
            }

            break;
        }
    }

    switch (l_leftover_bytes)
    {
    case 0:
        return;

    default:
        ::std::memset(l_dest_ptrc + l_avx_operation_count, value_p, l_leftover_bytes);
        break;
    }
}

#elif _AVX_ == true
void memcpy_with_avx(void* const dest_ptrc_p, const void* const source_ptrc_p, size_t count_to_copy_p, size_t bytes_to_copy_p) noexcept
{
    typedef int16 bool16;
    constexpr static auto _BOTH_ARE_ALIGNED_ = 2;
    constexpr static auto _BOTH_ARE_UNALIGNED_ = 0;


    __m256i* const l_dest_ptrc = reinterpret_cast<__m256i*>(dest_ptrc_p);
    const __m256i* const l_source_ptrc = reinterpret_cast<const __m256i* const>(source_ptrc_p);

    bool16 l_is_dest_ptrc_p_aligned = (MODULO_BY_32(reinterpret_cast<uintptr_t>(dest_ptrc_p)) == 0);
    bool16 l_is_source_ptrc_p_aligned = (MODULO_BY_32(reinterpret_cast<uintptr_t>(source_ptrc_p)) == 0);

    size_t l_bytes_to_set = count_to_copy_p * bytes_to_copy_p;
    size_t l_leftover_bytes = MODULO_BY_32(l_bytes_to_set);
    size_t l_bytes_to_be_setted_with_avx = (l_bytes_to_set - l_leftover_bytes);

    var::size_t l_avx_operation_count = 0;
    if (l_bytes_to_be_setted_with_avx != 0)
    {
        l_avx_operation_count = DIVIDE_BY_32(l_bytes_to_be_setted_with_avx);

        switch (l_is_dest_ptrc_p_aligned + l_is_source_ptrc_p_aligned)
        {
        case _BOTH_ARE_ALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm256_store_si256(l_dest_ptrc + executed_operation_count, _mm256_load_si256(l_source_ptrc + executed_operation_count));
            }

            break;


        case _BOTH_ARE_UNALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm256_storeu_si256(l_dest_ptrc + executed_operation_count, _mm256_loadu_si256(l_source_ptrc + executed_operation_count));
            }

            break;


        default:

            if (l_is_dest_ptrc_p_aligned == _TRUE_) // l_is_source_ptrc_p_aligned is always false at this point.
            {
                for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
                {
                    _mm256_store_si256(l_dest_ptrc + executed_operation_count, _mm256_loadu_si256(l_source_ptrc + executed_operation_count));
                }
            }
            else // l_is_source_ptrc_p_aligned is always true at this point.
            {
                for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
                {
                    _mm256_storeu_si256(l_dest_ptrc + executed_operation_count, _mm256_load_si256(l_source_ptrc + executed_operation_count));
                }
            }

            break;
        }
    }

    switch (l_leftover_bytes)
    {
        case 0:
            return;

        default:
            ::std::memcpy(l_dest_ptrc + l_avx_operation_count, l_source_ptrc + l_avx_operation_count, l_leftover_bytes);
            break;
    }
}

void memset_with_avx(void* const dest_ptrc_p, int8 value_p, length_t count_to_set_p, size_t bytes_to_set_p) noexcept
{
    constexpr static auto _ALIGNED_ = 0;


	__m256i* const l_dest_ptrc = reinterpret_cast<__m256i*>(dest_ptrc_p);
	const __m256i l_value_to_be_assigned = _mm256_set1_epi8(value_p);

	size_t l_bytes_to_set = count_to_set_p * bytes_to_set_p;
	size_t l_leftover_bytes = MODULO_BY_32(l_bytes_to_set);
	size_t l_bytes_to_be_setted_with_avx = (l_bytes_to_set - l_leftover_bytes);

	var::size_t l_avx_operation_count = 0;
    if (l_bytes_to_be_setted_with_avx != 0)
    {
        l_avx_operation_count = DIVIDE_BY_32(l_bytes_to_be_setted_with_avx);

        switch (MODULO_BY_32( reinterpret_cast<uintptr_t>(dest_ptrc_p) ))
        {
        case _ALIGNED_:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm256_store_si256(l_dest_ptrc + executed_operation_count, l_value_to_be_assigned);
            }

            break;


        default:

            for (var::size_t executed_operation_count = 0; executed_operation_count < l_avx_operation_count; ++executed_operation_count)
            {
                _mm256_storeu_si256(l_dest_ptrc + executed_operation_count, l_value_to_be_assigned);
            }

            break;
        }
    }

	switch (l_leftover_bytes)
	{
	case 0:
		return;

	default:
		::std::memset(l_dest_ptrc + l_avx_operation_count, value_p, l_leftover_bytes);
		break;
	}
}

#endif

var::boolean memcmp(const void* left_bytes_ptr_p, size_t left_bytes_size_p, const void* right_bytes_ptr_p, size_t right_bytes_size_p) noexcept
{
    if (left_bytes_size_p != right_bytes_size_p)
    {
        return false;
    }

    std::size_t l_leftover_bytes = MODULO_BY_8(left_bytes_size_p);
    
    var::BYTE_PTR l_left_bytes_ptr = (var::BYTE_PTR)left_bytes_ptr_p;
    var::BYTE_PTR l_right_bytes_ptr = (var::BYTE_PTR)right_bytes_ptr_p;

    for (std::size_t i = 0; i < l_leftover_bytes; ++i)
    {
        if (*l_left_bytes_ptr != *l_right_bytes_ptr)
        {
            return false;
        }

        ++l_left_bytes_ptr;
        ++l_right_bytes_ptr;
    }


    std::size_t l_counts_to_jump_8_bytes = DIVIDE_BY_8(left_bytes_size_p);

    var::QWORD_PTR l_left_qword_ptr = (var::QWORD_PTR)l_left_bytes_ptr;
    var::QWORD_PTR l_right_qword_ptr = (var::QWORD_PTR)l_right_bytes_ptr;

    for (var::size_t i = 0; ((i < l_counts_to_jump_8_bytes) && (*l_left_qword_ptr == *l_right_qword_ptr)); ++i)
    {
        ++l_left_qword_ptr;
        ++l_right_qword_ptr;
    }

    if ((var::size_t)((var::BYTE_PTR)l_left_qword_ptr - (var::BYTE_PTR)left_bytes_ptr_p) == left_bytes_size_p)
    {
        return true;
    }

    return false;
}

END_NAMESPACE