#ifndef _FE_CORE_QUEUE_HXX_
#define _FE_CORE_QUEUE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/iterator.hxx>
#include <FE/core/memory>
#include <initializer_list>


BEGIN_NAMESPACE(FE)


template<class T, size_t max_element_count = 0, FE::OBJECT_TRIVIALITY is_trivial = FE::is_trivially_constructible_and_destructible<T>::_VALUE_>
class queue final
{
public:
	queue() noexcept = delete;
	~queue() noexcept = delete;
};




template<class T>
class dynamic_queue_base
{
public:
	using container_type = T;
	using pointer = typename T::pointer;
	using difference_type = typename T::difference_type;
	using const_pointer = typename T::const_pointer;
	using const_iterator = typename T::const_iterator;
	using const_reverse_iterator = typename T::const_reverse_iterator;
	using reference = typename T::reference;
	using const_reference = typename T::const_reference;
	using length_type = typename T::length_type;
	using size_type = typename T::size_type;
	using value_type = typename T::value_type;
	using alignment = typename T::alignment;
	using allocator_type = typename T::allocator;

protected:
	_FORCE_INLINE_ dynamic_queue_base() noexcept {}
	_FORCE_INLINE_ _CONSTEXPR20_ ~dynamic_queue_base() noexcept {}
};


template<class T>
class queue<T, 0, FE::OBJECT_TRIVIALITY::_TRIVIAL> final : dynamic_queue_base<T>
{
public:
	using base_type = dynamic_queue_base<T>;
	using container_type = typename base_type::container_type;
	using pointer = typename base_type::pointer;
	using difference_type = typename base_type::difference_type;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using length_type = typename base_type::length_type;
	using size_type = typename base_type::size_type;
	using value_type = typename base_type::value_type;
	using alignment = typename base_type::alignment;
	using allocator_type = typename base_type::allocator;

	container_type _underlying_container;
};


template<class T>
class queue<T, 0, FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL> final : dynamic_queue_base<T>
{
public:
	using base_type = dynamic_queue_base<T>;
	using container_type = typename base_type::container_type;
	using pointer = typename base_type::pointer;
	using difference_type = typename base_type::difference_type;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using length_type = typename base_type::length_type;
	using size_type = typename base_type::size_type;
	using value_type = typename base_type::value_type;
	using alignment = typename base_type::alignment;
	using allocator_type = typename base_type::allocator;

	container_type _underlying_container;
};




template<class T, size_t max_element_count>
class static_queue_base
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
	pointer m_front_ptr;
	pointer m_back_ptr;

	pointer const m_absolute_begin_ptrc;

	_FORCE_INLINE_ static_queue_base() noexcept : m_memory(), m_front_ptr(reinterpret_cast<pointer>(m_memory)), m_back_ptr(m_front_ptr), m_absolute_begin_ptrc(m_front_ptr) {}
	_FORCE_INLINE_ _CONSTEXPR20_ ~static_queue_base() noexcept {}

public:
	_FORCE_INLINE_ const_reference front() const noexcept
	{
		return *this->m_front_ptr;
	}

	_FORCE_INLINE_ const_reference back() const noexcept
	{
		return *(this->m_back_ptr - 1);
	}

	_NODISCARD_ _FORCE_INLINE_ var::boolean is_empty() noexcept
	{
		return (this->m_front_ptr == this->m_back_ptr) ? true : false;
	}

	_FORCE_INLINE_ length_type length() noexcept
	{
		return this->m_back_ptr - this->m_front_ptr;
	}

	_FORCE_INLINE_ size_type size() noexcept
	{
		return this->m_back_ptr - this->m_front_ptr;
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
		return this->m_front_ptr;
	}

	_FORCE_INLINE_ FE::const_iterator<FE::contiguous_iterator<T>> cend() noexcept
	{
		return this->m_front_ptr + max_element_count;
	}

	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<T>> crbegin() noexcept
	{
		return (this->m_front_ptr + max_element_count) - 1;
	}

	_FORCE_INLINE_ FE::const_reverse_iterator<FE::contiguous_iterator<T>> crend() noexcept
	{
		return this->m_front_ptr - 1;
	}

	template<FE::OBJECT_TRIVIALITY is_trivial = FE::is_trivially_constructible_and_destructible<T>::_VALUE_>
	_FORCE_INLINE_ static void swap(queue<T, max_element_count, is_trivial>& first_ref_p, queue<T, max_element_count, is_trivial>& second_ref_p) noexcept
	{
		queue<T, max_element_count, is_trivial> l_temporary = std::move(first_ref_p);
		first_ref_p = std::move(second_ref_p);
		second_ref_p = std::move(l_temporary);
	}

	template<FE::OBJECT_TRIVIALITY is_trivial = FE::is_trivially_constructible_and_destructible<T>::_VALUE_>
	var::boolean operator==(queue<T, max_element_count, is_trivial>& other_ref_p) noexcept
	{
		return FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
	}

	template<FE::OBJECT_TRIVIALITY is_trivial = FE::is_trivially_constructible_and_destructible<T>::_VALUE_>
	var::boolean operator!=(queue<T, max_element_count, is_trivial>& other_ref_p) noexcept
	{
		return !FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
	}

