#ifndef _FE_CORE_PRIVATE_MEMORY_HPP_
#define _FE_CORE_PRIVATE_MEMORY_HPP_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#ifdef UNALIGNED_MEMSET
#error UNALIGNED_MEMSET is a reserved macro keyword
#endif
#ifdef ALIGNED_MEMSET
#error ALIGNED_MEMSET is a reserved macro keyword
#endif
#ifdef UNALIGNED_MEMCPY
#error UNALIGNED_MEMCPY is a reserved macro keyword
#endif
#ifdef ALIGNED_MEMCPY
#error ALIGNED_MEMCPY is a reserved macro keyword
#endif
#define DIVIDE_BY_2(input_p) ((input_p) >> 1)
#define DIVIDE_BY_4(input_p) ((input_p) >> 2)
#define DIVIDE_BY_8(input_p) ((input_p) >> 3)
#define DIVIDE_BY_16(input_p) ((input_p) >> 4)
#define DIVIDE_BY_32(input_p) ((input_p) >> 5)
#define DIVIDE_BY_64(input_p) ((input_p) >> 6)
#define DIVIDE_BY_128(input_p) ((input_p) >> 7)

#define MODULO_BY_2(input_p) ((input_p) & 1)
#define MODULO_BY_4(input_p) ((input_p) & 3)
#define MODULO_BY_8(input_p) ((input_p) & 7)
#define MODULO_BY_16(input_p) ((input_p) & 15)
#define MODULO_BY_32(input_p) ((input_p) & 31)
#define MODULO_BY_64(input_p) ((input_p) & 63)
#define MODULO_BY_128(input_p) ((input_p) & 127)
#define ABS(x) ((x < 0) ? x * -1 : x)
#include <FE/core/prerequisite_symbols.h>
#include <immintrin.h>
#ifdef __AVX__
#define _AVX_ true
#else
#define _AVX_ false
#endif

#ifdef __AVX512F__
#define _AVX512_ true
#else
#define _AVX512_ false
#endif




BEGIN_NAMESPACE(FE)


#if _AVX512_ == true
_FORCE_INLINE_ void unaligned_memset_with_avx512(void* const dest_ptrc_p, int8 value_p, size_t total_bytes_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(total_bytes_p == 0, "ERROR: element_bytes_p is 0.");

    __m512i* l_m512i_dest_ptr = static_cast<__m512i*>(dest_ptrc_p);
    const __m512i l_m512i_value_to_be_assigned = _mm512_set1_epi8(value_p);

    var::size_t l_leftover_bytes = MODULO_BY_64(total_bytes_p);
    size_t l_avx_operation_count = MODULO_BY_64(total_bytes_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm512_storeu_si512(l_m512i_dest_ptr, l_m512i_value_to_be_assigned);
        ++l_m512i_dest_ptr;
    }

    if (l_leftover_bytes >= 16)
    {
        memset(l_m512i_dest_ptr, value_p, l_leftover_bytes);
        return;
    }

    var::byte* l_byte_ptr = reinterpret_cast<var::byte*>(l_m512i_dest_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_byte_ptr = value_p;
        ++l_byte_ptr;
    }
}

