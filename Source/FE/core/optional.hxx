#ifndef _FE_CORE_OPTIONAL_HXX_
#define _FE_CORE_OPTIONAL_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>


BEGIN_NAMESPACE(FE)

// refactor optional

struct nullopt_t {};
_MAYBE_UNUSED_ constexpr inline nullopt_t nullopt;


template<typename T, FE::TYPE_TRIVIALITY object_triviality = FE::is_trivially_constructible_and_destructible<T>::value>
class optional final 
{
public:
	optional() noexcept = delete;
	~optional() noexcept = delete;
};


class optional_base
{
protected:
	volatile var::boolean m_is_constructed;

	_FORCE_INLINE_ constexpr optional_base() noexcept : m_is_constructed() {}
	_FORCE_INLINE_ constexpr optional_base(boolean is_constructed_p) noexcept : m_is_constructed(is_constructed_p) {}
	_FORCE_INLINE_ constexpr ~optional_base() noexcept {}

	template<typename T, FE::TYPE_TRIVIALITY object_triviality = FE::is_trivially_constructible_and_destructible<T>::value>
	_FORCE_INLINE_ static void swap(optional<T, object_triviality>& left_p, optional<T, object_triviality>& right_p)
	{
		optional<T, object_triviality> l_temporary = std::move(left_p);
		left_p = std::move(right_p);
		right_p = std::move(left_p);
	}
};


template<typename T>
class optional<T, FE::TYPE_TRIVIALITY::_NOT_TRIVIAL> final : public optional_base
{
	var::byte m_memory[sizeof(T)];
	T* const m_memory_ptrc;

public:
	using base = optional_base;
	using value_type = T;

	_FORCE_INLINE_ constexpr optional() noexcept : base(), m_memory(), m_memory_ptrc(reinterpret_cast<T*>(m_memory)) {}
	_FORCE_INLINE_ constexpr optional(_MAYBE_UNUSED_ nullopt_t nullopt_p) noexcept : base(false), m_memory(), m_memory_ptrc(reinterpret_cast<T*>(m_memory)) {}
	_FORCE_INLINE_ optional(T initial_value_p) noexcept : base(true), m_memory(), m_memory_ptrc(reinterpret_cast<T*>(m_memory))
	{
		new(this->m_memory_ptrc) T(std::move(initial_value_p));
	}

	_FORCE_INLINE_ ~optional() noexcept
	{
		if (this->m_is_constructed == true)
		{
			this->m_memory_ptrc->~T();
		}
	}

	_FORCE_INLINE_ optional(const optional& other_cref_p) noexcept : base(other_cref_p.m_is_constructed), m_memory(), m_memory_ptrc(reinterpret_cast<T*>(m_memory))
	{
		if (this->m_is_constructed == false)
		{
			return;
		}

		new(this->m_memory_ptrc) T(*other_cref_p.m_memory_ptrc);
	}

	_FORCE_INLINE_ optional(optional&& rvalue_p) noexcept : base(rvalue_p.m_is_constructed), m_memory(), m_memory_ptrc(reinterpret_cast<T*>(m_memory))
	{
		if (this->m_is_constructed == false)
		{
			return;
		}

		new(this->m_memory_ptrc) T(std::move(*rvalue_p.m_memory_ptrc));
	}

	_FORCE_INLINE_ optional& operator=(_MAYBE_UNUSED_ nullopt_t nullopt_p) noexcept
	{
		this->reset();
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(T value_p) noexcept
	{
		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			new(this->m_memory_ptrc) T(std::move(value_p));
			return *this;
		}

		*this->m_memory_ptrc = std::move(value_p);
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(const optional& other_cref_p) noexcept
	{
		if (other_cref_p.m_is_constructed == false)
		{
			this->m_is_constructed = false;
			return *this;
		}

		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			new(this->m_memory_ptrc) T(*other_cref_p.m_memory_ptrc);
			return *this;
		}

		*this->m_memory_ptrc = *other_cref_p.m_memory_ptrc;
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(optional&& rvalue_p) noexcept
	{
		if (rvalue_p.m_is_constructed == false)
		{
			this->m_is_constructed = false;
			return *this;
		}

		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			new(this->m_memory_ptrc) T(*std::move(rvalue_p.m_memory_ptrc));
			return *this;
		}

		*this->m_memory_ptrc = *rvalue_p.m_memory_ptrc;
		return *this;
	}

