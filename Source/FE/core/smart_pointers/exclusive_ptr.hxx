#ifndef _FE_CORE_EXCLUSIVE_PTR_HXX_
#define _FE_CORE_EXCLUSIVE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
/*
* 
	NOTE: proxy_getter is an inner struct of a class exclusive_ptr.

	- MSVC failed to compile the code below in debug mode -

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	using owner_type = FE::exclusive_ptr<T, allocator, type_trait>;
	if (base_type::__check_ref( owner_type::proxy_getter::__retrieve_ref_table_key(exclusive_ptr_cref_p), owner_type::proxy_getter::get(exclusive_ptr_cref_p) ) != nullptr)
	{                                                     ^ __retrieve_ref_table_key() is a static method.                          ^ __retrieve_ref_table_key() is also a static method.
		
		this->m_ref_table_key = owner_type::proxy_getter::__retrieve_ref_table_key(exclusive_ptr_cref_p);
	} 
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Build started...
	1>------ Build started: Project: FE_TEST, Configuration: Debug x64 ------
	1>smart_ptr_variants-test.cpp
	1>C:\Users\leeho\OneDrive\문서\GitHub\Frogman-Engine-Lab\Source\FE/core/smart_pointers/proxy_ptr.hxx(168,1): fatal  error C1001: Internal compiler error.
	1>(compiler file 'msc1.cpp', line 1639)
	1> To work around this problem, try simplifying or changing the program near the locations listed above.
	1>If possible please provide a repro here: https://developercommunity.visualstudio.com
	1>Please choose the Technical Support command on the Visual C++
	1> Help menu, or open the Technical Support help file for more information
	1>C:\Users\leeho\OneDrive\문서\GitHub\Frogman-Engine-Lab\Source\FE/core/smart_pointers/proxy_ptr.hxx(158,28): message : This diagnostic occurred in the compiler generated function 'FE::proxy_ptr<T> &FE::proxy_ptr<T>::operator =(const FE::exclusive_ptr<T,allocator,type_trait> &) noexcept'
	1>C:\Users\leeho\OneDrive\문서\GitHub\Frogman-Engine-Lab\Source\FE/core/smart_pointers/proxy_ptr.hxx(228,2): message : see reference to class template instantiation 'FE::proxy_ptr<T>' being compiled
	1>INTERNAL COMPILER ERROR in 'C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\HostX64\x64\CL.exe'
	1>    Please choose the Technical Support command on the Visual C++
	1>    Help menu, or open the Technical Support help file for more information
	1>Done building project "FE_TEST.vcxproj" -- FAILED.
	========== Build: 0 succeeded, 1 failed, 1 up-to-date, 0 skipped ==========
	========== Build started at 12:10 AM and took 02.038 seconds ==========
*/
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
#include <FE/core/smart_pointers/private/smart_ptr_base.hxx>
#else
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>
#endif




BEGIN_NAMESPACE(FE)


template<typename T>
class proxy_ptr;


#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
template<typename T>
class exclusive_ptr_base : public smart_ptr_variant_base<T>
{
protected:
	using base_type = smart_ptr_variant_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;
	using ref_table_recycler_type = typename base_type::ref_table_recycler_type;
	using ref_table_key_type = typename base_type::ref_table_key_type;


