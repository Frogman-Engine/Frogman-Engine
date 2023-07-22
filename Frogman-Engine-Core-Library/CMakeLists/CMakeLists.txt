CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(FE_CORE)




SET(CMAKE_CXX_STANDARD 20)
if(${CMAKE_CXX_STANDARD} EQUAL 23)
	ADD_COMPILE_DEFINITIONS(_HAS_CXX23_ _HAS_CXX20_ _HAS_CXX17_)

elseif(${CMAKE_CXX_STANDARD} EQUAL 20)
	ADD_COMPILE_DEFINITIONS(_HAS_CXX20_ _HAS_CXX17_)

elseif(${CMAKE_CXX_STANDARD} EQUAL 17)
	ADD_COMPILE_DEFINITIONS(_HAS_CXX17_)

else()
	message(FATAL_ERROR "CMAKE_CXX_STANDARD must be C++ 17 or the latest")
endif()




INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash)


SET(_THIRD_PARTY_CITY_HASH_
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/city.cc
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/city.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/citycrc.h
	)
SOURCE_GROUP("Third-Party\\City-Hash" FILES ${_THIRD_PARTY_CITY_HASH_})


SET(_ALGORITHM_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/algorithm/numeric.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/algorithm/utility.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/algorithm/string.hxx
	)
SOURCE_GROUP("FE\\core\\algorithm" FILES ${_ALGORITHM_})


SET(_CONCURRENT_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_queue.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_stack.hxx
	)
SOURCE_GROUP("FE\\core\\concurrent_containers" FILES ${_CONCURRENT_CONTAINERS_})


SET(_CONCURRENT_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_shared_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_unique_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_weak_ptr.hxx 
	)
SOURCE_GROUP("FE\\core\\concurrent_smart_pointers" FILES ${_CONCURRENT_SMART_POINTERS_})


SET(_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/queue.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/stack.hxx
	)
SOURCE_GROUP("FE\\core\\containers" FILES ${_CONTAINERS_})


SET(_MACROS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/macros/attributes.h 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/macros/macro_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/debug.h
	)
SOURCE_GROUP("FE\\core\\macros" FILES ${_MACROS_})


SET(_MEMORY_POOL_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/concurrent_pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/concurrent_pool_allocator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/pool_allocator.hxx
	)
SOURCE_GROUP("FE\\core\\memory_pool" FILES ${_MEMORY_POOL_})


SET(_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/clock.cpp 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/heap_memory_tracker.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/launch.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/launch.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/memory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/memory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/memory.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/memory_metrics.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/mutex.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/exception.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/thread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/function_table.cpp
	)
SOURCE_GROUP("FE\\core\\private" FILES ${_PRIVATE_})


SET(_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/shared_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/unique_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/weak_ptr.hxx 
	)
SOURCE_GROUP("FE\\core\\smart_pointers" FILES ${_SMART_POINTERS_})


SET(_CORE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/allocator.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/allocator_adaptor.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/async.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/clock.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_singleton.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/cstring.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/fstream_guard.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/fstring.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/function.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/function_table.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/hash.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/iterator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/heap_memory_tracker.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_metrics.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/movable_scoped_ref.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/mutex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/prerequisite_symbols.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/random.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/exception.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/singleton.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/string.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/tagged_object.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/thread.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/types.h
	)
SOURCE_GROUP("FE\\core" FILES ${_CORE_})

	
SET(_MISCELLANEOUS_PRIVATE_ ${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/private/macro_restrictions.h)
SOURCE_GROUP("FE\\miscellaneous\\private" FILES ${_MISCELLANEOUS_PRIVATE_})


SET(_MISCELLANEOUS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/misc.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/configuration.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/define_max_min.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/google_test_extension.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/undefine_max_min.h
	)
SOURCE_GROUP("FE\\miscellaneous" FILES ${_MISCELLANEOUS_})




if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")

	# Find the path to the GNU C compiler executable
	FIND_PROGRAM(GNU_C NAMES gcc)
	# Find the path to the Clang C compiler executable
	FIND_PROGRAM(CLANG_C NAMES clang)

	if(GNU_C)
		# Set the path to the found GNU C compiler executable
		SET(CMAKE_C_COMPILER ${GNU_C})
	elseif(CLANG_C)
		# Set the path to the found Clang C compiler executable
		SET(CMAKE_C_COMPILER ${CLANG_C})
	else()
		MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C compilers nor Clang C compilers")
	endif()


	# Find the path to the g++ compiler executable
	FIND_PROGRAM(GNU_CPP NAMES g++-13 g++-12 g++-11 g++)
	# Find the path to the clang++ compiler executable
	FIND_PROGRAM(CLANG_CPP NAMES clang++-16 clang++-15 clang++-14 clang++-13 clang++-12 clang++)

	if(GNU_CPP)
		# Set the path to the found g++ compiler executable
		SET(CMAKE_CXX_COMPILER ${GNU_CPP})
	elseif(CLANG_CPP)
		# Set the path to the found Clang C compiler executable
		SET(CMAKE_CXX_COMPILER ${CLANG_CPP})
	else()
		MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C++ compilers nor Clang C++ compilers")
	endif()

	ADD_COMPILE_DEFINITIONS(_LINUX_64BIT_OS_)

	SET(TBB_LINUX
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbb_debug.so>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbb.so>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbb.so>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbb.so>
	)

	SET(TBB_MALLOC_LINUX 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbbmalloc_debug.so>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbbmalloc.so>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbbmalloc.so>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8/libtbbmalloc.so>
	)

	SET(BOOST_STACKTRACE_LINUX 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Linux/libboost_stacktrace_basic.a>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Linux/libboost_stacktrace_basic.a>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Linux/libboost_stacktrace_basic.a>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Linux/libboost_stacktrace_basic.a>
	)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64")

	ADD_COMPILE_DEFINITIONS(_WINDOWS_64BIT_OS_)

	SET(TBB_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbb12_debug.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbb12.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbb12.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbb12.lib>
	)

	SET(TBB_MALLOC_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbbmalloc_debug.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbbmalloc.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbbmalloc.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp/tbbmalloc.lib>
	)
	
	SET(BOOST_STACKTRACE_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Windows/Visual-Studio-2022-v143-Compiler/debug/libboost_stacktrace_windbg_cached-vc143-mt-gd-x64-1_82.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Windows/Visual-Studio-2022-v143-Compiler/release/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Windows/Visual-Studio-2022-v143-Compiler/release/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/Boost-Libraries_1_82_0/binaries/Windows/Visual-Studio-2022-v143-Compiler/release/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
	)
	



endif()




ADD_SUBDIRECTORY(FE_CORE_DEBUGGER)
ADD_SUBDIRECTORY(FE_CORE_AVX)
ADD_SUBDIRECTORY(FE_CORE_AVX2)
ADD_SUBDIRECTORY(FE_CORE_AVX512)