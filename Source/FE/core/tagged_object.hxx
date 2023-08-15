#ifndef _FE_CORE_TAGGED_OBJECT_HXX_
#define _FE_CORE_TAGGED_OBJECT_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/memory.hxx>
#include <FE/core/cstring.hxx>




BEGIN_NAMESPACE(FE)


#pragma pack(push, _DWORD_SIZE_)

template <typename T, class alignment = ::FE::align_8bytes, class string = compile_time_constant_string<char>>
class alignas(alignment::size) tagged_object final
{
private:
	string m_tag;
	T m_object;

public:
	typedef T value_type;
	typedef alignment alignment_type;
	typedef string tag_type;

	constexpr tagged_object() noexcept : m_tag("\0"), m_object() {}
	_FORCE_INLINE_ tagged_object(T object_p, string tag_p) noexcept : m_tag(std::move(tag_p)), m_object(std::move(object_p)) {}
	_FORCE_INLINE_ tagged_object(T object_p) noexcept : m_tag("\0"), m_object(std::move(object_p)) {}
	

	_FORCE_INLINE_ tagged_object(tagged_object<T, alignment, string>& other_ref_p) noexcept
	{
		this->m_object = other_ref_p.m_object;
		this->m_tag = other_ref_p.m_tag;
	}


	_FORCE_INLINE_ tagged_object(tagged_object<T, alignment, string>&& rvalue_p) noexcept
	{
		this->m_object = rvalue_p.m_object;
		this->m_tag = rvalue_p.m_tag;
	}


	_CONSTEXPR20_ ~tagged_object() noexcept {};


	_FORCE_INLINE_ T& operator=(T value_p) noexcept
	{
		this->m_object = ::std::move(value_p);
		return this->m_object;
	}
	
	_FORCE_INLINE_ string& operator=(string tag_p) noexcept
	{
		this->m_tag = ::std::move(tag_p);
		return this->m_tag;
	}


	_FORCE_INLINE_ tagged_object& operator=(tagged_object<T, alignment, string>& other_ref_p) noexcept
	{
		this->m_object = other_ref_p.m_object;
		this->m_tag = other_ref_p.m_tag;

		return *this;
	}
	_FORCE_INLINE_ tagged_object& operator=(tagged_object<T, alignment, string>&& rvalue_p) noexcept
	{
		this->m_object = rvalue_p.m_object;
		this->m_tag = rvalue_p.m_tag;

		return *this;
	}

	constexpr T copy_object() noexcept { return this->m_object; }
	constexpr string copy_tag() noexcept { return this->m_tag; }


	_FORCE_INLINE_ boolean operator==(string tag_p) noexcept
	{
		return this->m_tag == tag_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator==(T value_p) noexcept
	{
		return this->m_object == value_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator!=(string tag_p) noexcept
	{
		return this->m_tag != tag_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator!=(T value_p) noexcept
	{
		return this->m_object != value_p ? true : false;
	}

	_FORCE_INLINE_ boolean operator==(string& tag_ref_p) noexcept
	{
		return this->m_tag == tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator==(T& value_ref_p) noexcept
	{
		return this->m_object == value_ref_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator!=(string& tag_ref_p) noexcept
	{
		return this->m_tag != tag_ref_p ? true : false;
	}
	_FORCE_INLINE_ boolean operator!=(T& value_ref_p) noexcept
	{
		return this->m_object != value_ref_p ? true : false;
	}


	_FORCE_INLINE_ friend boolean operator==(T value_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return value_p == element_ref_p.m_object ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(T value_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return value_p != element_ref_p.m_object ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator==(T& value_ref_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return value_ref_p == element_ref_p.m_object ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(T& value_ref_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return value_ref_p != element_ref_p.m_object ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator==(string tag_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return tag_p == element_ref_p.m_tag ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(string tag_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return tag_p != element_ref_p.m_tag ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator==(string& tag_ref_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return tag_ref_p == element_ref_p.m_tag ? true : false;
	}
	_FORCE_INLINE_ friend boolean operator!=(string& tag_ref_p, tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		return tag_ref_p != element_ref_p.m_tag ? true : false;
	}

	_FORCE_INLINE_ boolean operator==(tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		if (this->m_object != element_ref_p.m_object)
		{
			return false;
		}

		if (this->m_tag != element_ref_p.m_tag)
		{
			return false;
		}

		return true;
	}
	_FORCE_INLINE_ boolean operator!=(tagged_object<T, alignment, string>& element_ref_p) noexcept
	{
		if (this->m_object == element_ref_p.m_object)
		{
			return false;
		}

		if (this->m_tag == element_ref_p.m_tag)
		{
			return false;
		}

		return true;
	}

	_FORCE_INLINE_ static void swap(tagged_object<T, alignment, string>& left_ref_p, tagged_object<T, alignment, string>& right_ref_p) noexcept
	{
		tagged_object<T, alignment, string> l_temp = ::std::move(left_ref_p);
		left_ref_p = ::std::move(right_ref_p);
		right_ref_p = ::std::move(l_temp);
	}
};

#pragma pack(pop, _DWORD_SIZE_)


END_NAMESPACE
#endif 
