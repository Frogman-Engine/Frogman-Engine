#ifndef _FE_FRAMEWORK_HPP_
#define _FE_FRAMEWORK_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>




int main(int argc_p, char** argv_p) noexcept;




BEGIN_NAMESPACE(FE::framework)


using discard_t = bool;

struct initialization_arguments
{
	using initial_function_table_size_t = var::size_t;

	initial_function_table_size_t _initial_function_table_size;
	class application* _application_ptr;
};


class application
{
	friend int ::main(int argc_p, char** argv_p) noexcept;
	static initialization_arguments s_options;

protected:
	virtual void set_up() noexcept = 0;
	virtual int run(int argc_p, char** argv_p) noexcept = 0;
	virtual void clean_up() noexcept = 0;

public:
	static discard_t set_application(initialization_arguments initialization_arguments_p) noexcept;

private:
	static initialization_arguments get_application() noexcept;

private:
	static void __launch_main(initialization_arguments& initialization_arguments_p) noexcept;
	static void __shutdown_main() noexcept;
	_NORETURN_ static void __abnormal_shutdown_with_exit_code(int32 signal_p) noexcept;
};


END_NAMESPACE
#endif