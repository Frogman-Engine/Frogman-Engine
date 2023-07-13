#ifndef _FE_CORE_STACK_HXX_
#define _FE_CORE_STACK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/iterator.hxx>
#include <FE/core/memory>
#include <initializer_list>
#include <stack>

BEGIN_NAMESPACE(FE)


template<class T, count_t max_element_count, boolean is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<T>()>
class stack final
{
public:
	stack() noexcept = delete;
	~stack() noexcept = delete;
};


template<class T, count_t max_element_count>
class stack_base
{
public:
	using value_type = T;
	using length_type = count_t;
	using size_type = count_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using const_iterator = FE::const_iterator<FE::contiguous_iterator<T>>;
	using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<T>>;
	using difference_type = ptrdiff_t;

protected:
	var::byte m_memory[sizeof(value_type) * max_element_count];
	pointer m_top_ptr;
	pointer const m_base_ptrc;

	_FORCE_INLINE_ stack_base() noexcept : m_memory(), m_top_ptr(reinterpret_cast<pointer>(m_memory)), m_base_ptrc(m_top_ptr) {}
	_FORCE_INLINE_ _CONSTEXPR20_ ~stack_base() noexcept {}

public:
	_FORCE_INLINE_ const_reference top() const noexcept
	{
		return *this->m_top_ptr;
	}

	_NODISCARD_ _FORCE_INLINE_ var::boolean is_empty() noexcept
	{
		return (this->m_top_ptr == this->m_base_ptrc) ? true : false;
	}

	_FORCE_INLINE_ length_type length() noexcept
	{
		return this->m_top_ptr - this->m_base_ptrc;
	}

	_FORCE_INLINE_ size_type size() noexcept
	{
		return this->m_top_ptr - this->m_base_ptrc;
	}

	_FORCE_INLINE_ constexpr size_type max_size() const noexcept
	{
		return max_element_count;
	}

	_FORCE_INLINE_ constexpr size_type max_length() const noexcept
	{
		return max_element_count;
	}

	_FORCE_INLINE_ FE::const_iterator<FE::contiguous_iterator<T>> cbegin() noexcept
	{
		return this->m_base_ptrc;
	}

	_FORCE_INLINE_ FE::const_iterator<FE::contiguous_iterator<T>> cend() noexcept
	{
		return this->m_base_ptrc + max_element_count;
	}

	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<T>> crbegin() noexcept
	{
		return (this->m_base_ptrc + max_element_count) - 1;
	}

	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<T>> crend() noexcept
	{
		return this->m_base_ptrc - 1;
	}

	template<boolean is_trivially_constructible_and_destructible = FE::is_trivially_constructible_and_destructible<T>()>
	_FORCE_INLINE_ static void swap(stack<T, max_element_count, is_trivially_constructible_and_destructible>& first_ref_p, stack<T, max_element_count, is_trivially_constructible_and_destructible>& second_ref_p) noexcept
	{
		stack<T, max_element_count, is_trivially_constructible_and_destructible> l_temporary = std::move(first_ref_p);
		first_ref_p = std::move(second_ref_p);
		second_ref_p = std::move(l_temporary);
	}

protected:
	_FORCE_INLINE_ void __jump_top_pointer(difference_type ptrdiff_p) noexcept
	{
		this->m_top_ptr += ptrdiff_p;
	}

	_FORCE_INLINE_ void __set_top_pointer_to_zero() noexcept
	{
		this->m_top_ptr = this->m_base_ptrc;
	}
};

template<class T, count_t max_element_count>
class stack<T, max_element_count, true> final : public stack_base<T, max_element_count>
{
public:
	using base_type = stack_base<T, max_element_count>;
	using value_type = typename base_type::value_type;
	using length_type = typename base_type::length_type;
	using size_type = typename base_type::size_type;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using pointer = typename base_type::pointer;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;
	using difference_type = typename base_type::difference_type;

	_FORCE_INLINE_ stack() noexcept : base_type() {}
	_FORCE_INLINE_ _CONSTEXPR20_ ~stack() noexcept {}

