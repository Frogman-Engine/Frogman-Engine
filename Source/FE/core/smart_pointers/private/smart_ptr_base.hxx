#ifndef _FE_CORE_SMART_PTR_BASE_HXX_
#define _FE_CORE_SMART_PTR_BASE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/allocator_adaptor.hxx>
#include <vector>




BEGIN_NAMESPACE(FE)


template<typename T>
class smart_ptr_base
{
protected:
	using pointer = T*;
	using element_type = T;

	pointer m_smart_ptr;
};


template<typename T>
class engine_smart_ptr_base : public smart_ptr_base<T>
{
protected:
	using base_type = smart_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;

	using ref_table_type = std::vector<pointer, FE::std_style::scalable_aligned_allocator<element_type, FE::align_8bytes>>;

	static constexpr auto ref_table_initial_size = 1024;
	thread_local static ref_table_type tl_s_ref_table;
};

template<typename T>
thread_local typename engine_smart_ptr_base<T>::ref_table_type engine_smart_ptr_base<T>::tl_s_ref_table;


END_NAMESPACE
#endif