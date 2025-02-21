﻿#ifndef _FE_CORE_MEMORY_HXX_
#define _FE_CORE_MEMORY_HXX_
/*
Copyright © from 2022 to present, UNKNOWN STRYKER. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifdef FE_UNALIGNED_MEMZERO
	#error FE_UNALIGNED_MEMSET is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_ALIGNED_MEMZERO
	#error FE_ALIGNED_MEMSET is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_UNALIGNED_MEMCPY
	#error FE_UNALIGNED_MEMCPY is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_ALIGNED_MEMCPY
	#error FE_ALIGNED_MEMCPY is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_DEST_ALIGNED_MEMCPY
	#error FE_DEST_ALIGNED_MEMCPY is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_SOURCE_ALIGNED_MEMCPY
	#error FE_SOURCE_ALIGNED_MEMCPY is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_ALIGNED_MEMMOVE
	#error FE_ALIGNED_MEMMOVE is a reserved Frogman Engine macro keyword.
#endif
#ifdef FE_UNALIGNED_MEMMOVE
	#error FE_UNALIGNED_MEMMOVE is a reserved Frogman Engine macro keyword.
#endif




#ifdef __FE_DIVIDE_BY_2
	#error __FE_DIVIDE_BY_2 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_2(input) ((input) >> 1)

#ifdef __FE_DIVIDE_BY_4
	#error __FE_DIVIDE_BY_4 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_4(input) ((input) >> 2)

#ifdef __FE_DIVIDE_BY_8
	#error __FE_DIVIDE_BY_8 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_8(input) ((input) >> 3)

#ifdef __FE_DIVIDE_BY_16
	#error __FE_DIVIDE_BY_16 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_16(input) ((input) >> 4)

#ifdef __FE_DIVIDE_BY_32
	#error __FE_DIVIDE_BY_32 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_32(input) ((input) >> 5)

#ifdef __FE_DIVIDE_BY_64
	#error __FE_DIVIDE_BY_64 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_64(input) ((input) >> 6)

#ifdef __FE_DIVIDE_BY_128
	#error __FE_DIVIDE_BY_128 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_DIVIDE_BY_128(input) ((input) >> 7)


#ifdef __FE_MODULO_BY_2
	#error __FE_MODULO_BY_2 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_2(input) ((input) & 1)

#ifdef __FE_MODULO_BY_4
	#error __FE_MODULO_BY_4 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_4(input) ((input) & 3)

#ifdef __FE_MODULO_BY_8
	#error __FE_MODULO_BY_8 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_8(input) ((input) & 7)

#ifdef __FE_MODULO_BY_16
	#error __FE_MODULO_BY_16 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_16(input) ((input) & 15)

#ifdef __FE_MODULO_BY_32
	#error __FE_MODULO_BY_32 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_32(input) ((input) & 31)

#ifdef __FE_MODULO_BY_64
	#error __FE_MODULO_BY_64 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_64(input) ((input) & 63)

#ifdef __FE_MODULO_BY_128
	#error __FE_MODULO_BY_128 is a reserved Frogman Engine macro keyword.
#endif
#define __FE_MODULO_BY_128(input) ((input) & 127)


#include <FE/prerequisites.h>
#include <FE/algorithm/math.hpp>


#ifdef _FE_ON_X86_64_
	// AVX
	#include <immintrin.h>

// You won't be able to run any modern game softwares if your CPU is too old to support SSE and SSE2.
#define _SSE_
#define _SSE2_

	#ifdef __AVX__
		#define _AVX_
	#endif

	#ifdef __AVX2__
		#define _AVX2_
	#endif

	#ifdef __AVX512F__
		#define _AVX512F_
	#endif

#elif defined(_FE_ON_ARM64_)
	#if defined(__ARM_NEON) || defined(__ARM_NEON__)
		#define _ARM_NEON_
		#include <arm_neon.h>
	#endif

	#ifdef __ARM_NEON_FP
		#define _ARM_NEON_FP_
		#include <arm_neon.h>
	#endif
#endif

// For FE::unique_ptr
#include <memory_resource>
#include <type_traits>
#include <utility>




BEGIN_NAMESPACE(FE)


template <typename T>
class unique_ptr
{
	static_assert(std::is_reference_v<T> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a reference type variable.");
	static_assert(std::is_const_v<T> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a const type variable.");

public:
	using pointer = T*;
	using const_pointer = const T*;
	using element_type = T;

private:
	std::pmr::memory_resource* m_resource;
	pointer m_ptr;

public:
	_FE_FORCE_INLINE_ _FE_CONSTEXPR17_ unique_ptr() noexcept
		: m_resource(), m_ptr() {}

	template <typename... Arguments>
	_FE_FORCE_INLINE_ unique_ptr(std::pmr::polymorphic_allocator<T> allocator_p, Arguments&&... arguments_p) noexcept
		: m_resource( allocator_p.resource() ), m_ptr( allocator_p.allocate(1) )
	{
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: failed to allocate memory");
		new(m_ptr) T(std::forward<Arguments>(arguments_p)...);
	}

	_FE_FORCE_INLINE_ ~unique_ptr() noexcept
	{
		if (this->m_ptr == nullptr)
		{
			return;
		}

		this->m_ptr->~T();
		std::pmr::polymorphic_allocator<T>{m_resource}.deallocate(m_ptr, 1);
	}

	_FE_FORCE_INLINE_ unique_ptr(const unique_ptr&) = delete;
	_FE_FORCE_INLINE_ unique_ptr& operator=(const unique_ptr&) = delete;

	_FE_FORCE_INLINE_ unique_ptr(unique_ptr&& other) noexcept
		: m_resource(other.m_resource), m_ptr(other.m_ptr)
	{
		other.m_resource = nullptr;
		other.m_ptr = nullptr;
	}

	_FE_FORCE_INLINE_ unique_ptr& operator=(unique_ptr&& other_p) noexcept
	{
		this->reset();
		this->m_resource = other_p.m_resource;
		this->m_ptr = other_p.m_ptr;
		other_p.m_resource = nullptr;
		other_p.m_ptr = nullptr;
		return *this;
	}

	_FE_FORCE_INLINE_ void reset() noexcept
	{
		if (this->m_ptr == nullptr)
		{
			return;
		}

		this->m_ptr->~T();
		std::pmr::polymorphic_allocator<T>{m_resource}.deallocate(this->m_ptr, 1);
		this->m_resource = nullptr;
		this->m_ptr = nullptr;
	}

	_FE_FORCE_INLINE_ void swap(unique_ptr& other_p) noexcept
	{
		std::swap(this->m_resource, other_p.m_resource);
		std::swap(this->m_ptr, other_p.m_ptr);
	}

	_FE_FORCE_INLINE_ T* get() noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ const T* get() const noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ T* operator->() noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ const T* operator->() const noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ T& operator*() noexcept
	{
		return *m_ptr;
	}

	_FE_FORCE_INLINE_ const T& operator*() const noexcept
	{
		return *m_ptr;
	}

	_FE_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return this->m_ptr != nullptr;
	}

	_FE_FORCE_INLINE_ bool operator==(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr == other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator!=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr != other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator<(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr < other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator<=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr <= other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator>(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr > other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator>=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr >= other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator==(std::nullptr_t) const noexcept
	{
		return this->m_ptr == nullptr;
	}

	_FE_FORCE_INLINE_ bool operator!=(std::nullptr_t) const noexcept
	{
		return this->m_ptr != nullptr;
	}

	_FE_FORCE_INLINE_ bool operator==(const T* rhp_p) const noexcept
	{
		return this->m_ptr == rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator!=(const T* rhp_p) const noexcept
	{
		return this->m_ptr != rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator<(const T* rhp_p) const noexcept
	{
		return this->m_ptr < rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator<=(const T* rhp_p) const noexcept
	{
		return this->m_ptr <= rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator>(const T* rhp_p) const noexcept
	{
		return this->m_ptr > rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator>=(const T* rhp_p) const noexcept
	{
		return this->m_ptr >= rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator==(T* rhp_p) const noexcept
	{
		return this->m_ptr == rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator!=(T* rhp_p) const noexcept
	{
		return this->m_ptr != rhp_p;
	}
};

template <typename T, typename... Arguments>
_FE_FORCE_INLINE_ unique_ptr<std::remove_all_extents_t<T>> allocate_unique(const std::pmr::polymorphic_allocator<T>& allocator_p = std::pmr::get_default_resource(), Arguments&&... arguments_p) noexcept
{
	static_assert(std::is_reference_v<T> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a reference type variable.");
	static_assert(std::is_const_v<T> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a const type variable.");

	return unique_ptr<std::remove_all_extents_t<T>>(allocator_p, std::forward<Arguments>(arguments_p)...);
}




template <typename T>
class unique_ptr<T[]>
{
	static_assert(std::is_reference_v<std::remove_all_extents_t<T>> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a reference type variable.");
	static_assert(std::is_const_v<std::remove_all_extents_t<T>> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a const type variable.");

public:
	using pointer = std::remove_all_extents_t<T>*;
	using const_pointer = const std::remove_all_extents_t<T>*;
	using element_type = std::remove_all_extents_t<T>;

private:
	std::pmr::memory_resource* m_resource;
	pointer m_ptr;
	var::size m_length;

public:
	_FE_FORCE_INLINE_ _FE_CONSTEXPR17_ unique_ptr() noexcept
		: m_resource(), m_ptr(), m_length() {}

	template <typename... Arguments>
	_FE_FORCE_INLINE_ unique_ptr(std::pmr::polymorphic_allocator<T> allocator_p, FE::size size_p, Arguments&&... arguments_p) noexcept
		: m_resource(allocator_p.resource()), m_ptr( allocator_p.allocate(size_p) ), m_length(size_p)
	{
		FE_ASSERT(size_p != 0, "Assertion failed: failed to allocate memory");
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: failed to allocate memory");
		for (var::size i = 0; i < m_length; ++i)
		{
			new(m_ptr + i) element_type(std::forward<Arguments>(arguments_p)...);
		}
	}

	_FE_FORCE_INLINE_ ~unique_ptr() noexcept
	{
		if (this->m_ptr == nullptr)
		{
			return;
		}

		for (var::size i = 0; i < m_length; ++i)
		{
			this->m_ptr[i].~element_type();
		}
		std::pmr::polymorphic_allocator<T>{m_resource}.deallocate(m_ptr, m_length);
	}

	_FE_FORCE_INLINE_ unique_ptr(const unique_ptr&) = delete;
	_FE_FORCE_INLINE_ unique_ptr& operator=(const unique_ptr&) = delete;

	_FE_FORCE_INLINE_ unique_ptr(unique_ptr&& other_p) noexcept
		: m_resource(other_p.m_resource), m_ptr(other_p.m_ptr), m_length(other_p.m_length)
	{
		other_p.m_resource = 0;
		other_p.m_ptr = nullptr;
		other_p.m_length = 0;
	}

	_FE_FORCE_INLINE_ unique_ptr& operator=(unique_ptr&& other_p) noexcept
	{
		this->reset();
		this->m_resource = other_p.m_resource;
		this->m_ptr = other_p.m_ptr;
		this->m_length = other_p.m_length;
		other_p.m_resource = nullptr;
		other_p.m_ptr = nullptr;
		other_p.m_length = 0;
		return *this;
	}

	_FE_FORCE_INLINE_ void reset() noexcept
	{
		if (this->m_ptr == nullptr)
		{
			return;
		}

		for (var::size i = 0; i < m_length; ++i)
		{
			this->m_ptr[i].~element_type();
		}
		std::pmr::polymorphic_allocator<T>{m_resource}.deallocate(this->m_ptr, this->m_length);
		this->m_resource = nullptr;
		this->m_ptr = nullptr;
		this->m_length = 0;
	}

	_FE_FORCE_INLINE_ void swap(unique_ptr& other_p) noexcept
	{
		std::swap(this->m_resource, other_p.m_resource);
		std::swap(this->m_ptr, other_p.m_ptr);
		std::swap(this->m_length, other_p.m_length);
	}

	_FE_FORCE_INLINE_ pointer get() noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ const_pointer get() const noexcept
	{
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ element_type& operator[](FE::size index_p) noexcept
	{
		FE_ASSERT(index_p < m_length, "Assertion failed: index out of bounds");
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return this->m_ptr[index_p];
	}

	_FE_FORCE_INLINE_ const element_type& operator[](FE::size index_p) const noexcept
	{
		FE_ASSERT(index_p < m_length, "Assertion failed: index out of bounds");
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return this->m_ptr[index_p];
	}

	_FE_FORCE_INLINE_ pointer operator->() noexcept
	{
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ const_pointer operator->() const noexcept
	{
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return this->m_ptr;
	}

	_FE_FORCE_INLINE_ element_type& operator*() noexcept
	{
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return *m_ptr;
	}

	_FE_FORCE_INLINE_ const element_type& operator*() const noexcept
	{
		FE_ASSERT(m_ptr != nullptr, "Assertion failed: pointer is null");
		return *m_ptr;
	}

	_FE_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return this->m_ptr != nullptr;
	}

	_FE_FORCE_INLINE_ bool operator==(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr == other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator!=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr != other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator<(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr < other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator<=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr <= other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator>(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr > other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator>=(const unique_ptr& other_p) const noexcept
	{
		return this->m_ptr >= other_p.m_ptr;
	}

	_FE_FORCE_INLINE_ bool operator==(std::nullptr_t) const noexcept
	{
		return this->m_ptr == nullptr;
	}

	_FE_FORCE_INLINE_ bool operator!=(std::nullptr_t) const noexcept
	{
		return this->m_ptr != nullptr;
	}

	_FE_FORCE_INLINE_ bool operator==(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr == rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator!=(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr != rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator<(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr < rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator<=(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr <= rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator>(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr > rhp_p;
	}

	_FE_FORCE_INLINE_ bool operator>=(const_pointer const rhp_p) const noexcept
	{
		return this->m_ptr >= rhp_p;
	}

	_FE_FORCE_INLINE_ FE::size get_length() const noexcept
	{
		return m_length;
	}
};

template <typename T, typename... Arguments>
_FE_FORCE_INLINE_ unique_ptr<std::remove_all_extents_t<T>[]> allocate_unique(FE::size size_p, const std::pmr::polymorphic_allocator<std::remove_all_extents_t<T>[]>& allocator_p = std::pmr::get_default_resource(), Arguments&&... arguments_p) noexcept
{
	static_assert(std::is_reference_v<std::remove_all_extents_t<T>> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a reference type variable.");
	static_assert(std::is_const_v<std::remove_all_extents_t<T>> == false, "Static assertion failed: unique_ptr cannot hold a pointer to a const type variable.");
	return unique_ptr<std::remove_all_extents_t<T>[]>(allocator_p, size_p, std::forward<Arguments>(arguments_p)...);
}




_FE_MAYBE_UNUSED_ constexpr uint8 byte_size = 1;
_FE_MAYBE_UNUSED_ constexpr uint8 word_size = 2;
_FE_MAYBE_UNUSED_ constexpr uint8 dword_size = 4;
_FE_MAYBE_UNUSED_ constexpr uint8 qword_size = 8;

using reserve = size;
using resize_to = size;
using extend = size;

// The FE::is_power_of_two function is a constexpr function that checks if a given size_t value is a power of two by using a bitwise operation.
_FE_CONSTEXPR17_ FE::boolean is_power_of_two(FE::size value_p) noexcept
{
	/* Since 4 is a power of 2 and
		0b0001 == 1
		0b0010 == 2
		0b0011 == 3
		0b0100 == 4
		...

		if you can see the pattern, you can find that
		4 - 1 is 3 and equals to 0b0011 in binary.

		  0b0100
		& 0b0011
		--------
		  0b0000

		Therefore,
		0b0100 AND 0b0011 == 0b0000.
	*/
	return (value_p & (value_p - 1)) == 0;
}