protected:
	_FORCE_INLINE_ void __jump_front_pointer(difference_type ptrdiff_p) noexcept
	{
		this->m_front_ptr += ptrdiff_p;
	}

	_FORCE_INLINE_ void __set_front_pointer_to_zero() noexcept
	{
		this->m_front_ptr = this->m_absolute_begin_ptrc;
	}

	_FORCE_INLINE_ void __jump_back_pointer(difference_type ptrdiff_p) noexcept
	{
		this->m_back_ptr += ptrdiff_p;
	}

	_FORCE_INLINE_ void __set_back_pointer_to_zero() noexcept
	{
		this->m_back_ptr = this->m_absolute_begin_ptrc;
	}
};


template<class T, count_t max_element_count>
class queue<T, max_element_count, FE::OBJECT_TRIVIALITY::_TRIVIAL> final : public static_queue_base<T, max_element_count>
{
public:
	using base_type = static_queue_base<T, max_element_count>;
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

	_FORCE_INLINE_ queue() noexcept : base_type() {}
	_FORCE_INLINE_ _CONSTEXPR20_ ~queue() noexcept {}

	_FORCE_INLINE_ queue(std::initializer_list<value_type>&& initializer_list_p) noexcept : base_type()
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));

		this->__jump_back_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ queue(queue& other_ref_p) noexcept : base_type()
	{
		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			other_ref_p.m_memory, max_element_count, sizeof(value_type));

		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
	}

	_FORCE_INLINE_ queue(queue&& rvalue_p) noexcept : base_type()
	{
		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			rvalue_p.m_memory, max_element_count, sizeof(value_type));

		UNALIGNED_MEMSET(rvalue_p.m_memory, _NULL_, max_element_count * sizeof(value_type));

		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);
		rvalue_p.__set_front_pointer_to_zero();
		rvalue_p.__set_back_pointer_to_zero();
	}

	_FORCE_INLINE_ queue& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_back_pointer(initializer_list_p.size());
		return *this;
	}

	_FORCE_INLINE_ queue& operator=(queue& other_ref_p) noexcept
	{
		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			other_ref_p.m_memory, max_element_count, sizeof(value_type));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
		return *this;
	}

	_FORCE_INLINE_ queue& operator=(queue&& rvalue_p) noexcept
	{
		UNALIGNED_MEMCPY(this->m_memory, max_element_count, sizeof(value_type),
			rvalue_p.m_memory, max_element_count, sizeof(value_type));

		UNALIGNED_MEMSET(rvalue_p.m_memory, _NULL_, max_element_count * sizeof(value_type));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();

		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);

		rvalue_p.__set_front_pointer_to_zero();
		rvalue_p.__set_back_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ void push(value_type value_p) noexcept
	{
		if (this->is_empty() == true)
		{
			this->__set_front_pointer_to_zero();
			this->__set_back_pointer_to_zero();
		}

		FE_ASSERT(this->m_back_ptr >= this->m_absolute_begin_ptrc + max_element_count, "UNRECOVERABLE ERROR!: Exceeded the queue index boundary");

		*this->m_back_ptr = value_p;
		++this->m_back_ptr;
	}

	_FORCE_INLINE_ value_type pop() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "UNRECOVERABLE ERROR!: Exceeded the queue index boundary");

		T l_return_value_buffer = *this->m_front_ptr;
		*this->m_front_ptr = (T)_NULL_;
		++this->m_front_ptr;
		return l_return_value_buffer;
	}

	_FORCE_INLINE_ void pop_all() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "WARNING: It is pointless to pop empty elements.");

		UNALIGNED_MEMSET(this->m_front_ptr, _NULL_, (this->m_back_ptr - this->m_front_ptr) * sizeof(T));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
	}
};


template<class T, count_t max_element_count>
class queue<T, max_element_count, FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL> final : public static_queue_base<T, max_element_count>
{
	OBJECT_LIFECYCLE m_bool_mask[max_element_count];

public:
	using base_type = static_queue_base<T, max_element_count>;
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

	_FORCE_INLINE_ queue() noexcept : base_type(), m_bool_mask() {}

