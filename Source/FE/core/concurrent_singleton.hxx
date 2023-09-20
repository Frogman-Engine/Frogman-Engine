#ifndef _FE_CORE_CONCURRENT_SINGLETON_HXX_
#define _FE_CORE_CONCURRENT_SINGLETON_HXX_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/prerequisites.h>
#include <FE/core/concurrent_memory_block.hxx>


#define FRIEND_CLASS_CONCURRENT_SINGLETON(typename_p) friend class ::FE::concurrent_memory_block<typename_p>; friend class ::FE::concurrent_singleton<typename_p>




BEGIN_NAMESPACE(FE)

/*
concurrent_singleton<T> can be used to reduce singleton code pattern duplication.
the construction and the destruction operations are lock-free and thread-safe but the instance may not be safe from data race condition.
steps to do:
1. add the macro FRIEND_CLASS_SINGLETON(typename_p); to the desired class declaration.
2. set the constructors private to hide those.

For further information, please check our Unit Test Cases.
*/
template<typename T>
class concurrent_singleton final
{
private:
	static FE::concurrent_memory_block<T> s_instance;

public: 
	typedef T value_type;
	typedef FE::concurrent_memory_block<T> memory_block_type;

	concurrent_singleton() noexcept = delete;
	~concurrent_singleton() noexcept = delete;
	concurrent_singleton(const concurrent_singleton& deprecated_p) noexcept = delete;
	concurrent_singleton& operator=(const concurrent_singleton& deprecated_p) noexcept = delete;
	concurrent_singleton(concurrent_singleton&& deprecated_p) noexcept = delete;
	concurrent_singleton& operator=(concurrent_singleton&& deprecated_p) noexcept = delete;


	_FORCE_INLINE_ static T& singleton_instance() noexcept
	{
		if (concurrent_singleton<T>::s_instance.is_constructed() == false) _UNLIKELY_
		{
			concurrent_singleton<T>::s_instance.call_constructor();
		}

		return *(*concurrent_singleton<T>::s_instance);
	}

	template<typename ... Arguments>
	_FORCE_INLINE_ static T& singleton_instance(Arguments&& ...arguments_p) noexcept
	{
		if (concurrent_singleton<T>::s_instance.is_constructed() == false) _UNLIKELY_
		{
			concurrent_singleton<T>::s_instance.call_constructor(arguments_p...);
		}

		return *(*concurrent_singleton<T>::s_instance);
	}

	_FORCE_INLINE_ static void destruct_singleton() noexcept
	{
		concurrent_singleton<T>::s_instance.call_destructor();
	}
};

template<typename T>
::FE::concurrent_memory_block<T> FE::concurrent_singleton<T>::s_instance;

END_NAMESPACE
#endif