struct align_8bytes final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = 8;
};

struct align_16bytes final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = 16;
};

struct align_32bytes final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = 32;
};

struct align_64bytes final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = 64;
};

struct align_128bytes final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = 128;
};

struct align_CPU_L1_cache_line final
{
	_FE_MAYBE_UNUSED_ static constexpr size size = std::hardware_destructive_interference_size;
};

/*
The FE::SIMD_auto_alignment struct defines a type alias for alignment based on the available SIMD instruction set
specifying different alignment sizes for AVX512, AVX/AVX2, and fallback to a default alignment.
*/
struct SIMD_auto_alignment
{
#ifdef _AVX512F_
	using alignment_type = align_64bytes;
#elif defined(_AVX_) || defined(_AVX2_)
	using alignment_type = align_32bytes;
#else
	using alignment_type = align_16bytes;
#endif

	_FE_MAYBE_UNUSED_ static constexpr size size = alignment_type::size;
};

#pragma warning(push)
#pragma warning(disable:4324)
template<typename T, class Alignment = typename FE::SIMD_auto_alignment>
struct alignas(Alignment::size) aligned final
{
	using value_type = T;
	using alignment_type = Alignment;

	T _data;
};
#pragma warning(pop)

template<FE::size SizeInBytes, class Alignment>
struct align_as final
{
	_FE_MAYBE_UNUSED_ static constexpr inline FE::size size = sizeof(FE::aligned<FE::byte[SizeInBytes], Alignment>);
};

