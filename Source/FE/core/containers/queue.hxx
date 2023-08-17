//#ifndef _FE_CORE_QUEUE_HXX_
//#define _FE_CORE_QUEUE_HXX_
//// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
//#include <FE/core/prerequisites.h>
//#include <FE/core/iterator.hxx>
//#include <FE/core/memory.hxx>
//#include <initializer_list>
//
//
//
//
//BEGIN_NAMESPACE(FE)
//
//
//template<class container>
//class queue
//{
//public:
//	using container_type = container;
//	using pointer = typename container::pointer;
//	using difference_type = typename container::difference_type;
//	using const_pointer = typename container::const_pointer;
//	using const_iterator = typename container::const_iterator;
//	using const_reverse_iterator = typename container::const_reverse_iterator;
//	using reference = typename container::reference;
//	using const_reference = typename container::const_reference;
//	using length_type = typename container::length_type;
//	using size_type = typename container::size_type;
//	using value_type = typename container::value_type;
//	using alignment = typename container::alignment;
//	using allocator_type = typename container::allocator;
//
//	container_type _underlying_container;
//
//	_FORCE_INLINE_ dynamic_queue_base() noexcept {}
//	_FORCE_INLINE_ _CONSTEXPR20_ ~dynamic_queue_base() noexcept {}
//};
//
//
//
//
//template<class T, size_t max_element_count, class type_trait = FE::type_trait<T, FE::stack_memory<T>>>
//class queue final
//{
//public:
//	using value_type = T;
//	using length_type = count_t;
//	using size_type = count_t;
//	using reference = T&;
//	using const_reference = const T&;
//	using pointer = T*;
//	using const_pointer = const T*;
//	using const_iterator = FE::const_iterator<FE::contiguous_iterator<T>>;
//	using const_reverse_iterator = FE::const_reverse_iterator<FE::contiguous_iterator<T>>;
//	using difference_type = ptrdiff_t;
//
//protected:
//	var::byte m_memory[sizeof(value_type) * max_element_count];
//	pointer m_front_ptr;
//	pointer m_back_ptr;
//
//	pointer const m_absolute_begin_ptrc;
//
//public:
//	_FORCE_INLINE_ queue() noexcept : m_memory(), m_front_ptr(reinterpret_cast<pointer>(m_memory)), m_back_ptr(m_front_ptr), m_absolute_begin_ptrc(m_front_ptr) {}
//	_FORCE_INLINE_ _CONSTEXPR20_ ~queue() noexcept {}
//
//	_FORCE_INLINE_ queue(std::initializer_list<value_type>&& initializer_list_p) noexcept : base_type()
//	{
//		FE_ASSERT(initializer_list_p.size() > max_element_count, "${%s@0}!: The length of std::initializer_list exceeds the max_element_count", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
//
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));
//
//		this->__jump_back_pointer(initializer_list_p.size());
//	}
//
//	_FORCE_INLINE_ queue(queue& other_ref_p) noexcept : base_type()
//	{
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			other_ref_p.m_memory, max_element_count, sizeof(value_type));
//
//		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
//		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
//	}
//
//	_FORCE_INLINE_ queue(queue&& rvalue_p) noexcept : base_type()
//	{
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			rvalue_p.m_memory, max_element_count, sizeof(value_type));
//
//#ifdef _DEBUG_
//		UNALIGNED_MEMSET(rvalue_p.m_memory, _NULL_, max_element_count * sizeof(value_type));
//#endif
//
//		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
//		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);
//		rvalue_p.__set_front_pointer_to_zero();
//		rvalue_p.__set_back_pointer_to_zero();
//	}
//
//	_FORCE_INLINE_ queue& operator=(std::initializer_list<value_type> initializer_list_p) noexcept
//	{
//		FE_ASSERT(initializer_list_p.size() > max_element_count, "${%s@0}!: The length of std::initializer_list exceeds the max_element_count", TO_STRING(MEMORY_ERROR_1XX::_ERROR_INVALID_SIZE));
//
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			initializer_list_p.begin(), initializer_list_p.size(), sizeof(value_type));
//
//		this->__set_front_pointer_to_zero();
//		this->__set_back_pointer_to_zero();
//		this->__jump_back_pointer(initializer_list_p.size());
//		return *this;
//	}
//
//	_FORCE_INLINE_ queue& operator=(queue& other_ref_p) noexcept
//	{
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			other_ref_p.m_memory, max_element_count, sizeof(value_type));
//
//		this->__set_front_pointer_to_zero();
//		this->__set_back_pointer_to_zero();
//		this->__jump_front_pointer(other_ref_p.m_front_ptr - other_ref_p.m_absolute_begin_ptrc);
//		this->__jump_back_pointer(other_ref_p.m_back_ptr - other_ref_p.m_front_ptr);
//		return *this;
//	}
//
//	_FORCE_INLINE_ queue& operator=(queue&& rvalue_p) noexcept
//	{
//		if (rvalue_p.size() == 00)
//		{
//			return *this;
//		}
//		this->m_front_ptr
//		type_trait::move_construct();
//		::FE::unaligned_memcpy(this->m_memory, max_element_count, sizeof(value_type),
//			rvalue_p.m_memory, max_element_count, sizeof(value_type));
//
//#ifdef _DEBUG_
//		UNALIGNED_MEMSET(rvalue_p.m_memory, _NULL_, max_element_count * sizeof(value_type));
//#endif
//
//		this->__set_front_pointer_to_zero();
//		this->__set_back_pointer_to_zero();
//
//		this->__jump_front_pointer(rvalue_p.m_front_ptr - rvalue_p.m_absolute_begin_ptrc);
//		this->__jump_back_pointer(rvalue_p.m_back_ptr - rvalue_p.m_front_ptr);
//
//		rvalue_p.__set_front_pointer_to_zero();
//		rvalue_p.__set_back_pointer_to_zero();
//		return *this;
//	}
//
//	_FORCE_INLINE_ void push(value_type value_p) noexcept
//	{
//		if (this->is_empty() == true)
//		{
//			this->__set_front_pointer_to_zero();
//			this->__set_back_pointer_to_zero();
//		}
//
//		FE_ASSERT(this->m_back_ptr >= this->m_absolute_begin_ptrc + max_element_count, "${%s@0}: Exceeded the queue index boundary", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
//
//		*this->m_back_ptr = value_p;
//		++this->m_back_ptr;
//	}
//
//	_FORCE_INLINE_ value_type pop() noexcept
//	{
//		FE_ASSERT(this->is_empty() == true, "${%s@0}: Exceeded the queue index boundary", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
//
//		T l_return_value_buffer = std::move(*this->m_front_ptr);
//		type_trait::destruct(this->m_front_ptr);
//		++this->m_front_ptr;
//		return std::move(l_return_value_buffer);
//	}
//
//	_FORCE_INLINE_ void pop_all() noexcept
//	{
//		FE_ASSERT(this->is_empty() == true, "${%s@0}: the queue is empty", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
//
//		type_trait::destruct(this->m_front_ptr, this->m_back_ptr);
//
//		this->__set_front_pointer_to_zero();
//		this->__set_back_pointer_to_zero();
//	}
//
//	_FORCE_INLINE_ const_reference front() const noexcept
//	{
//		return *this->m_front_ptr;
//	}
//
//	_FORCE_INLINE_ const_reference back() const noexcept
//	{
//		return *(this->m_back_ptr - 1);
//	}
//
//	_NODISCARD_ _FORCE_INLINE_ var::boolean is_empty() noexcept
//	{
//		return (this->m_front_ptr == this->m_back_ptr) ? true : false;
//	}
//
//	_FORCE_INLINE_ length_type length() noexcept
//	{
//		return this->m_back_ptr - this->m_front_ptr;
//	}
//
//	_FORCE_INLINE_ size_type size() noexcept
//	{
//		return this->m_back_ptr - this->m_front_ptr;
//	}
//
//	_FORCE_INLINE_ constexpr size_type max_size() const noexcept
//	{
//		return max_element_count;
//	}
//
//	_FORCE_INLINE_ constexpr size_type capacity() const noexcept
//	{
//		return max_element_count;
//	}
//
//	_FORCE_INLINE_ const_iterator cbegin() noexcept
//	{
//		return this->m_front_ptr;
//	}
//
//	_FORCE_INLINE_ const_iterator cend() noexcept
//	{
//		return this->m_front_ptr + max_element_count;
//	}
//
//	_FORCE_INLINE_ const_reverse_iterator crbegin() noexcept
//	{
//		return (this->m_front_ptr + max_element_count) - 1;
//	}
//
//	_FORCE_INLINE_ const_reverse_iterator crend() noexcept
//	{
//		return this->m_front_ptr - 1;
//	}
//
//	_FORCE_INLINE_ static void swap(queue& first_ref_p, queue& second_ref_p) noexcept
//	{
//		queue l_temporary = std::move(first_ref_p);
//		first_ref_p = std::move(second_ref_p);
//		second_ref_p = std::move(l_temporary);
//	}
//
//	var::boolean operator==(queue& other_ref_p) noexcept
//	{
//		return FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
//	}
//
//	var::boolean operator!=(queue& other_ref_p) noexcept
//	{
//		return !FE::memcmp_s(this->cbegin(), this->cend(), other_ref_p.cbegin(), other_ref_p.cend());
//	}
//
//protected:
//	_FORCE_INLINE_ void __jump_front_pointer(difference_type ptrdiff_p) noexcept
//	{
//		this->m_front_ptr += ptrdiff_p;
//	}
//
//	_FORCE_INLINE_ void __set_front_pointer_to_zero() noexcept
//	{
//		this->m_front_ptr = this->m_absolute_begin_ptrc;
//	}
//
//	_FORCE_INLINE_ void __jump_back_pointer(difference_type ptrdiff_p) noexcept
//	{
//		this->m_back_ptr += ptrdiff_p;
//	}
//
//	_FORCE_INLINE_ void __set_back_pointer_to_zero() noexcept
//	{
//		this->m_back_ptr = this->m_absolute_begin_ptrc;
//	}
//};
//
//
//END_NAMESPACE
//#endif