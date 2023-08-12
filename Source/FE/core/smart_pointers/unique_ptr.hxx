#ifndef _FE_CORE_UNIQUE_PTR_HXX_
#define _FE_CORE_UNIQUE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/smart_pointers/private/smart_ptr_base.hxx>




BEGIN_NAMESPACE(FE)


template<typename T>
class unique_ptr_base : public smart_ptr_base<T>
{
protected:
	using base_type = smart_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;

	pointer __alloc_and_assign_if_empty(element_type value_p) noexcept
	{
		
	}
};


template<typename T, class allocator = FE::scalable_aligned_allocator<T, FE::align_8bytes>>
class unique_ptr final : public unique_ptr_base<T>
{
public:
	using base_type = unique_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = allocator;
};


template<typename T, class allocator>
class unique_ptr<T[], allocator> final : public unique_ptr_base<T>
{
public:
	using base_type = unique_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = allocator;
};


END_NAMESPACE
#endif