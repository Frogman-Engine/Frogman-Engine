#ifndef _FE_CORE_FUNCTION_TABLE_HXX_
#define _FE_CORE_FUNCTION_TABLE_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisite_symbols.h>
#include <FE/core/allocator_adaptor.hxx>
#include <FE/core/function.hxx>
#include <FE/core/hash.hpp>
#include <unordered_map> // due to its poor cpu cache utilization, it will be replaced with FE::hash_map.


BEGIN_NAMESPACE(FE)

// function_table is currently under development. It might not be suitable to use
class function_table
{
	friend class FE::internal::engine_main;

public:												
	using underlying_container = ::std::unordered_map< const char*, FE::task_base*, FE::hash<const char*>, std::equal_to<const char*>, FE::std_style::scalable_aligned_allocator<std::pair<const char* const, FE::task_base*>> >;
	/* 
		::std::unordered_map uses node-based linked list for its underlying container.
		Since the inner bucket data structure has poor cache access patterns, ::std::unordered_map needs to be replaced with a hash map with contiguous buckets
	*/

private:
	thread_local static underlying_container tl_s_hash_map;
	// + byte-wise generic function object pool member will be added

public:
	function_table() noexcept = delete;
	~function_table() noexcept = delete;
	function_table(const function_table& other_cref_p) noexcept = delete;
	function_table(function_table&& rvalue_p) noexcept = delete;

	static void register_method(underlying_container::value_type value_p) noexcept { FE::function_table::tl_s_hash_map.insert(value_p); }
	static var::boolean check_presence(underlying_container::key_type key_p) noexcept { return (FE::function_table::tl_s_hash_map.find(key_p) == FE::function_table::tl_s_hash_map.end()) ? false : true; }
	static FE::task_base* retrieve(underlying_container::key_type key_p) noexcept { return FE::function_table::tl_s_hash_map.find(key_p)->second; }

	template<typename return_type>
	_FORCE_INLINE_ static return_type invoke(underlying_container::key_type key_p) noexcept 
	{
		return_type l_buffer;
		_MAYBE_UNUSED_ auto l_return_type_info = FE::function_table::tl_s_hash_map.find(key_p)->second->execute(PASS_RETURN_BUFFER(l_buffer));
		FE_ASSERT(l_return_type_info == FE::RETURN_TYPE::_VOID, "ERROR: invoked a function with a non-void return type, but the result is void");
		return l_buffer;
	}
	_FORCE_INLINE_ static void invoke(underlying_container::key_type key_p) noexcept 
	{
		_MAYBE_UNUSED_ auto l_return_type_info = FE::function_table::tl_s_hash_map.find(key_p)->second->execute();
		FE_ASSERT(l_return_type_info == FE::RETURN_TYPE::_NON_VOID, "ERROR: invoked a function with void return type, but the result is not void");
	}
};


END_NAMESPACE
#endif
