#ifndef _FE_CORE_MEMORY_BLOCK_HXX_
#define _FE_CORE_MEMORY_BLOCK_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/memory.hxx>


BEGIN_NAMESPACE(FE)


#pragma pack(push, _DWORD_SIZE_)
template<typename T, class Alignment = FE::align_8bytes>
class alignas(Alignment::size) memory_block final
{
private:
	var::boolean m_is_block_constructed;
	var::byte m_memory[sizeof(T)];
	T* const m_memory_pointer;

public:
	typedef T value_type;
	typedef Alignment alignment_type;
	
	_FORCE_INLINE_ memory_block() noexcept : m_is_block_constructed(), m_memory(), m_memory_pointer(reinterpret_cast<T*>(m_memory)) {}

	_FORCE_INLINE_ ~memory_block()
	{
		if (this->m_is_block_constructed == true)
		{
			this->m_memory_pointer->~T();
		}
	}

	_FORCE_INLINE_ memory_block(const memory_block& other_p) noexcept : m_is_block_constructed(other_p.m_is_block_constructed), m_memory(), m_memory_pointer(reinterpret_cast<T*>(m_memory))
	{
		if (other_p.m_is_block_constructed == true)
		{
			new(this->m_memory_pointer) T();
			*this->m_memory_pointer = *other_p.m_memory_pointer;
		}
	}

	_FORCE_INLINE_ memory_block(memory_block&& rvalue_p) noexcept : m_is_block_constructed(rvalue_p.m_is_block_constructed), m_memory(), m_memory_pointer(reinterpret_cast<T*>(m_memory))
	{
		if (rvalue_p.m_is_block_constructed == false)
		{
			return;
		}

		new(this->m_memory_pointer) T();
		*this->m_memory_pointer = std::move(*rvalue_p.m_memory_pointer);
	}

	_FORCE_INLINE_ memory_block& operator=(const memory_block& other_p) noexcept
	{
		if (other_p.m_is_block_constructed == false)
		{
			return *this;
		}

		if (this->m_is_block_constructed == false)
		{
			new(this->m_memory_pointer) T();
			this->m_is_block_constructed = true;
		}

		*this->m_memory_pointer = *other_p.m_memory_pointer;

		return *this;
	}

	_FORCE_INLINE_ memory_block& operator=(memory_block&& rvalue_p) noexcept
	{
		if (rvalue_p.m_is_block_constructed == false)
		{
			return *this;
		}

		if (this->m_is_block_constructed == false)
		{
			new(this->m_memory_pointer) T();
			this->m_is_block_constructed = true;
		}

		*this->m_memory_pointer = std::move(*rvalue_p.m_memory_pointer);

		return *this;
	}

	_FORCE_INLINE_ T& operator*() noexcept
	{
		FE_ASSERT(this->m_is_block_constructed == false, "ERROR: Attempted to dereference an uninitialized memory block.");

		return *this->m_memory_pointer;
	}

	_FORCE_INLINE_ T* operator->() noexcept
	{
		FE_ASSERT(this->m_is_block_constructed == false, "ERROR: Attempted to access an uninitialized memory block.");

		return this->m_memory_pointer;
	}

	_FORCE_INLINE_ var::boolean is_constructed() noexcept { return this->m_is_block_constructed; }

	_FORCE_INLINE_ var::boolean call_constructor() noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(this->m_memory_pointer) T();
		}
		return this->m_is_block_constructed;
	}

	_FORCE_INLINE_ var::boolean call_copy_constructor(T& other_p) noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(this->m_memory_pointer) T(other_p);
		}
		return this->m_is_block_constructed;
	}

	_FORCE_INLINE_ var::boolean call_move_constructor(T&& rvalue_p) noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(this->m_memory_pointer) T(std::move(rvalue_p));
		}
		return this->m_is_block_constructed;
	}

	template<typename ... Arguments>
	_FORCE_INLINE_ var::boolean call_constructor(Arguments&& ...arguments_p) noexcept
	{
		if (this->m_is_block_constructed == false)
		{
			this->m_is_block_constructed = true;
			new(this->m_memory_pointer) T(arguments_p...);
		}
		return this->m_is_block_constructed;
	}

	_FORCE_INLINE_ var::boolean call_destructor() noexcept
	{
		if (this->m_is_block_constructed == true)
		{
			this->m_is_block_constructed = false;
			this->m_memory_pointer->~T();
		}
		return this->m_is_block_constructed;
	}

};

#pragma pack(pop, _DWORD_SIZE_)

END_NAMESPACE
#endif