enum struct Address : bool
{
	_NotAligned = false,
	_Aligned = true
};

/*
The FE::zmmword class is a final, aligned data structure designed to store and manipulate SIMD (Single Instruction, Multiple Data) vectors using AVX512, AVX, or SSE2 instruction sets, depending on the available hardware capabilities.
*/
class alignas(64) zmmword final
{
#if defined(_AVX512F_) 
	__m512i _zmm0;
#elif defined(_AVX_)
	__m256i _ymm0;
	__m256i _ymm1;
#elif defined(_SSE2_)
	__m128i _xmm0;
	__m128i _xmm1;
	__m128i _xmm2;
	__m128i _xmm3;
#endif
public:
#if defined(_AVX512F_) 
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_512bit_p) noexcept
	{
		//FE_ASSERT(aligned_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_512bit_p) % 64) == 0, "Assertion failed: the address value must be aligned by 64.");
		_mm512_store_si512(&_zmm0, _mm512_load_si512(reinterpret_cast<const __m512i* const>(aligned_512bit_p)));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_512bit_p) noexcept
	{
		//FE_ASSERT(unaligned_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm512_store_si512(&_zmm0, _mm512_loadu_si512(reinterpret_cast<const __m512i* const>(unaligned_512bit_p)));
	}
#elif defined(_AVX_)
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_512bit_p) noexcept
	{
		//FE_ASSERT(aligned_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_512bit_p) % 64) == 0, "Assertion failed: the address value must be aligned by 64.");
		_mm256_store_si256(&_ymm0, _mm256_load_si256(reinterpret_cast<const __m256i* const>(aligned_512bit_p)));
		_mm256_store_si256(&_ymm1, _mm256_load_si256(reinterpret_cast<const __m256i* const>(aligned_512bit_p) + 1));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_512bit_p) noexcept
	{
		//FE_ASSERT(unaligned_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm256_store_si256(&_ymm0, _mm256_loadu_si256(reinterpret_cast<const __m256i* const>(unaligned_512bit_p)));
		_mm256_store_si256(&_ymm1, _mm256_loadu_si256(reinterpret_cast<const __m256i* const>(unaligned_512bit_p) + 1));
	}
#elif defined(_SSE2_)
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_512bit_p) noexcept
	{
		//FE_ASSERT(aligned_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_512bit_p) % 64) == 0, "Assertion failed: the address value must be aligned by 64.");
		_mm_store_si128(&_xmm0, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_512bit_p)));
		_mm_store_si128(&_xmm1, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_512bit_p) + 1));
		_mm_store_si128(&_xmm2, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_512bit_p) + 2));
		_mm_store_si128(&_xmm3, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_512bit_p) + 3));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_512bit_p) noexcept
	{
		//FE_ASSERT(vector_512bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm_store_si128(&_xmm0, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_512bit_p)));
		_mm_store_si128(&_xmm1, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_512bit_p) + 1));
		_mm_store_si128(&_xmm2, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_512bit_p) + 2));
		_mm_store_si128(&_xmm3, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_512bit_p) + 3));
	}
#endif
	_FE_FORCE_INLINE_ const zmmword* load() const noexcept { return this; }
	_FE_FORCE_INLINE_ zmmword* load() noexcept { return this; }
};