	_FORCE_INLINE_ stack(std::initializer_list<value_type>&& initializer_list_p) noexcept : base_type()
	{
		ABORT_IF(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));

		this->__jump_top_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ stack(stack& other_ref_p) noexcept : base_type()
	{
		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					other_ref_p.m_memory, max_element_count, sizeof(value_type));

		this->__jump_top_pointer(other_ref_p.m_top_ptr - other_ref_p.m_base_ptrc);
		other_ref_p.__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ stack(stack&& rvalue_p) noexcept : base_type()
	{
		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					rvalue_p.m_memory, max_element_count, sizeof(value_type));

		FE::memset_s(rvalue_p.m_memory, _NULL_, max_element_count, sizeof(value_type));

		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_base_ptrc);
		rvalue_p.__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ stack& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		ABORT_IF(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));

		this->__jump_top_pointer(initializer_list_p.size());
		return *this;
	}

	_FORCE_INLINE_ stack& operator=(stack& other_ref_p) noexcept
	{
		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					other_ref_p.m_memory, max_element_count, sizeof(value_type));

		this->__jump_top_pointer(other_ref_p.m_top_ptr - other_ref_p.m_base_ptrc);
		other_ref_p.__set_top_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ stack& operator=(stack&& rvalue_p) noexcept
	{
		FE::memcpy_s(this->m_memory, max_element_count, sizeof(value_type),
					rvalue_p.m_memory, max_element_count, sizeof(value_type));

		FE::memset_s(rvalue_p.m_memory, _NULL_, max_element_count, sizeof(value_type));

		this->__jump_top_pointer(rvalue_p.m_top_ptr - rvalue_p.m_base_ptrc);
		rvalue_p.__set_top_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ void push(value_type value_p) noexcept
	{
		ABORT_IF(this->m_top_ptr >= this->m_base_ptrc + max_element_count, "UNRECOVERABLE ERROR!: The stack top exceeded the index boundary of the underlying container");

		*this->m_top_ptr = value_p;
		++this->m_top_ptr;
	}

	_FORCE_INLINE_ value_type pop() noexcept
	{
		ABORT_IF(this->is_empty() == true, "UNRECOVERABLE ERROR!: The stack top index reached zero. The index value_p must be greater than zero");

		--this->m_top_ptr;
		T l_return_value_buffer = *this->m_top_ptr;
		*this->m_top_ptr = (T)_NULL_;
		return l_return_value_buffer;
	}
	
	_FORCE_INLINE_ void pop_all() noexcept
	{
		ABORT_IF(this->is_empty() == true, "WARNING: It is pointless to pop empty elements.");

		this->__set_top_pointer_to_zero();
		FE::memset_s(this->m_base_ptrc, _NULL_, max_element_count, sizeof(T));
	}
};


template<class T, count_t max_element_count>
class stack<T, max_element_count, false> final : public stack_base<T, max_element_count>
{
	OBJECT_LIFECYCLE m_bool_mask[max_element_count];

public:
	using base_type = stack_base<T, max_element_count>;
	using value_type = typename base_type::value_type;
	using length_type = typename base_type::length_type;
	using size_type = typename base_type::size_type;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using pointer = typename base_type::pointer;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;
	using difference_type = typename base_type::difference_type;

	_FORCE_INLINE_ stack() noexcept : base_type(), m_bool_mask() {}