	_CONSTEXPR20_ _FORCE_INLINE_ static void __reserve(size_t new_size_p) noexcept
	{
		base_type::tl_s_ref_table.reserve(new_size_p);
		base_type::tl_s_ref_table_recycler.reserve(new_size_p);
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static void __shrink_to_fit() noexcept
	{
		base_type::tl_s_ref_table.shrink_to_fit();
		base_type::tl_s_ref_table_recycler.shrink_to_fit();
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static size_t __register_ref(pointer pointer_p) noexcept
	{
		if(base_type::tl_s_ref_table_recycler.empty() != true)
		{
			ref_table_key_type l_index_key = base_type::tl_s_ref_table_recycler.front();
			base_type::tl_s_ref_table_recycler.pop();
			base_type::tl_s_ref_table[l_index_key] = pointer_p;

			FE_VERIFY_SMART_PTR_VARIANT(base_type::tl_s_ref_table[l_index_key] != pointer_p, "Assertion Failed: failed to register a reference to the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[l_index_key]), pointer_p);
			return l_index_key;
		}

		ref_table_key_type l_index_key = base_type::tl_s_ref_table.size();
		base_type::tl_s_ref_table.emplace_back(pointer_p);

		FE_VERIFY_SMART_PTR_VARIANT(base_type::tl_s_ref_table[l_index_key] != pointer_p, "Assertion Failed: failed to register a reference to the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[l_index_key]), pointer_p);
		return l_index_key;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static void __unregister_ref(ref_table_key_type index_key_p, pointer pointer_p) noexcept
	{
		FE_VERIFY_SMART_PTR_VARIANT(base_type::tl_s_ref_table[index_key_p] != pointer_p, "Assertion Failed: failed to unregister a reference from the table.\n${%s@0} must be equal to ${%p@1}.", TO_STRING(base_type::tl_s_ref_table[index_key_p]), pointer_p);
		base_type::tl_s_ref_table[index_key_p] = nullptr;
		base_type::tl_s_ref_table_recycler.push(index_key_p);
	}


	_CONSTEXPR20_ _FORCE_INLINE_ exclusive_ptr_base(pointer value_p = nullptr, ref_table_key_type key_p = 0) noexcept : base_type(value_p, key_p)
	{
	}
};
#endif




// Do not predict the size of exclusive_ptr. Use sizeof() operator instead.
template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
class exclusive_ptr final
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	: public exclusive_ptr_base<T>
#endif
{
	static_assert(std::is_pointer<T>::value == false, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");

public:
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	using base_type = exclusive_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
#else
	using base_type = void;
	using pointer = typename std::remove_all_extents<T>::type*;
	using element_type = typename std::remove_all_extents<T>::type;
#endif
	using allocator_type = allocator;
	using traits_type = type_trait;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
public:
	// this is an internal function and wiil be removed if _DISABLE_SMART_PTR_VARIANT_REF_TABLE_ is defined. DO NOT USE.
	_FORCE_INLINE_ typename base_type::ref_table_key_type __retrieve_ref_table_key() const noexcept
	{
		return this->m_ref_table_key;
	}
#else
private:
	pointer m_smart_ptr;

public:
#endif

	_FORCE_INLINE_ constexpr exclusive_ptr(pointer value_p = nullptr) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(value_p)
#else
		m_smart_ptr(value_p)
#endif
	{
	}

	_CONSTEXPR23_ _FORCE_INLINE_ ~exclusive_ptr() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type::__unregister_ref(this->m_ref_table_key, this->m_smart_ptr);
#endif
		allocator::deallocate(this->m_smart_ptr, 1);
		this->m_smart_ptr = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(const exclusive_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(exclusive_ptr&& rvalue_p) noexcept : 
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(rvalue_p.m_smart_ptr, rvalue_p.m_ref_table_key)
#else
		m_smart_ptr(rvalue_p.m_smart_ptr)
#endif
	{
		rvalue_p.m_smart_ptr = nullptr;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		rvalue_p.m_ref_table_key = _MAX_VALUE_<typename base_type::ref_table_key_type>;
#endif
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(element_type value_p) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(allocator::allocate(1))
#else
		m_smart_ptr(allocator::allocate(1))
#endif
	{
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_ref_table_key = base_type::__register_ref(this->m_smart_ptr);
#endif
		*this->m_smart_ptr = std::move(value_p);
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(const exclusive_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(exclusive_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = _MAX_VALUE_<typename base_type::ref_table_key_type>;
#endif
		return *this;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(element_type value_p) noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			this->m_smart_ptr = allocator::allocate(1);
		}

		*this->m_smart_ptr = std::move(value_p);

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_ref_table_key = base_type::__register_ref(this->m_smart_ptr);
#endif
		return *this;
	}

	_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type::__unregister_ref(this->m_ref_table_key, this->m_smart_ptr);
#endif
		this->m_smart_ptr = nullptr;
		return l_result;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset() noexcept
	{
		this->~exclusive_ptr();
	}

	_CONSTEXPR23_ _FORCE_INLINE_ void reset(element_type value_p) noexcept
	{
		this->~exclusive_ptr();
		*this = std::move(value_p);
	}

	_FORCE_INLINE_ void swap(exclusive_ptr& other_ref_p) noexcept
	{
		pointer l_temporary_smart_ptr = other_ref_p.m_smart_ptr;
		other_ref_p.m_smart_ptr = this->m_smart_ptr;
		this->m_smart_ptr = l_temporary_smart_ptr;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		typename base_type::ref_table_key_type l_temporary_key = other_ref_p.m_ref_table_key;
		other_ref_p.m_ref_table_key = this->m_ref_table_key;
		this->m_ref_table_key = l_temporary_key;
#endif
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ bool operator!() const noexcept
	{
		return (this->m_smart_ptr == nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_VERIFY_SMART_PTR_VARIANT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));;
		return *this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_VERIFY_SMART_PTR_VARIANT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}


	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator==(std::nullptr_t nullptr_p) noexcept
	{
		return this->m_smart_ptr == nullptr_p;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator!=(std::nullptr_t nullptr_p) noexcept
	{
		return this->m_smart_ptr != nullptr_p;
	}


	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator==(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr == other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator!=(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr != other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr > other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>=(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr >= other_cref_p.m_smart_ptr;
	}
	
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr < other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<=(const exclusive_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr <= other_cref_p.m_smart_ptr;
	}


	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator==(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr == other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator!=(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr != other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr > other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>=(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr >= other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr < other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<=(const proxy_ptr<T>& other_cref_p) noexcept
	{
		return this->m_smart_ptr <= other_cref_p.m_smart_ptr;
	}
};

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>, class type_trait = FE::type_trait<T, allocator>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ exclusive_ptr<T, allocator, type_trait> make_exclusive() noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, allocator, type_trait>(T());
}

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>, class type_trait = FE::type_trait<T, allocator>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ exclusive_ptr<T, allocator, type_trait> make_exclusive(T value_p) noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, allocator, type_trait>(T(std::move(value_p)));
}




// Do not predict the size of exclusive_ptr. Use sizeof() operator instead.
template<typename T, class allocator, class type_trait>
class exclusive_ptr<T[], allocator, type_trait> final 
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	: public exclusive_ptr_base<T>
#endif
{
	static_assert(std::is_pointer<T>::value == false, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");

public:
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	using base_type = exclusive_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
#else
	using base_type = void;
	using pointer = typename std::remove_all_extents<T>::type*;
	using element_type = typename std::remove_all_extents<T>::type;
#endif
	using allocator_type = allocator;
	using traits_type = type_trait;

#ifdef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
private:
	pointer m_smart_ptr;

public:
#endif

	_FORCE_INLINE_ constexpr exclusive_ptr(pointer value_p = nullptr) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(value_p)
#else
		m_smart_ptr(value_p)
#endif
	{
	}
};


END_NAMESPACE
#endif