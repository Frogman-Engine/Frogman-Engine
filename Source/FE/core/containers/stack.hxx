#ifndef _FE_CORE_STACK_HXX_
#define _FE_CORE_STACK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/iterator.hxx>
#include <FE/core/memory.hxx>
#include <initializer_list>


BEGIN_NAMESPACE(FE)


template<class Container>
class stack final 
{
	using container_type = Container;
	using pointer = typename Container::pointer;
	using difference_type = typename Container::difference_type;
	using const_pointer = typename Container::const_pointer;
	using const_iterator = typename Container::const_iterator;
	using const_reverse_iterator = typename Container::const_reverse_iterator;
	using reference = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using length_type = typename Container::length_type;
	using size_type = typename Container::size_type;
	using value_type = typename Container::value_type;
	using Alignment = typename Container::Alignment;
	using allocator_type = typename Container::allocator;

public:
	_CONSTEXPR20_ stack() noexcept {}
	_FORCE_INLINE_ ~stack() noexcept {}
};




template<class T, size_t MaxElementCount, class Traits = FE::type_traits<T, FE::stack_memory<T>>>
class fstack final
{
public:
	using value_type = T;
	using length_type = var::size_t;
	using size_type = var::size_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using const_iterator = FE::const_iterator<FE::contiguous_iterator<T>>;
	using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<T>>;
	using difference_type = ptrdiff_t;

private:
	var::byte m_memory[sizeof(value_type) * MaxElementCount];
	pointer m_top_ptr;
	pointer const m_absolute_begin_pointer;

public:
	_CONSTEXPR20_ fstack() noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_pointer(m_top_ptr) {}
	_FORCE_INLINE_ ~fstack() noexcept { this->pop_all(); }

	_CONSTEXPR20_ fstack(std::initializer_list<value_type>&& initializer_list_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_pointer(m_top_ptr)
	{
		FE_ASSERT(initializer_list_p.size() > MaxElementCount, "ERROR!: The length of std::initializer_list exceeds the MaxElementCount");
		FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}!: Cannot assign an empty initializer_list", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE));

		Traits::move_construct(this->m_absolute_begin_pointer, const_cast<value_type*>(initializer_list_p.begin()), initializer_list_p.size());

		this->__jump_top_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ fstack(fstack& other_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_pointer(m_top_ptr)
	{
		if (other_p.is_empty())
		{
			return;
		}

		Traits::copy_construct(this->m_absolute_begin_pointer, this->capacity(), other_p.m_absolute_begin_pointer, other_p.size());

		this->__jump_top_pointer(other_p.m_top_ptr - other_p.m_absolute_begin_pointer);
	}

	_FORCE_INLINE_ fstack(fstack&& rvalue_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_pointer(m_top_ptr)
	{
		if (rvalue_p.is_empty())
		{
			return;
		}

		Traits::move_construct(this->m_absolute_begin_pointer, this->capacity(), rvalue_p.m_absolute_begin_pointer, rvalue_p.size());

		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_absolute_begin_pointer);
		rvalue_p.__set_top_pointer_to_zero();
	}

	_CONSTEXPR20_ fstack& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		FE_ASSERT(initializer_list_p.size() > MaxElementCount, "ERROR!: The length of std::initializer_list exceeds the MaxElementCount");
		FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}!: Cannot assign an empty initializer_list", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_INVALID_SIZE));

		if (this->is_empty())
		{
			this->~fstack();
			new(this) fstack(std::move(initializer_list_p));
			return *this;
		}

		size_t l_initializer_list_size = initializer_list_p.size();
		this->__restructrue_fstack_with_move_semantics(const_cast<value_type*>(initializer_list_p.begin()), l_initializer_list_size);
		this->__set_top_pointer_to_zero();
		this->__jump_top_pointer(l_initializer_list_size);
		return *this;
	}

	_FORCE_INLINE_ fstack& operator=(fstack& other_p) noexcept
	{
		size_t l_other_size = other_p.size();
		if (l_other_size == 0)
		{
			return *this;
		}

		if (this->is_empty())
		{
			this->~fstack();
			new(this) fstack(other_p);
			return *this;
		}

		this->__restructrue_fstack_with_copy_semantics(other_p.m_absolute_begin_pointer, l_other_size);

		this->__set_top_pointer_to_zero();
		this->__jump_top_pointer(other_p.m_top_ptr - other_p.m_absolute_begin_pointer);
		return *this;
	}

