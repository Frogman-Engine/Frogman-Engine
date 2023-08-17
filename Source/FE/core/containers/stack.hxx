#ifndef _FE_CORE_STACK_HXX_
#define _FE_CORE_STACK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/iterator.hxx>
#include <FE/core/memory.hxx>
#include <initializer_list>


BEGIN_NAMESPACE(FE)


template<class container>
class stack final 
{
	using container_type = container;
	using pointer = typename container::pointer;
	using difference_type = typename container::difference_type;
	using const_pointer = typename container::const_pointer;
	using const_iterator = typename container::const_iterator;
	using const_reverse_iterator = typename container::const_reverse_iterator;
	using reference = typename container::reference;
	using const_reference = typename container::const_reference;
	using length_type = typename container::length_type;
	using size_type = typename container::size_type;
	using value_type = typename container::value_type;
	using alignment = typename container::alignment;
	using allocator_type = typename container::allocator;

public:
	_CONSTEXPR20_ _FORCE_INLINE_ stack() noexcept {}
	_CONSTEXPR23_ _FORCE_INLINE_ ~stack() noexcept {}
};




template<class T, size_t max_element_count, class type_trait = FE::type_trait<T, FE::stack_memory<T>>>
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
	var::byte m_memory[sizeof(value_type) * max_element_count];
	pointer m_top_ptr;
	pointer const m_absolute_begin_ptrc;

public:
	_CONSTEXPR20_ _FORCE_INLINE_ fstack() noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_ptrc(m_top_ptr) {}
	_CONSTEXPR23_ _FORCE_INLINE_ ~fstack() noexcept {}

	_FORCE_INLINE_ fstack(std::initializer_list<value_type>&& initializer_list_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_ptrc(m_top_ptr)
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");
		FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}!: Cannot assign an empty initializer_list", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));

		type_trait::move_construct(this->m_absolute_begin_ptrc, const_cast<value_type*>(initializer_list_p.begin()), initializer_list_p.size());

		this->__jump_top_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ fstack(fstack& other_ref_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_ptrc(m_top_ptr)
	{
		if (other_ref_p.size() == 0)
		{
			return;
		}

		type_trait::copy_construct(this->m_absolute_begin_ptrc, this->capacity(), other_ref_p.m_absolute_begin_ptrc, other_ref_p.size());

		this->__jump_top_pointer(other_ref_p.m_top_ptr - other_ref_p.m_absolute_begin_ptrc);
	}

	_FORCE_INLINE_ fstack(fstack&& rvalue_p) noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_absolute_begin_ptrc(m_top_ptr)
	{
		if (rvalue_p.size() == 0)
		{
			return;
		}

		type_trait::move_construct(this->m_absolute_begin_ptrc, this->capacity(), rvalue_p.m_absolute_begin_ptrc, rvalue_p.size());

		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_absolute_begin_ptrc);
		rvalue_p.__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ fstack& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");
		FE_ASSERT(initializer_list_p.size() == 0, "${%s@0}!: Cannot assign an empty initializer_list", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));

		if (this->size() == 0)
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

	_FORCE_INLINE_ fstack& operator=(fstack& other_ref_p) noexcept
	{
		size_t l_other_size = other_ref_p.size();
		if (l_other_size == 0)
		{
			return *this;
		}

		if (this->size() == 0)
		{
			this->~fstack();
			new(this) fstack(other_ref_p);
			return *this;
		}

		this->__restructrue_fstack_with_copy_semantics(other_ref_p.m_absolute_begin_ptrc, l_other_size);

		this->__set_top_pointer_to_zero();
		this->__jump_top_pointer(other_ref_p.m_top_ptr - other_ref_p.m_absolute_begin_ptrc);
		return *this;
	}

	_FORCE_INLINE_ fstack& operator=(fstack&& rvalue_p) noexcept
	{
		size_t l_other_size = rvalue_p.size();
		if (l_other_size == 0)
		{
			return *this;
		}

		if (this->size() == 0)
		{
			this->~fstack();
			new(this) fstack(std::move(rvalue_p));
			return *this;
		}

		this->__restructrue_fstack_with_move_semantics(rvalue_p.m_absolute_begin_ptrc, l_other_size);

		this->__set_top_pointer_to_zero();
		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_absolute_begin_ptrc);
		rvalue_p.__set_top_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ void push(value_type value_p) noexcept
	{
		FE_ASSERT(this->m_top_ptr >= this->m_absolute_begin_ptrc + max_element_count, "${%s@0}: The fstack top exceeded the index boundary", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

		type_trait::construct(*this->m_top_ptr, std::move(value_p));
		++this->m_top_ptr;
	}

	_FORCE_INLINE_ value_type pop() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "${%s@0}: The fstack top index reached zero. The index value_p must be greater than zero", TO_STRING(FE::MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));

		--this->m_top_ptr;
		T l_return_value_buffer = std::move(*this->m_top_ptr);
		type_trait::destruct(*this->m_top_ptr);
		return std::move(l_return_value_buffer);
	}
	
	_FORCE_INLINE_ void pop_all() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "WARNING: It is pointless to pop empty elements.");

		type_trait::destruct(this->m_absolute_begin_ptrc, this->m_top_ptr);
		this->__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ const_reference top() const noexcept
	{
		return *(this->m_top_ptr - 1);
	}

	_NODISCARD_ _FORCE_INLINE_ var::boolean is_empty() noexcept
	{
		return (this->m_top_ptr == this->m_absolute_begin_ptrc) ? true : false;
	}

	_FORCE_INLINE_ length_type length() noexcept
	{
		return this->m_top_ptr - this->m_absolute_begin_ptrc;
	}

	_FORCE_INLINE_ size_type size() noexcept
	{
		return this->m_top_ptr - this->m_absolute_begin_ptrc;
	}

	_FORCE_INLINE_ constexpr size_type max_size() const noexcept
	{
		return max_element_count;
	}

	_FORCE_INLINE_ constexpr size_type capacity() const noexcept
	{
		return max_element_count;
	}

	_FORCE_INLINE_ const_iterator cbegin() noexcept
	{
		return this->m_absolute_begin_ptrc;
	}

	_FORCE_INLINE_ const_iterator cend() noexcept
	{
		return this->m_top_ptr;
	}

	_FORCE_INLINE_ const_reverse_iterator crbegin() noexcept
	{
		return this->m_top_ptr - 1;
	}

	_FORCE_INLINE_ const_reverse_iterator crend() noexcept
	{
		return this->m_absolute_begin_ptrc - 1;
	}

	_FORCE_INLINE_ constexpr FE::TYPE_TRIVIALITY is_trivial() noexcept { return FE::is_trivially_constructible_and_destructible<T>::value; }

	_FORCE_INLINE_ void swap(fstack& other_ref_p) noexcept
	{
		fstack l_temporary = std::move(*this);
		*this = std::move(other_ref_p);
		other_ref_p = std::move(l_temporary);
	}

	var::boolean operator==(fstack& other_ref_p) noexcept
	{
		return FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
	}

	var::boolean operator!=(fstack& other_ref_p) noexcept
	{
		return !FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
	}

