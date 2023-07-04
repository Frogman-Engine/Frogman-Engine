#include <gtest/gtest.h>
#include <FE/miscellaneous/google_test_extension.h>
#include <FE/core/concurrent_memory_block.hxx>
#include <FE/core/thread.hpp>
#include <future>


struct my_struct
{
	bool _has_constructor_been_called;
	bool _has_copy_constructor_been_called;
	bool _has_move_constructor_been_called;
	bool _has_destructor_been_called;
	int _field = 0;

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
	FE::concurrent_memory_block<my_struct>* l_concurrent_memory_block_ptr = (FE::concurrent_memory_block<my_struct>*)calloc(1, sizeof(FE::concurrent_memory_block<my_struct>));

	{
		l_concurrent_memory_block_ptr->call_constructor();
		EXPECT_EQ((***l_concurrent_memory_block_ptr)._has_constructor_been_called, true);


		FE::movable_scoped_ref<my_struct> l_movable_scoped_ref = **l_concurrent_memory_block_ptr; // Critical Section. threads can not call the destructor from this point
		
		EXPECT_EQ(l_movable_scoped_ref.is_being_used(), true);

		(*l_movable_scoped_ref)._field = 5; // Critical Section.

		if (l_concurrent_memory_block_ptr->call_destructor() == FE::_FAILED_) // It always fail to invoke the destructor.
		{
			EXPECT_EQ((***l_concurrent_memory_block_ptr)._has_destructor_been_called, false);
		}

	} // The reference gets invalidated when it reaches a scope.

	l_concurrent_memory_block_ptr->call_destructor();

	EXPECT_EQ(l_concurrent_memory_block_ptr->is_constructed(), false); // destructed with no errors.
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
	FE::concurrent_memory_block<my_struct>* l_concurrent_memory_block_ptr = (FE::concurrent_memory_block<my_struct>*)calloc(1, sizeof(FE::concurrent_memory_block<my_struct>));
	l_concurrent_memory_block_ptr->call_constructor();

	std::promise<bool> l_promise;
	std::future<bool> l_future = l_promise.get_future();

	FE::two_args< std::promise<bool>&, FE::concurrent_memory_block<my_struct>&> l_two_args {l_promise, *l_concurrent_memory_block_ptr};
	FE::void_function_with_2_args<std::promise<bool>&, FE::concurrent_memory_block<my_struct>&> l_function_with_2_args(fn, std::move(l_two_args));

	FE::thread l_worker;
	l_worker.fork(&l_function_with_2_args);

	EXPECT_TRUE(l_future.get());
	
	while (l_concurrent_memory_block_ptr->call_destructor() == false) {} // The destructor is attempting to be called, but it must wait for the completion of local worker's task.

	EXPECT_EQ(l_concurrent_memory_block_ptr->is_constructed(), false);

	l_worker.join();
}