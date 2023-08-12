#ifndef _FE_CORE_PROXY_PTR_HXX_
#define _FE_CORE_PROXY_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/smart_pointers/private/smart_ptr_base.hxx>




BEGIN_NAMESPACE(FE)


template<typename T>
class proxy_ptr_base : public engine_smart_ptr_base<T>
{
protected:
	using base_type = engine_smart_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;


	_FORCE_INLINE_ static pointer __check_ref(typename ref_table_type::size_type index_p, pointer validation_subject_p) noexcept
	{
		pointer l_value = tl_s_ref_table[index_p];

		return (l_value == validation_subject_p) ? l_value : nullptr;
	}
};


template<typename T>
class proxy_ptr final : public proxy_ptr_base<T>
{
	using base_type = proxy_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
};


template<typename T>
class proxy_ptr<T[]> final : public proxy_ptr_base<T>
{
	using base_type = proxy_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
};


END_NAMESPACE
#endif