class alignas(32) ymmword final
{
#if defined(_AVX_)
	__m256i _ymm0;
#elif defined(_SSE2_)
	__m128i _xmm0;
	__m128i _xmm1;
#endif
public:
#if defined(_AVX_)
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_256bit_p) noexcept
	{
		//FE_ASSERT(aligned_256bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_256bit_p) % 32) == 0, "Assertion failed: the address value must be aligned by 32.");
		_mm256_store_si256(&_ymm0, _mm256_load_si256(reinterpret_cast<const __m256i* const>(aligned_256bit_p)));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_256bit_p) noexcept
	{
		//FE_ASSERT(unaligned_256bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm256_store_si256(&_ymm0, _mm256_loadu_si256(reinterpret_cast<const __m256i* const>(unaligned_256bit_p)));
	}
#elif defined(_SSE2_)
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_256bit_p) noexcept
	{
		//FE_ASSERT(aligned_256bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_256bit_p) % 32) == 0, "Assertion failed: the address value must be aligned by 32.");
		_mm_store_si128(&_xmm0, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_256bit_p)));
		_mm_store_si128(&_xmm1, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_256bit_p) + 1));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_256bit_p) noexcept
	{
		//FE_ASSERT(unaligned_256bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm_store_si128(&_xmm0, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_256bit_p)));
		_mm_store_si128(&_xmm1, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_256bit_p) + 1));
	}
#endif
	_FE_FORCE_INLINE_ const ymmword* load() const noexcept { return this; }
	_FE_FORCE_INLINE_ ymmword* load() noexcept { return this; }
};

class alignas(16) xmmword final
{
	__m128i _xmm0;
public:
	template <typename T>
	_FE_FORCE_INLINE_ void store(const T* const aligned_128bit_p) noexcept
	{
		//FE_ASSERT(aligned_128bit_p != nullptr, "Assertion failed: the pointer is null.");
		//FE_ASSERT((reinterpret_cast<FE::intptr>(aligned_128bit_p) % 16) == 0, "Assertion failed: the address value must be aligned by 16.");
		_mm_store_si128(&_xmm0, _mm_load_si128(reinterpret_cast<const __m128i* const>(aligned_128bit_p)));
	}
	template <typename T>
	_FE_FORCE_INLINE_ void storeu(const T* const unaligned_128bit_p) noexcept
	{
		//FE_ASSERT(unaligned_128bit_p != nullptr, "Assertion failed: the pointer is null.");
		_mm_store_si128(&_xmm0, _mm_loadu_si128(reinterpret_cast<const __m128i* const>(unaligned_128bit_p)));
	}
	_FE_FORCE_INLINE_ const xmmword* load() const noexcept { return this; }
	_FE_FORCE_INLINE_ xmmword* load() noexcept { return this; }
};

#if defined(_AVX512F_) && defined(_AVX_) && defined(_SSE2_)


_FE_FORCE_INLINE_ void __x86_64_unaligned_memcpy_AVX512_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}

	// __FE_DIVIDE_BY_64(bytes_to_copy_p) == SIMD operation count
	for (__m512i* const end = static_cast<__m512i*>(out_dest_p) + __FE_DIVIDE_BY_64(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm512_storeu_si512(static_cast<__m512i*>(out_dest_p), _mm512_loadu_si512(static_cast<const __m512i*>(source_p)));
		out_dest_p = static_cast<__m512i*>(out_dest_p) + 1;
		source_p = static_cast<const __m512i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_64(bytes_to_copy_p);
    if(bytes_to_copy_p > 0)
	{
		__x86_64_unaligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p);
	}
}

_FE_FORCE_INLINE_ void __x86_64_aligned_memcpy_AVX512_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_64(reinterpret_cast<uintptr>(out_dest_p)) != 0, "${%s@}: out_dest_p is not aligned by 64.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_64(reinterpret_cast<uintptr>(source_p)) != 0, "${%s@}: source_p is not aligned by 64.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}

	// __FE_DIVIDE_BY_64(bytes_to_copy_p) == SIMD operation count
	for (__m512i* const end = static_cast<__m512i*>(out_dest_p) + __FE_DIVIDE_BY_64(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm512_store_si512(static_cast<__m512i*>(out_dest_p), _mm512_load_si512(static_cast<const __m512i*>(source_p)));
		out_dest_p = static_cast<__m512i*>(out_dest_p) + 1;
		source_p = static_cast<const __m512i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_64(bytes_to_copy_p);
    if(bytes_to_copy_p > 0)
	{
		__x86_64_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p);
	}
}

_FE_FORCE_INLINE_ void __x86_64_dest_aligned_memcpy_AVX512_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_64(reinterpret_cast<uintptr>(out_dest_p)) != 0, "${%s@}: out_dest_p is not aligned by 64.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}

	// __FE_DIVIDE_BY_64(bytes_to_copy_p) == SIMD operation count
	for (__m512i* const end = static_cast<__m512i*>(out_dest_p) + __FE_DIVIDE_BY_64(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm512_store_si512(static_cast<__m512i*>(out_dest_p), _mm512_loadu_si512(static_cast<const __m512i*>(source_p)));
		out_dest_p = static_cast<__m512i*>(out_dest_p) + 1;
		source_p = static_cast<const __m512i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_64(bytes_to_copy_p);
    if(bytes_to_copy_p > 0)
	{
		__x86_64_dest_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p);
	}
}

_FE_FORCE_INLINE_ void __x86_64_source_aligned_memcpy_AVX512_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_64(reinterpret_cast<uintptr>(source_p)) != 0, "${%s@}: source_p is not aligned by 64.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}
	
	// __FE_DIVIDE_BY_64(bytes_to_copy_p) == SIMD operation count
	for (__m512i* const end = static_cast<__m512i*>(out_dest_p) + __FE_DIVIDE_BY_64(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm512_storeu_si512(static_cast<__m512i*>(out_dest_p), _mm512_load_si512(static_cast<const __m512i*>(source_p)));
		out_dest_p = static_cast<__m512i*>(out_dest_p) + 1;
		source_p = static_cast<const __m512i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_64(bytes_to_copy_p);
    if(bytes_to_copy_p > 0)
	{
		__x86_64_source_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p);
	}
}


_FE_FORCE_INLINE_ void __x86_64_unaligned_memmove_AVX512_AVX_SSE2(void* const out_dest_p, const void* const source_p, FE::size bytes_to_move_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(bytes_to_move_p == 0, "${%s@0}: ${%s@1} is 0.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(bytes_to_move_p));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}

	if (source_p < out_dest_p)
	{
		var::byte* l_dest_byte_ptr = static_cast<var::byte*>(out_dest_p) + (bytes_to_move_p - 1);
		byte* l_source_byte_ptr = static_cast<byte*>(source_p) + (bytes_to_move_p - 1);

		{
			size l_leftover_bytes_to_copy_by_byte = __FE_MODULO_BY_64(bytes_to_move_p);

			for (var::size i = 0; i != l_leftover_bytes_to_copy_by_byte; ++i)
			{
				*l_dest_byte_ptr = *l_source_byte_ptr;
				--l_dest_byte_ptr;
				--l_source_byte_ptr;
			}
		}

		var::size l_operation_count = __FE_DIVIDE_BY_64(bytes_to_move_p);

		__m512i* l_m512i_dest_ptr = reinterpret_cast<__m512i*>(l_dest_byte_ptr - 63);
		const __m512i* l_m512i_source_ptr = reinterpret_cast<const __m512i*>(l_source_byte_ptr - 63);

		for (; l_operation_count > 1; --l_operation_count)
		{
			_mm512_storeu_si512(l_m512i_dest_ptr, _mm512_loadu_si512(l_m512i_source_ptr));
			--l_m512i_dest_ptr;
			--l_m512i_source_ptr;
		}

		size l_leftover_bytes = reinterpret_cast<var::byte*>(l_m512i_dest_ptr) - static_cast<var::byte* const>(out_dest_p);

		if (l_leftover_bytes > 0)
		{
			__x86_64_unaligned_memmove_AVX_SSE2(out_dest_p, source_p, l_leftover_bytes);
			return;
		}
	}
	else
	{
		__x86_64_unaligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p);
	}
}

