#ifndef _FE_CORE_EXCLUSIVE_PTR_HXX_
#define _FE_CORE_EXCLUSIVE_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
/*
* 
	NOTE: proxy_getter is an inner struct of a class exclusive_ptr.

	- MSVC failed to compile the code below in debug mode -

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	using owner_type = FE::exclusive_ptr<T, allocator, type_traits>;
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
	1>C:\Users\leeho\OneDrive\문서\GitHub\Frogman-Engine-Lab\Source\FE/core/smart_pointers/proxy_ptr.hxx(158,28): message : This diagnostic occurred in the compiler generated function 'FE::proxy_ptr<T> &FE::proxy_ptr<T>::operator =(const FE::exclusive_ptr<T,allocator,type_traits> &) noexcept'
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


template<typename T>
class exclusive_ptr_base
{
	static_assert(std::is_pointer<T>::value == false, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");

	using ref_table_type = ref_table_base<T>;
	using ref_table_key_type = typename ref_table_type::ref_table_key_type;

	using ref_table_value_type = typename ref_table_type::ref_table_value_type;
	static_assert(std::is_same<ref_table_value_type, const exclusive_ptr_base<T>*>::value == true, "Static Assertion Failure: ref_table_value_type must be the same as exclusive_ptr_base<T>*");

public:
	using pointer = typename std::remove_all_extents<T>::type*;
	using this_pointer = exclusive_ptr_base*;
	using element_type = typename std::remove_all_extents<T>::type;

protected:
	pointer m_smart_ptr;
	ref_table_key_type m_ref_table_key;

	_FORCE_INLINE_ exclusive_ptr_base() noexcept : m_smart_ptr(), m_ref_table_key(ref_table_type::invalid_key_value)
	{
		if (ref_table_type::ref_table_initial_size > ref_table_type::tl_s_ref_table.capacity()) _UNLIKELY_
		{
			reserve_table(ref_table_type::ref_table_initial_size);
		}
	}

	_FORCE_INLINE_ exclusive_ptr_base(pointer value_p) noexcept : m_smart_ptr(value_p), m_ref_table_key(ref_table_type::invalid_key_value)
	{
		if (ref_table_type::ref_table_initial_size > ref_table_type::tl_s_ref_table.capacity()) _UNLIKELY_
		{
			reserve_table(ref_table_type::ref_table_initial_size);
		}
	}

	_FORCE_INLINE_ ~exclusive_ptr_base() noexcept {}

public:
	_FORCE_INLINE_ pointer get() const noexcept
	{
		return this->m_smart_ptr;
	}

	_FORCE_INLINE_ ref_table_key_type get_ref_table_key() const noexcept
	{
		return this->m_ref_table_key;
	}

	_FORCE_INLINE_ static void shrink_to_fit_table() noexcept
	{
		ref_table_type::tl_s_ref_table.shrink_to_fit();
		ref_table_type::tl_s_ref_table_recycler.shrink_to_fit();
	}

	_FORCE_INLINE_ static void resize_table(size_t new_size_p) noexcept
	{
		ref_table_type::tl_s_ref_table.resize(new_size_p);
		ref_table_type::tl_s_ref_table_recycler.resize(DIVIDE_BY_2(new_size_p));
	}

	_FORCE_INLINE_ static void reserve_table(capacity_t capacity_p) noexcept
	{
		ref_table_type::tl_s_ref_table.reserve(capacity_p);
		ref_table_type::tl_s_ref_table_recycler.reserve(DIVIDE_BY_2(capacity_p));
	}

	_FORCE_INLINE_ static capacity_t table_capacity() noexcept
	{
		return ref_table_type::tl_s_ref_table.capacity();
	}

	_FORCE_INLINE_ static size_t table_size() noexcept
	{
		return ref_table_type::tl_s_ref_table.size();
	}
};


template<typename T, class Allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>>
class exclusive_ptr final : public FE::exclusive_ptr_base<T>
{
	FE_STATIC_ASSERT(std::is_pointer<T>::value == true, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");
	FE_STATIC_ASSERT((std::is_same<T, Allocator::value_type>::value == false), "static assertion failed: enforcing Allocator's value_type to be equivalent to the typename T. The template parameter T must be identical to the value_type of the Allocator.");

public:
	using ref_table_type = ref_table_for_exclusive_ptr<T, Allocator>;
	using ref_table_key_type = typename ref_table_type::ref_table_key_type;

	using ref_table_value_type = typename ref_table_type::ref_table_value_type;
	static_assert(std::is_same<ref_table_value_type, const exclusive_ptr_base<T>*>::value == true, "Static Assertion Failure: ref_table_value_type must be the same as exclusive_ptr_base<T>*");

	using base_type = FE::exclusive_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = Allocator;

public:
	_CONSTEXPR17_ exclusive_ptr() noexcept : base_type() {}

	_CONSTEXPR23_ ~exclusive_ptr() noexcept
	{
		if (this->m_smart_ptr != nullptr)
		{
			Allocator::deallocate(this->m_smart_ptr, 1);
			this->m_smart_ptr = nullptr;
		}

		if (this->m_ref_table_key != ref_table_type::invalid_key_value)
		{
			ref_table_type::__unregister_ref(this->m_ref_table_key, this);
			this->m_ref_table_key = ref_table_type::invalid_key_value;
		}
	}

	_CONSTEXPR23_ exclusive_ptr(const exclusive_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ exclusive_ptr(exclusive_ptr&& rvalue_p) noexcept : base_type(rvalue_p.m_smart_ptr)
	{
		if ((rvalue_p.m_smart_ptr == nullptr) || (rvalue_p.m_ref_table_key == ref_table_type::invalid_key_value))
		{
			return;
		}

		ref_table_type::__update_ref(rvalue_p.m_ref_table_key, this);
		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = ref_table_type::invalid_key_value;
		rvalue_p.m_smart_ptr = nullptr;
	}

	_FORCE_INLINE_ exclusive_ptr(element_type value_p) noexcept : base_type(Allocator::allocate(1))
	{
		this->m_ref_table_key = ref_table_type::__register_ref(this);
		*this->m_smart_ptr = std::move(value_p);
	}

	_CONSTEXPR23_ exclusive_ptr& operator=(const exclusive_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ exclusive_ptr& operator=(exclusive_ptr&& rvalue_p) noexcept
	{
		if ((rvalue_p.m_smart_ptr == nullptr) || (rvalue_p.m_ref_table_key == ref_table_type::invalid_key_value))
		{
			return *this;
		}

		if (this->m_smart_ptr != nullptr)
		{
			Allocator::deallocate(this->m_smart_ptr, 1);
		}

		if (this->m_ref_table_key != ref_table_type::invalid_key_value)
		{
			ref_table_type::__unregister_ref(this->m_ref_table_key, this);
		}

		ref_table_type::__update_ref(rvalue_p.m_ref_table_key, this);

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;

		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = ref_table_type::invalid_key_value;
		return *this;
	}

	_CONSTEXPR20_ exclusive_ptr& operator=(element_type value_p) noexcept
	{
		if (this->m_smart_ptr == nullptr)
		{
			this->m_smart_ptr = Allocator::allocate(1);
		}

		if (this->m_ref_table_key == ref_table_type::invalid_key_value)
		{
			this->m_ref_table_key = ref_table_type::__register_ref(this);
		}

		*this->m_smart_ptr = std::move(value_p);
		return *this;
	}

	_NODISCARD_ _CONSTEXPR20_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;
		ref_table_type::__unregister_ref(this->m_ref_table_key, this);
		this->m_ref_table_key = ref_table_type::invalid_key_value;
		return l_result;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		this->~exclusive_ptr();
	}

	_FORCE_INLINE_ void reset(element_type value_p) noexcept
	{
		*this->operator=(std::move(value_p));
	}

	_CONSTEXPR20_ void swap(exclusive_ptr& in_out_other_p) noexcept
	{
		exclusive_ptr l_tmp = std::move(in_out_other_p);
		in_out_other_p = std::move(*this);
		*this = std::move(l_tmp);
	}

	_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_FORCE_INLINE_ bool operator!() const noexcept
	{
		return (this->m_smart_ptr == nullptr) ? true : false;
	}

	_FORCE_INLINE_ element_type& operator*() noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));;
		return *this->m_smart_ptr;
	}

	_FORCE_INLINE_ pointer operator->() noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}


	_FORCE_INLINE_ boolean operator==(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr == nullptr_p;
	}

	_FORCE_INLINE_ boolean operator!=(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr != nullptr_p;
	}


	_FORCE_INLINE_ boolean operator==(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}
	
	_FORCE_INLINE_ boolean operator<(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}


	_FORCE_INLINE_ boolean operator==(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}
};

template<typename T, class Allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ exclusive_ptr<T, Allocator> make_exclusive() noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, Allocator>(T());
}

template<typename T, class Allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<T>>>
_CONSTEXPR23_ _NODISCARD_ exclusive_ptr<T, Allocator> make_exclusive(T value_p) noexcept
{
	static_assert(std::is_array<T>::value == false, "static assertion failed: The typename T must not be an array type");
	return exclusive_ptr<T, Allocator>(T(std::move(value_p)));
}




template<typename T, class Allocator>
class exclusive_ptr<T[], Allocator> final : public FE::exclusive_ptr_base<T[]>
{
	FE_STATIC_ASSERT(std::is_pointer<T>::value == true, "static assertion failed: The typename T cannot be a pointer type. Use a nested smart pointer instead. e.g. FE::exclusive_ptr<FE::exclusive_ptr<T>> l_exclusive_ptr;");
	FE_STATIC_ASSERT((std::is_same<T, Allocator::value_type>::value == false), "static assertion failed: enforcing Allocator's value_type to be equivalent to the typename T. The template parameter T must be identical to the value_type of the Allocator.");

public:
	using ref_table_type = ref_table_for_exclusive_ptr<T[], Allocator>;
	using ref_table_key_type = typename ref_table_type::ref_table_key_type;

	using ref_table_value_type = typename ref_table_type::ref_table_value_type;
	static_assert(std::is_same<ref_table_value_type, const exclusive_ptr_base<T[]>*>::value == true, "Static Assertion Failure: ref_table_value_type must be the same as exclusive_ptr_base<T>*");

	using base_type = FE::exclusive_ptr_base<T[]>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using allocator_type = Allocator;

private:
	pointer m_smart_ptr_end;

public:
	_CONSTEXPR17_ exclusive_ptr() noexcept : base_type(), m_smart_ptr_end(base_type::m_smart_ptr) {}

	_CONSTEXPR23_ ~exclusive_ptr() noexcept
	{
		if (this->m_smart_ptr != nullptr)
		{
			Allocator::deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
			this->m_smart_ptr = nullptr;
			this->m_smart_ptr_end = nullptr;
		}

		if (this->m_ref_table_key != ref_table_type::invalid_key_value)
		{
			ref_table_type::__unregister_ref(this->m_ref_table_key, this);
			this->m_ref_table_key = ref_table_type::invalid_key_value;
		}
	}

	_CONSTEXPR23_ exclusive_ptr(const exclusive_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ exclusive_ptr(exclusive_ptr&& rvalue_p) noexcept : base_type(rvalue_p.m_smart_ptr), m_smart_ptr_end(rvalue_p.m_smart_ptr_end)
	{
		if ((rvalue_p.m_smart_ptr == nullptr) || (rvalue_p.m_ref_table_key == ref_table_type::invalid_key_value))
		{
			return;
		}
		
	
		ref_table_type::__update_ref(rvalue_p.m_ref_table_key, this);
		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = ref_table_type::invalid_key_value;
		rvalue_p.m_smart_ptr = nullptr;
		rvalue_p.m_smart_ptr_end = nullptr;
	}

	_FORCE_INLINE_ exclusive_ptr(FE::reserve&& array_size_p) noexcept : base_type(Allocator::allocate(array_size_p._value)), m_smart_ptr_end(base_type::m_smart_ptr + array_size_p._value)
	{
		this->m_ref_table_key = ref_table_type::__register_ref(this);
	}

	_CONSTEXPR20_ exclusive_ptr(std::initializer_list<element_type>&& values_p) noexcept : base_type(Allocator::allocate( values_p.size() )), m_smart_ptr_end(base_type::m_smart_ptr + values_p.size())
	{
		if (values_p.size() == 0)
		{
			return;
		}

		this->__copy_from_initializer_list(std::move(values_p));
		this->m_ref_table_key = ref_table_type::__register_ref(this);
	}

	_CONSTEXPR23_ exclusive_ptr& operator=(const exclusive_ptr& other_p) noexcept = delete;

	_CONSTEXPR20_ exclusive_ptr& operator=(exclusive_ptr&& rvalue_p) noexcept
	{
		if ((rvalue_p.m_smart_ptr == nullptr) || (rvalue_p.m_ref_table_key == ref_table_type::invalid_key_value))
		{
			return *this;
		}

		if (this->m_smart_ptr != nullptr)
		{
			Allocator::deallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr);
		}

		if (this->m_ref_table_key != ref_table_type::invalid_key_value)
		{
			ref_table_type::__unregister_ref(this->m_ref_table_key, this);
		}

		ref_table_type::__update_ref(rvalue_p.m_ref_table_key, this);

		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;

		this->m_smart_ptr_end = rvalue_p.m_smart_ptr_end;
		rvalue_p.m_smart_ptr_end = nullptr;

		this->m_ref_table_key = rvalue_p.m_ref_table_key;
		rvalue_p.m_ref_table_key = ref_table_type::invalid_key_value;
		return *this;
	}

	_CONSTEXPR20_ exclusive_ptr& operator=(std::initializer_list<element_type>&& values_p) noexcept
	{
		if (values_p.size() == 0)
		{
			return *this;
		}

		this->__reallocate(values_p.size());
		this->__copy_from_initializer_list(std::move(values_p));

		if (this->m_ref_table_key == ref_table_type::invalid_key_value)
		{
			this->m_ref_table_key = ref_table_type::__register_ref(this);
		}

		return *this;
	}

	_FORCE_INLINE_ exclusive_ptr& operator=(FE::resize_to&& new_array_size_p) noexcept
	{
		this->__reallocate(new_array_size_p._value);

		if (this->m_ref_table_key == ref_table_type::invalid_key_value)
		{
			this->m_ref_table_key = ref_table_type::__register_ref(this);
		}
		return *this;
	}

	_NODISCARD_ pointer release() noexcept
	{
		pointer l_result = this->m_smart_ptr;
		this->m_smart_ptr = nullptr;

		ref_table_type::__unregister_ref(this->m_ref_table_key, this);
		this->m_ref_table_key = ref_table_type::invalid_key_value;

		return l_result;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		this->~exclusive_ptr();
	}

	_FORCE_INLINE_ void reset(std::initializer_list<element_type>&& values_p) noexcept
	{
		this->operator=(std::move(values_p));
	}

	_FORCE_INLINE_ void reset(FE::resize_to new_array_size_p) noexcept
	{
		this->operator=(std::move(new_array_size_p));
	}

	_FORCE_INLINE_ void swap(exclusive_ptr& in_out_other_p) noexcept
	{
		exclusive_ptr l_tmp = std::move(in_out_other_p);
		in_out_other_p = std::move(*this);
		*this = std::move(l_tmp);
	}

	_FORCE_INLINE_ size_t size() const noexcept
	{
		return this->m_smart_ptr_end - this->m_smart_ptr;
	}

	_FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_FORCE_INLINE_ bool operator!() const noexcept
	{
		return (this->m_smart_ptr == nullptr) ? true : false;
	}

	_FORCE_INLINE_ element_type& operator*() noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));;
		return *this->m_smart_ptr;
	}

	_FORCE_INLINE_ pointer operator->() noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		return this->m_smart_ptr;
	}

	_FORCE_INLINE_ element_type& operator[](index_t index_p) noexcept
	{
		FE_ASSERT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
		FE_ASSERT(static_cast<index_t>(this->m_smart_ptr_end - this->m_smart_ptr) <= index_p, "${%s@0}: ${%s@1} exceeds the index boundary. ${%s@1} was ${%lu@2}.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE), TO_STRING(index_p), &index_p);

		return this->m_smart_ptr[index_p];
	}


	_FORCE_INLINE_ boolean operator==(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr == nullptr_p;
	}

	_FORCE_INLINE_ boolean operator!=(std::nullptr_t nullptr_p) const noexcept
	{
		return this->m_smart_ptr != nullptr_p;
	}


	_FORCE_INLINE_ boolean operator==(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const exclusive_ptr& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}


	_FORCE_INLINE_ boolean operator==(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr == other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator!=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr != other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr > other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator>=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr >= other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr < other_p.m_smart_ptr;
	}

	_FORCE_INLINE_ boolean operator<=(const proxy_ptr<T>& other_p) const noexcept
	{
		return this->m_smart_ptr <= other_p.m_smart_ptr;
	}

private:
	_CONSTEXPR20_ void __copy_from_initializer_list(std::initializer_list<element_type>&& values_p) noexcept
	{
		if constexpr (FE::is_trivially_constructible_and_destructible<T>::value == FE::TYPE_TRIVIALITY::_TRIVIAL)
		{
			std::memcpy(this->m_smart_ptr, const_cast<element_type*>(values_p.begin()), values_p.size() * sizeof(element_type));
		}
		else if constexpr (FE::is_trivially_constructible_and_destructible<T>::value == FE::TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			count_t l_initializer_list_size = values_p.size();

			pointer l_initializer_list_iterator = const_cast<pointer>(values_p.begin());
			pointer l_smart_ptr_iterator = this->m_smart_ptr;
			for (var::count_t i = 0; i < l_initializer_list_size; ++i)
			{
				*l_smart_ptr_iterator = std::move(*l_initializer_list_iterator);
				++l_smart_ptr_iterator;
				++l_initializer_list_iterator;
			}
		}
	}

	_FORCE_INLINE_ void __reallocate(size_t new_count_p) noexcept
	{
		this->m_smart_ptr = Allocator::reallocate(this->m_smart_ptr, this->m_smart_ptr_end - this->m_smart_ptr, new_count_p);
		this->m_smart_ptr_end = this->m_smart_ptr + new_count_p;
	}
};


template<typename T, class Allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>>
_CONSTEXPR23_ _NODISCARD_ exclusive_ptr<typename std::remove_all_extents<T>::type[], Allocator> make_exclusive(size_t array_size_p) noexcept
{
	static_assert(std::is_array<T>::value == true, "static assertion failed: The typename T must be an array type");
	return exclusive_ptr<typename std::remove_all_extents<T>::type[], Allocator>(FE::reserve{ array_size_p });
}

template<typename T, class Allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>>
_CONSTEXPR23_ _NODISCARD_ exclusive_ptr<typename std::remove_all_extents<T>::type[], Allocator> make_exclusive(std::initializer_list<typename std::remove_all_extents<T>::type>&& values_p) noexcept
{
	static_assert(std::is_array<T>::value == true, "static assertion failed: The typename T must be an array type");
	return exclusive_ptr<typename std::remove_all_extents<T>::type[], Allocator>(std::move(values_p));
}


END_NAMESPACE
#endif