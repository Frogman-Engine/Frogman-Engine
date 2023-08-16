#ifndef _FE_CORE_SMART_PTR_BASE_HXX_
#define _FE_CORE_SMART_PTR_BASE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
#ifdef FE_VERIFY_SMART_PTR_VARIANT
#error FE_VERIFY_SMART_PTR_VARIANT is a reserved Frogman Engine macro keyword.
#endif
// ${%d at n} - int32
// ${%u at n} - uint32
// ${%ld at n} - int64
// ${%lu at n} - uint64
// ${%lf at n} - float64
// ${%f at n} - float32
// ${%b at n} - bool
// ${%c at n} - char
// ${%s at n} - string
// ${%p at n} - hexadecimal 64bit pointer
#define FE_VERIFY_SMART_PTR_VARIANT(expression_p, ...) if(expression_p) _UNLIKELY_ { ::FE::log::logger::log("Frogman Engine Crash Report", ::FE::log::buffered_string_formatter({__VA_ARGS__}), _SOURCE_CODE_LOCATION_); ::std::abort(); }
#include <FE/core/prerequisites.h>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/do_once.hxx>
#include <vector>
#include <queue> // this will be replaced with an in-house queue




BEGIN_NAMESPACE(FE)


template<typename T>
class smart_ptr_variant_base 
{
protected:
	using pointer = typename std::remove_extent<T>::type*;
	using element_type = typename std::remove_extent<T>::type;
	using ref_table_key_type = typename std::vector<pointer, FE::std_style::scalable_aligned_allocator<pointer>>::size_type;
	using ref_table_type = std::vector<pointer, FE::std_style::scalable_aligned_allocator<pointer>>;
	using ref_table_recycler_type = std::queue<ref_table_key_type>;  // this will be replaced with an in-house queue

	static constexpr auto ref_table_initial_size = 4096;
	thread_local static ref_table_type tl_s_ref_table;
	thread_local static ref_table_recycler_type tl_s_ref_table_recycler;

	pointer m_smart_ptr;
	ref_table_key_type m_ref_table_key;

	_CONSTEXPR20_ _FORCE_INLINE_ smart_ptr_variant_base(pointer value_p = nullptr, ref_table_key_type key_p = 0) noexcept : m_smart_ptr(value_p), m_ref_table_key(key_p)
	{
		thread_local static FE::do_once tl_s_initialize_once_per_thread
		(
			[&]()
			{
				tl_s_ref_table.reserve(ref_table_initial_size);
			}
		);
	}
};

template<typename T>
thread_local typename smart_ptr_variant_base<T>::ref_table_type smart_ptr_variant_base<T>::tl_s_ref_table;

template<typename T>
thread_local typename smart_ptr_variant_base<T>::ref_table_recycler_type smart_ptr_variant_base<T>::tl_s_ref_table_recycler;


END_NAMESPACE
#endif
#endif