_FORCE_INLINE_ void aligned_memset_with_avx512(void* const dest_ptrc_p, int8 value_p, size_t total_bytes_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(total_bytes_p == 0, "ERROR: element_bytes_p is 0.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(dest_ptrc_p) % 64) != 0, "ERROR: dest_ptrc_p is not aligned by 64.");

    __m512i* l_m512i_dest_ptr = static_cast<__m512i*>(dest_ptrc_p);
    const __m512i l_m512i_value_to_be_assigned = _mm512_set1_epi8(value_p);

    var::size_t l_leftover_bytes = MODULO_BY_64(total_bytes_p);
    size_t l_avx_operation_count = MODULO_BY_64(total_bytes_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm512_store_si512(l_m512i_dest_ptr, l_m512i_value_to_be_assigned);
        ++l_m512i_dest_ptr;
    }

    if (l_leftover_bytes >= 16)
    {
        memset(l_m512i_dest_ptr, value_p, l_leftover_bytes);
        return;
    }

    var::byte* l_byte_ptr = reinterpret_cast<var::byte*>(l_m512i_dest_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_byte_ptr = value_p;
        ++l_byte_ptr;
    }
}


_FORCE_INLINE_ void unaligned_memcpy_with_avx512(void* const dest_ptrc_p, const void* const source_ptrc_p, FE::size_t bytes_to_copy_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(bytes_to_copy_p == 0, "ERROR: element_bytes_p is 0.");

    __m512i* l_m512i_dest_ptr = static_cast<__m512i*>(dest_ptrc_p);
    const __m512i* l_m512i_source_ptr = static_cast<const __m512i*>(source_ptrc_p);

    var::size_t l_leftover_bytes = MODULO_BY_64(bytes_to_copy_p);
    size_t l_avx_operation_count = MODULO_BY_64(bytes_to_copy_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm512_storeu_si512(l_m512i_dest_ptr, _mm512_loadu_si512(l_m512i_source_ptr));
        ++l_m512i_dest_ptr;
        ++l_m512i_source_ptr;
    }

    if (l_leftover_bytes >= 16)
    {
        memcpy(l_m512i_dest_ptr, l_m512i_source_ptr, l_leftover_bytes);
        return;
    }

    var::byte* l_dest_byte_ptr = reinterpret_cast<var::byte*>(l_m512i_dest_ptr);
    byte* l_source_byte_ptr = reinterpret_cast<byte*>(l_m512i_source_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_dest_byte_ptr = *l_source_byte_ptr;
        ++l_dest_byte_ptr;
        ++l_source_byte_ptr;
    }
}

_FORCE_INLINE_ void aligned_memcpy_with_avx512(void* const dest_ptrc_p, const void* const source_ptrc_p, FE::size_t bytes_to_copy_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(bytes_to_copy_p == 0, "ERROR: element_bytes_p is 0.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(dest_ptrc_p) % 64) != 0, "ERROR: dest_ptrc_p is not aligned by 64.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(source_ptrc_p) % 64) != 0, "ERROR: source_ptrc_p is not aligned by 64.");

    __m512i* l_m512i_dest_ptr = static_cast<__m512i*>(dest_ptrc_p);
    const __m512i* l_m512i_source_ptr = static_cast<const __m512i*>(source_ptrc_p);

    var::size_t l_leftover_bytes = MODULO_BY_64(bytes_to_copy_p);
    size_t l_avx_operation_count = MODULO_BY_64(bytes_to_copy_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm512_store_si512(l_m512i_dest_ptr, _mm512_load_si512(l_m512i_source_ptr));
        ++l_m512i_dest_ptr;
        ++l_m512i_source_ptr;
    }

    if (l_leftover_bytes >= 16)
    {
        memcpy(l_m512i_dest_ptr, l_m512i_source_ptr, l_leftover_bytes);
        return;
    }

    var::byte* l_dest_byte_ptr = reinterpret_cast<var::byte*>(l_m512i_dest_ptr);
    byte* l_source_byte_ptr = reinterpret_cast<byte*>(l_m512i_source_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_dest_byte_ptr = *l_source_byte_ptr;
        ++l_dest_byte_ptr;
        ++l_source_byte_ptr;
    }
}
#elif _AVX_ == true
_FORCE_INLINE_ void unaligned_memset_with_avx(void* const dest_ptrc_p, int8 value_p, size_t total_bytes_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(total_bytes_p == 0, "ERROR: element_bytes_p is 0.");

    __m256i* l_m256i_dest_ptr = static_cast<__m256i*>(dest_ptrc_p);
    const __m256i l_m256i_value_to_be_assigned = _mm256_set1_epi8(value_p);

    var::size_t l_leftover_bytes = MODULO_BY_32(total_bytes_p);
    size_t l_avx_operation_count = DIVIDE_BY_32(total_bytes_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm256_storeu_si256(l_m256i_dest_ptr, l_m256i_value_to_be_assigned);
        ++l_m256i_dest_ptr;
    }

    __m128i* l_m128i_dest_ptr = reinterpret_cast<__m128i*>(l_m256i_dest_ptr);
    if (l_leftover_bytes >= 16)
    {
        _mm_storeu_si128(l_m128i_dest_ptr, _mm_set1_epi8(value_p));
        ++l_m128i_dest_ptr;
        l_leftover_bytes -= 16;
    }
    var::byte* l_byte_ptr = reinterpret_cast<var::byte*>(l_m128i_dest_ptr);

    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_byte_ptr = value_p;
        ++l_byte_ptr;
    }
}