	_FORCE_INLINE_ T& operator*() noexcept
	{
		FE_ASSERT(this->m_is_constructed == false, "ERROR: Attempted to dereference nullopt.");

		return *this->m_memory_ptrc;
	}

	_FORCE_INLINE_ T* operator->() noexcept
	{
		FE_ASSERT(this->m_is_constructed == false, "ERROR: Attempted to access nullopt.");

		return this->m_memory_ptrc;
	}

	_FORCE_INLINE_ var::boolean has_value() noexcept { return this->m_is_constructed; }

	_FORCE_INLINE_ var::boolean construct() noexcept
	{
		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			new(this->m_memory_ptrc) T();
		}
		return this->m_is_constructed;
	}

	template<typename ... arguments>
	_FORCE_INLINE_ var::boolean construct(arguments&& ...arguments_p) noexcept
	{
		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			new(this->m_memory_ptrc) T(arguments_p...);
		}
		return this->m_is_constructed;
	}

	_FORCE_INLINE_ void reset() noexcept
	{
		FE_ASSERT(this->m_is_constructed == false, "WARNING: Unable to reset an empty optional");
		if (this->m_is_constructed == true)
		{
			this->m_is_constructed = false;
			this->m_memory_ptrc->~T();
		}
	}

};


template<typename T>
class optional<T, FE::TYPE_TRIVIALITY::_TRIVIAL> final : public optional_base
{
	T m_plain_old_data;

public:
	using base = optional_base;
	using value_type = T;

	_FORCE_INLINE_ constexpr optional() noexcept : base(), m_plain_old_data() {}
	_FORCE_INLINE_ constexpr optional(_MAYBE_UNUSED_ nullopt_t nullopt_p) noexcept : base(false), m_plain_old_data() {}
	_FORCE_INLINE_ optional(T initial_value_p) noexcept : base(true), m_plain_old_data(initial_value_p) {}
	_FORCE_INLINE_ ~optional() noexcept { this->m_is_constructed = false; }
	_FORCE_INLINE_ optional(const optional& other_cref_p) noexcept : base(other_cref_p.m_is_constructed), m_plain_old_data(other_cref_p.m_plain_old_data) {}
	_FORCE_INLINE_ optional(optional&& rvalue_p) noexcept : base(rvalue_p.m_is_constructed), m_plain_old_data(rvalue_p.m_plain_old_data)
	{
		std::memset(&(rvalue_p.m_plain_old_data), _NULL_, sizeof(rvalue_p.m_plain_old_data));
	}

	_FORCE_INLINE_ optional& operator=(_MAYBE_UNUSED_ nullopt_t nullopt_p) noexcept
	{
		this->reset();
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(T value_p) noexcept
	{
		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			this->m_plain_old_data = value_p;
			return *this;
		}

		this->m_plain_old_data = value_p;
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(const optional& other_cref_p) noexcept
	{
		if (other_cref_p.m_is_constructed == false)
		{
			this->m_is_constructed = false;
			return *this;
		}

		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			this->m_plain_old_data = other_cref_p.m_plain_old_data;
			return *this;
		}

		this->m_plain_old_data = other_cref_p.m_plain_old_data;
		return *this;
	}

	_FORCE_INLINE_ optional& operator=(optional&& rvalue_p) noexcept
	{
		if (rvalue_p.m_is_constructed == false)
		{
			this->m_is_constructed = false;
			return *this;
		}

		if (this->m_is_constructed == false)
		{
			this->m_is_constructed = true;
			this->m_plain_old_data = std::move(rvalue_p.m_plain_old_data);
			return *this;
		}

		this->m_plain_old_data = std::move(rvalue_p.m_plain_old_data);
		return *this;
	}

	_FORCE_INLINE_ T& operator*() noexcept
	{
		FE_ASSERT(this->m_is_constructed == false, "ERROR: Attempted to dereference nullopt.");

		return this->m_plain_old_data;
	}

	_FORCE_INLINE_ T* operator->() noexcept
	{
		FE_ASSERT(this->m_is_constructed == false, "ERROR: Attempted to access nullopt.");

		return &this->m_plain_old_data;
	}

	_FORCE_INLINE_ var::boolean has_value() noexcept { return this->m_is_constructed; }

	_FORCE_INLINE_ void reset() noexcept
	{
		this->m_is_constructed = false;
	}
};


END_NAMESPACE
#endif
