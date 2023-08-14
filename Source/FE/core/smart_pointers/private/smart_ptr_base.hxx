#ifndef _FE_CORE_SMART_PTR_BASE_HXX_
#define _FE_CORE_SMART_PTR_BASE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/allocator_adaptor.hxx>
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
#include <vector>
#endif




BEGIN_NAMESPACE(FE)


template<typename T>
class smart_ptr_variant_base 
{
protected:
	using pointer = T*;
	using element_type = T;;
	using ref_table_key_type = typename std::vector<pointer, FE::std_style::scalable_aligned_allocator<element_type, FE::align_8bytes>>::size_type;
	using ref_table_type = std::vector<pointer, FE::std_style::scalable_aligned_allocator<element_type, FE::align_8bytes>>;

	static constexpr auto ref_table_initial_size = 1024;
	thread_local static ref_table_type tl_s_ref_table;

	ref_table_key_type m_ref_table_key;
	pointer m_smart_ptr;
};

template<typename T>
thread_local typename smart_ptr_variant_base<T>::ref_table_type smart_ptr_variant_base<T>::tl_s_ref_table;


END_NAMESPACE
#endif