_FORCE_INLINE_ void aligned_memset_with_avx(void* const dest_ptrc_p, int8 value_p, size_t total_bytes_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(total_bytes_p == 0, "ERROR: element_bytes_p is 0.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(dest_ptrc_p) % 32) != 0, "ERROR: dest_ptrc_p is not aligned by 32.");

    __m256i* l_m256i_dest_ptr = static_cast<__m256i*>(dest_ptrc_p);
    const __m256i l_m256i_value_to_be_assigned = _mm256_set1_epi8(value_p);

    var::size_t l_leftover_bytes = MODULO_BY_32(total_bytes_p);
    size_t l_avx_operation_count = DIVIDE_BY_32(total_bytes_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm256_store_si256(l_m256i_dest_ptr, l_m256i_value_to_be_assigned);
        ++l_m256i_dest_ptr;
    }

    __m128i* l_m128i_dest_ptr = reinterpret_cast<__m128i*>(l_m256i_dest_ptr);
    if (l_leftover_bytes >= 16)
    {
        _mm_store_si128(l_m128i_dest_ptr, _mm_set1_epi8(value_p));
        ++l_m128i_dest_ptr;
        l_leftover_bytes -= 16;
    }
    var::byte* l_byte_ptr = reinterpret_cast<var::byte*>(l_m128i_dest_ptr);

    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_byte_ptr = value_p;
        ++l_byte_ptr;
    }
}


_FORCE_INLINE_ void unaligned_memcpy_with_avx(void* const dest_ptrc_p, const void* const source_ptrc_p, FE::size_t bytes_to_copy_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(bytes_to_copy_p == 0, "ERROR: element_bytes_p is 0.");

    __m256i* l_m256i_dest_ptr = static_cast<__m256i*>(dest_ptrc_p);
    const __m256i* l_m256i_source_ptr = static_cast<const __m256i*>(source_ptrc_p);

    var::size_t l_leftover_bytes = MODULO_BY_32(bytes_to_copy_p);
    size_t l_avx_operation_count = DIVIDE_BY_32(bytes_to_copy_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm256_storeu_si256(l_m256i_dest_ptr, _mm256_loadu_si256(l_m256i_source_ptr));
        ++l_m256i_dest_ptr;
        ++l_m256i_source_ptr;
    }

    __m128i* l_m128i_dest_ptr = reinterpret_cast<__m128i*>(l_m256i_dest_ptr);
    const __m128i* l_m128i_source_ptr = reinterpret_cast<const __m128i*>(l_m256i_source_ptr);
    if (l_leftover_bytes >= 16)
    {
        _mm_storeu_si128(l_m128i_dest_ptr, _mm_loadu_si128(l_m128i_source_ptr));
        ++l_m128i_dest_ptr;
        ++l_m128i_source_ptr;
        l_leftover_bytes -= 16;
    }

    var::byte* l_dest_byte_ptr = reinterpret_cast<var::byte*>(l_m128i_dest_ptr);
    byte* l_source_byte_ptr = reinterpret_cast<byte*>(l_m128i_source_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_dest_byte_ptr = *l_source_byte_ptr;
        ++l_dest_byte_ptr;
        ++l_source_byte_ptr;
    }
}