private:
	_FORCE_INLINE_ void __jump_top_pointer(difference_type ptrdiff_p) noexcept
	{
		this->m_top_ptr += ptrdiff_p;
	}

	_FORCE_INLINE_ void __set_top_pointer_to_zero() noexcept
	{
		this->m_top_ptr = this->m_absolute_begin_ptrc;
	}

	_FORCE_INLINE_ void __restructrue_fstack_with_move_semantics(value_type* const source_begin_ptrc_p, size_t source_size_p) noexcept
	{
		size_t l_this_size = this->size();

		if (source_size_p > l_this_size)
		{
			size_t l_count_to_construct = source_size_p - l_this_size;
			type_trait::move_construct(this->m_top_ptr, source_begin_ptrc_p - l_count_to_construct, l_count_to_construct);

			type_trait::move_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, l_this_size);
		}
		else if (source_size_p < l_this_size)
		{
			size_t l_count_to_destruct = l_this_size - source_size_p;
			type_trait::destruct(this->m_top_ptr - l_count_to_destruct, this->m_top_ptr);

			type_trait::move_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, source_size_p);
		}
		else
		{
			type_trait::move_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, source_size_p);
		}
	}

	_FORCE_INLINE_ void __restructrue_fstack_with_copy_semantics(value_type* const source_begin_ptrc_p, size_t source_size_p) noexcept
	{
		size_t l_this_size = this->size();

		if (source_size_p > l_this_size)
		{
			size_t l_count_to_construct = source_size_p - l_this_size;
			type_trait::copy_construct(this->m_top_ptr, source_begin_ptrc_p - l_count_to_construct, l_count_to_construct);

			type_trait::copy_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, l_this_size);
		}
		else if (source_size_p < l_this_size)
		{
			size_t l_count_to_destruct = l_this_size - source_size_p;
			type_trait::destruct(this->m_top_ptr - l_count_to_destruct, this->m_top_ptr);

			type_trait::copy_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, source_size_p);
		}
		else
		{
			type_trait::copy_assign(this->m_absolute_begin_ptrc, source_begin_ptrc_p, source_size_p);
		}
	}
};

END_NAMESPACE
#endif
