#ifndef _FE_CORE_ITERATOR_HXX_
#define _FE_CORE_ITERATOR_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>




BEGIN_NAMESPACE(FE)


template <class Implementation>
struct iterator final
{
	using iterator_category = typename Implementation::category;
	using value_type = typename Implementation::value_type;
	using difference_type = typename Implementation::difference_type;
	using pointer = typename Implementation::pointer;
	using reference = typename Implementation::reference;
	using const_pointer = typename Implementation::const_pointer;
	using const_reference = typename Implementation::const_reference;

private:
	pointer m_iterator;

public:
	_CONSTEXPR17_ iterator() noexcept : m_iterator() {}

	_FORCE_INLINE_ iterator(pointer value_p) noexcept : m_iterator(value_p) {}
	_FORCE_INLINE_ iterator(const iterator& other_p) noexcept : m_iterator(other_p.m_iterator) {}
	_FORCE_INLINE_ iterator(iterator&& other_p) noexcept : m_iterator(other_p.m_iterator) { other_p.m_iterator = nullptr; }
	_CONSTEXPR23_ _FORCE_INLINE_ ~iterator() noexcept {}

	_FORCE_INLINE_ reference operator*() const noexcept
	{
		return *(this->m_iterator);
	}

	_FORCE_INLINE_ pointer operator->() const noexcept
	{
		return this->m_iterator;
	}

	_FORCE_INLINE_ reference operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(index_p == FE::_MAX_VALUE_<index_t>, "${%s@0}: negative integers cannot be assigned to an index_t variable.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
		return Implementation::index(this->m_iterator, index_p);
	}

