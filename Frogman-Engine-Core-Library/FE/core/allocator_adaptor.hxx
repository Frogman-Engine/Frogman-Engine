#ifndef _FE_CORE_ALLOCATOR_ADAPTORS_HXX_
#define _FE_CORE_ALLOCATOR_ADAPTORS_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "allocator.hxx"


BEGIN_NAMESPACE(FE)


namespace std_style 
{
	template<typename T>
	class scalable_aligned_allocator // trackable scalable_aligned_allocator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = var::size_t;
		using allocator = FE::scalable_aligned_allocator<T>;

		constexpr scalable_aligned_allocator() noexcept {}

		template <typename U>
		constexpr scalable_aligned_allocator(_MAYBE_UNUSED_ const scalable_aligned_allocator<U>& standard_allocator_cref_p) noexcept {}


		_NODISCARD_ _FORCE_INLINE_ T* allocate(size_t count_p) noexcept
		{
			return allocator::allocate(count_p);
		}

		_NODISCARD_ _FORCE_INLINE_ T* reallocate(T* const ptrc_p, size_t prev_count_p, size_t new_count_p) noexcept
		{
			return allocator::reallocate(ptrc_p, prev_count_p, new_count_p);
		}

		_FORCE_INLINE_ void deallocate(T* const ptrc_p, size_t count_p) noexcept
		{
			allocator::deallocate(ptrc_p, count_p);
		}
	};


	template<typename T>
	class cache_aligned_allocator // trackable cache_aligned_allocator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = var::size_t;
		using allocator = FE::cache_aligned_allocator<T>;


		constexpr cache_aligned_allocator() noexcept {}

		template <typename U>
		constexpr cache_aligned_allocator(_MAYBE_UNUSED_ const cache_aligned_allocator<U>& cache_aligned_allocator_cref_p) noexcept {}


		_NODISCARD_ _FORCE_INLINE_ T* allocate(size_t count_p) noexcept
		{
			return allocator::allocate(count_p);
		}

		_NODISCARD_ _FORCE_INLINE_ T* reallocate(T* const ptrc_p, size_t prev_count_p, size_t new_count_p) noexcept
		{
			return allocator::reallocate(ptrc_p, prev_count_p, new_count_p);
		}

		_FORCE_INLINE_ void deallocate(T* const ptrc_p, size_t count_p) noexcept
		{
			allocator::deallocate(ptrc_p, count_p);
		}
	};
}


END_NAMESPACE
#endif
