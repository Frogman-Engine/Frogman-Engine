#ifndef _FE_CORE_THREAD_HPP_
#define _FE_CORE_THREAD_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <thread>




BEGIN_NAMESPACE(FE)


struct task_base;


class thread final
{
private:
	::std::thread m_thread;

public:
	thread_local static var::uint64 tl_s_this_thread_instance_id;

	typedef ::std::thread thread_type;
	typedef var::uint64 id_type;

	_MAYBE_UNUSED_ static constexpr var::uint16 minimum_suitable_thread_count = 6;
	_MAYBE_UNUSED_ static constexpr var::uint16 max_thread_id_digit_length = 24;

	thread() noexcept = default;

	~thread() noexcept = default;


	thread(thread& other_ref_p) noexcept;


	thread(thread&& move_p) noexcept;


	thread& operator=(thread& other_ref_p) noexcept;


	thread& operator=(thread&& move_p) noexcept;


	var::boolean is_this_thread_active() noexcept;
	
	void fork(FE::task_base* const function_ptrc_p, void* out_return_buffer_ptr_p = nullptr) noexcept;

	void join() noexcept;

	static void swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept;

	static var::uint64 calculate_suitable_thread_count() noexcept;

	static var::uint64 this_thread_id() noexcept;

private:
	static var::uint64 __generate_instance_id() noexcept;
};


END_NAMESPACE
#endif