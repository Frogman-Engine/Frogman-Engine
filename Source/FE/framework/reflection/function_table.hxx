#ifndef _FE_FRAMEWORK_FUNCTION_TABLE_HXX_
#define _FE_FRAMEWORK_FUNCTION_TABLE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/function.hxx>
#include <FE/core/fstring.hxx>
#include <FE/core/hash.hpp>
#include <FE/core/pool_allocator.hxx>
#include <memory>
#include <mutex>
#include <unordered_map>


#define _FUNCTION_TABLE_MEMORY_NAMESPACE_ "FnTable"




BEGIN_NAMESPACE(FE::framework)

using method_signature_t = FE::fstring<128>;


// function_table is currently under development. It might not be suitable to use
class function_table
{
public:		
	constexpr static size_t function_pool_size = 64 KB;

	template<typename T>
	using smart_function_ptr = FE::generic_pool_ptr<T, function_pool_size, FE::align_CPU_L1_cache_line>;

	using underlying_container = std::unordered_map<method_signature_t,
													FE::task_base*, 
													FE::hash<method_signature_t>,
													std::equal_to<method_signature_t>,
													FE::namespace_pool_allocator<std::pair<const method_signature_t, FE::task_base*>, FE::align_CPU_L1_cache_line>
													>;
private:
	FE::generic_pool<function_pool_size, FE::align_CPU_L1_cache_line> m_function_pool;
	underlying_container m_task_map;
	std::mutex m_mutex;
	
public:
	function_table() noexcept : m_function_pool(), m_task_map(typename underlying_container::allocator_type{ _FUNCTION_TABLE_MEMORY_NAMESPACE_ }), m_mutex() {}
	~function_table() noexcept = default;

	function_table(const function_table& other_cref_p) noexcept = delete;
	function_table(function_table&& rvalue_p) noexcept = delete;

	template<class TaskType, typename FunctionPtr>
	_FORCE_INLINE_ void register_task(const underlying_container::key_type& key_p, FunctionPtr function_p) noexcept
	{	
		FE_STATIC_ASSERT((std::is_base_of<FE::task_base, TaskType>::value == false), "An invalid function type detected.");
		{
			std::lock_guard<std::mutex> l_lock(m_mutex);
			smart_function_ptr<TaskType> l_unique_ptr = this->m_function_pool.allocate<TaskType>(_FUNCTION_TABLE_MEMORY_NAMESPACE_, 1);
			*(l_unique_ptr.get()) = function_p;
			FE::task_base* const l_task_ptr = l_unique_ptr.release();
			this->m_task_map.emplace(key_p, l_task_ptr);
		}
	}

	_FORCE_INLINE_ boolean check_presence(const underlying_container::key_type& key_p) noexcept { return this->m_task_map.find(key_p) != this->m_task_map.end(); }
	_FORCE_INLINE_ _NODISCARD_ FE::task_base* retrieve(const underlying_container::key_type& key_p) noexcept { return this->m_task_map.find(key_p)->second; }

	template<class Arguments = FE::arguments<void>>
	_FORCE_INLINE_ _NODISCARD_ FE::task_base* invoke_function(const underlying_container::key_type& key_p, Arguments arguments_p = FE::arguments<void>()) noexcept
	{
		FE::task_base* const l_task_ptr = this->m_task_map.find(key_p)->second;
		
		if constexpr (Arguments::count != ARGUMENTS_COUNT::_0)
		{
			l_task_ptr->set_arguments(&arguments_p, sizeof(Arguments));
		}

		l_task_ptr->operator()();
		return l_task_ptr;
	}

	template<class C, class Arguments = FE::arguments<void>>
	_FORCE_INLINE_ _NODISCARD_ FE::task_base* invoke_method(C& in_out_instance_p, const underlying_container::key_type& key_p, Arguments arguments_p = FE::arguments<void>()) noexcept
	{
		FE_STATIC_ASSERT((std::is_class<C>::value == false), "Static Assertion Failure: The template typename C is not a class type.");
		FE::task_base* const l_task_ptr = this->m_task_map.find(key_p)->second;

		if constexpr (Arguments::count != ARGUMENTS_COUNT::_0)
		{
			l_task_ptr->set_arguments(&arguments_p, sizeof(Arguments));
		}

		l_task_ptr->set_instance(&in_out_instance_p);
		l_task_ptr->operator()();
		return l_task_ptr;
	}

	_FORCE_INLINE_ void reserve(size_t size_p) noexcept { this->m_task_map.reserve(size_p); }
};


END_NAMESPACE
#endif
