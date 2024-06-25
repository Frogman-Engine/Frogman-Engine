﻿#ifndef _FE_FRAMEWORK_REFLECTION_FUNCTION_TABLE_HPP_
#define _FE_FRAMEWORK_REFLECTION_FUNCTION_TABLE_HPP_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/function.hxx>
#include <FE/core/hash.hpp>
#include <FE/core/memory_metrics.h>
#include <FE/core/string.hxx>

// std
#include <mutex>
#include <memory_resource>

// ronbin hood hash
#include <robin_hood.h>




BEGIN_NAMESPACE(FE::framework::reflection)


class function_table
{
public:		
	using underlying_container = robin_hood::unordered_map<FE::string, FE::task_base*, FE::hash<FE::string>>;
	using function_pool_type = std::pmr::monotonic_buffer_resource;
	using lock_type = std::mutex;
	using alignment_type = FE::align_CPU_L1_cache_line;

	static constexpr size initial_size_in_bytes = (64 KB);
	static constexpr size initial_capacity = initial_size_in_bytes / alignment_type::size;

private:
	static function_pool_type s_function_pool;
	static underlying_container* s_task_map;
	static lock_type s_lock;

public:
	function_table() noexcept = default;
	~function_table() noexcept = default;

	static boolean initialize() noexcept
	{
		FE_ASSERT(s_task_map != nullptr, "Assertion failure: cannot initialize FE::framework::reflection::function_table more than once.");
		if(s_task_map == nullptr)
		{
			s_task_map = (underlying_container*)ALIGNED_ALLOC(sizeof(underlying_container), FE::align_CPU_L1_cache_line::size);
			new(s_task_map) underlying_container(function_table::initial_capacity);
			return true;
		}

		return false;
	}
	
	static boolean clean_up() noexcept
	{
		FE_ASSERT(s_task_map == nullptr, "Assertion failure: unable to clean_up() FE::framework::reflection::function_table. It is null.");

		if(s_task_map != nullptr)
		{
			s_task_map->~underlying_container();
			ALIGNED_FREE(s_task_map);
			s_task_map = nullptr;
			return true;
		}

		return false;
	}

	template<class TaskType, typename FunctionPtr>
	_FORCE_INLINE_ static void register_task(const typename underlying_container::key_type& key_p, FunctionPtr function_p) noexcept
	{	
		FE_STATIC_ASSERT((std::is_base_of<FE::task_base, TaskType>::value == false), "An invalid function type detected.");
		{
			std::lock_guard<std::mutex> l_lock(s_lock);
			std::pmr::polymorphic_allocator< FE::aligned<FE::byte, FE::align_CPU_L1_cache_line> > l_allocator{&s_function_pool};

			TaskType* const l_task = reinterpret_cast<TaskType* const>(l_allocator.allocate(1));
			new(l_task) TaskType(std::move(function_p));
			s_task_map->emplace(key_p, l_task);
		}
	}

	_FORCE_INLINE_ static boolean check_presence(const typename underlying_container::key_type& key_p) noexcept 
	{
		std::lock_guard<std::mutex> l_lock(s_lock);
		return s_task_map->find(key_p) != s_task_map->end(); 
	}

	_NODISCARD_ _FORCE_INLINE_ static FE::task_base* retrieve(const typename underlying_container::key_type& key_p) noexcept 
	{
		std::lock_guard<std::mutex> l_lock(s_lock);
		auto l_result = s_task_map->find(key_p);
		FE_ASSERT(l_result == s_task_map->end(), "Assertion failure: unable to retrieve an unregistered task object pointer.");
		return l_result->second; 
	}

	template<class Arguments = FE::arguments<void>>
	_FORCE_INLINE_ static FE::task_base* invoke_function(const typename underlying_container::key_type& key_p, Arguments arguments_p = FE::arguments<void>()) noexcept
	{
		auto l_result = s_task_map->find(key_p);
		FE_ASSERT(l_result == s_task_map->end(), "Assertion failure: unable to retrieve an unregistered task object pointer.");
		
		FE::task_base* const l_task = l_result->second;

		if constexpr (Arguments::count != ARGUMENTS_COUNT::_0)
		{
			l_task->set_arguments(&arguments_p, sizeof(Arguments));
		}

		l_task->operator()();
		return l_task;
	}

	template<class C, class Arguments = FE::arguments<void>>
	_FORCE_INLINE_ static FE::task_base* invoke_method(C& in_out_instance_p, const typename underlying_container::key_type& key_p, Arguments arguments_p = FE::arguments<void>()) noexcept
	{
		FE_STATIC_ASSERT((std::is_class<C>::value == false), "Static Assertion Failure: The template typename C is not a class type.");
		
		auto l_result = s_task_map->find(key_p);
		FE_ASSERT(l_result == s_task_map->end(), "Assertion failure: unable to retrieve an unregistered task object pointer.");
		
		FE::task_base* const l_task = l_result->second;

		if constexpr (Arguments::count != ARGUMENTS_COUNT::_0)
		{
			l_task->set_arguments(&arguments_p, sizeof(Arguments));
		}

		l_task->set_instance(&in_out_instance_p);
		l_task->operator()();
		return l_task;
	}

	_FORCE_INLINE_ static void reserve(size size_p) noexcept
	{
		std::lock_guard<std::mutex> l_lock(s_lock);
		s_task_map->reserve(size_p);
	}
};


END_NAMESPACE
#endif