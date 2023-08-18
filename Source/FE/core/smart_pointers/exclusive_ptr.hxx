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
#include <FE/core/smart_pointers/private/ref_table.hxx>




BEGIN_NAMESPACE(FE)


template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>>
class exclusive_ptr final
{
	static_assert(std::is_pointer<T>::value == false, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");
	
	using ref_table_type = ref_table_for_exclusive_ptr<T, allocator>;
	using ref_table_key_type = typename ref_table_type::ref_table_key_type;

public:
	static constexpr ref_table_key_type invalid_key_value = FE::_MAX_VALUE_<ref_table_key_type>;

	using pointer = typename std::remove_all_extents<T>::type*;
	using element_type = typename std::remove_all_extents<T>::type;
	using allocator_type = allocator;

private:
	pointer m_smart_ptr;
	ref_table_key_type m_ref_table_key;

public:
	_FORCE_INLINE_ constexpr exclusive_ptr() noexcept : m_smart_ptr(), m_ref_table_key(invalid_key_value) {}

	_CONSTEXPR23_ _FORCE_INLINE_ ~exclusive_ptr() noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			return;
		}

		ref_table_type::__unregister_ref(this->m_ref_table_key, this->m_smart_ptr);
		allocator::deallocate(this->m_smart_ptr, 1);
		this->m_smart_ptr = nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(const exclusive_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(exclusive_ptr&& rvalue_p) noexcept : m_smart_ptr(rvalue_p.m_smart_ptr), m_ref_table_key(rvalue_p.m_ref_table_key)
	{
		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_ref_table_key = invalid_key_value;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr(element_type value_p) noexcept : m_smart_ptr(allocator::allocate(1)), m_ref_table_key(invalid_key_value)
	{
		this->m_ref_table_key = ref_table_type::__register_ref(this->m_smart_ptr);
		*this->m_smart_ptr = std::move(value_p);
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(const exclusive_ptr& other_cref_p) noexcept = delete;

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(exclusive_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

		if (this->m_smart_ptr != nullptr)
		{
			allocator::deallocate(this->m_smart_ptr, 1);
		}

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;

		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = invalid_key_value;
		return *this;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ exclusive_ptr& operator=(element_type value_p) noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			this->m_smart_ptr = allocator::allocate(1);
		}

		*this->m_smart_ptr = std::move(value_p);
		this->m_ref_table_key = ref_table_type::__register_ref(this->m_smart_ptr);
		return *this;
	}

	_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		ref_table_type::__unregister_ref(this->m_ref_table_key, l_result);
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

		ref_table_key_type l_temporary_key = other_ref_p.m_ref_table_key;
		other_ref_p.m_ref_table_key = this->m_ref_table_key;
		this->m_ref_table_key = l_temporary_key;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ ref_table_key_type get_ref_table_key() const noexcept
	{
		return this->m_ref_table_key;
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
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));;
		return *this->m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ pointer operator->() const noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
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

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ exclusive_ptr<T, allocator> make_exclusive() noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, allocator>(T());
}

template<typename T, class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ _FORCE_INLINE_ exclusive_ptr<T, allocator> make_exclusive(T value_p) noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, allocator>(T(std::move(value_p)));
}




// Do not predict the size of exclusive_ptr. Use sizeof() operator instead.
template<typename T, class allocator>
class exclusive_ptr<T[], allocator> final 
{
	static_assert(std::is_pointer<T>::value == false, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");

public:

};


END_NAMESPACE
#endif