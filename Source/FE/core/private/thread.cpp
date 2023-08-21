// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/thread.hpp>
#include <FE/core/algorithm/utility.hxx>
#include <FE/core/function.hxx>


#ifdef _WINDOWS_64BIT_OS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

#elif defined(_LINUX_64BIT_OS_)
#include <pthread.h>
#endif


thread_local FE::var::uint64 FE::thread::tl_s_this_thread_instance_id = 0;


FE::thread::thread(thread& other_ref_p) noexcept : m_thread(::std::move(other_ref_p.m_thread)) {}
FE::thread::thread(thread&& move_p) noexcept : m_thread(::std::move(move_p.m_thread)) {}

FE::thread& FE::thread::operator=(thread& other_ref_p) noexcept
{
	this->m_thread = ::std::move(other_ref_p.m_thread);
	return *this;
}

FE::thread& FE::thread::operator=(thread&& move_p) noexcept
{
	this->m_thread = ::std::move(move_p.m_thread);
	return *this;
};

void FE::thread::fork(FE::task_base* const function_ptrc_p, void* out_return_buffer_ptr_p) noexcept
{
	FE_ASSERT(function_ptrc_p == nullptr, "ERROR: function_ptrc_p is nullptr.");

	this->m_thread = ::std::thread
	(
		[&, function_ptrc_p]()
		{
			tl_s_this_thread_instance_id = __generate_instance_id();
			function_ptrc_p->operator()(out_return_buffer_ptr_p);
		}
	);
}


void FE::thread::swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept
{
	::std::swap(left_thread_ref_p.m_thread, right_thread_ref_p.m_thread);
	::FE::algorithm::utility::swap(left_thread_ref_p.tl_s_this_thread_instance_id, right_thread_ref_p.tl_s_this_thread_instance_id);
}

FE::uint64 FE::thread::calculate_suitable_thread_count() noexcept
{
	if ( ((::std::thread::hardware_concurrency() >> 1) + (::std::thread::hardware_concurrency() / 8)) < minimum_suitable_thread_count)
	{
		return minimum_suitable_thread_count;
	}

	return static_cast<var::uint64>(::std::thread::hardware_concurrency() >> 1) + static_cast<var::uint64>(::std::thread::hardware_concurrency() / 8);
}

FE::uint64 FE::thread::this_thread_id() noexcept
{
#ifdef _WINDOWS_64BIT_OS_
	return GetCurrentThreadId();
#elif defined(_LINUX_64BIT_OS_)
	return (FE::var::uint64)pthread_self();
#endif
}

FE::uint64 FE::thread::__generate_instance_id() noexcept
{
	static var::uint64 l_s_id = 0;
	return ++l_s_id;
}