	_FORCE_INLINE_ ~stack() noexcept
	{
		if (this->is_empty() == true) { return; }

		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, this->m_base_ptrc + FE::bool_mask_length<OBJECT_LIFECYCLE>(this->m_bool_mask, max_element_count), this->m_bool_mask);
	}

	_FORCE_INLINE_ stack(std::initializer_list<value_type>&& initializer_list_p) noexcept : base_type(), m_bool_mask()
	{
		ABORT_IF(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, initializer_list_p.size(), this->m_bool_mask,
																				const_cast<T*>(initializer_list_p.begin()), initializer_list_p.size());
		this->__jump_top_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ stack(stack& other_ref_p) noexcept : base_type(), m_bool_mask()
	{
		length_t l_other_bool_mask_length = FE::bool_mask_length<OBJECT_LIFECYCLE>(other_ref_p.m_bool_mask, max_element_count);

		FE::copy_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
																				other_ref_p.m_base_ptrc, l_other_bool_mask_length, static_cast<const OBJECT_LIFECYCLE*>(other_ref_p.m_bool_mask));
		this->__jump_top_pointer(l_other_bool_mask_length);
		other_ref_p.__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ stack(stack&& rvalue_p) noexcept : base_type(), m_bool_mask()
	{
		length_t l_rvalue_bool_mask_length = FE::bool_mask_length<OBJECT_LIFECYCLE>(rvalue_p.m_bool_mask, max_element_count);

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
																				rvalue_p.m_base_ptrc, l_rvalue_bool_mask_length, static_cast<OBJECT_LIFECYCLE*>(rvalue_p.m_bool_mask));
	
		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(rvalue_p.m_base_ptrc, rvalue_p.m_base_ptrc + (rvalue_p.m_top_ptr - rvalue_p.m_base_ptrc), rvalue_p.m_bool_mask);

		this->__jump_top_pointer(l_rvalue_bool_mask_length);
		rvalue_p.__set_top_pointer_to_zero();
	}

	_FORCE_INLINE_ stack& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		ABORT_IF(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, initializer_list_p.size(), this->m_bool_mask,
																				const_cast<T*>(initializer_list_p.begin()), initializer_list_p.size());
		this->__jump_top_pointer(initializer_list_p.size());
		return *this;
	}

	_FORCE_INLINE_ stack& operator=(stack& other_ref_p) noexcept
	{
		length_t l_other_bool_mask_length = FE::bool_mask_length<OBJECT_LIFECYCLE>(other_ref_p.m_bool_mask, max_element_count);

		FE::copy_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
																				other_ref_p.m_base_ptrc, l_other_bool_mask_length, static_cast<const OBJECT_LIFECYCLE*>(other_ref_p.m_bool_mask));
		this->__jump_top_pointer(l_other_bool_mask_length);
		other_ref_p.__set_top_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ stack& operator=(stack&& rvalue_p) noexcept
	{
		length_t l_rvalue_bool_mask_length = FE::bool_mask_length<OBJECT_LIFECYCLE>(rvalue_p.m_bool_mask, max_element_count);

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_base_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
																				rvalue_p.m_base_ptrc, l_rvalue_bool_mask_length, static_cast<OBJECT_LIFECYCLE*>(rvalue_p.m_bool_mask));
		
		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(rvalue_p.m_base_ptrc, rvalue_p.m_base_ptrc + (rvalue_p.m_top_ptr - rvalue_p.m_base_ptrc), rvalue_p.m_bool_mask);

		this->__jump_top_pointer(l_rvalue_bool_mask_length);
		rvalue_p.__set_top_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ void push(value_type value_p) noexcept
	{
		ABORT_IF(this->m_top_ptr >= this->m_base_ptrc + max_element_count, "UNRECOVERABLE ERROR!: The stack top exceeded the index boundary of the underlying container");
		
		FE::move_construct(this->m_top_ptr, this->m_bool_mask[this->m_top_ptr - this->m_base_ptrc], std::move(value_p));
		++this->m_top_ptr;
	}

	_FORCE_INLINE_ value_type pop() noexcept
	{
		ABORT_IF(this->is_empty() == true, "UNRECOVERABLE ERROR!: The stack top index reached zero. The index value_p must be greater than zero");

		--this->m_top_ptr;
		T l_return_value_buffer = *this->m_top_ptr;
		FE::destruct(this->m_top_ptr, this->m_bool_mask[this->m_top_ptr - this->m_base_ptrc]);
		return l_return_value_buffer;
	}
	
	_FORCE_INLINE_ void pop_all() noexcept
	{
		ABORT_IF(this->is_empty() == true, "WARNING: It is pointless to pop empty elements.");

		this->__set_top_pointer_to_zero();
		FE::destruct(this->m_base_ptrc, this->m_base_ptrc + (this->m_top_ptr - this->m_base_ptrc), this->m_bool_mask);
	}
};


END_NAMESPACE
#endif