﻿#ifndef _MEMORY_HXX_
#define _MEMORY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <immintrin.h>


#define DIVIDE_BY_8(input_p) (input_p >> 3)
#define DIVIDE_BY_32(input_p) (input_p >> 5)
#define DIVIDE_BY_64(input_p) (input_p >> 6)

#define MODULO_BY_8(input_p) (input_p & 7)
#define MODULO_BY_32(input_p) (input_p & 31)
#define MODULO_BY_64(input_p) (input_p & 63)


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

#if _AVX_ == true
void memcpy_with_avx(void* const dest_ptrc_p, const void* const source_ptrc_p, size_t count_to_copy_p, size_t bytes_to_copy_p) noexcept;
void memset_with_avx(void* const dest_ptrc_p, int8 value_p, length_t count_to_set_p, size_t bytes_to_set_p) noexcept;
#endif

#if _AVX512_ == true
void memcpy_with_avx512(void* const dest_ptrc_p, const void* const source_ptrc_p, size_t count_to_copy_p, size_t bytes_to_copy_p) noexcept;
void memset_with_avx512(void* const dest_ptrc_p, int8 value_p, length_t count_to_set_p, size_t bytes_to_set_p) noexcept;
#endif

var::boolean memcmp(const void* left_bytes_ptr_p, size_t left_bytes_size_p, const void* right_bytes_ptr_p, size_t right_bytes_size_p) noexcept;

enum struct MEMORY_ERROR_1XX : int16
{
	_NONE = 0,
	_ERROR_INVALID_SIZE = -100,
	_FATAL_ERROR_OUT_OF_RANGE = -101,
	_FATAL_ERROR_NULLPTR = -102
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


// it is used when reserving memory of Frogman Engine API data containers.
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
	_MAYBE_UNUSED_ static constexpr uint16 s_size = padding_size_p;
};


template <typename T, class padding_size = align_null>
struct alignas(padding_size::s_size) align
{
	T _content;
};


END_NAMESPACE
#endif
