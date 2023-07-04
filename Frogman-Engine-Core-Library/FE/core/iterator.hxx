#ifndef _ITERATOR_HXX_
#define _ITERATOR_HXX_
#include "prerequisite_symbols.h"
#include <functional>


BEGIN_NAMESPACE(FE)


template <class implementation>
struct iterator final
{
	using iterator_category = typename implementation::category;
	using value_type = typename implementation::value_type;
	using difference_type = typename implementation::difference_type;
	using pointer = typename implementation::pointer;
	using reference = typename implementation::reference;
private:
	pointer m_iterator;

public:
	constexpr iterator() noexcept : m_iterator() {}

	iterator(pointer value_p) noexcept : m_iterator(value_p) {}
	iterator(const iterator& other_cref_p) noexcept : m_iterator(other_cref_p.m_iterator) {}
	iterator(iterator&& other_p) noexcept : m_iterator(other_p.m_iterator) { other_p.m_iterator = nullptr; }
	_CONSTEXPR20_ ~iterator() noexcept {}

	reference operator*() noexcept
	{
		return *(this->m_iterator);
	}

	pointer operator->() noexcept
	{
		return this->m_iterator;
	}

	reference operator[](index_t index_p) noexcept
	{
		return implementation::index(this->m_iterator, index_p);
	}

	iterator operator+(difference_type pointer_offset_p) noexcept
	{
		return implementation::plus(this->m_iterator, pointer_offset_p);
	}

	iterator& operator+=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = implementation::plus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	iterator& operator++() noexcept
	{
		this->m_iterator = implementation::increment(this->m_iterator);
		return *this;
	}

	iterator operator++(int) noexcept
	{
		iterator l_temporary = *this;
		this->m_iterator = implementation::increment(this->m_iterator);
		return l_temporary;
	}


	iterator operator-(difference_type pointer_offset_p) noexcept
	{
		return implementation::minus(this->m_iterator, pointer_offset_p);
	}

	iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_iterator = implementation::minus(this->m_iterator, pointer_offset_p);
		return *this;
	}

	iterator& operator-(const iterator& other_cref_p) noexcept
	{
		implementation::minus(this->m_iterator, other_cref_p.m_iterator);
		return *this;
	}

	iterator& operator-=(const iterator& other_cref_p) noexcept
	{
		this->m_iterator = implementation::minus(this->m_iterator, other_cref_p.m_iterator);
		return *this;
	}

	iterator& operator--() noexcept
	{
		this->m_iterator = implementation::decrement(this->m_iterator);
		return *this;
	}

	iterator& operator--(int) noexcept
	{
		iterator l_temporary = *this;
		this->m_iterator = implementation::decrement(this->m_iterator);
		return l_temporary;
	}


	iterator& operator=(const iterator& other_cref_p) noexcept
	{
		this->m_iterator = other_cref_p.m_iterator;
		return *this;
	}

	iterator& operator=(iterator&& rvalue_other_p) noexcept
	{
		this->m_iterator = rvalue_other_p.m_iterator;
		rvalue_other_p.m_iterator = nullptr;
		return *this;
	}


	var::boolean operator<(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator < other_cref_p.m_iterator;
	}

	var::boolean operator<=(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator <= other_cref_p.m_iterator;
	}

	var::boolean operator>(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator > other_cref_p.m_iterator;
	}

	var::boolean operator>=(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator >= other_cref_p.m_iterator;
	}

	var::boolean operator==(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator == other_cref_p.m_iterator;
	}

	var::boolean operator!=(const iterator& other_cref_p) noexcept
	{
		return this->m_iterator != other_cref_p.m_iterator;
	}
};


template <class implementation>
struct reverse_iterator final
{
	using reverse_iterator_category = typename implementation::category;
	using value_type = typename implementation::value_type;
	using difference_type = typename implementation::difference_type;
	using pointer = typename implementation::pointer;
	using reference = typename implementation::reference;
private:
	pointer m_reverse_iterator;

public:
	constexpr reverse_iterator() noexcept : m_reverse_iterator() {}

	reverse_iterator(pointer value_p) noexcept : m_reverse_iterator(value_p) {}
	reverse_iterator(const reverse_iterator& other_cref_p) noexcept : m_reverse_iterator(other_cref_p.m_reverse_iterator) {}
	reverse_iterator(reverse_iterator&& other_p) noexcept : m_reverse_iterator(other_p.m_reverse_iterator) { other_p.m_reverse_iterator = nullptr; }
	_CONSTEXPR20_ ~reverse_iterator() noexcept {}

