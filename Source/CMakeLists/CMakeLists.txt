CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(FE)


SET(CMAKE_CXX_STANDARD 20)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash)


SET(_THIRD_PARTY_CITY_HASH_
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/city.cc
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/city.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Third-Party/City-Hash/citycrc.h
	)
#SOURCE_GROUP("Third-Party\\City-Hash" FILES ${_THIRD_PARTY_CITY_HASH_})


SET(_ALGORITHM_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/algorithm/utility.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/algorithm/string.hxx
	)
#SOURCE_GROUP("FE\\core\\algorithm" FILES ${_ALGORITHM_})


SET(_LOG_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/logger.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/format_string.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/debug_macros.h
	)
#SOURCE_GROUP("FE\\core\\log" FILES ${_LOG_})

SET(_LOG_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/private/logger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/private/format_string.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/log/private/internal_functions.h
	)
#SOURCE_GROUP("FE\\core\\log\\private" FILES ${_LOG_PRIVATE_})


SET(_CONCURRENT_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_queue.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_containers/concurrent_stack.hxx
	)
#SOURCE_GROUP("FE\\core\\concurrent_containers" FILES ${_CONCURRENT_CONTAINERS_})


SET(_CONCURRENT_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/concurrent_unique_ptr.hxx
	)
#SOURCE_GROUP("FE\\core\\concurrent_smart_pointers" FILES ${_CONCURRENT_SMART_POINTERS_})

SET(_CONCURRENT_SMART_POINTERS_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_smart_pointers/private/concurrent_smart_ptr_base.hxx
	)
#SOURCE_GROUP("FE\\core\\concurrent_smart_pointers\\private" FILES ${_CONCURRENT_SMART_POINTERS_PRIVATE_})


SET(_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/queue.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/containers/stack.hxx
	)
#SOURCE_GROUP("FE\\core\\containers" FILES ${_CONTAINERS_})


SET(_MACROS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/macros/attributes.h 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/macros/macro_definitions.h
	)
#SOURCE_GROUP("FE\\core\\macros" FILES ${_MACROS_})


SET(_MEMORY_POOL_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/concurrent_pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/concurrent_pool_allocator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_pool/pool_allocator.hxx
	)
#SOURCE_GROUP("FE\\core\\memory_pool" FILES ${_MEMORY_POOL_})


SET(_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/clock.cpp 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/heap_memory_tracker.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/hash.cpp  
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/memory_metrics.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/mutex.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/strlen.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/private/thread.cpp
	)
#SOURCE_GROUP("FE\\core\\private" FILES ${_PRIVATE_})


SET(_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/unique_ptr.hxx
	)
#SOURCE_GROUP("FE\\core\\smart_pointers" FILES ${_SMART_POINTERS_})

SET(_SMART_POINTERS_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/smart_pointers/private/smart_ptr_base.hxx 	
	)
#SOURCE_GROUP("FE\\core\\smart_pointers\\private" FILES ${_SMART_POINTERS_PRIVATE_})


SET(_CORE_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/allocator.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/allocator_adaptor.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/async.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/clock.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/concurrent_singleton.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/cstring.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/debug.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/do_once.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/fstream_guard.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/fstring.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/function.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/hash.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/heap_memory_tracker.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/iterator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_metrics.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/movable_scoped_ref.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/mutex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/optional.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/prerequisite_symbols.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/random.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/singleton.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/string.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/tagged_object.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/thread.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/core/types.h
	)