	_FORCE_INLINE_ fstack& operator=(fstack&& rvalue_p) noexcept
	{
		size_t l_other_size = rvalue_p.size();
		if (l_other_size == 0)
		{
			return *this;
		}

		if (this->is_empty())
		{
			this->~fstack();
			new(this) fstack(std::move(rvalue_p));
			return *this;
		}

		this->__restructrue_fstack_with_move_semantics(rvalue_p.m_absolute_begin_pointer, l_other_size);

		this->__set_top_pointer_to_zero();
		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_absolute_begin_pointer);
		rvalue_p.__set_top_pointer_to_zero();
		return *this;
	}

	_CONSTEXPR20_ void push(value_type value_p) noexcept
	{
		FE_ASSERT(this->m_top_ptr >= this->m_absolute_begin_pointer + MaxElementCount, "${%s@0}: The fstack top exceeded the index boundary", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

		Traits::construct(*this->m_top_ptr, std::move(value_p));
		++this->m_top_ptr;
	}

	_CONSTEXPR20_ value_type pop() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "${%s@0}: The fstack top index reached zero. The index value_p must be greater than zero", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

		--this->m_top_ptr;
		T l_return_value_buffer = std::move(*this->m_top_ptr);

		if constexpr (Traits::is_trivially_constructible_and_destructible == TYPE_TRIVIALITY::_NOT_TRIVIAL)
		{
			Traits::destruct(*this->m_top_ptr);
		}

		return std::move(l_return_value_buffer);
	}
	
	_FORCE_INLINE_ void pop_all() noexcept
	{
		if (this->is_empty() == false)
		{
			if constexpr (Traits::is_trivially_constructible_and_destructible == TYPE_TRIVIALITY::_NOT_TRIVIAL) 
			{
				Traits::destruct(this->m_absolute_begin_pointer, this->m_top_ptr);
			}
			this->__set_top_pointer_to_zero();
		}
	}

	_FORCE_INLINE_ const_reference top() const noexcept
	{
		return *(this->m_top_ptr - 1);
	}

	_NODISCARD_ _FORCE_INLINE_ var::boolean is_empty() const noexcept
	{
		return (this->m_top_ptr == this->m_absolute_begin_pointer) ? true : false;
	}

	_NODISCARD_ _FORCE_INLINE_ size_type count() const noexcept
	{
		return this->m_top_ptr - this->m_absolute_begin_pointer;
	}

	_NODISCARD_ _FORCE_INLINE_ size_type size() const noexcept
	{
		return this->m_top_ptr - this->m_absolute_begin_pointer;
	}

	_NODISCARD_ _FORCE_INLINE_ size_type max_size() const noexcept
	{
		return MaxElementCount;
	}

	_NODISCARD_ _FORCE_INLINE_ size_type capacity() const noexcept
	{
		return MaxElementCount;
	}

	_NODISCARD_ _FORCE_INLINE_ const_iterator cbegin() const noexcept
	{
		return this->m_absolute_begin_pointer;
	}

	_NODISCARD_ _FORCE_INLINE_ const_iterator cend() const noexcept
	{
		return this->m_top_ptr;
	}

	_NODISCARD_ _FORCE_INLINE_ const_reverse_iterator crbegin() const noexcept
	{
		return this->m_top_ptr - 1;
	}

	_NODISCARD_ _FORCE_INLINE_ const_reverse_iterator crend() const noexcept
	{
		return this->m_absolute_begin_pointer - 1;
	}

	_FORCE_INLINE_ void swap(fstack& in_out_other_p) noexcept
	{
		fstack l_temporary = std::move(*this);
		*this = std::move(in_out_other_p);
		in_out_other_p = std::move(l_temporary);
	}

	_NODISCARD_ _FORCE_INLINE_ boolean operator==(const fstack& other_p) const noexcept
	{
		return FE::memcmp_s(this->cbegin(), this->cend(), other_p.cbegin(), other_p.cend());
	}

	_NODISCARD_ _FORCE_INLINE_ boolean operator!=(const fstack& other_p) const noexcept
	{
		return !FE::memcmp_s(this->cbegin(), this->cend(), other_p.cbegin(), other_p.cend());
	}

private:
	_FORCE_INLINE_ void __jump_top_pointer(difference_type ptrdiff_p) noexcept
	{
		this->m_top_ptr += ptrdiff_p;
	}

	_FORCE_INLINE_ void __set_top_pointer_to_zero() noexcept
	{
		this->m_top_ptr = this->m_absolute_begin_pointer;
	}

	_CONSTEXPR20_ void __restructrue_fstack_with_move_semantics(value_type* const source_begin_p, size_t source_size_p) noexcept
	{
		size_t l_this_size = this->size();

		if (source_size_p > l_this_size)
		{
			size_t l_count_to_construct = source_size_p - l_this_size;
			Traits::move_construct(this->m_top_ptr, source_begin_p - l_count_to_construct, l_count_to_construct);

			Traits::move_assign(this->m_absolute_begin_pointer, source_begin_p, l_this_size);
		}
		else if (source_size_p < l_this_size)
		{
			size_t l_count_to_destruct = l_this_size - source_size_p;

			if constexpr (Traits::is_trivially_constructible_and_destructible == TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				Traits::destruct(this->m_top_ptr - l_count_to_destruct, this->m_top_ptr);
			}

			Traits::move_assign(this->m_absolute_begin_pointer, source_begin_p, source_size_p);
		}
		else
		{
			Traits::move_assign(this->m_absolute_begin_pointer, source_begin_p, source_size_p);
		}
	}

	_CONSTEXPR20_ void __restructrue_fstack_with_copy_semantics(value_type* const source_begin_p, size_t source_size_p) noexcept
	{
		size_t l_this_size = this->size();

		if (source_size_p > l_this_size)
		{
			size_t l_count_to_construct = source_size_p - l_this_size;
			Traits::copy_construct(this->m_top_ptr, source_begin_p - l_count_to_construct, l_count_to_construct);

			Traits::copy_assign(this->m_absolute_begin_pointer, source_begin_p, l_this_size);
		}
		else if (source_size_p < l_this_size)
		{
			size_t l_count_to_destruct = l_this_size - source_size_p;

			if constexpr (Traits::is_trivially_constructible_and_destructible == TYPE_TRIVIALITY::_NOT_TRIVIAL)
			{
				Traits::destruct(this->m_top_ptr - l_count_to_destruct, this->m_top_ptr);
			}

			Traits::copy_assign(this->m_absolute_begin_pointer, source_begin_p, source_size_p);
		}
		else
		{
			Traits::copy_assign(this->m_absolute_begin_pointer, source_begin_p, source_size_p);
		}
	}
};

END_NAMESPACE
#endif