_FE_FORCE_INLINE_ void __x86_64_aligned_memmove_AVX512_AVX_SSE2(void* const out_dest_p, const void* const source_p, FE::size bytes_to_move_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(bytes_to_move_p == 0, "${%s@0}: ${%s@1} is 0.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(bytes_to_move_p));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}

	if (source_p < out_dest_p)
	{
		var::byte* l_dest_byte_ptr = static_cast<var::byte*>(out_dest_p) + (bytes_to_move_p - 1);
		byte* l_source_byte_ptr = static_cast<byte*>(source_p) + (bytes_to_move_p - 1);

		{
			size l_leftover_bytes_to_copy_by_byte = __FE_MODULO_BY_64(bytes_to_move_p);

			for (var::size i = 0; i != l_leftover_bytes_to_copy_by_byte; ++i)
			{
				*l_dest_byte_ptr = *l_source_byte_ptr;
				--l_dest_byte_ptr;
				--l_source_byte_ptr;
			}
		}

		var::size l_operation_count = __FE_DIVIDE_BY_64(bytes_to_move_p);

		__m512i* l_m512i_dest_ptr = reinterpret_cast<__m512i*>(l_dest_byte_ptr - 63);
		const __m512i* l_m512i_source_ptr = reinterpret_cast<const __m512i*>(l_source_byte_ptr - 63);

		for (; l_operation_count > 1; --l_operation_count)
		{
			_mm512_store_si512(l_m512i_dest_ptr, _mm512_loadu_si512(l_m512i_source_ptr));
			--l_m512i_dest_ptr;
			--l_m512i_source_ptr;
		}

		size l_leftover_bytes = reinterpret_cast<var::byte*>(l_m512i_dest_ptr) - static_cast<var::byte* const>(out_dest_p);

		if (l_leftover_bytes > 0)
		{
			__x86_64_aligned_memmove_AVX_SSE2(out_dest_p, source_p, l_leftover_bytes);
			return;
		}
	}
	else
	{
		__x86_64_dest_aligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p);
	}
}

#elif defined(_AVX_) && defined(_SSE2_)
_FE_FORCE_INLINE_ void __x86_64_unaligned_memzero_AVX_SSE2(void* out_dest_p, var::size bytes_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	
	// __FE_DIVIDE_BY_32(bytes_to_copy_p) == SIMD operation count
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_p); out_dest_p != end;)
	{
		_mm256_storeu_si256(static_cast<__m256i*>(out_dest_p),
							_mm256_xor_si256(	_mm256_loadu_si256(static_cast<const __m256i*>(out_dest_p)	), 
												_mm256_loadu_si256(static_cast<const __m256i*>(out_dest_p)	)
											)
							);
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
	}

	bytes_p = __FE_MODULO_BY_32(bytes_p);
	//if (bytes_p >= 16)
	//{
	//	_mm_storeu_si128(static_cast<__m128i*>(out_dest_p),  
	//					_mm_xor_si128(	_mm_loadu_si128( static_cast<const __m128i*>(out_dest_p) ),
	//									_mm_loadu_si128( static_cast<const __m128i*>(out_dest_p) )
	//									)
	//					);
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	bytes_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(out_dest_p) xor *static_cast<byte*>(out_dest_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
	}
}

_FE_FORCE_INLINE_ void __x86_64_aligned_memzero_AVX_SSE2(void* out_dest_p, var::size bytes_p) noexcept
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_p); out_dest_p != end;)
	{
		_mm256_store_si256(static_cast<__m256i*>(out_dest_p),
			_mm256_xor_si256(_mm256_load_si256(static_cast<const __m256i*>(out_dest_p)),
				_mm256_load_si256(static_cast<const __m256i*>(out_dest_p))
			)
		);
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
	}

	bytes_p = __FE_MODULO_BY_32(bytes_p);
	//if (bytes_p >= 16)
	//{
	//	_mm_store_si128(static_cast<__m128i*>(out_dest_p),
	//		_mm_xor_si128(_mm_load_si128(static_cast<const __m128i*>(out_dest_p)),
	//			_mm_load_si128(static_cast<const __m128i*>(out_dest_p))
	//		)
	//	);
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	bytes_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(out_dest_p) xor *static_cast<byte*>(out_dest_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
	}
}


_FE_FORCE_INLINE_ void __x86_64_unaligned_memcpy_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));

	// __FE_DIVIDE_BY_32(bytes_to_copy_p) == SIMD operation count
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm256_storeu_si256(static_cast<__m256i*>(out_dest_p), _mm256_loadu_si256(static_cast<const __m256i*>(source_p)));
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
		source_p = static_cast<const __m256i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_32(bytes_to_copy_p);
	//if (bytes_to_copy_p >= 16)
	//{
	//	_mm_storeu_si128(static_cast<__m128i*>(out_dest_p), _mm_loadu_si128(static_cast<const __m128i*>(source_p)));
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	source_p = static_cast<const __m128i*>(source_p) + 1;
	//	bytes_to_copy_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_to_copy_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
		source_p = static_cast<byte*>(source_p) + 1;
	}
}

_FE_FORCE_INLINE_ void __x86_64_aligned_memcpy_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_32(reinterpret_cast<uintptr>(out_dest_p)) != 0, "${%s@0}: ${%s@1} is not aligned by 32.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_32(reinterpret_cast<uintptr>(source_p)) != 0, "${%s@0}: ${%s@1} is not aligned by 32.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment), TO_STRING(source_p));

	// __FE_DIVIDE_BY_32(bytes_to_copy_p) == SIMD operation count
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm256_store_si256(static_cast<__m256i*>(out_dest_p), _mm256_load_si256(static_cast<const __m256i*>(source_p)));
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
		source_p = static_cast<const __m256i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_32(bytes_to_copy_p);
	//if (bytes_to_copy_p >= 16)
	//{
	//	_mm_store_si128(static_cast<__m128i*>(out_dest_p), _mm_load_si128(static_cast<const __m128i*>(source_p)));
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	source_p = static_cast<const __m128i*>(source_p) + 1;
	//	bytes_to_copy_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_to_copy_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
		source_p = static_cast<byte*>(source_p) + 1;
	}
}

