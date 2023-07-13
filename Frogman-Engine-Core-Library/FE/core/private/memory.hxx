#ifndef _FE_CORE_PRIVATE_MEMORY_HXX_
#define _FE_CORE_PRIVATE_MEMORY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>


BEGIN_NAMESPACE(FE)


template <typename bool_type>
_FORCE_INLINE_ var::length_t bool_mask_length(const bool_type* const boolean_mask_ptrc_p, length_t max_length_p) noexcept
{
	static_assert(sizeof(bool_type) == 1, "The size of bool_type must be one byte");
	ABORT_IF(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");

	const bool_type* l_boolean_mask_begin_ptr = boolean_mask_ptrc_p;
	const bool_type* const l_boolean_mask_end_ptrc = l_boolean_mask_begin_ptr + max_length_p;

	while (l_boolean_mask_begin_ptr != l_boolean_mask_end_ptrc && *l_boolean_mask_begin_ptr == static_cast<bool_type>(1))
	{
		++l_boolean_mask_begin_ptr;
	}

	return l_boolean_mask_begin_ptr - boolean_mask_ptrc_p;
}

template <typename T>
_FORCE_INLINE_ void construct(T* const object_ptrc_p, const OBJECT_LIFECYCLE bool_mask_p) noexcept
{
	ABORT_IF(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	ABORT_IF(bool_mask_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T();
}

template <typename T>
_FORCE_INLINE_ void copy_construct(T* const object_ptrc_p, const OBJECT_LIFECYCLE bool_mask_p, T& other_ref_p) noexcept
{
	ABORT_IF(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	ABORT_IF(bool_mask_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T(other_ref_p);
}

template <typename T>
_FORCE_INLINE_ void move_construct(T* const object_ptrc_p, const OBJECT_LIFECYCLE bool_mask_p, T&& rvalue_p) noexcept
{
	ABORT_IF(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	ABORT_IF(bool_mask_p == OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: Unable to double-construct the object, that object_ptrc_p is pointing to");

	new(object_ptrc_p) T(std::move(rvalue_p));
}

template <typename T>
_FORCE_INLINE_ void destruct(T* const object_ptrc_p, const OBJECT_LIFECYCLE bool_mask_p) noexcept
{
	ABORT_IF(object_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	ABORT_IF(bool_mask_p == OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: Unable to double-destruct the object, that object_ptrc_p is pointing to");

	object_ptrc_p->~T();
}

template<class iterator>
_FORCE_INLINE_ void destruct(iterator begin_p, iterator end_p, OBJECT_LIFECYCLE* const boolean_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(FE::is_trivially_constructible_and_destructible<T>() == false, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	ABORT_IF(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");

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
	ABORT_IF(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	ABORT_IF(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

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
	ABORT_IF(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	ABORT_IF(data_source_begin_ptrc_p == nullptr, "ERROR: data_source_begin_ptrc_p is nullptr.");

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
	ABORT_IF(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	ABORT_IF(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	ABORT_IF(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

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
	ABORT_IF(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	ABORT_IF(source_data_begin_ptrc_p == nullptr, "ERROR: source_data_begin_ptrc_p is nullptr.");
	ABORT_IF(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");

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