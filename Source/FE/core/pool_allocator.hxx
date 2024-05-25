#ifndef _FE_CORE_POOL_ALLOCATOR_HXX_
#define _FE_CORE_POOL_ALLOCATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/private/pool_allocator_base.hxx>




BEGIN_NAMESPACE(FE)


template <typename T, class Alignment = FE::SIMD_auto_alignment>
class pool_allocator : public pool_allocator_base<Alignment>
{
public:
	using base_type = pool_allocator_base<Alignment>;
	using value_type = T;
	using pointer = value_type*;
	using const_pointer = const pointer;
	using reference = value_type&;
	using const_reference = value_type&;
	using difference_type = var::ptrdiff_t;
	using size_type = var::size_t;
	using alignment_type = Alignment;

	_MAYBE_UNUSED_ static constexpr inline auto is_trivial = FE::is_trivial<value_type>::value;
	_MAYBE_UNUSED_ static constexpr inline ADDRESS is_address_aligned = (std::is_same<alignment_type, FE::SIMD_auto_alignment>::value == true) ? ADDRESS::_ALIGNED : ADDRESS::_NOT_ALIGNED;


	constexpr pool_allocator() noexcept {}

	template <typename U = T>
	constexpr pool_allocator(_MAYBE_UNUSED_ const pool_allocator<U, Alignment>& other_p) noexcept {}


	_FORCE_INLINE_ void create_pages(const size_type count_p) noexcept
	{
		base_type::s_pool->create_pages(count_p);
	}

	_FORCE_INLINE_ void shrink_to_fit() noexcept
	{
		base_type::s_pool->shrink_to_fit();
	}


	_NODISCARD_ _FORCE_INLINE_ pointer allocate(const size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), &count_p);

		return (T*)base_type::s_pool->template allocate<var::byte>(FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(count_p)).release();
	}

	_NODISCARD_ _FORCE_INLINE_ pointer reallocate(pointer const pointer_p, const size_type prev_count_p, const size_type new_count_p) noexcept
	{
		if (new_count_p == 0)
		{
			base_type::s_pool->template deallocate<var::byte>(reinterpret_cast<var::byte* const>(pointer_p), FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(prev_count_p));
			return nullptr;
		}

		pointer l_result = (T*)base_type::s_pool->template allocate<var::byte>(FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(new_count_p)).release();

		if (pointer_p != nullptr) _LIKELY_
		{
			FE::memcpy<is_address_aligned, is_address_aligned>(l_result, sizeof(T) * new_count_p, pointer_p, sizeof(T) * prev_count_p);
			base_type::s_pool->template deallocate<var::byte>(reinterpret_cast<var::byte* const>(pointer_p), FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(prev_count_p));
		}

		return l_result;
	}

	_FORCE_INLINE_ void deallocate(pointer const pointer_p, _MAYBE_UNUSED_ const size_type count_p) noexcept
	{
		FE_ASSERT(count_p == 0, "${%s@0}: queried allocation size is ${%lu@1}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE), &count_p);
		FE_ASSERT(pointer_p == nullptr, "${%s@0}: attempted to delete nullptr.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR));

		base_type::s_pool->template deallocate<var::byte>(reinterpret_cast<var::byte* const>(pointer_p), FE::calculate_aligned_memory_size_in_bytes<T, Alignment>(count_p));
	}

	_CONSTEXPR20_ var::boolean operator==(_MAYBE_UNUSED_ const pool_allocator& other_p) noexcept
	{
		return true;
	}
#ifndef _HAS_CXX23_
	_CONSTEXPR20_ var::boolean operator!=(_MAYBE_UNUSED_ const pool_allocator& other_p) noexcept
	{
		return false;
	}
#endif
};


END_NAMESPACE
#endif