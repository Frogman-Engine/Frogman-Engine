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
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef var::size_t size_type;
		typedef FE::scalable_aligned_allocator<T> allocator;


		constexpr scalable_aligned_allocator() noexcept {}

		template <typename U>
		constexpr scalable_aligned_allocator(_MAYBE_UNUSED_ const scalable_aligned_allocator<U>& standard_allocator_cref_p) noexcept {};


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