#SOURCE_GROUP("FE\\core" FILES ${_CORE_})

	
SET(_MISCELLANEOUS_PRIVATE_ ${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/private/macro_restrictions.h)
#SOURCE_GROUP("FE\\miscellaneous\\private" FILES ${_MISCELLANEOUS_PRIVATE_})


SET(_MISCELLANEOUS_
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/misc.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/configuration.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/define_max_min.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/google_test_extension.h
	${CMAKE_CURRENT_SOURCE_DIR}/../FE/miscellaneous/undefine_max_min.h
	)
#SOURCE_GROUP("FE\\miscellaneous" FILES ${_MISCELLANEOUS_})




if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")

	FIND_PROGRAM(GNU_C NAMES gcc)
	FIND_PROGRAM(CLANG_C NAMES clang)

	if(GNU_C)
		SET(CMAKE_C_COMPILER ${GNU_C})

	elseif(CLANG_C)
		SET(CMAKE_C_COMPILER ${CLANG_C})

	else()
		MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C compilers nor Clang C compilers")
	endif()


	FIND_PROGRAM(GNU_CPP NAMES g++-13 g++-12 g++-11 g++)
	FIND_PROGRAM(CLANG_CPP NAMES clang++-16 clang++-15 clang++-14 clang++-13 clang++-12 clang++)

	if(GNU_CPP)
		SET(CMAKE_CXX_COMPILER ${GNU_CPP})

	elseif(CLANG_CPP)
		SET(CMAKE_CXX_COMPILER ${CLANG_CPP})

	else()
		MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C++ compilers nor Clang C++ compilers")
	endif()


	ADD_COMPILE_DEFINITIONS(_LINUX_64BIT_OS_)
	
	
	if(GNU_CPP)
		SET(DEBUG_COMPILE_OPTIONS			 -Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0)
		SET(RELWITHDEBINFO_COMPILE_OPTIONS	 -Wall -Wextra 		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
		SET(RELEASE_COMPILE_OPTIONS			 -Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
		SET(MINSIZEREL_COMPILE_OPTIONS		 -Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
		
	elseif(CLANG_CPP)
		SET(DEBUG_COMPILE_OPTIONS			-Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0)
		SET(RELWITHDEBINFO_COMPILE_OPTIONS	-Wall -Wextra 		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
		SET(RELEASE_COMPILE_OPTIONS			-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
		SET(MINSIZEREL_COMPILE_OPTIONS		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3)
	endif()


	SET(TBB_LINUX
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbb_debug.so.12.10>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbb.so.12.10>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbb.so.12.10>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbb.so.12.10>
	)

	SET(TBB_MALLOC_LINUX 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbbmalloc_debug.so>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbbmalloc.so>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbbmalloc.so>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/linux/oneapi-tbb-2021.10.0/lib/intel64/gcc4.8/libtbbmalloc.so>
	)

	SET(BOOST_STACKTRACE_LINUX 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Linux/gcc-11.4/debug/libboost_stacktrace_basic.a>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Linux/gcc-11.4/release/libboost_stacktrace_basic.a>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Linux/gcc-11.4/release/libboost_stacktrace_basic.a>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Linux/gcc-11.4/release/libboost_stacktrace_basic.a>
	)

	SET(FE_FRAMEWORK_LINUX 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Linux/debug/lib/libFE_FRAMEWORK.a>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Linux/release_with_debug_info/lib/libFE_FRAMEWORK.a>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Linux/release/lib/libFE_FRAMEWORK.a>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Linux/minimally_sized_release/lib/libFE_FRAMEWORK.a>
	)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64")

	SET(DEBUG_COMPILE_OPTIONS			/Zc:__cplusplus /WX- /W4 /MP /Od /Ob0 /Oi /Ot /Oy- /GT /MTd /Gy)
	SET(RELWITHDEBINFO_COMPILE_OPTIONS	/Zc:__cplusplus /WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy- /GT /MT /Gy /GL)
	SET(RELEASE_COMPILE_OPTIONS			/Zc:__cplusplus /WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /GL)
	SET(MINSIZEREL_COMPILE_OPTIONS		/Zc:__cplusplus /WX- /W4 /MP /Ox /Ob2 /Oi /Os /Oy /GT /MT /Gy /GL)


	SET(TBB_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbb12_debug.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbb12.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbb12.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbb12.lib>
	)

	SET(TBB_MALLOC_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbbmalloc_debug.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbbmalloc.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbbmalloc.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/oneapi-tbb/windows/oneapi-tbb-2021.10.0/lib/intel64/vc14_uwp/tbbmalloc.lib>
	)
	
	SET(BOOST_STACKTRACE_WINDOWS 
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Windows/Visual-Studio-2022-v143-Compiler/debug/lib/libboost_stacktrace_windbg_cached-vc143-mt-gd-x64-1_82.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Windows/Visual-Studio-2022-v143-Compiler/release/lib/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Windows/Visual-Studio-2022-v143-Compiler/release/lib/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost_1_82_0/lib/Windows/Visual-Studio-2022-v143-Compiler/release/lib/libboost_stacktrace_windbg_cached-vc143-mt-x64-1_82.lib>
	)

	SET(FE_FRAMEWORK_WINDOWS
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Windows/debug/lib/FE_FRAMEWORK.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Windows/release_with_debug_info/lib/FE_FRAMEWORK.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Windows/release/lib/FE_FRAMEWORK.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/FE_FRAMEWORK/Windows/minimally_sized_release/lib/FE_FRAMEWORK.lib>
	)
	



endif()




ADD_SUBDIRECTORY(FE_TEST)
ADD_SUBDIRECTORY(FE_AVX)
ADD_SUBDIRECTORY(FE_FRAMEWORK)
