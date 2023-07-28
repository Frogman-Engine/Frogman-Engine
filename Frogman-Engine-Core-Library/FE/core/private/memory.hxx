#ifndef _FE_CORE_PRIVATE_MEMORY_HXX_
#define _FE_CORE_PRIVATE_MEMORY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>




BEGIN_NAMESPACE(FE)


template<class iterator>
var::boolean memcmp_s(iterator left_iterator_begin_p, iterator left_iterator_end_p, iterator right_iterator_begin_p, iterator right_iterator_end_p) noexcept
{
	static_assert(std::is_class<iterator>::value == true);
	FE_ASSERT(left_iterator_begin_p == nullptr, "ERROR: left_iterator_begin_p is nullptr.");
	FE_ASSERT(left_iterator_end_p == nullptr, "ERROR: left_iterator_end_p is nullptr.");
	FE_ASSERT(right_iterator_begin_p == nullptr, "ERROR: right_iterator_begin_p is nullptr.");
	FE_ASSERT(right_iterator_end_p == nullptr, "ERROR: right_iterator_end_p is nullptr.");

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




template <class T, typename ... arguments>
_FORCE_INLINE_ void assign(T& dest_object_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p, arguments&& ...arguments_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	if (dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(&dest_object_ref_p) T(arguments_p...);
        dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	dest_object_ref_p = ::std::move(arguments_p...);
}

template <class T>
_FORCE_INLINE_ void copy_assign(T& dest_object_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p, const T& source_cref_p, _MAYBE_UNUSED_ OBJECT_LIFECYCLE source_bool_mask_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(source_bool_mask_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: cannot copy a null object");

	if (dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(&dest_object_ref_p) T(source_cref_p);
		dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	dest_object_ref_p = source_cref_p;
}

template <class T>
_FORCE_INLINE_ void move_assign(T& dest_object_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p, T&& source_rvalue_reference_p, _MAYBE_UNUSED_ OBJECT_LIFECYCLE source_bool_mask_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(source_bool_mask_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: cannot copy a null object");

	if (dest_bool_mask_ref_p == OBJECT_LIFECYCLE::_DESTRUCTED)
	{
		new(&dest_object_ref_p) T(std::move(source_rvalue_reference_p));
		dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
		return;
	}

	dest_object_ref_p = std::move(source_rvalue_reference_p);
}




template <class T>
_FORCE_INLINE_ void construct(T& dest_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: unable to double-construct.");

	new(&dest_ref_p) T();
	dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
}

template <class T>
_FORCE_INLINE_ void copy_construct(T& dest_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p, const T& source_cref_p, _MAYBE_UNUSED_ OBJECT_LIFECYCLE source_bool_mask_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: unable to double-construct.");
	FE_ASSERT(source_bool_mask_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: unable to copy null object.");

	new(&dest_ref_p) T(source_cref_p);
	dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
}

template <class T>
_FORCE_INLINE_ void move_construct(T& dest_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p, T&& source_rvalue_reference_p, _MAYBE_UNUSED_ OBJECT_LIFECYCLE source_bool_mask_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_CONSTRUCTED, "ERROR: unable to double-construct.");
	FE_ASSERT(source_bool_mask_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: unable to copy null object.");

	new(&dest_ref_p) T(source_rvalue_reference_p);
	dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
}




template <typename iterator, typename ... arguments>
_FORCE_INLINE_ void assign(iterator begin_p, iterator end_p, OBJECT_LIFECYCLE* const boolean_mask_ptrc_p, arguments && ...arguments_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(begin_p == nullptr, "ERROR: begin_p is nullptr.");
	FE_ASSERT(end_p == nullptr, "ERROR: end_p is nullptr.");

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
			*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
			++l_boolean_mask_ptr;
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator data_source_begin_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_copy_assignable<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_p == nullptr, "ERROR: data_source_begin_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	iterator l_initializer_list_begin = data_source_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
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
				*l_dest_iterator_begin = *l_initializer_list_begin;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator data_source_begin_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_move_assignable<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_p == nullptr, "ERROR: data_source_begin_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	iterator l_initializer_list_begin = data_source_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin);

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
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
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin);

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
			else
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator source_data_begin_p, capacity_t source_data_length_p, const OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_copy_assignable<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_p == nullptr, "ERROR: source_data_begin_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	const OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	iterator l_initializer_list_begin = source_data_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = *l_initializer_list_begin;

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if (*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_initializer_list_begin;
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
				*l_dest_iterator_begin = *l_initializer_list_begin;

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if (*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_assign(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator source_data_begin_p, capacity_t source_data_length_p, OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_move_assignable<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_p == nullptr, "ERROR: source_data_begin_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	iterator l_initializer_list_begin = source_data_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin);

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if(*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_initializer_list_begin;
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
				*l_dest_iterator_begin = std::move(*l_initializer_list_begin);

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
			else if(*l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}




template <class T>
_FORCE_INLINE_ void destruct(T& dest_ref_p, OBJECT_LIFECYCLE& dest_bool_mask_ref_p) noexcept
{
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ref_p == FE::OBJECT_LIFECYCLE::_DESTRUCTED, "ERROR: unable to destruct.");

	dest_ref_p.~T();
	dest_bool_mask_ref_p = FE::OBJECT_LIFECYCLE::_DESTRUCTED;
}

template<class iterator>
_FORCE_INLINE_ void destruct(iterator begin_p, iterator end_p, OBJECT_LIFECYCLE* const boolean_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_destructible<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(boolean_mask_ptrc_p == nullptr, "ERROR: boolean_mask_ptrc_p is nullptr.");
	FE_ASSERT(begin_p == nullptr, "ERROR: begin_p is nullptr.");
	FE_ASSERT(end_p == nullptr, "ERROR: end_p is nullptr.");

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
_FORCE_INLINE_ void copy_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator data_source_begin_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_copy_constructible<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_p == nullptr, "ERROR: data_source_begin_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	iterator l_initializer_list_begin = data_source_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
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
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator data_source_begin_p, capacity_t source_data_length_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_move_constructible<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(data_source_begin_p == nullptr, "ERROR: data_source_begin_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_boolean_mask_ptr = dest_bool_mask_ptrc_p;
	iterator l_initializer_list_begin = data_source_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_boolean_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
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
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_boolean_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_boolean_mask_ptr;
				++l_initializer_list_begin;
				++l_dest_iterator_begin;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void copy_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator source_data_begin_p, capacity_t source_data_length_p, const OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_copy_constructible<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_p == nullptr, "ERROR: source_data_begin_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	const OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	iterator l_initializer_list_begin = source_data_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin;
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
				new(l_dest_iterator_begin.operator->()) T(*l_initializer_list_begin);
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}

template<class iterator>
_FORCE_INLINE_ void move_construct(iterator dest_begin_p, capacity_t dest_length_p, OBJECT_LIFECYCLE* const dest_bool_mask_ptrc_p, iterator source_data_begin_p, capacity_t source_data_length_p, OBJECT_LIFECYCLE* const source_data_bool_mask_ptrc_p) noexcept
{
	using T = typename iterator::value_type;
	static_assert(std::is_class<iterator>::value == true);
	static_assert(std::is_move_constructible<T>::value == true);
	static_assert(FE::is_trivially_constructible_and_destructible<T>::_VALUE_ == FE::OBJECT_TRIVIALITY::_NOT_TRIVIAL, "WARNING: T must not be trivially constructible and destructible. This function call has no effect and is a waste of computing resource");
	FE_ASSERT(dest_bool_mask_ptrc_p == nullptr, "ERROR: dest_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(source_data_begin_p == nullptr, "ERROR: source_data_begin_p is nullptr.");
	FE_ASSERT(source_data_bool_mask_ptrc_p == nullptr, "ERROR: source_data_bool_mask_ptrc_p is nullptr.");
	FE_ASSERT(dest_begin_p == nullptr, "ERROR: dest_begin_p is nullptr.");

	OBJECT_LIFECYCLE* l_dest_bool_mask_ptr = dest_bool_mask_ptrc_p;
	OBJECT_LIFECYCLE* l_source_bool_mask_ptr = source_data_bool_mask_ptrc_p;

	iterator l_initializer_list_begin = source_data_begin_p;
	iterator l_dest_iterator_begin = dest_begin_p;

	if (source_data_length_p >= dest_length_p)
	{
		for (var::index_t i = 0; i < dest_length_p; ++i)
		{
			if (*l_dest_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_DESTRUCTED && *l_source_bool_mask_ptr == FE::OBJECT_LIFECYCLE::_CONSTRUCTED)
			{
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin;
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
				new(l_dest_iterator_begin.operator->()) T(std::move(*l_initializer_list_begin));
				*l_dest_bool_mask_ptr = FE::OBJECT_LIFECYCLE::_CONSTRUCTED;

				++l_initializer_list_begin;
				++l_dest_iterator_begin;

				++l_dest_bool_mask_ptr;
				++l_source_bool_mask_ptr;
			}
		}
	}
}




END_NAMESPACE

#endif