	_FORCE_INLINE_ ~queue() noexcept
	{
		if (this->is_empty() == true) { return; }

		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_front_ptr, this->m_back_ptr, this->m_bool_mask);
	}

	_FORCE_INLINE_ queue(std::initializer_list<value_type>&& initializer_list_p) noexcept : base_type(), m_bool_mask()
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, initializer_list_p.size(), this->m_bool_mask,
			const_cast<T*>(initializer_list_p.begin()), initializer_list_p.size());

		this->__jump_back_pointer(initializer_list_p.size());
	}

	_FORCE_INLINE_ queue(queue& other_ref_p) noexcept : base_type(), m_bool_mask()
	{
		FE::copy_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
			other_ref_p.m_front_ptr, other_ref_p.m_back_ptr - other_ref_p.m_front_ptr, static_cast<const OBJECT_LIFECYCLE*>(other_ref_p.m_bool_mask + (other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc)));
		
		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
	}

	_FORCE_INLINE_ queue(queue&& rvalue_p) noexcept : base_type(), m_bool_mask()
	{
		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
			rvalue_p.m_front_ptr, rvalue_p.m_back_ptr - rvalue_p.m_front_ptr, static_cast<OBJECT_LIFECYCLE*>(rvalue_p.m_bool_mask + (rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc)));

		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(rvalue_p.m_front_ptr, rvalue_p.m_back_ptr, rvalue_p.m_bool_mask + (rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc));

		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);
		rvalue_p.__set_front_pointer_to_zero();
		rvalue_p.__set_back_pointer_to_zero();
	}

	_FORCE_INLINE_ queue& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
	{
		FE_ASSERT(initializer_list_p.size() > max_element_count, "ERROR!: The length of std::initializer_list exceeds the max_element_count");

		FE::move_assign<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, initializer_list_p.size(), this->m_bool_mask,
			const_cast<T*>(initializer_list_p.begin()), initializer_list_p.size()); 
		
		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_back_pointer(initializer_list_p.size());
		return *this;
	}

	_FORCE_INLINE_ queue& operator=(queue& other_ref_p) noexcept
	{
		FE::copy_assign<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
			other_ref_p.m_front_ptr, other_ref_p.m_back_ptr - other_ref_p.m_front_ptr, static_cast<const OBJECT_LIFECYCLE*>(other_ref_p.m_bool_mask + (other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc)));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
		return *this;
	}

	_FORCE_INLINE_ queue& operator=(queue&& rvalue_p) noexcept
	{
		FE::move_assign<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, max_element_count, static_cast<OBJECT_LIFECYCLE*>(this->m_bool_mask),
			rvalue_p.m_front_ptr, rvalue_p.m_back_ptr - rvalue_p.m_front_ptr, static_cast<OBJECT_LIFECYCLE*>(rvalue_p.m_bool_mask + (rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc)));

		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(rvalue_p.m_front_ptr, rvalue_p.m_back_ptr, rvalue_p.m_bool_mask + (rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);
		rvalue_p.__set_front_pointer_to_zero();
		rvalue_p.__set_back_pointer_to_zero();
		return *this;
	}

	_FORCE_INLINE_ void rearrange() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "WARNING: It is pointless to arrange empty elements.");

		FE::move_assign<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_absolute_begin_ptrc, max_element_count, this->m_bool_mask, this->m_front_ptr, this->m_back_ptr - this->m_front_ptr, this->m_bool_mask + (this->m_front_ptr - this->m_absolute_begin_ptrc));
		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_front_ptr, this->m_back_ptr, this->m_bool_mask + (this->m_front_ptr - this->m_absolute_begin_ptrc));

		size_t l_size = this->m_back_ptr - this->m_front_ptr;

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
		this->__jump_back_pointer(l_size);
	}

	_FORCE_INLINE_ void push(value_type value_p) noexcept
	{
		if (this->is_empty() == true)
		{
			this->__set_front_pointer_to_zero();
			this->__set_back_pointer_to_zero();
		}

		FE_ASSERT(this->m_back_ptr >= this->m_absolute_begin_ptrc + max_element_count, "UNRECOVERABLE ERROR!: Exceeded the queue index boundary");

		FE::move_construct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_back_ptr, this->m_bool_mask + (this->m_back_ptr - this->m_absolute_begin_ptrc), std::move(value_p));
		++this->m_back_ptr;
	}

	_FORCE_INLINE_ value_type pop() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "UNRECOVERABLE ERROR!: Exceeded the queue index boundary");

		T l_return_value_buffer = ::std::move(*this->m_front_ptr);
		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_front_ptr, this->m_bool_mask + (this->m_front_ptr - this->m_absolute_begin_ptrc));
		++this->m_front_ptr;
		return ::std::move(l_return_value_buffer);
	}

	_FORCE_INLINE_ void pop_all() noexcept
	{
		FE_ASSERT(this->is_empty() == true, "WARNING: It is pointless to pop empty elements.");

		FE::destruct<FE::iterator<FE::contiguous_iterator<value_type>>>(this->m_front_ptr, this->m_back_ptr, this->m_bool_mask + (this->m_front_ptr - this->m_absolute_begin_ptrc));

		this->__set_front_pointer_to_zero();
		this->__set_back_pointer_to_zero();
	}
};


END_NAMESPACE
#endif