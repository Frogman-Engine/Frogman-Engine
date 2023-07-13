#ifndef _FE_CORE_CONCURRENT_MEMORY_BLOCK_HXX_
#define _FE_CORE_CONCURRENT_MEMORY_BLOCK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "private/memory.hpp"
#include "movable_scoped_ref.hxx"


BEGIN_NAMESPACE(FE)


#pragma pack(push, _DWORD_SIZE_)
// construction and destruction operations are lock-free and thread-safe but the instance may not be safe from data race condition.
template<typename T, class padding_size = FE::align_null>
class alignas(padding_size::s_size) concurrent_memory_block final
{
private:
	internal::IN_USE m_is_being_used;
	::std::atomic_bool m_is_block_constructed;
	T m_object;

	thread_local static T tl_s_null_object;

public: 
	typedef T value_type;
	typedef padding_size alignment_type;


	constexpr concurrent_memory_block() noexcept : m_is_being_used(false), m_is_block_constructed(true) {}


	_NODISCARD_ _FORCE_INLINE_ movable_scoped_ref<T> operator*() noexcept
	{
		FE_ASSERT(this->m_is_block_constructed.load(::std::memory_order_acquire) == false, "ERROR: Attempted to dereference an uninitialized memory block.");

		return ::std::move(movable_scoped_ref(&this->m_object, &this->m_is_being_used, true));
	}

	_NODISCARD_ _FORCE_INLINE_ movable_scoped_ref<T> try_access() noexcept
	{
		if (FE_LOG(this->m_is_block_constructed.load(::std::memory_order_acquire) == false, "WARNING: failed to access the memory block because the block is not constructed. The function will return early with a null object.")) _UNLIKELY_
		{
			return movable_scoped_ref(&concurrent_memory_block<T, padding_size>::tl_s_null_object, nullptr, false);
		}

		return ::std::move(movable_scoped_ref(&this->m_object, &this->m_is_being_used, true));
	}

public:
	_FORCE_INLINE_ boolean is_constructed() noexcept { return this->m_is_block_constructed.load(::std::memory_order_relaxed); }

	// it forces m_object to be constructed
	_FORCE_INLINE_ boolean call_constructor() noexcept
	{
		boolean l_is_constructed = this->m_is_block_constructed.exchange(true, ::std::memory_order_acq_rel);
		if (l_is_constructed == false)
		{
			new(&(this->m_object)) T();
		}
		return !l_is_constructed;
	}

	// it forces construction of m_object
	template<typename ... arguments>
	_FORCE_INLINE_ boolean call_constructor(arguments&& ...arguments_p) noexcept
	{
		boolean l_is_constructed = this->m_is_block_constructed.exchange(true, ::std::memory_order_acq_rel);
		if (l_is_constructed == false)
		{
			new(&(this->m_object)) T(arguments_p...);
		}
		return !l_is_constructed;
	}

	// it forces destruction of m_object without memory deletion
	_FORCE_INLINE_ boolean call_destructor() noexcept
	{
		boolean l_is_constructed = this->m_is_block_constructed.exchange(false, ::std::memory_order_acq_rel);
		if (l_is_constructed == true && this->m_is_being_used == false)
		{
			this->m_object.~T();
			return _SUCCESSFUL_;
		}
		
		this->m_is_block_constructed.store(true, ::std::memory_order_release);
		return _FAILED_;
	}

	_FORCE_INLINE_ var::boolean is_being_used() noexcept { return this->m_is_being_used.load(::std::memory_order_acquire); }

};

template<typename T, class padding_size>
thread_local T concurrent_memory_block<T, padding_size>::tl_s_null_object;

#pragma pack(pop, _DWORD_SIZE_)

END_NAMESPACE
#endif