	reference operator*() noexcept
	{
		return *(this->m_reverse_iterator);
	}

	pointer operator->() noexcept
	{
		return this->m_reverse_iterator;
	}

	reference operator[](index_t index_p) noexcept
	{
		return implementation::index(this->m_reverse_iterator, index_p);
	}

	reverse_iterator operator+(difference_type pointer_offset_p) noexcept
	{
		return implementation::minus(this->m_reverse_iterator, pointer_offset_p);
	}

	reverse_iterator& operator+=(difference_type pointer_offset_p) noexcept
	{
		this->m_reverse_iterator = implementation::minus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	reverse_iterator& operator++() noexcept
	{
		this->m_reverse_iterator = implementation::decrement(this->m_reverse_iterator);
		return *this;
	}

	reverse_iterator operator++(int) noexcept
	{
		reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = implementation::decrement(this->m_reverse_iterator);
		return l_temporary;
	}


	reverse_iterator operator-(difference_type pointer_offset_p) noexcept
	{
		return implementation::plus(this->m_reverse_iterator, pointer_offset_p);
	}

	reverse_iterator& operator-=(difference_type pointer_offset_p) noexcept
	{
		this->m_reverse_iterator = implementation::plus(this->m_reverse_iterator, pointer_offset_p);
		return *this;
	}

	reverse_iterator& operator-(const reverse_iterator& other_cref_p) noexcept
	{
		implementation::plus(this->m_reverse_iterator, other_cref_p.m_reverse_iterator);
		return *this;
	}

	reverse_iterator& operator-=(const reverse_iterator& other_cref_p) noexcept
	{
		this->m_reverse_iterator = implementation::plus(this->m_reverse_iterator, other_cref_p.m_reverse_iterator);
		return *this;
	}

	reverse_iterator& operator--() noexcept
	{
		this->m_reverse_iterator = implementation::increment(this->m_reverse_iterator);
		return *this;
	}

	reverse_iterator& operator--(int) noexcept
	{
		reverse_iterator l_temporary = *this;
		this->m_reverse_iterator = implementation::increment(this->m_reverse_iterator);
		return l_temporary;
	}


	reverse_iterator& operator=(const reverse_iterator& other_cref_p) noexcept
	{
		this->m_reverse_iterator = other_cref_p.m_reverse_iterator;
		return *this;
	}

	reverse_iterator& operator=(reverse_iterator&& rvalue_other_p) noexcept
	{
		this->m_reverse_iterator = rvalue_other_p.m_reverse_iterator;
		rvalue_other_p.m_reverse_iterator = nullptr;
		return *this;
	}


	var::boolean operator<(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator < other_cref_p.m_reverse_iterator;
	}

	var::boolean operator<=(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator <= other_cref_p.m_reverse_iterator;
	}

	var::boolean operator>(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator > other_cref_p.m_reverse_iterator;
	}

	var::boolean operator>=(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator >= other_cref_p.m_reverse_iterator;
	}

	var::boolean operator==(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator == other_cref_p.m_reverse_iterator;
	}

	var::boolean operator!=(const reverse_iterator& other_cref_p) noexcept
	{
		return this->m_reverse_iterator != other_cref_p.m_reverse_iterator;
	}
};




template <typename T>
struct contiguous_iterator
{
	typedef contiguous_iterator category;
	typedef T value_type;
	typedef ::FE::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	static reference index(pointer pointer_p, index_t index_p) noexcept
	{
		return *(pointer_p + index_p);
	}

	static pointer plus(pointer pointer_p, difference_type difference_p) noexcept
	{
		return pointer_p + difference_p;
	}

	static pointer increment(pointer pointer_p) noexcept
	{
		return ++pointer_p;
	}

	static pointer minus(pointer left_pointer_p, pointer right_pointer_p) noexcept
	{
		return left_pointer_p - right_pointer_p;
	}

	static pointer minus(pointer pointer_p, difference_type difference_p) noexcept
	{
		return pointer_p - difference_p;
	}

	static pointer decrement(pointer pointer_p) noexcept
	{
		return --pointer_p;
	}
};

END_NAMESPACE
#endif