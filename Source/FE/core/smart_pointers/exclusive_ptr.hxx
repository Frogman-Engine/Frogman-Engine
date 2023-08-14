#ifndef _FE_CORE_EXCLUSIVE_PTR_HXX_
#define _FE_CORE_EXCLUSIVE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/smart_pointers/private/smart_ptr_base.hxx>




BEGIN_NAMESPACE(FE)


template<typename T>
class exclusive_ptr_base : public smart_ptr_variant_base<T>
{
protected:
	using base_type = smart_ptr_variant_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;


	_FORCE_INLINE_ static void __initialize_ref_table() noexcept
	{
		tl_s_ref_table.reserve(ref_table_initial_size);
	}

	_FORCE_INLINE_ static void __reserve(size_t new_size_p) noexcept
	{
		tl_s_ref_table.reserve(new_size_p);
	}

	_FORCE_INLINE_ static void __shrink_to_fit() noexcept
	{
		tl_s_ref_table.shrink_to_fit();
	}

	_FORCE_INLINE_ static size_t __register_ref(pointer pointer_p) noexcept
	{
		typename ref_table_type::size_type l_index_key = tl_s_ref_table.size();
		tl_s_ref_table.emplace_back(pointer_p);

		FE_ASSERT(tl_s_ref_table[l_index_key] != pointer_p, "Assertion Failed: failed to register a reference to the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(tl_s_ref_table[l_index_key]), pointer_p);
		return l_index_key;
	}

	_FORCE_INLINE_ static void __unregister_ref(typename ref_table_type::size_type index_key_p, pointer pointer_p) noexcept
	{
		FE_ASSERT(tl_s_ref_table[index_key_p] != pointer_p, "Assertion Failed: failed to unregister a reference from the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(tl_s_ref_table[index_key_p]), pointer_p);
		tl_s_ref_table[index_key_p] = nullptr;
	}
};


template<typename T, class allocator = FE::scalable_aligned_allocator<T, FE::align_8bytes>>
class exclusive_ptr final : public exclusive_ptr_base<T>
{
public:
	using base_type = exclusive_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = allocator;
};


template<typename T, class allocator>
class exclusive_ptr<T[], allocator> final : public exclusive_ptr_base<T>
{
public:
	using base_type = exclusive_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = allocator;
};


END_NAMESPACE
#endif