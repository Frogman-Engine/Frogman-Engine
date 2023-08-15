#ifndef _FE_CORE_ALLOCATOR_ADAPTORS_HXX_
#define _FE_CORE_ALLOCATOR_ADAPTORS_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "allocator.hxx"




BEGIN_NAMESPACE(FE)


namespace std_style 
{
	template <class implementation>
	class new_delete_proxy_allocator final
	{
	public:
		using value_type = typename implementation::value_type;
		using pointer = typename implementation::pointer;
		using const_pointer = const typename implementation::const_pointer;
		using reference = typename implementation::reference;
		using const_reference = const typename implementation::const_reference;
		using size_type = typename implementation::size_type;
		using allocator = implementation;

		_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
		_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = implementation::is_allocated_from_an_address_aligned_allocator;


		constexpr new_delete_proxy_allocator() noexcept {}

		template <typename another_implementation>
		constexpr new_delete_proxy_allocator(_MAYBE_UNUSED_ const new_delete_proxy_allocator<another_implementation>& standard_allocator_cref_p) noexcept {}


		_NODISCARD_ _FORCE_INLINE_ pointer allocate(size_type count_p) noexcept
		{
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

			pointer l_result = allocator::allocate(count_p);

			if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				new(l_result) value_type[count_p]{};
			}
			return l_result;
		}

		_NODISCARD_ _FORCE_INLINE_ pointer reallocate(pointer const pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
		{
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));

			if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				pointer const l_end = pointer_p + prev_count_p;
				for (pointer begin = pointer_p; begin != l_end; ++begin)
				{
					begin->~value_type();
				}
			}

			pointer l_result = allocator::reallocate(pointer_p, prev_count_p, new_count_p);

			if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				new(l_result) value_type[new_count_p]{};
			}
			return l_result;
		}

		_FORCE_INLINE_ void deallocate(pointer const pointer_p, size_type count_p) noexcept
		{
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: attempted to delete ${%p@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), pointer_p);

			if constexpr (is_trivially_constructible_and_destructible == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				pointer const l_end = pointer_p + count_p;
				for (pointer begin = pointer_p; begin != l_end; ++begin)
				{
					begin->~value_type();
				}
			}
			allocator::deallocate(pointer_p, count_p);
		}
	};

	
#if _AVX512_ == true
	template<typename T, class alignment = align_64bytes>
#elif _AVX_ == true
	template<typename T, class alignment = align_32bytes>
#endif
	class scalable_aligned_allocator // trackable scalable_aligned_allocator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = var::size_t;
		using allocator = FE::scalable_aligned_allocator<T, alignment>;

		_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
		_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = true;


		constexpr scalable_aligned_allocator() noexcept {}

		template <typename U>
		constexpr scalable_aligned_allocator(_MAYBE_UNUSED_ const scalable_aligned_allocator<U, alignment>& standard_allocator_cref_p) noexcept {}


		_NODISCARD_ _FORCE_INLINE_ pointer allocate(size_type count_p) noexcept
		{
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

			return allocator::allocate(count_p);
		}

		_NODISCARD_ _FORCE_INLINE_ pointer reallocate(pointer pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
		{
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));

			return allocator::reallocate(pointer_p, prev_count_p, new_count_p);
		}

		_FORCE_INLINE_ void deallocate(pointer const pointer_p, size_type count_p) noexcept
		{
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

			allocator::deallocate(pointer_p, count_p);
		}
	};

	// trackable cache_aligned_allocator
	template<typename T>
	class cache_aligned_allocator 
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = var::size_t;
		using allocator = FE::cache_aligned_allocator<T>;

		_MAYBE_UNUSED_ static constexpr inline auto is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<value_type>::value;
		_MAYBE_UNUSED_ static constexpr inline boolean is_allocated_from_an_address_aligned_allocator = true;


		constexpr cache_aligned_allocator() noexcept {}

		template <typename U>
		constexpr cache_aligned_allocator(_MAYBE_UNUSED_ const cache_aligned_allocator<U>& cache_aligned_allocator_cref_p) noexcept {}


		_NODISCARD_ _FORCE_INLINE_ pointer allocate(size_type count_p) noexcept
		{
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

			return allocator::allocate(count_p);
		}

		_NODISCARD_ _FORCE_INLINE_ pointer reallocate(pointer const pointer_p, size_type prev_count_p, size_type new_count_p) noexcept
		{
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));

			return allocator::reallocate(pointer_p, prev_count_p, new_count_p);
		}

		_FORCE_INLINE_ void deallocate(pointer const pointer_p, size_type count_p) noexcept
		{
			FE_ASSERT(pointer_p == nullptr, "${%s@0}: ${%s@1} is nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(pointer_p));
			FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE), &count_p);

			allocator::deallocate(pointer_p, count_p);
		}
	};
}


END_NAMESPACE
#endif
