#ifndef _FE_CORE_PROXY_PTR_HXX_
#define _FE_CORE_PROXY_PTR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/smart_pointers/private/smart_ptr_base.hxx>




BEGIN_NAMESPACE(FE)


template<typename T, class allocator, class type_trait>
class exclusive_ptr;


#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
template<typename T>
class proxy_ptr_base : public smart_ptr_variant_base<T>
{
protected:
	using base_type = smart_ptr_variant_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
	using ref_table_type = typename base_type::ref_table_type;


	_CONSTEXPR20_ _FORCE_INLINE_ static pointer __check_ref(typename ref_table_type::size_type index_p, pointer validation_subject_p) noexcept
	{
		pointer l_value = base_type::tl_s_ref_table[index_p];

		return (l_value == validation_subject_p) ? l_value : nullptr;
	}
};
#endif




template<typename T>
class proxy_ptr final 
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	: public proxy_ptr_base<T>
#endif
{
public:
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	using base_type = proxy_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
#else
	using base_type = void;
	using pointer = typename std::remove_all_extents<T>::type*;
	using element_type = typename std::remove_all_extents<T>::type;
#endif
#ifdef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
private:
	pointer m_smart_ptr;

public:
#endif

	constexpr _FORCE_INLINE_ proxy_ptr() noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type()
#else
		m_smart_ptr()
#endif
	{
	}

	_FORCE_INLINE_ proxy_ptr(const proxy_ptr& other_cref_p) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(base_type::__check_ref(other_cref_p.m_ref_table_key, other_cref_p.m_smart_ptr))
#else
		m_smart_ptr(other_cref_p.m_smart_ptr)
#endif
	{
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = other_cref_p.m_ref_table_key;
		}
#endif
	}

	_FORCE_INLINE_ proxy_ptr(proxy_ptr&& rvalue_p) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(base_type::__check_ref(rvalue_p.m_ref_table_key, rvalue_p.m_smart_ptr))
#else
		m_smart_ptr(rvalue_p.m_smart_ptr)
#endif
	{
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = rvalue_p.m_ref_table_key;
			rvalue_p.m_ref_table_key = _MAX_VALUE_<typename base_type::ref_table_key_type>;
		}
#endif
		rvalue_p.m_smart_ptr = nullptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_FORCE_INLINE_ proxy_ptr(const FE::exclusive_ptr<T, allocator, type_trait>& exclusive_ptr_cref_p) noexcept :
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		base_type(base_type::__check_ref(exclusive_ptr_cref_p.__retrieve_ref_table_key(), exclusive_ptr_cref_p.get()))
#else
		m_smart_ptr(exclusive_ptr_cref_p.m_smart_ptr)
#endif
	{
		using owner_type = FE::exclusive_ptr<T, allocator, type_trait>;

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = exclusive_ptr_cref_p.__retrieve_ref_table_key();
		}
#endif
	}

	_FORCE_INLINE_ proxy_ptr& operator=(const proxy_ptr& other_cref_p) noexcept
	{
		if (other_cref_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_smart_ptr = base_type::__check_ref(other_cref_p.m_ref_table_key, other_cref_p.m_smart_ptr);
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = other_cref_p.m_ref_table_key;
		}
#else
		this->m_smart_ptr = other_cref_p.m_smart_ptr;
#endif
		
		return *this;
	}

	_FORCE_INLINE_ proxy_ptr& operator=(proxy_ptr&& rvalue_p) noexcept
	{
		if (rvalue_p.m_smart_ptr == nullptr)
		{
			return *this;
		}

#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_smart_ptr = base_type::__check_ref(rvalue_p.m_ref_table_key, rvalue_p.m_smart_ptr);
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = rvalue_p.m_ref_table_key;
			rvalue_p.m_ref_table_key = _MAX_VALUE_<typename base_type::ref_table_key_type>;
		}
#else
		this->m_smart_ptr = rvalue_p.m_smart_ptr;
		rvalue_p.m_smart_ptr = nullptr;
#endif
		return *this;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_FORCE_INLINE_ proxy_ptr& operator=(const FE::exclusive_ptr<T, allocator, type_trait>& exclusive_ptr_cref_p) noexcept
	{
		using owner_type = FE::exclusive_ptr<T, allocator, type_trait>;
		
		if (!exclusive_ptr_cref_p)
		{
			return *this;
		}
		
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		typename base_type::ref_table_key_type l_retrieved_ref_table_key = exclusive_ptr_cref_p.__retrieve_ref_table_key();
		this->m_smart_ptr = base_type::__check_ref(l_retrieved_ref_table_key, exclusive_ptr_cref_p.get());
		if (this->m_smart_ptr != nullptr)
		{
			this->m_ref_table_key = l_retrieved_ref_table_key;
		}
#else
		this->m_smart_ptr = exclusive_ptr_cref_p.m_smart_ptr;
#endif
		return *this;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		this->m_smart_ptr = nullptr;
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		this->m_ref_table_key = _MAX_VALUE_<typename base_type::ref_table_key_type>;
#endif
	}

	_FORCE_INLINE_ void swap(proxy_ptr& other_ref_p) noexcept
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

	_FORCE_INLINE_ var::boolean is_expired() const noexcept
	{
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
		return base_type::__check_ref(this->m_ref_table_key, this->m_smart_ptr) == nullptr;
#else
		return this->m_smart_ptr == nullptr;
#endif
	}

	_CONSTEXPR23_ _FORCE_INLINE_ explicit operator bool() const noexcept
	{
		return (this->m_smart_ptr != nullptr) ? true : false;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ bool operator!() const noexcept
	{
		return this->m_smart_ptr == nullptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ element_type& operator*() const noexcept
	{
		FE_VERIFY_SMART_PTR_VARIANT(this->m_smart_ptr == nullptr, "${%s@0}: ${%s@1} is nullptr", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_NULLPTR), TO_STRING(this->m_smart_ptr));
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


	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator==(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr == other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator!=(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr != other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr > other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>=(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr >= other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr < other_cref_p.m_smart_ptr;
	}

	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<=(const proxy_ptr& other_cref_p) noexcept
	{
		return this->m_smart_ptr <= other_cref_p.m_smart_ptr;
	}


	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator==(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr == other_cref_p.m_smart_ptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator!=(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr != other_cref_p.m_smart_ptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr > other_cref_p.m_smart_ptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator>=(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr >= other_cref_p.m_smart_ptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr < other_cref_p.m_smart_ptr;
	}

	template<class allocator = FE::new_delete_proxy_allocator<FE::scalable_aligned_allocator<typename std::remove_all_extents<T>::type>>, class type_trait = FE::type_trait<typename std::remove_all_extents<T>::type, allocator>>
	_CONSTEXPR23_ _FORCE_INLINE_ var::boolean operator<=(const FE::exclusive_ptr<T, allocator, type_trait>& other_cref_p) noexcept
	{
		return this->m_smart_ptr <= other_cref_p.m_smart_ptr;
	}
};


template<typename T>
class proxy_ptr<T[]> final
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	: public proxy_ptr_base<T>
#endif
{
#ifndef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
	using base_type = proxy_ptr_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;
#else
	using base_type = void;
	using pointer = typename std::remove_all_extents<T>::type*;
	using element_type = typename std::remove_all_extents<T>::type;
#endif
#ifdef _DISABLE_SMART_PTR_VARIANT_REF_TABLE_
private:
	pointer m_smart_ptr;

public:
#endif
};


END_NAMESPACE
#endif