_FE_FORCE_INLINE_ void __x86_64_dest_aligned_memcpy_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_32(reinterpret_cast<uintptr>(out_dest_p)) != 0, "${%s@0}: ${%s@1} is not aligned by 32.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment), TO_STRING(out_dest_p));

	// __FE_DIVIDE_BY_32(bytes_to_copy_p) == SIMD operation count
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm256_store_si256(static_cast<__m256i*>(out_dest_p), _mm256_loadu_si256(static_cast<const __m256i*>(source_p)));
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
		source_p = static_cast<const __m256i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_32(bytes_to_copy_p);
	//if (bytes_to_copy_p >= 16)
	//{
	//	_mm_store_si128(static_cast<__m128i*>(out_dest_p), _mm_loadu_si128(static_cast<const __m128i*>(source_p)));
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	source_p = static_cast<const __m128i*>(source_p) + 1;
	//	bytes_to_copy_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_to_copy_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
		source_p = static_cast<byte*>(source_p) + 1;
	}
}

_FE_FORCE_INLINE_ void __x86_64_source_aligned_memcpy_AVX_SSE2(void* out_dest_p, const void* source_p, var::size bytes_to_copy_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_32(reinterpret_cast<uintptr>(source_p)) != 0, "${%s@0}: ${%s@1} is not aligned by 32.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment), TO_STRING(source_p));

	// __FE_DIVIDE_BY_32(bytes_to_copy_p) == SIMD operation count
	for (__m256i* const end = static_cast<__m256i*>(out_dest_p) + __FE_DIVIDE_BY_32(bytes_to_copy_p); out_dest_p != end;)
	{
		_mm256_storeu_si256(static_cast<__m256i*>(out_dest_p), _mm256_load_si256(static_cast<const __m256i*>(source_p)));
		
		out_dest_p = static_cast<__m256i*>(out_dest_p) + 1;
		source_p = static_cast<const __m256i*>(source_p) + 1;
	}

	bytes_to_copy_p = __FE_MODULO_BY_32(bytes_to_copy_p);
	//if (bytes_to_copy_p >= 16)
	//{
	//	_mm_storeu_si128(static_cast<__m128i*>(out_dest_p), _mm_load_si128(static_cast<const __m128i*>(source_p)));
	//	out_dest_p = static_cast<__m128i*>(out_dest_p) + 1;
	//	source_p = static_cast<const __m128i*>(source_p) + 1;
	//	bytes_to_copy_p -= 16;
	//}

	for (var::byte* const end = static_cast<var::byte*>(out_dest_p) + bytes_to_copy_p; out_dest_p != end;)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) + 1;
		source_p = static_cast<byte*>(source_p) + 1;
	}
}

/*
if (source_p < out_dest_p) being true means that the two void*s "out_dest_p and source_p" are pointing to the same range of memory
possibly overlap each other. If that is the case
memmove iterates and copies the data in the reverse order of memcpy operation.

        copy & traversal order 
    <---------------------------
  front                       back
    ++++++++++++++++++++++++++++
    |                          |
    ++++++++++++++++++++++++++++
low address               high address

Otherwise, it invokes memcpy to proceed its operation.
*/
_FE_FORCE_INLINE_ void __x86_64_unaligned_memmove_AVX_SSE2(void* out_dest_p, const void* source_p, size bytes_to_move_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(bytes_to_move_p == 0, "${%s@0}: ${%s@1} is 0.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(bytes_to_move_p));

	out_dest_p = static_cast<var::byte*>(out_dest_p) + (bytes_to_move_p - 1);
	source_p = static_cast<byte*>(source_p) + (bytes_to_move_p - 1);

	for (var::size n = __FE_MODULO_BY_16(bytes_to_move_p); n > 0; --n)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<FE::byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) - 1;
		source_p = static_cast<byte*>(source_p) - 1;
	}

	out_dest_p = reinterpret_cast<__m256i*>(static_cast<var::byte*>(out_dest_p) - 31);
	source_p = reinterpret_cast<const __m256i*>(static_cast<byte*>(source_p) - 31);

	var::size l_operation_count = __FE_DIVIDE_BY_16(bytes_to_move_p);
	for (; l_operation_count > 1; l_operation_count -= 2)
	{
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(out_dest_p), _mm256_loadu_si256(reinterpret_cast<const __m256i*>(source_p)));
		out_dest_p = reinterpret_cast<__m256i*>(out_dest_p) - 1;
		source_p = reinterpret_cast<const __m256i*>(source_p) - 1;
	}

	out_dest_p = reinterpret_cast<__m128i*>(out_dest_p) + 1;
	source_p = reinterpret_cast<const __m128i*>(source_p) + 1;

	for (; l_operation_count > 0; --l_operation_count)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(out_dest_p), _mm_loadu_si128(reinterpret_cast<const __m128i*>(source_p)));
		out_dest_p = reinterpret_cast<__m128i*>(out_dest_p) - 1;
		source_p = reinterpret_cast<const __m128i*>(source_p) - 1;
	}
}

/*
if (source_p < out_dest_p) being true means that the two void*s "out_dest_p and source_p" are pointing to the same range of memory
possibly overlap each other. If that is the case
memmove iterates and copies the data in the reverse order of memcpy operation.

        copy & traversal order 
    <---------------------------
  front                       back
    ++++++++++++++++++++++++++++
    |                          |
    ++++++++++++++++++++++++++++
low address               high address

Otherwise, it invokes memcpy to proceed its operation.
*/
_FE_FORCE_INLINE_ void __x86_64_aligned_memmove_AVX_SSE2(void* out_dest_p, const void* source_p, size bytes_to_move_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(source_p));
	FE_NEGATIVE_ASSERT(bytes_to_move_p == 0, "${%s@0}: ${%s@1} is 0.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_InvalidSize), TO_STRING(bytes_to_move_p));
	//if(FE_UNLIKELY(out_dest_p == source_p)) _FE_UNLIKELY_
	//{
 //   	return;
	//}
	FE_NEGATIVE_ASSERT(__FE_MODULO_BY_32(reinterpret_cast<uintptr>(out_dest_p)) != 0, "${%s@0}: ${%s@1} is not aligned by 32.", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_IllegalAddressAlignment), TO_STRING(out_dest_p));
	//if (source_p < out_dest_p)
	//{

	//}
	//else
	//{
	//	__x86_64_dest_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p);
	//	return;
	//}

	out_dest_p = static_cast<var::byte*>(out_dest_p) + (bytes_to_move_p - 1);
	source_p = static_cast<byte*>(source_p) + (bytes_to_move_p - 1);

	for (var::size n = __FE_MODULO_BY_16(bytes_to_move_p); n > 0; --n)
	{
		*static_cast<var::byte*>(out_dest_p) = *static_cast<FE::byte*>(source_p);
		out_dest_p = static_cast<var::byte*>(out_dest_p) - 1;
		source_p = static_cast<byte*>(source_p) - 1;
	}

	out_dest_p = reinterpret_cast<__m256i*>(static_cast<var::byte*>(out_dest_p) - 31);
	source_p = reinterpret_cast<const __m256i*>(static_cast<byte*>(source_p) - 31);

	var::size l_operation_count = __FE_DIVIDE_BY_16(bytes_to_move_p);
	for (; l_operation_count > 1; l_operation_count -= 2)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(out_dest_p), _mm256_loadu_si256(reinterpret_cast<const __m256i*>(source_p)));
		out_dest_p = reinterpret_cast<__m256i*>(out_dest_p) - 1;
		source_p = reinterpret_cast<const __m256i*>(source_p) - 1;
	}

	out_dest_p = reinterpret_cast<__m128i*>(out_dest_p) + 1;
	source_p = reinterpret_cast<const __m128i*>(source_p) + 1;

	for (; l_operation_count > 0; --l_operation_count)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(out_dest_p), _mm_loadu_si128(reinterpret_cast<const __m128i*>(source_p)));
		out_dest_p = reinterpret_cast<__m128i*>(out_dest_p) - 1;
		source_p = reinterpret_cast<const __m128i*>(source_p) - 1;
	}
	return;
}
#endif


