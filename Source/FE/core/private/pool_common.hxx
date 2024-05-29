#ifndef _FE_CORE_PRIVATE_POOL_COMMON_HXX_
#define _FE_CORE_PRIVATE_POOL_COMMON_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/allocator.hxx>
#include <FE/core/private/allocator_base.hpp>
#include <FE/core/type_traits.hxx>


// std
#include <array>
#include <list>
#include <map>
#include <memory>
#pragma warning (push)




BEGIN_NAMESPACE(FE)


enum struct POOL_TYPE : uint8
{
    _BLOCK = 0,
    _GENERIC = 1,
};


namespace internal::pool
{
    template <typename T, POOL_TYPE PoolType>
    struct block_info;

    template<typename T, POOL_TYPE PoolType, size_t PageCapacity, class Alignment>
    struct chunk;
}


template<typename T, POOL_TYPE PoolType, size_t PageCapacity, class Alignment, class Allocator>
struct pool_deleter;

template<typename T, POOL_TYPE PoolType, size_t PageCapacity, class Alignment, class Allocator>
class pool;


template<uint64 Capacity>
struct capacity final
{
    _MAYBE_UNUSED_ static constexpr inline size_t size = Capacity;
};

template<uint64 Count>
struct object_count final
{
    _MAYBE_UNUSED_ static constexpr inline size_t size = Count;
};

template<uint64 SizeInBytes>
struct size_in_bytes final
{
    _MAYBE_UNUSED_ static constexpr inline size_t size = SizeInBytes;
};

END_NAMESPACE
#pragma warning (pop)
#endif