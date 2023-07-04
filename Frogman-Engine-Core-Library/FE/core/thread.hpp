#ifndef _FE_CORE_THREAD_HPP_
#define _FE_CORE_THREAD_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include "prerequisite_symbols.h"
#include "function.hxx"
#include <thread>


#define PASS_ARGUMENT_OBJECT(argument_object_p) &argument_object_p, typeid(argument_object_p).name()


BEGIN_NAMESPACE(FE)


class thread final
{
private:
	::std::thread m_thread;

public:
	thread_local static var::uint64 tl_s_this_thread_id;

	typedef ::std::thread thread_type;
	typedef var::uint64 id_type;

	_MAYBE_UNUSED_ static constexpr var::uint16 _MINIMUM_SUITABLE_THREAD_COUNT_ = 6;


	thread() noexcept = default;

	~thread() noexcept = default;


	thread(thread& other_ref_p) noexcept;


	thread(thread&& move_p) noexcept;


	thread& operator=(thread& other_ref_p) noexcept;


	thread& operator=(thread&& move_p) noexcept;


	var::boolean is_this_thread_active() noexcept;
	

	void fork(FE::task_base* const function_ptrc_p) noexcept;

	void fork(FE::task_base* const function_ptrc_p, void* const out_return_ptrc_p, const char* const typename_str_ptrc_p) noexcept;


	void join() noexcept;

	static void swap(thread& left_thread_ref_p, thread right_thread_ref_p) noexcept;

	static var::uint64 calculate_suitable_thread_count() noexcept;

private:
	static var::uint64 __generate_id() noexcept;
};


END_NAMESPACE
#endif