#if defined(_AVX512F_) && defined(_AVX_) && defined(_SSE2_)
	#define FE_UNALIGNED_MEMZERO(out_dest_p, bytes_p) ::FE::__x86_64_unaligned_memzero_AVX_SSE2(out_dest_p, bytes_p)
	#define FE_ALIGNED_MEMZERO(out_dest_p, bytes_p) ::FE::__x86_64_aligned_memzero_AVX_SSE2(out_dest_p, bytes_p)
	#define FE_UNALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_unaligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_aligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_DEST_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_dest_aligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_SOURCE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_source_aligned_memcpy_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_UNALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::FE::__x86_64_unaligned_memmove_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p)
	#define FE_ALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::FE::__x86_64_aligned_memmove_AVX512_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p)
#elif defined(_AVX_) && defined(_SSE2_)
	#define FE_UNALIGNED_MEMZERO(out_dest_p, bytes_p) ::FE::__x86_64_unaligned_memzero_AVX_SSE2(out_dest_p, bytes_p)
	#define FE_ALIGNED_MEMZERO(out_dest_p, bytes_p) ::FE::__x86_64_aligned_memzero_AVX_SSE2(out_dest_p, bytes_p)
	#define FE_UNALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_unaligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_DEST_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_dest_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_SOURCE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::FE::__x86_64_source_aligned_memcpy_AVX_SSE2(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_UNALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::FE::__x86_64_unaligned_memmove_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p)
	#define FE_ALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::FE::__x86_64_aligned_memmove_AVX_SSE2(out_dest_p, source_p, bytes_to_move_p)
#else
	#define FE_UNALIGNED_MEMZERO(out_dest_p, bytes_p) ::std::memset(out_dest_p, 0, bytes_p)
	#define FE_ALIGNED_MEMZERO(out_dest_p, bytes_p) ::std::memset(out_dest_p, 0, bytes_p)
	#define FE_UNALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::std::memcpy(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::std::memcpy(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_DEST_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::std::memcpy(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_SOURCE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_to_copy_p) ::std::memcpy(out_dest_p, source_p, bytes_to_copy_p)
	#define FE_UNALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::std::memmove(out_dest_p, source_p, bytes_to_move_p)
	#define FE_ALIGNED_MEMMOVE(out_dest_p, source_p, bytes_to_move_p) ::std::memmove(out_dest_p, source_p, bytes_to_move_p)
#endif

/*
The calculate_aligned_memory_size_in_bytes function template computes the aligned memory size in bytes required for a specified number of elements of type T
ensuring that the memory alignment adheres to the specified Alignment.
*/
template<typename T, class Alignment>
_FE_FORCE_INLINE_ _FE_CONSTEXPR20_ size calculate_aligned_memory_size_in_bytes(uint64 elements_p) noexcept  
{
	FE_NEGATIVE_ASSERT(elements_p == 0, "Assertion Failure: ${%s@0} cannot be zero.", TO_STRING(elements_p));

	size l_actual_size = sizeof(T) * elements_p;
	var::size l_multiplier = l_actual_size / sizeof(FE::aligned<T, Alignment>);
	l_multiplier += ((l_actual_size % sizeof(FE::aligned<T, Alignment>)) != 0);

	return sizeof(FE::aligned<T, Alignment>) * l_multiplier;
}

template<class ConstIterator>
FE::boolean memcmp(ConstIterator left_iterator_begin_p, ConstIterator left_iterator_end_p, ConstIterator right_iterator_begin_p, ConstIterator right_iterator_end_p) noexcept  
{
	static_assert(std::is_class<ConstIterator>::value == true);
	FE_NEGATIVE_ASSERT(left_iterator_begin_p == nullptr, "ERROR: left_iterator_begin_p is nullptr.");
	FE_NEGATIVE_ASSERT(left_iterator_end_p == nullptr, "ERROR: left_iterator_end_p is nullptr.");
	FE_NEGATIVE_ASSERT(right_iterator_begin_p == nullptr, "ERROR: right_iterator_begin_p is nullptr.");
	FE_NEGATIVE_ASSERT(right_iterator_end_p == nullptr, "ERROR: right_iterator_end_p is nullptr.");

	ConstIterator l_left_iterator_begin = left_iterator_begin_p;

	if ((left_iterator_end_p - left_iterator_begin_p) != (right_iterator_end_p - right_iterator_begin_p))
	{
		return false;
	}

	while ((l_left_iterator_begin != left_iterator_end_p) && (*l_left_iterator_begin == *right_iterator_begin_p))
	{
		++l_left_iterator_begin;
		++right_iterator_begin_p;
	}

	if ((l_left_iterator_begin - left_iterator_begin_p) == (left_iterator_end_p - left_iterator_begin_p))
	{
		return true;
	}

	return false;
}

template<Address DestAddressAlignment = Address::_NotAligned, Address SourceAddressAlignment = Address::_NotAligned>
_FE_FORCE_INLINE_ void memcpy(void* out_dest_p, size dest_capacity_in_bytes_p, const void* source_p, uint64 source_capacity_in_bytes_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(source_p));

	if constexpr (DestAddressAlignment == Address::_Aligned && SourceAddressAlignment == Address::_Aligned)
	{
		FE_ALIGNED_MEMCPY(out_dest_p, source_p, ::FE::algorithm::math::min(dest_capacity_in_bytes_p, source_capacity_in_bytes_p));
	}
	else if constexpr (DestAddressAlignment == Address::_Aligned && SourceAddressAlignment == Address::_NotAligned)
	{
		FE_DEST_ALIGNED_MEMCPY(out_dest_p, source_p, ::FE::algorithm::math::min(dest_capacity_in_bytes_p, source_capacity_in_bytes_p));
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned && SourceAddressAlignment == Address::_Aligned)
	{
		FE_SOURCE_ALIGNED_MEMCPY(out_dest_p, source_p, ::FE::algorithm::math::min(dest_capacity_in_bytes_p, source_capacity_in_bytes_p));
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned && SourceAddressAlignment == Address::_NotAligned)
	{
		FE_UNALIGNED_MEMCPY(out_dest_p, source_p, ::FE::algorithm::math::min(dest_capacity_in_bytes_p, source_capacity_in_bytes_p));
	}
}