_FORCE_INLINE_ void aligned_memcpy_with_avx(void* const dest_ptrc_p, const void* const source_ptrc_p, FE::size_t bytes_to_copy_p) noexcept
{
    FE_ASSERT(dest_ptrc_p == nullptr, "ERROR: dest_ptrc_p is nullptr.");
    FE_ASSERT(bytes_to_copy_p == 0, "ERROR: element_bytes_p is 0.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(dest_ptrc_p) % 32) != 0, "ERROR: dest_ptrc_p is not aligned by 32.");
    FE_ASSERT((reinterpret_cast<uintptr_t>(source_ptrc_p) % 32) != 0, "ERROR: source_ptrc_p is not aligned by 32.");

    __m256i* l_m256i_dest_ptr = static_cast<__m256i*>(dest_ptrc_p);
    const __m256i* l_m256i_source_ptr = static_cast<const __m256i*>(source_ptrc_p);

    var::size_t l_leftover_bytes = MODULO_BY_32(bytes_to_copy_p);
    size_t l_avx_operation_count = DIVIDE_BY_32(bytes_to_copy_p - l_leftover_bytes);

    for (var::size_t executed_operation_count = 0; executed_operation_count != l_avx_operation_count; ++executed_operation_count)
    {
        _mm256_store_si256(l_m256i_dest_ptr, _mm256_load_si256(l_m256i_source_ptr));
        ++l_m256i_dest_ptr;
        ++l_m256i_source_ptr;
    }

    __m128i* l_m128i_dest_ptr = reinterpret_cast<__m128i*>(l_m256i_dest_ptr);
    const __m128i* l_m128i_source_ptr = reinterpret_cast<const __m128i*>(l_m256i_source_ptr);
    if (l_leftover_bytes >= 16)
    {
        _mm_store_si128(l_m128i_dest_ptr, _mm_load_si128(l_m128i_source_ptr));
        ++l_m128i_dest_ptr;
        ++l_m128i_source_ptr;
        l_leftover_bytes -= 16;
    }

    var::byte* l_dest_byte_ptr = reinterpret_cast<var::byte*>(l_m128i_dest_ptr);
    byte* l_source_byte_ptr = reinterpret_cast<byte*>(l_m128i_source_ptr);
    for (var::size_t i = 0; i != l_leftover_bytes; ++i)
    {
        *l_dest_byte_ptr = *l_source_byte_ptr;
        ++l_dest_byte_ptr;
        ++l_source_byte_ptr;
    }
}
#endif


#if _AVX512_ == true
#define UNALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::FE::unaligned_memset_with_avx512(dest_ptrc_p, value_p, total_bytes_p)
#define ALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::FE::aligned_memset_with_avx512(dest_ptrc_p, value_p, total_bytes_p)
#define UNALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::FE::unaligned_memcpy_with_avx512(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)
#define ALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::FE::aligned_memcpy_with_avx512(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)

#elif _AVX_ == true
#define UNALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::FE::unaligned_memset_with_avx(dest_ptrc_p, value_p, total_bytes_p)
#define ALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::FE::aligned_memset_with_avx(dest_ptrc_p, value_p, total_bytes_p)
#define UNALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::FE::unaligned_memcpy_with_avx(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)
#define ALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::FE::aligned_memcpy_with_avx(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)

#else
#define UNALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::std::memset(dest_ptrc_p, value_p, total_bytes_p)
#define ALIGNED_MEMSET(dest_ptrc_p, value_p, total_bytes_p) ::std::memset(dest_ptrc_p, value_p, total_bytes_p)
#define UNALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::std::memcpy(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)
#define ALIGNED_MEMCPY(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p) ::std::memcpy(dest_ptrc_p, source_ptrc_p, bytes_to_copy_p)
#endif


_FORCE_INLINE_ void unaligned_memcpy(void* const dest_memblock_ptrc_p, length_t dest_length_p, size_t dest_element_bytes_p, const void* const source_memblock_ptrc_p, length_t source_length_p, size_t source_element_bytes_p) noexcept
{
    ABORT_IF(dest_memblock_ptrc_p == nullptr, "ERROR: dest_memblock_ptrc_p is nullptr.");
    ABORT_IF(source_memblock_ptrc_p == nullptr, "ERROR: source_memblock_ptrc_p is nullptr.");

    ABORT_IF(dest_length_p == 0, "ERROR: dest_length_p is 0.");
    ABORT_IF(dest_element_bytes_p == 0, "ERROR: dest_bytes_p is 0.");
    ABORT_IF(source_element_bytes_p == 0, "ERROR: source_bytes_p is 0.");

    size_t l_source_size = source_element_bytes_p * source_length_p;
    size_t l_dest_size = dest_element_bytes_p * dest_length_p;

    if (l_source_size >= l_dest_size)
    {
        UNALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_dest_size);
    }
    else
    {
        UNALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_source_size);
    }
}

_FORCE_INLINE_ void aligned_memcpy(void* const dest_memblock_ptrc_p, length_t dest_length_p, size_t dest_element_bytes_p, const void* const source_memblock_ptrc_p, length_t source_length_p, size_t source_element_bytes_p) noexcept
{
    ABORT_IF(dest_memblock_ptrc_p == nullptr, "ERROR: dest_memblock_ptrc_p is nullptr.");
    ABORT_IF(source_memblock_ptrc_p == nullptr, "ERROR: source_memblock_ptrc_p is nullptr.");

    ABORT_IF(dest_length_p == 0, "ERROR: dest_length_p is 0.");
    ABORT_IF(dest_element_bytes_p == 0, "ERROR: dest_bytes_p is 0.");
    ABORT_IF(source_element_bytes_p == 0, "ERROR: source_bytes_p is 0.");

    size_t l_source_size = source_element_bytes_p * source_length_p;
    size_t l_dest_size = dest_element_bytes_p * dest_length_p;

    if (l_source_size >= l_dest_size)
    {
        ALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_dest_size);
    }
    else
    {
        ALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, l_source_size);
    }
}

