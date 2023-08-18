#ifndef _FE_CORE_REF_TABLE_HXX_
#define _FE_CORE_REF_TABLE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/do_once.hxx>
#include <vector>
#include <queue> // this will be replaced with an in-house queue




BEGIN_NAMESPACE(FE)


template<typename T>
class proxy_ptr;

template<typename T, class allocator>
class exclusive_ptr;


template<typename T>
class ref_table_base 
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


	_CONSTEXPR20_ _FORCE_INLINE_ void initialize() noexcept
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
thread_local typename ref_table_base<T>::ref_table_type ref_table_base<T>::tl_s_ref_table;

template<typename T>
thread_local typename ref_table_base<T>::ref_table_recycler_type ref_table_base<T>::tl_s_ref_table_recycler;




template<typename T, class allocator>
class ref_table_for_exclusive_ptr : public ref_table_base<T>
{
	friend class exclusive_ptr<T, allocator>;

	using base_type = ref_table_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;
	using ref_table_recycler_type = typename base_type::ref_table_recycler_type;
	using ref_table_key_type = typename base_type::ref_table_key_type;


	_CONSTEXPR20_ _FORCE_INLINE_ static void __reserve(size_t new_size_p) noexcept
	{
		base_type::tl_s_ref_table.reserve(new_size_p);
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static void __shrink_to_fit() noexcept
	{
		base_type::tl_s_ref_table.shrink_to_fit();
		base_type::tl_s_ref_table_recycler.shrink_to_fit();
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static size_t __register_ref(pointer pointer_p) noexcept
	{
		if (base_type::tl_s_ref_table_recycler.empty() != true)
		{
			ref_table_key_type l_index_key = base_type::tl_s_ref_table_recycler.front();
			base_type::tl_s_ref_table_recycler.pop();
			base_type::tl_s_ref_table[l_index_key] = pointer_p;

			FE_ASSERT(base_type::tl_s_ref_table[l_index_key] != pointer_p, "Assertion Failed: failed to register a reference to the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[l_index_key]), pointer_p);
			return l_index_key;
		}

		ref_table_key_type l_index_key = base_type::tl_s_ref_table.size();
		base_type::tl_s_ref_table.emplace_back(pointer_p);

		FE_ASSERT(base_type::tl_s_ref_table[l_index_key] != pointer_p, "Assertion Failed: failed to register a reference to the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[l_index_key]), pointer_p);
		return l_index_key;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static void __unregister_ref(ref_table_key_type index_key_p, pointer pointer_p) noexcept
	{
		FE_ASSERT(base_type::tl_s_ref_table[index_key_p] != pointer_p, "Assertion Failed: failed to unregister a reference from the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[index_key_p]), pointer_p);
		base_type::tl_s_ref_table[index_key_p] = nullptr;
		base_type::tl_s_ref_table_recycler.push(index_key_p);
	}


	_CONSTEXPR20_ _FORCE_INLINE_ void initialize() noexcept
	{
		base_type::initialize();
	}
};




template<typename T>
class ref_table_for_proxy_ptr : public ref_table_base<T>
{
	friend class proxy_ptr<T>;

	using base_type = ref_table_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;
	using ref_table_key_type = typename base_type::ref_table_key_type;


	_CONSTEXPR20_ _FORCE_INLINE_ static pointer __check_ref(typename ref_table_type::size_type index_p, pointer validation_subject_p) noexcept
	{
		pointer l_value = base_type::tl_s_ref_table[index_p];

		return (l_value == validation_subject_p) ? l_value : nullptr;
	}
};


END_NAMESPACE
#endif