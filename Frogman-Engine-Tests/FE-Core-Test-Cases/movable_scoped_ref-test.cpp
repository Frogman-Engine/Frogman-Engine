#include <gtest/gtest.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/thread.hpp>
#include <FE/core/function.hxx>
#include <future>
#pragma warning (disable: 26495)



struct my_struct
{
	bool _has_constructor_been_called;
	bool _has_copy_constructor_been_called;
	bool _has_move_constructor_been_called;
	bool _has_destructor_been_called;
	int _field_variable = 0;

	my_struct() noexcept
	{
		this->_has_constructor_been_called = true;
	}

	my_struct(_MAYBE_UNUSED_ const my_struct& my_struct_cref_p) noexcept
	{
		this->_has_copy_constructor_been_called = true;
	}

	my_struct(_MAYBE_UNUSED_ my_struct&& rvalue_p) noexcept
	{
		this->_has_move_constructor_been_called = true;
	}

	~my_struct() noexcept
	{
		this->_has_destructor_been_called = true;
	}
};




TEST(movable_scoped_ref, serial)
{
	FE::concurrent_memory_block<my_struct> l_concurrent_memory_block;

	{
		l_concurrent_memory_block.call_constructor();
		EXPECT_TRUE((**l_concurrent_memory_block)._has_constructor_been_called);

		FE::movable_scoped_ref<my_struct> l_movable_scoped_ref = *l_concurrent_memory_block; // Critical Section. Threads can not invoke call_destructor() of l_concurrent_memory_block from this point
		
		EXPECT_TRUE(l_movable_scoped_ref.is_being_used());

		(*l_movable_scoped_ref)._field_variable = 5; // Critical Section.

		if (l_concurrent_memory_block.call_destructor() == FE::_FAILED_) // It always fail to invoke the destructor, since l_concurrent_memory_block is being referenced by l_movable_scoped_ref.
		{
			EXPECT_FALSE((**l_concurrent_memory_block)._has_destructor_been_called);
		}

	} // The l_movable_scoped_ref gets invalidated when it reaches the end of its scope.

	l_concurrent_memory_block.call_destructor();

	EXPECT_EQ(l_concurrent_memory_block.is_constructed(), false); // destructed with no errors.
}




void fn(std::promise<bool>& promise_p, FE::concurrent_memory_block<my_struct>& concurrent_memory_block_p) noexcept
{
	FE::movable_scoped_ref<my_struct> l_movable_scoped_reference = *concurrent_memory_block_p;
	promise_p.set_value(true);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_EQ(l_movable_scoped_reference.is_being_used(), true);
}

TEST(movable_scoped_ref, parallel)
{
	FE::c_style_task<void(std::promise<bool>&, FE::concurrent_memory_block<my_struct>&), FE::FORWARD_DATA::_AS_LVALUE_REF, std::promise<bool>, FE::concurrent_memory_block<my_struct>> l_function;
	l_function._arguments_buffer._second.call_constructor();
	l_function._function = fn;
	std::future<bool> l_future = l_function._arguments_buffer._first.get_future();

	FE::thread l_worker;
	l_worker.fork(&l_function);

	EXPECT_TRUE(l_future.get());

	while (l_function._arguments_buffer._second.call_destructor() == false) {} // Busy waiting l_worker's job to be done 

	EXPECT_EQ(l_function._arguments_buffer._second.is_constructed(), false);

	l_worker.join();
}