_FORCE_INLINE_ void unaligned_memcpy(void* const dest_memblock_ptrc_p, size_t dest_bytes_p, const void* const source_memblock_ptrc_p, size_t source_bytes_p) noexcept
{
    ABORT_IF(dest_memblock_ptrc_p == nullptr, "ERROR: dest_memblock_ptrc_p is nullptr.");
    ABORT_IF(source_memblock_ptrc_p == nullptr, "ERROR: source_memblock_ptrc_p is nullptr.");

    ABORT_IF(dest_bytes_p == 0, "ERROR: dest_bytes_p is 0.");
    ABORT_IF(source_bytes_p == 0, "ERROR: source_bytes_p is 0.");

    if (source_bytes_p >= dest_bytes_p)
    {
        UNALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, dest_bytes_p);
    }
    else
    {
        UNALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, source_bytes_p);
    }
}

_FORCE_INLINE_ void aligned_memcpy(void* const dest_memblock_ptrc_p, size_t dest_bytes_p, const void* const source_memblock_ptrc_p, size_t source_bytes_p) noexcept
{
    ABORT_IF(dest_memblock_ptrc_p == nullptr, "ERROR: dest_memblock_ptrc_p is nullptr.");
    ABORT_IF(source_memblock_ptrc_p == nullptr, "ERROR: source_memblock_ptrc_p is nullptr.");

    ABORT_IF(dest_bytes_p == 0, "ERROR: dest_bytes_p is 0.");
    ABORT_IF(source_bytes_p == 0, "ERROR: source_bytes_p is 0.");

    if (source_bytes_p >= dest_bytes_p)
    {
        ALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, dest_bytes_p);
    }
    else
    {
        ALIGNED_MEMCPY(dest_memblock_ptrc_p, source_memblock_ptrc_p, source_bytes_p);
    }
}




enum struct MEMORY_SIZE_SCALABILITY : boolean
{
    _STATICALLY_SIZED = false,
    _DYNAMICALLY_SIZED = true
};

enum struct MEMORY_ERROR_1XX : int16
{
    _NONE = 0,
    _ERROR_INVALID_SIZE = 100,
    _FATAL_ERROR_NULLPTR = 101,
    _FATAL_ERROR_OUT_OF_RANGE = 102
};

struct total_memory_utilization_data
{
	var::size_t _global_total_bytes = 0;
	var::size_t _thread_local_total_bytes = 0;

	var::size_t _global_total_bytes_by_type = 0;
	var::size_t _thread_local_total_bytes_by_type = 0;
};

struct global_memory_utilization
{
	var::size_t _global_total_bytes = 0;
	var::size_t _thread_local_total_bytes = 0;
};

struct type_memory_utilization
{
	var::size_t _global_total_bytes_by_type = 0;
	var::size_t _thread_local_total_bytes_by_type = 0;
};


_MAYBE_UNUSED_ constexpr uint8 _BYTE_SIZE_ = 1;
_MAYBE_UNUSED_ constexpr uint8 _WORD_SIZE_ = 2;
_MAYBE_UNUSED_ constexpr uint8 _DWORD_SIZE_ = 4;
_MAYBE_UNUSED_ constexpr uint8 _QWORD_SIZE_ = 8;


// it is used when reserving memory of Frogman Engine data containers.
struct reserve final
{
	var::uint64 _length = 0;
};

// it contains memory padding size.
struct align_null final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 0;
};

// it contains memory padding size.
struct align_2bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 2;
};

// it contains memory padding size.
struct align_4bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 4;
};

// it contains memory padding size.
struct align_8bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 8;
};

// it contains memory padding size.
struct align_16bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 16;
};

// it contains memory padding size.
struct align_32bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 32;
};

// it contains memory padding size.
struct align_64bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 64;
};

// it contains memory padding size.
struct align_128bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 128;
};


// it contains memory padding size.
template<uint64 padding_size_p>
struct align_custom_bytes final
{
	_MAYBE_UNUSED_ static constexpr inline uint16 s_size = padding_size_p;
};


template <typename T, class alignment = align_null>
struct alignas(alignment::s_size) align
{
	T _data;
};


END_NAMESPACE
#endif
