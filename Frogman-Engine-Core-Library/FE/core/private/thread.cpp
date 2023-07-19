// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/thread.hpp>
#include <FE/core/algorithm/utility.hxx>


thread_local ::FE::var::uint64 FE::thread::tl_s_this_thread_id = 0;


::FE::thread::thread(thread& other_ref_p) noexcept : m_thread(::std::move(other_ref_p.m_thread)) {}
::FE::thread::thread(thread&& move_p) noexcept : m_thread(::std::move(move_p.m_thread)) {}

::FE::thread& FE::thread::operator=(thread& other_ref_p) noexcept
{
	this->m_thread = ::std::move(other_ref_p.m_thread);
	return *this;
}

::FE::thread& FE::thread::operator=(thread&& move_p) noexcept
{
	this->m_thread = ::std::move(move_p.m_thread);
	return *this;
};

::FE::var::boolean FE::thread::is_this_thread_active() noexcept
{
	return this->m_thread.joinable();
}

void FE::thread::fork(FE::task_base* const function_ptrc_p) noexcept
{
	FE_ASSERT(function_ptrc_p == nullptr, "ERROR: function_ptrc_p is nullptr.");
	this->m_thread = ::std::thread
	(
		[&, function_ptrc_p]()
		{
			tl_s_this_thread_id = __generate_id();

			ENABLE_IF_EXCEPTION_LOGGER_ENABLED(::FE::exception::__construct_exception());
			_DISCARD_ auto l_ignore_nodiscard_ = function_ptrc_p->execute();
			ENABLE_IF_EXCEPTION_LOGGER_ENABLED(::FE::exception::__destruct_exception());
		}
	);
}

void FE::thread::fork(FE::task_base* const function_ptrc_p, void* const out_return_ptrc_p, const char* const typename_str_ptrc_p) noexcept
{
	FE_ASSERT(function_ptrc_p == nullptr, "ERROR: function_ptrc_p is nullptr.");
	FE_ASSERT(out_return_ptrc_p == nullptr, "ERROR: out_return_ptrc_p is nullptr.");
	FE_ASSERT(typename_str_ptrc_p == nullptr, "ERROR: typename_str_ptrc_p is nullptr.");

	this->m_thread = ::std::thread
	(
		[&, function_ptrc_p, out_return_ptrc_p, typename_str_ptrc_p]()
		{
			tl_s_this_thread_id = __generate_id();

			ENABLE_IF_EXCEPTION_LOGGER_ENABLED(::FE::exception::__construct_exception());
			_DISCARD_ auto l_is_void = function_ptrc_p->execute(out_return_ptrc_p, typename_str_ptrc_p);
			ENABLE_IF_EXCEPTION_LOGGER_ENABLED(::FE::exception::__destruct_exception());

			FE_ASSERT(l_is_void == FE::RETURN_TYPE::_VOID && out_return_ptrc_p != nullptr, "ERROR: a non-void function assigned to a void-return-type task object.");
		}
	);
}

void FE::thread::join() noexcept
{
	this->m_thread.join();
}

void FE::thread::swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept
{
	::std::swap(left_thread_ref_p.m_thread, right_thread_ref_p.m_thread);
	::FE::algorithm::utility::swap(left_thread_ref_p.tl_s_this_thread_id, right_thread_ref_p.tl_s_this_thread_id);
}

::FE::var::uint64 FE::thread::calculate_suitable_thread_count() noexcept
{
	if ( ((::std::thread::hardware_concurrency() >> 1) + (::std::thread::hardware_concurrency() / 8)) < _MINIMUM_SUITABLE_THREAD_COUNT_)
	{
		return _MINIMUM_SUITABLE_THREAD_COUNT_;
	}

	return static_cast<var::uint64>(::std::thread::hardware_concurrency() >> 1) + static_cast<var::uint64>(::std::thread::hardware_concurrency() / 8);
}

::FE::var::uint64 FE::thread::__generate_id() noexcept
{
	static var::uint64 l_s_id = 0;

	return ++l_s_id;
}