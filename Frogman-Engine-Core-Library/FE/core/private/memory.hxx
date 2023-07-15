#ifndef _FE_CORE_PRIVATE_MEMORY_HXX_
#define _FE_CORE_PRIVATE_MEMORY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>


BEGIN_NAMESPACE(FE)




template <typename bool_type>
_FORCE_INLINE_ var::length_t bool_mask_length(const bool_type* const boolean_mask_ptrc_p, length_t max_length_p) noexcept
{
	static_assert(sizeof(bool_type) == 1, "The size of bool_type must be one byte");
	FE_ASSERT(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");

	const bool_type* l_boolean_mask_begin_ptr = boolean_mask_ptrc_p;
	const bool_type* const l_boolean_mask_end_ptrc = l_boolean_mask_begin_ptr + max_length_p;

	while (l_boolean_mask_begin_ptr != l_boolean_mask_end_ptrc && *l_boolean_mask_begin_ptr == static_cast<bool_type>(1))
	{
		++l_boolean_mask_begin_ptr;
	}

	return l_boolean_mask_begin_ptr - boolean_mask_ptrc_p;
}


template<class iterator>
var::boolean memcmp_s(iterator left_iterator_begin_p, iterator left_iterator_end_p, iterator right_iterator_begin_p, iterator right_iterator_end_p) noexcept
{
	iterator l_left_iterator_begin = left_iterator_begin_p;

	if ((left_iterator_end_p - left_iterator_begin_p) != (right_iterator_end_p - right_iterator_begin_p))
	{
		return false;
	}

	while ((*l_left_iterator_begin == *right_iterator_begin_p) && (l_left_iterator_begin != left_iterator_end_p))
	{
		++l_left_iterator_begin;
		++right_iterator_begin_p;
	}

	if ((l_left_iterator_begin - left_iterator_begin_p) == (left_iterator_end_p - left_iterator_begin_p))
	{
		return true;
	}

	return false;
}


template <typename T, typename ... arguments>
_FORCE_INLINE_ void assign(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p, arguments&& ...arguments_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: object_ptrc_p is nullptr.");
    FE_ASSERT(bool_mask_ptrc_p == nullptr, "ERROR: bool_mask_ptrc_p is nullptr.");

	if (*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(object_ptrc_p) T(arguments_p...);
        *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	*object_ptrc_p = ::std::move(arguments_p...);
}

template <typename T>
_FORCE_INLINE_ void copy_assign(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p, T& other_ref_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: object_ptrc_p is nullptr.");
    FE_ASSERT(bool_mask_ptrc_p == nullptr, "ERROR: bool_mask_ptrc_p is nullptr.");

	if (*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(object_ptrc_p) T(other_ref_p);
        *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	*object_ptrc_p = other_ref_p;
}

template <typename T>
_FORCE_INLINE_ void move_assign(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p, T&& rvalue_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: object_ptrc_p is nullptr.");
    FE_ASSERT(bool_mask_ptrc_p == nullptr, "ERROR: bool_mask_ptrc_p is nullptr.");

	if (*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(object_ptrc_p) T(std::move(rvalue_p));
        *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	*object_ptrc_p = std::move(rvalue_p);
}




template <typename T>
_FORCE_INLINE_ void construct(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T();
    *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
}

template <typename T>
_FORCE_INLINE_ void copy_construct(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p, T& other_ref_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T(other_ref_p);
    *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
}

template <typename T>
_FORCE_INLINE_ void move_construct(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p, T&& rvalue_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(*bool_mask_ptrc_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T(std::move(rvalue_p));
    *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_CONSTRUCTED;
}




template <typename iterator, typename ... arguments>
_FORCE_INLINE_ void assign(iterator begin_p, iterator end_p, OBJECT_LIFECYCLE* const boolean_mask_ptrc_p, arguments && ...arguments_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = boolean_mask_ptrc_p;

	for (iterator it = begin_p; it != end_p; ++it)
	{
		if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
		{
			*it = std::move(arguments_p...);
			++l_boolean_mask_ptr;
		}
		else
		{
			new(it.operator->()) T(arguments_p...);
			++l_boolean_mask_ptr;
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, const typename iterator::value_type* const data_source_begin_ptrc_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	const T* l_initializer_list_begin_ptr = data_source_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin_ptr;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin_ptr;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const data_source_begin_ptrc_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	T* l_initializer_list_begin_ptr = data_source_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin_ptr);

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin_ptr);

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const source_data_begin_ptrc_p, capacity_t source_data_length_p, const OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	const OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	const T* l_initializer_list_begin_ptr = source_data_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin_ptr;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if (*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin_ptr;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if (*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const source_data_begin_ptrc_p, capacity_t source_data_length_p, OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	T* l_initializer_list_begin_ptr = source_data_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin_ptr);

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if(*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin_ptr);

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if(*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}




template <typename T>
_FORCE_INLINE_ void destruct(T* const object_ptrc_p, OBJECT_LIFECYCLE* const bool_mask_ptrc_p) noexcept
{
	FE_ASSERT(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(bool_mask_p == OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: Unable to double-destruct the object, that object_ptrc_p is pointing to");

	object_ptrc_p->~T();
    *bool_mask_ptrc_p = OBJECT_LIFECYCLE::_DESTRUCTED;
}

template<class iterator>
_FORCE_INLINE_ void destruct(iterator begin_p, iterator end_p, OBJECT_LIFECYCLE* const boolean_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = boolean_mask_ptrc_p;

	for (iterator it = begin_p; it != end_p; ++it)
	{
		if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
		{
			it->~T();
			*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_DESTRUCTED;

			++l_boolean_mask_ptr;
		}
	}
}




template<class iterator>
_FORCE_INLINE_ void copy_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, const typename iterator::value_type* const data_source_begin_ptrc_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	const T* l_initializer_list_begin_ptr = data_source_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const data_source_begin_ptrc_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	T* l_initializer_list_begin_ptr = data_source_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const source_data_begin_ptrc_p, capacity_t source_data_length_p, const OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	const OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	const T* l_initializer_list_begin_ptr = source_data_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin_ptr);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, typename iterator::value_type* const source_data_begin_ptrc_p, capacity_t source_data_length_p, OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	T* l_initializer_list_begin_ptr = source_data_begin_ptrc_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
	else
	{
		for (var::index_t i = 0; i < source_data_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin_ptr));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin_ptr;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}




END_NAMESPACE

#endif
