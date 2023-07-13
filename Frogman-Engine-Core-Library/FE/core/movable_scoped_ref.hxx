#ifndef _FE_CORE_MOVABLE_SCOPED_REF_HXX_
#define _FE_CORE_MOVABLE_SCOPED_REF_HXX_
#pragma warning(disable:4390)
#include "prerequisite_symbols.h"
#include "exception.hpp"


BEGIN_NAMESPACE(FE)


namespace internal
{
	using IN_USE = ::std::atomic_bool;
}


template <typename T>
class movable_scoped_ref
{
	T* m_data_ptr;
	internal::IN_USE* m_signal_ptr;

public:
	using value_type = T;
	using flag_type = internal::IN_USE*;


	constexpr movable_scoped_ref() noexcept : m_data_ptr() {};
	movable_scoped_ref(T* const data_ptrc_p, internal::IN_USE* const signal_ptr_p, bool value_for_is_being_used_p) noexcept : m_data_ptr(data_ptrc_p)
	{
		signal_ptr_p->store(value_for_is_being_used_p, std::memory_order_release);
		this->m_signal_ptr = signal_ptr_p;
	}


	~movable_scoped_ref() noexcept
	{
		if (this->m_signal_ptr == nullptr) { return; }

		this->m_signal_ptr->store(false, std::memory_order_release);
	}


	movable_scoped_ref(const movable_scoped_ref& other_cref_p) noexcept = delete;


	movable_scoped_ref(movable_scoped_ref&& rvalue_p) noexcept : m_data_ptr(rvalue_p.m_data_ptr), m_signal_ptr(rvalue_p.m_signal_ptr)
	{
		rvalue_p.m_signal_ptr = nullptr;
		rvalue_p.m_data_ptr = nullptr;
	}


	movable_scoped_ref& operator=(const movable_scoped_ref& other_cref_p) noexcept = delete;


	movable_scoped_ref& operator=(movable_scoped_ref&& rvalue_p) noexcept
	{
		this->m_signal_ptr = rvalue_p.m_signal_ptr;
		rvalue_p.m_signal_ptr = nullptr;
		this->m_data_ptr = rvalue_p.m_data_ptr;
		rvalue_p.m_data_ptr = nullptr;
		return *this;
	}


	var::boolean is_being_used() noexcept
	{
		return (this->m_signal_ptr == nullptr) ? _FAILED_ : this->m_signal_ptr->load(std::memory_order_relaxed);
	}

	var::boolean stop_using() noexcept
	{
		if (FE_LOG(this->m_signal_ptr == nullptr, "WARNING: The signal pointer is nullptr. This function will return early with false.")) _LIKELY_ { return _FAILED_; }

		this->m_signal_ptr->store(false, std::memory_order_release);
		return _SUCCESSFUL_;
	}

	T& operator*() noexcept
	{
		FE_ASSERT(this->m_signal_ptr == nullptr, "ERROR: The signal pointer is nullptr. Failed to acquire the data.");
		return *this->m_data_ptr;
	}
};


END_NAMESPACE

#endif // !_FE_CORE_SIGNAL_HXX_