	_FORCE_INLINE_ iterator operator+(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::plus(this->m_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ iterator& operator+=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = Implementation::plus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ iterator& operator++() noexcept
	{
		this->m_iterator = Implementation::increment(this->m_iterator);
		return *this;
	}

	_FORCE_INLINE_ iterator operator++(int) noexcept
	{
		iterator l_temporary = *this;
		this->m_iterator = Implementation::increment(this->m_iterator);
		return l_temporary;
	}


	_FORCE_INLINE_ iterator operator-(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::minus(this->m_iterator, pointer_offset_p);
	}

	_CONSTEXPR20_ _FORCE_INLINE_ iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = Implementation::minus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ difference_type operator-(const iterator& other_p) noexcept
	{
		return Implementation::minus(this->m_iterator, other_p.m_iterator);
	}

	_CONSTEXPR20_ _FORCE_INLINE_ iterator& operator-=(const iterator& other_p) noexcept
	{
		this->m_iterator = Implementation::minus(this->m_iterator, other_p.m_iterator);
		return *this;
	}

	_FORCE_INLINE_ iterator& operator--() noexcept
	{
		this->m_iterator = Implementation::decrement(this->m_iterator);
		return *this;
	}

	_FORCE_INLINE_ iterator& operator--(int) noexcept
	{
		iterator l_temporary = *this;
		this->m_iterator = Implementation::decrement(this->m_iterator);
		return l_temporary;
	}

	_FORCE_INLINE_ iterator& operator=(pointer value_p) noexcept
	{
		this->m_iterator = value_p;
		return *this;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ iterator& operator=(const iterator& other_p) noexcept
	{
		this->m_iterator = other_p.m_iterator;
		return *this;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ iterator& operator=(iterator&& rvalue_p) noexcept
	{
		this->m_iterator = rvalue_p.m_iterator;
		rvalue_p.m_iterator = nullptr;
		return *this;
	}


	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator<(const iterator& other_p) const noexcept
	{
		return this->m_iterator < other_p.m_iterator;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator<=(const iterator& other_p) const noexcept
	{
		return this->m_iterator <= other_p.m_iterator;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator>(const iterator& other_p) const noexcept
	{
		return this->m_iterator > other_p.m_iterator;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator>=(const iterator& other_p) const noexcept
	{
		return this->m_iterator >= other_p.m_iterator;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator==(const iterator& other_p) const noexcept
	{
		return this->m_iterator == other_p.m_iterator;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ var::boolean operator!=(const iterator& other_p) const noexcept
	{
		return this->m_iterator != other_p.m_iterator;
	}
};


template <class Implementation>
struct reverse_iterator final
{
	using reverse_iterator_category = typename Implementation::category;
	using value_type = typename Implementation::value_type;
	using difference_type = typename Implementation::difference_type;
	using pointer = typename Implementation::pointer;
	using reference = typename Implementation::reference;
	using const_pointer = typename Implementation::const_pointer;
	using const_reference = typename Implementation::const_reference;

private:
	pointer m_reverse_iterator;

public:
	_CONSTEXPR17_ reverse_iterator() noexcept : m_reverse_iterator() {}

	_FORCE_INLINE_ reverse_iterator(pointer value_p) noexcept : m_reverse_iterator(value_p) {}
	_FORCE_INLINE_ reverse_iterator(const reverse_iterator& other_p) noexcept : m_reverse_iterator(other_p.m_reverse_iterator) {}
	_FORCE_INLINE_ reverse_iterator(reverse_iterator&& rvalue_p) noexcept : m_reverse_iterator(rvalue_p.m_reverse_iterator) { rvalue_p.m_reverse_iterator = nullptr; }
	_FORCE_INLINE_ ~reverse_iterator() noexcept {}

	_FORCE_INLINE_ reference operator*() const noexcept
	{
		return *(this->m_reverse_iterator);
	}

	_FORCE_INLINE_ pointer operator->() const noexcept
	{
		return this->m_reverse_iterator;
	}

	_FORCE_INLINE_ reference operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(index_p == FE::_MAX_VALUE_<index_t>, "${%s@0}: negative integers cannot be assigned to an index_t variable.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
		return Implementation::index(this->m_reverse_iterator, index_p);
	}

	_FORCE_INLINE_ reverse_iterator operator+(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::minus(this->m_reverse_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ reverse_iterator& operator+=(difference_type pointer_offset_p) noexcept
	{
		this->m_reverse_iterator = Implementation::minus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator& operator++() noexcept
	{
		this->m_reverse_iterator = Implementation::decrement(this->m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator operator++(int) noexcept
	{
		reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = Implementation::decrement(this->m_reverse_iterator);
		return l_temporary;
	}


	_FORCE_INLINE_ reverse_iterator operator-(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::plus(this->m_reverse_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ reverse_iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_reverse_iterator = Implementation::plus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ difference_type operator-(const reverse_iterator& other_p) const noexcept
	{
		return Implementation::minus(other_p.m_reverse_iterator, this->m_reverse_iterator);
	}

	_FORCE_INLINE_ reverse_iterator& operator-=(const reverse_iterator& other_p) noexcept
	{
		this->m_reverse_iterator = Implementation::plus(this->m_reverse_iterator, other_p.m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator& operator--() noexcept
	{
		this->m_reverse_iterator = Implementation::increment(this->m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator& operator--(int) noexcept
	{
		reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = Implementation::increment(this->m_reverse_iterator);
		return l_temporary;
	}

	_FORCE_INLINE_ reverse_iterator& operator=(pointer value_p) noexcept
	{
		this->m_reverse_iterator = value_p;
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator& operator=(const reverse_iterator& other_p) noexcept
	{
		this->m_reverse_iterator = other_p.m_reverse_iterator;
		return *this;
	}

	_FORCE_INLINE_ reverse_iterator& operator=(reverse_iterator&& rvalue_p) noexcept
	{
		this->m_reverse_iterator = rvalue_p.m_reverse_iterator;
		rvalue_p.m_reverse_iterator = nullptr;
		return *this;
	}


	_FORCE_INLINE_ boolean operator<(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator < other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator<=(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator <= other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator>(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator > other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator>=(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator >= other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator==(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator == other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator!=(const reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator != other_p.m_reverse_iterator;
	}
};


template <class Implementation>
struct const_iterator final
{
	using iterator_category = typename Implementation::category;
	using value_type = typename Implementation::value_type;
	using difference_type = typename Implementation::difference_type;
	using pointer = typename Implementation::pointer;
	using reference = typename Implementation::reference;
	using const_pointer = typename Implementation::const_pointer;
	using const_reference = typename Implementation::const_reference;

private:
	pointer m_iterator;

public:
	_CONSTEXPR17_ const_iterator() noexcept : m_iterator() {}

	_FORCE_INLINE_ const_iterator(const pointer value_p) noexcept : m_iterator(value_p) {}
	_FORCE_INLINE_ const_iterator(const const_iterator& other_p) noexcept : m_iterator(other_p.m_iterator) {}
	_FORCE_INLINE_ const_iterator(const_iterator&& other_p) noexcept : m_iterator(other_p.m_iterator) { other_p.m_iterator = nullptr; }
	_FORCE_INLINE_ ~const_iterator() noexcept {}

	_FORCE_INLINE_ const_reference operator*() const noexcept
	{
		return *(this->m_iterator);
	}

	_FORCE_INLINE_ const_pointer operator->() const noexcept
	{
		return this->m_iterator;
	}

	_FORCE_INLINE_ const_reference operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(index_p == FE::_MAX_VALUE_<index_t>, "${%s@0}: negative integers cannot be assigned to an index_t variable.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
		return Implementation::index(this->m_iterator, index_p);
	}

	_FORCE_INLINE_ const_iterator operator+(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::plus(this->m_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ const_iterator& operator+=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = Implementation::plus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ const_iterator& operator++() noexcept
	{
		this->m_iterator = Implementation::increment(this->m_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_iterator operator++(int) noexcept
	{
		const_iterator l_temporary = *this;
		this->m_iterator = Implementation::increment(this->m_iterator);
		return l_temporary;
	}


	_FORCE_INLINE_ const_iterator operator-(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::minus(this->m_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ const_iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = Implementation::minus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ difference_type operator-(const const_iterator& other_p) const noexcept
	{
		return Implementation::minus(this->m_iterator, other_p.m_iterator);
	}

	_FORCE_INLINE_ const_iterator& operator-=(const const_iterator& other_p) noexcept
	{
		this->m_iterator = Implementation::minus(this->m_iterator, other_p.m_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_iterator& operator--() noexcept
	{
		this->m_iterator = Implementation::decrement(this->m_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_iterator& operator--(int) noexcept
	{
		const_iterator l_temporary = *this;
		this->m_iterator = Implementation::decrement(this->m_iterator);
		return l_temporary;
	}

	_FORCE_INLINE_ const_iterator& operator=(const pointer value_p) noexcept
	{
		this->m_iterator = value_p;
		return *this;
	}

	_FORCE_INLINE_ const_iterator& operator=(const const_iterator& other_p) noexcept
	{
		this->m_iterator = other_p.m_iterator;
		return *this;
	}

	_FORCE_INLINE_ const_iterator& operator=(const_iterator&& rvalue_p) noexcept
	{
		this->m_iterator = rvalue_p.m_iterator;
		rvalue_p.m_iterator = nullptr;
		return *this;
	}


	_FORCE_INLINE_ boolean operator<(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator < other_p.m_iterator;
	}

	_FORCE_INLINE_ boolean operator<=(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator <= other_p.m_iterator;
	}

	_FORCE_INLINE_ boolean operator>(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator > other_p.m_iterator;
	}

	_FORCE_INLINE_ boolean operator>=(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator >= other_p.m_iterator;
	}

	_FORCE_INLINE_ boolean operator==(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator == other_p.m_iterator;
	}

	_FORCE_INLINE_ boolean operator!=(const const_iterator& other_p) const noexcept
	{
		return this->m_iterator != other_p.m_iterator;
	}
};


template <class Implementation>
struct const_reverse_iterator final
{
	using reverse_iterator_category = typename Implementation::category;
	using value_type = typename Implementation::value_type;
	using difference_type = typename Implementation::difference_type;
	using pointer = typename Implementation::pointer;
	using reference = typename Implementation::reference;
	using const_pointer = typename Implementation::const_pointer;
	using const_reference = typename Implementation::const_reference;

private:
	pointer m_reverse_iterator;

public:
	_CONSTEXPR17_ const_reverse_iterator() noexcept : m_reverse_iterator() {}

	_FORCE_INLINE_ const_reverse_iterator(const pointer value_p) noexcept : m_reverse_iterator(value_p) {}
	_FORCE_INLINE_ const_reverse_iterator(const const_reverse_iterator& other_cref_p) noexcept : m_reverse_iterator(other_cref_p.m_reverse_iterator) {}
	_FORCE_INLINE_ const_reverse_iterator(const_reverse_iterator&& other_p) noexcept : m_reverse_iterator(other_p.m_reverse_iterator) { other_p.m_reverse_iterator = nullptr; }
	_FORCE_INLINE_ ~const_reverse_iterator() noexcept {}

	_FORCE_INLINE_ const_reference operator*() const noexcept
	{
		return *(this->m_reverse_iterator);
	}

	_FORCE_INLINE_ const_pointer operator->() const noexcept
	{
		return this->m_reverse_iterator;
	}

	_FORCE_INLINE_ const_reference operator[](index_t index_p) const noexcept
	{
		FE_ASSERT(index_p == FE::_MAX_VALUE_<index_t>, "%{$s@0}: negative integers cannot be assigned to an index_t variable.", TO_STRING(MEMORY_ERROR_1XX::_FATAL_ERROR_OUT_OF_RANGE));
		return Implementation::index(this->m_reverse_iterator, index_p);
	}

	_FORCE_INLINE_ const_reverse_iterator operator+(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::minus(this->m_reverse_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ const_reverse_iterator& operator+=(difference_type pointer_offset_p) const noexcept
	{
		this->m_reverse_iterator = Implementation::minus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator++() noexcept
	{
		this->m_reverse_iterator = Implementation::decrement(this->m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator operator++(int) noexcept
	{
		const_reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = Implementation::decrement(this->m_reverse_iterator);
		return l_temporary;
	}


	_FORCE_INLINE_ const_reverse_iterator operator-(difference_type pointer_offset_p) const noexcept
	{
		return Implementation::plus(this->m_reverse_iterator, pointer_offset_p);
	}

	_FORCE_INLINE_ const_reverse_iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_reverse_iterator = Implementation::plus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	_FORCE_INLINE_ difference_type operator-(const const_reverse_iterator& other_p) const noexcept
	{
		return Implementation::minus(other_p.m_reverse_iterator, this->m_reverse_iterator);
	}

	_FORCE_INLINE_ const_reverse_iterator& operator-=(const const_reverse_iterator& other_p) noexcept
	{
		this->m_reverse_iterator = Implementation::plus(this->m_reverse_iterator, other_p.m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator--() noexcept
	{
		this->m_reverse_iterator = Implementation::increment(this->m_reverse_iterator);
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator--(int) noexcept
	{
		const_reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = Implementation::increment(this->m_reverse_iterator);
		return l_temporary;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator=(const pointer value_p) noexcept
	{
		this->m_reverse_iterator = value_p;
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator=(const const_reverse_iterator& other_p) noexcept
	{
		this->m_reverse_iterator = other_p.m_reverse_iterator;
		return *this;
	}

	_FORCE_INLINE_ const_reverse_iterator& operator=(const_reverse_iterator&& rvalue_p) noexcept
	{
		this->m_reverse_iterator = rvalue_p.m_reverse_iterator;
		rvalue_p.m_reverse_iterator = nullptr;
		return *this;
	}


	_FORCE_INLINE_ boolean operator<( const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator < other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator<=(const const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator <= other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator>(const const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator > other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator>=(const const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator >= other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator==(const const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator == other_p.m_reverse_iterator;
	}

	_FORCE_INLINE_ boolean operator!=(const const_reverse_iterator& other_p) const noexcept
	{
		return this->m_reverse_iterator != other_p.m_reverse_iterator;
	}
};




template <typename T>
struct contiguous_iterator final
{
	using category = contiguous_iterator;
	using value_type = T;
	using difference_type = ::FE::var::ptrdiff_t;
	using pointer = T*;
	using reference = T&;
	using const_pointer = const T*;
	using const_reference = const T&;

	_CONSTEXPR20_ _FORCE_INLINE_ static reference index(pointer pointer_p, index_t index_p) noexcept
	{
		return *(pointer_p + index_p);
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static pointer plus(pointer pointer_p, difference_type difference_p) noexcept
	{
		return pointer_p + difference_p;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static pointer increment(pointer pointer_p) noexcept
	{
		return ++pointer_p;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static difference_type minus(pointer left_pointer_p, pointer right_pointer_p) noexcept
	{
		return left_pointer_p - right_pointer_p;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static pointer minus(pointer pointer_p, difference_type difference_p) noexcept
	{
		return pointer_p - difference_p;
	}

	_CONSTEXPR20_ _FORCE_INLINE_ static pointer decrement(pointer pointer_p) noexcept
	{
		return --pointer_p;
	}
};

END_NAMESPACE
#endif
