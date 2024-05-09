#ifndef _FE_CORE_TRACKABLE_HXX_
#define _FE_CORE_TRACKABLE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/algorithm/utility.hxx>
#include <FE/core/smart_references/private/smart_ref_base.hpp>




BEGIN_NAMESPACE(FE)


template<typename T>
class ref;


template<typename T>
class trackable final : public internal::smart_ref::trackable_base<T>
{
public:
	using base_type = internal::smart_ref::trackable_base<T>;
	using pointer = typename base_type::pointer;
	using element_type = typename base_type::element_type;

	using ref_table_value_type = typename base_type::ref_table_value_type;
	using ref_table_key_type = typename base_type::ref_table_key_type;

public:
	_CONSTEXPR20_ trackable() noexcept : base_type() {}
	_CONSTEXPR20_ trackable(element_type value_p) noexcept : base_type(std::move(value_p))
	{
		this->m_key = base_type::__register_property_address(&this->m_object);
	}

	template<typename... Args>
	_CONSTEXPR20_ trackable(Args... value_p) noexcept : base_type(std::move(value_p)...)
	{
		this->m_key = base_type::__register_property_address(&this->m_object);
	}

	_CONSTEXPR23_ ~trackable() noexcept
	{
		if (this->m_key != base_type::invalid_key_value)
		{
			base_type::__unregister_property_address(this->m_key);
		}
	}

	_CONSTEXPR20_ trackable(const trackable&) noexcept = delete;

	_CONSTEXPR20_ trackable(trackable&& rvalue_p) noexcept : base_type(std::move(rvalue_p.m_object))
	{
		if (rvalue_p.m_key == base_type::invalid_key_value)
		{
			return;
		}

		this->m_key = algorithm::utility::exchange<ref_table_key_type>(rvalue_p.m_key, base_type::invalid_key_value);
	}

	_CONSTEXPR23_ trackable& operator=(const trackable&) noexcept = delete;

	_CONSTEXPR20_ trackable& operator=(trackable&& rvalue_p) noexcept
	{
		if (rvalue_p.m_key == base_type::invalid_key_value)
		{
			return *this;
		}

		if (this->m_key != base_type::invalid_key_value)
		{
			base_type::__unregister_property_address(this->m_key);
		}

		this->m_object = std::move(rvalue_p.m_object);
		this->m_key = algorithm::utility::exchange<ref_table_key_type>(rvalue_p.m_key, base_type::invalid_key_value);
		return *this;
	}

	_CONSTEXPR20_ trackable& operator=(element_type value_p) noexcept
	{
		if (this->m_key == base_type::invalid_key_value)
		{
			this->m_key = base_type::__register_property_address(&this->m_object);
		}

		base_type::m_object = std::move(value_p);
		return *this;
	}

	_CONSTEXPR20_ void swap(trackable& in_out_other_p) noexcept
	{
		trackable l_tmp = std::move(in_out_other_p);
		in_out_other_p = std::move(*this);
		*this = std::move(l_tmp);
	}


	_FORCE_INLINE_ boolean operator==(const trackable& other_p) const noexcept
	{
		return this->m_object == other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator!=(const trackable& other_p) const noexcept
	{
		return this->m_object != other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator>(const trackable& other_p) const noexcept
	{
		return this->m_object > other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator>=(const trackable& other_p) const noexcept
	{
		return this->m_object >= other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator<(const trackable& other_p) const noexcept
	{
		return this->m_object < other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator<=(const trackable& other_p) const noexcept
	{
		return this->m_object <= other_p.m_object;
	}


	_FORCE_INLINE_ boolean operator==(const ref<T>& other_p) const noexcept
	{
		return this->m_object == other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator!=(const ref<T>& other_p) const noexcept
	{
		return this->m_object != other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator>(const ref<T>& other_p) const noexcept
	{
		return this->m_object > other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator>=(const ref<T>& other_p) const noexcept
	{
		return this->m_object >= other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator<(const ref<T>& other_p) const noexcept
	{
		return this->m_object < other_p.m_object;
	}

	_FORCE_INLINE_ boolean operator<=(const ref<T>& other_p) const noexcept
	{
		return this->m_object <= other_p.m_object;
	}
};


END_NAMESPACE
#endif 