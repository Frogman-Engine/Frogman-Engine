#ifndef _FE_CORE_MEMORY_BLOCK_HXX_
#define _FE_CORE_MEMORY_BLOCK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "private/memory.hpp"
#include "exception.hpp"


BEGIN_NAMESPACE(FE)


#pragma pack(push, _DWORD_SIZE_)
template<typename T, class padding_size = FE::internal::align_null>
class alignas(padding_size::s_size) memory_block final
{
private:
	var::boolean m_is_block_constructed;
	T m_object;

	thread_local static T tl_s_null_object;


public:
	typedef T value_type;
	typedef padding_size alignment_type;
	

	constexpr memory_block() noexcept : m_is_block_constructed(true) {}


	T& operator*() noexcept
	{
		FE_ASSERT(this->m_is_block_constructed == false, "ERROR: Attempted to dereference an uninitialized memory block.", _ASSERTED_LOCATION_);

		return this->m_object;
	}

	T& try_dereference() noexcept
	{
		if (FE_EXCEPTION(this->m_is_block_constructed == false, "WARNING: failed to dereference the memory block because the block is not constructed. The function will return early with a null object.", _EXCEPTION_ORIGIN_)) _UNLIKELY_
		{
			return memory_block<T, padding_size>::tl_s_null_object;
		}

		return this->m_object;
	}

	T* operator->() noexcept
	{
		FE_ASSERT(this->m_is_block_constructed == false, "ERROR: Attempted to access an uninitialized memory block.", _ASSERTED_LOCATION_);

		return &this->m_object;
	}

	T* try_access() noexcept
	{
		if (FE_EXCEPTION(this->m_is_block_constructed == false, "WARNING: failed to access the memory block because the block is not constructed. The function will return early with a null object.", _EXCEPTION_ORIGIN_)) _UNLIKELY_
		{
			return &memory_block<T, padding_size>::tl_s_null_object;
		}

		return &this->m_object;
	}

	_FORCE_INLINE_ boolean is_constructed() noexcept { return this->m_is_block_constructed; }

	// it forces m_object to be constructed
	_FORCE_INLINE_ boolean call_constructor() noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(&(this->m_object)) T();
		}
		return this->m_is_block_constructed;
	}

	// it forces construction of m_object
	template<typename ... arguments>
	_FORCE_INLINE_ boolean call_constructor(arguments&& ...arguments_p) noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(&(this->m_object)) T(arguments_p...);
		}
		return this->m_is_block_constructed;
	}

	// it forces destruction of m_object without memory deletion
	_FORCE_INLINE_ boolean call_destructor() noexcept
	{
		if (this->m_is_block_constructed == true)
		{
			this->m_is_block_constructed = false;
			this->m_object.~T();
		}
		return this->m_is_block_constructed;
	}

};

template<typename T, class padding_size>
thread_local T memory_block<T, padding_size>::tl_s_null_object;

#pragma pack(pop, _DWORD_SIZE_)

END_NAMESPACE
#endif