/*
The FE::memcpy function is a template function that performs memory copying between a source and destination pointer with optimizations based on the alignment of the addresses involved
while also ensuring that neither pointer is null.
*/
template<Address DestAddressAlignment = Address::_NotAligned, Address SourceAddressAlignment = Address::_NotAligned>
_FE_FORCE_INLINE_ void memcpy(void* out_dest_p, const void* source_p, uint64 bytes_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(source_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(source_p));

	if constexpr (DestAddressAlignment == Address::_Aligned && SourceAddressAlignment == Address::_Aligned)
	{
		FE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_p);
	}
	else if constexpr (DestAddressAlignment == Address::_Aligned && SourceAddressAlignment == Address::_NotAligned)
	{
		FE_DEST_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_p);
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned && SourceAddressAlignment == Address::_Aligned)
	{
		FE_SOURCE_ALIGNED_MEMCPY(out_dest_p, source_p, bytes_p);
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned && SourceAddressAlignment == Address::_NotAligned)
	{
		FE_UNALIGNED_MEMCPY(out_dest_p, source_p, bytes_p);
	}
}

/*
The FE::memzero function is a template function that initializes a specified number of bytes in a memory block to a given value
with support for both aligned and unaligned memory addresses based on the specified template parameter.
*/
template<Address DestAddressAlignment = Address::_NotAligned>
_FE_FORCE_INLINE_ void memzero(void* out_dest_p, uint64 bytes_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(out_dest_p));

	if constexpr (DestAddressAlignment == Address::_Aligned)
	{
		FE_ALIGNED_MEMZERO(out_dest_p, bytes_p);
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned)
	{
		FE_UNALIGNED_MEMZERO(out_dest_p, bytes_p);
	}
}

/*
The FE::memmove function is a template function that safely copies a specified number of bytes from a source memory location to a destination memory location
with optimizations based on the alignment of the destination address.
*/
template<Address DestAddressAlignment = Address::_NotAligned>
_FE_FORCE_INLINE_ void memmove(void* out_dest_p, const void* source_p, size bytes_p) noexcept  
{
	FE_NEGATIVE_ASSERT(out_dest_p == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(out_dest_p));
	FE_NEGATIVE_ASSERT(bytes_p == 0, "${%s@0}: ${%s@1} is zero", TO_STRING(FE::ErrorCode::_FatalMemoryError_1XX_NullPtr), TO_STRING(bytes_p));

	if constexpr (DestAddressAlignment == Address::_Aligned)
	{
		FE_ALIGNED_MEMMOVE(out_dest_p, source_p, bytes_p);
	}
	else if constexpr (DestAddressAlignment == Address::_NotAligned)
	{
		FE_UNALIGNED_MEMMOVE(out_dest_p, source_p, bytes_p);
	}
}




#ifdef FE_ALIGNED_ALLOC
#error FE_ALIGNED_ALLOC is a reserved Frogman Engine macro function.
#endif
#ifdef FE_ALIGNED_FREE
#error FE_ALIGNED_FREE is a reserved Frogman Engine macro function.
#endif
#ifdef _FE_ON_WINDOWS_X86_64_
#define FE_ALIGNED_ALLOC(size_p, alignment_p) ::_aligned_malloc(size_p, alignment_p)
#define FE_ALIGNED_FREE(ptr_to_memory_p) ::_aligned_free(ptr_to_memory_p)
#elif defined(_FE_ON_LINUX_X86_64_)
#define FE_ALIGNED_ALLOC(size_p, alignment_p) _mm_malloc(size_p, alignment_p)
#define FE_ALIGNED_FREE(ptr_to_memory_p) _mm_free(ptr_to_memory_p)
#endif


_FE_MAYBE_UNUSED_ constexpr var::uint64 invalid_memory_util_query = max_value<var::uint64>;

_FE_MAYBE_UNUSED_ constexpr FE::uint64 one_kb = 1024;
_FE_MAYBE_UNUSED_ constexpr FE::uint64 one_mb = 1048576;
_FE_MAYBE_UNUSED_ constexpr FE::uint64 one_gb = 1073741824;


enum struct HEAP_MEMORY_UTIL_INFO : FE::uint8
{
	_TOTAL_VIRTUAL_MEMORY_SIZE = 0,
	_TOTAL_VIRTUAL_MEMORY_UTIL = 1,

	_THIS_PROCESS_VIRTUAL_MEMORY_UTIL = 2,

	_TOTAL_PHYSICAL_MEMORY_SIZE = 3,
	_TOTAL_PHYSICAL_MEMORY_UTIL = 4,

	_THIS_PROCESS_PHYSICAL_MEMORY_UTIL = 5/*,

	_LIBRARY_TOTAL_HEAP_UTIL_SIZE = 6,

	_LIBRARY_HEAP_UTIL_SIZE_BY_THREAD_ID = 7,
	_LIBRARY_HEAP_UTIL_SIZE_BY_TYPE = 8*/
};

_FE_FORCE_INLINE_ var::float64 convert_bytes_to_kilobytes(uint64 bytes_p) noexcept
{
	return static_cast<var::float64>(bytes_p) / static_cast<var::float64>(one_kb);
}
_FE_FORCE_INLINE_ var::float64 convert_bytes_to_megabytes(uint64 bytes_p) noexcept
{
	return static_cast<var::float64>(bytes_p) / static_cast<var::float64>(one_mb);
}
_FE_FORCE_INLINE_ var::float64 convert_bytes_to_gigabytes(uint64 bytes_p) noexcept
{
	return static_cast<var::float64>(bytes_p) / static_cast<var::float64>(one_gb);
}

var::uint64 request_app_memory_utilization(const HEAP_MEMORY_UTIL_INFO select_data_p) noexcept;

/*
The operator new function allocates a specified number of bytes of memory
aligned to the size of the CPU's L1 cache line.
*/
void* ::operator new(std::size_t bytes_p);
void* ::operator new[](std::size_t bytes_p);

void ::operator delete(void* ptr_p) noexcept;
void ::operator delete[](void* ptr_p) noexcept;

void ::operator delete(void* ptr_p, std::size_t size_p) noexcept;
void ::operator delete[](void* ptr_p, std::size_t size_p) noexcept;




END_NAMESPACE

#undef __FE_DIVIDE_BY_2
#undef __FE_DIVIDE_BY_4
#undef __FE_DIVIDE_BY_8
#undef __FE_DIVIDE_BY_16
#undef __FE_DIVIDE_BY_32
#undef __FE_DIVIDE_BY_64
#undef __FE_DIVIDE_BY_128

#undef __FE_MODULO_BY_2
#undef __FE_MODULO_BY_4
#undef __FE_MODULO_BY_8
#undef __FE_MODULO_BY_16
#undef __FE_MODULO_BY_32
#undef __FE_MODULO_BY_64
#undef __FE_MODULO_BY_128
#endif
