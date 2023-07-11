CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


# Set Project Name
PROJECT(Frogma_Engine_Core_Library_Debugger)


SET(CMAKE_BUILD_TYPE "Debug")
SET(SIMD_OPTION "AVX")
SET(CMAKE_CXX_STANDARD 20)


if(${CMAKE_CXX_STANDARD} EQUAL 23)

ADD_COMPILE_DEFINITIONS(_HAS_CXX23_=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX20_=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)

elseif(${CMAKE_CXX_STANDARD} EQUAL 20)

ADD_COMPILE_DEFINITIONS(_HAS_CXX23_=0)
ADD_COMPILE_DEFINITIONS(_HAS_CXX20_=1)
ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)

elseif(${CMAKE_CXX_STANDARD} EQUAL 17)

ADD_COMPILE_DEFINITIONS(_HAS_CXX23_=0)
ADD_COMPILE_DEFINITIONS(_HAS_CXX20_=0)
ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)

else()
message(FATAL_ERROR "CMAKE_CXX_STANDARD must be C++ 17 or the latest")
endif()


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/Boost-Libraries_1_82_0/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/City-Hash/include)


SET(_UNIT_TEST_CODE_
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/allocator_adaptor-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/allocator-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/cstring-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/fstring-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/hash-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/iterator-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/math-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/memory_block-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/movable_scoped_ref-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/numeric-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/private-memory-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/singleton_templates-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/string_algorithm-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/string-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/tagged_object-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/thread-mutex-unit-test.cpp
	)
SOURCE_GROUP("unit-tests" FILES ${_UNIT_TEST_CODE_})


SET(_ALGORITHM_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/algorithm/numeric.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/algorithm/utility.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/algorithm/string.hxx
	)
SOURCE_GROUP("FE\\core\\algorithm" FILES ${_ALGORITHM_})


SET(_CONCURRENT_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_containers/concurrent_queue.hxx
	)
SOURCE_GROUP("FE\\core\\concurrent_containers" FILES ${_CONCURRENT_CONTAINERS_})


SET(_CONCURRENT_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_smart_pointers/concurrent_exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_smart_pointers/concurrent_proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_smart_pointers/concurrent_shared_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_smart_pointers/concurrent_unique_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_smart_pointers/concurrent_weak_ptr.hxx 
	)
SOURCE_GROUP("FE\\core\\concurrent_smart_pointers" FILES ${_CONCURRENT_SMART_POINTERS_})


SET(_CONTAINERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/array.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/deque.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/hash_map.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/linked_array.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/list.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/containers/queue.hxx
	)
SOURCE_GROUP("FE\\core\\containers" FILES ${_CONTAINERS_})


SET(_MACROS_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/macros/attributes.h 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/macros/macro_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/debug.h
	)
SOURCE_GROUP("FE\\core\\macros" FILES ${_MACROS_})


SET(_MEMORY_POOL_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_pool/concurrent_pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_pool/concurrent_pool_allocator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_pool/pool.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_pool/pool_allocator.hxx
	)
SOURCE_GROUP("FE\\core\\memory_pool" FILES ${_MEMORY_POOL_})


SET(_PRIVATE_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/clock.cpp 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/configuration_deserializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/configuration_deserializer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/heap_utilization.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/launch.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/launch.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/memory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/memory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/memory_metrics.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/mutex.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/exception.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/private/thread.cpp
	)
SOURCE_GROUP("FE\\core\\private" FILES ${_PRIVATE_})


SET(_SMART_POINTERS_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/smart_pointers/exclusive_ptr.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/smart_pointers/proxy_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/smart_pointers/shared_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/smart_pointers/unique_ptr.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/smart_pointers/weak_ptr.hxx 
	)
SOURCE_GROUP("FE\\core\\smart_pointers" FILES ${_SMART_POINTERS_})


SET(_CORE_
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/allocator.hxx 	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/allocator_adaptor.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/async.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/clock.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/concurrent_singleton.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/cstring.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/fstream_guard.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/fstring.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/function.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/hash.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/iterator.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/heap_utilization.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/math.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_block.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/memory_metrics.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/movable_scoped_ref.hxx 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/mutex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/prerequisite_symbols.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/random.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/exception.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/exception_mode.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/singleton.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/string.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/tagged_object.hxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/thread.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/core/types.h
	)
SOURCE_GROUP("FE\\core" FILES ${_CORE_})

	
SET(_MISCELLANEOUS_PRIVATE_ ${CMAKE_CURRENT_SOURCE_DIR}/../../FE/miscellaneous/private/macro_restrictions.h)
SOURCE_GROUP("FE\\miscellaneous\\private" FILES ${_MISCELLANEOUS_PRIVATE_})


SET(_MISCELLANEOUS_ 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/miscellaneous/configuration.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/miscellaneous/define_max_min.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/miscellaneous/google_test_extension.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FE/miscellaneous/undefine_max_min.h
	)
SOURCE_GROUP("FE\\miscellaneous" FILES ${_MISCELLANEOUS_})

				


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
message("Configurating The Build Environment for Linux X86-64 Distributions")

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


if(${SIMD_OPTION} STREQUAL "AVX-512")
ADD_COMPILE_OPTIONS(-mavx512)

elseif(${SIMD_OPTION} STREQUAL "AVX-2")
ADD_COMPILE_OPTIONS(-mavx2)

elseif(${SIMD_OPTION} STREQUAL "AVX")
ADD_COMPILE_OPTIONS(-mavx)

else()
message(FATAL_ERROR "Detected an invalid X86-64 intrinsic SIMD option")

endif()


if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
ADD_COMPILE_OPTIONS(-pthread -finline-functions -march=x86-64 -O3)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
ADD_COMPILE_OPTIONS(-pthread -g -march=x86-64 -O0)

else()
message(FATAL_ERROR "Detected an invalid Build Option")

endif()


ADD_COMPILE_DEFINITIONS(_LINUX_64BIT_OS_=1)
ADD_COMPILE_DEFINITIONS(_WINDOWS_64BIT_OS_=0)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
FIND_LIBRARY(UNIT_TEST_LINUX libgtest.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Linux-Packages)
FIND_LIBRARY(CITY_HASH libCITY_HASH.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/City-Hash/Binaries/Linux/a)
FIND_LIBRARY(TBB_LINUX libtbb_debug.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8 PATH_SUFFIXES gcc4.8)
FIND_LIBRARY(TBB_MALLOC_LINUX libtbbmalloc_debug.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8 PATH_SUFFIXES gcc4.8)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
FIND_LIBRARY(UNIT_TEST_LINUX libgtest.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Linux-Packages)
FIND_LIBRARY(CITY_HASH libCITY_HASH.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/City-Hash/Binaries/Linux/a)
FIND_LIBRARY(TBB_LINUX libtbb.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8 PATH_SUFFIXES gcc4.8)
FIND_LIBRARY(TBB_MALLOC_LINUX libtbbmalloc.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Linux/so/intel64/gcc4.8 PATH_SUFFIXES gcc4.8)

else()
message(FATAL_ERROR "Detected an invalid Build Option")

endif()


# Add the executable target
ADD_EXECUTABLE(	${PROJECT_NAME} 
				main.cpp
				${_ALGORITHM_}
				${_CONCURRENT_CONTAINERS_}
				${_CONCURRENT_SMART_POINTERS_}
				${_CONTAINERS_}
				${_MACROS_}
				${_MEMORY_POOL_} 
				${_PRIVATE_}
				${_SMART_POINTERS_}
				${_CORE_}
				${_MISCELLANEOUS_PRIVATE_}
				${_MISCELLANEOUS_}
				${_UNIT_TEST_CODE_}
				)

# Set the output directory for the executable
SET_TARGET_PROPERTIES(	${PROJECT_NAME} 
						PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Linux
						) 

# Link against the libraries
TARGET_LINK_LIBRARIES(	${PROJECT_NAME} stdc++fs 

						${UNIT_TEST_LINUX}
						${CITY_HASH}

						${TBB_LINUX}
						${TBB_MALLOC_LINUX}
						)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
message("Configurating The Build Environment for Windows X86-64")

ADD_COMPILE_DEFINITIONS(_WINDOWS_64BIT_OS_=1)
ADD_COMPILE_DEFINITIONS(_LINUX_64BIT_OS_=0)


if(${SIMD_OPTION} STREQUAL "AVX-512")
ADD_COMPILE_OPTIONS(/arch:AVX512)

elseif(${SIMD_OPTION} STREQUAL "AVX-2")
ADD_COMPILE_OPTIONS(/arch:AVX2)

elseif(${SIMD_OPTION} STREQUAL "AVX")
ADD_COMPILE_OPTIONS(/arch:AVX)

else()
message(FATAL_ERROR "Detected an invalid X86-64 intrinsic SIMD option")

endif()

ADD_COMPILE_OPTIONS(/WX- /W4 /MP /Od /Oi /MTd /Gy /DEBUG)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
FIND_LIBRARY(UNIT_TEST_WINDOWS gtest.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Debug)
FIND_LIBRARY(CITY_HASH CITY_HASH.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/City-Hash/Binaries/Windows/Debug)
FIND_LIBRARY(TBB_WINDOWS tbb12_debug.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp PATH_SUFFIXES vc14_uwp)
FIND_LIBRARY(TBB_MALLOC_WINDOWS tbbmalloc_debug.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp PATH_SUFFIXES vc14_uwp)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
FIND_LIBRARY(UNIT_TEST_WINDOWS gtest.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Release)
FIND_LIBRARY(CITY_HASH CITY_HASH.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/City-Hash/Binaries/Windows/Release)
FIND_LIBRARY(TBB_WINDOWS tbb12.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp PATH_SUFFIXES vc14_uwp)
FIND_LIBRARY(TBB_MALLOC_WINDOWS tbbmalloc.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Third-Party-Libraries/OneAPI-TBB_2021_9_0/binaries/Windows/lib/intel64/vc14_uwp PATH_SUFFIXES vc14_uwp)

else()
message(FATAL_ERROR "Detected an invalid Build Option")

endif()


ADD_EXECUTABLE(	${PROJECT_NAME} 
				main.cpp
				${_ALGORITHM_}
				${_CONCURRENT_CONTAINERS_}
				${_CONCURRENT_SMART_POINTERS_}
				${_CONTAINERS_}
				${_MACROS_}
				${_MEMORY_POOL_} 
				${_PRIVATE_}
				${_SMART_POINTERS_}
				${_CORE_}
				${_MISCELLANEOUS_PRIVATE_}
				${_MISCELLANEOUS_}
				${_UNIT_TEST_CODE_}
				)

# Set the output directory for the executable
SET_TARGET_PROPERTIES(	${PROJECT_NAME}
						PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Windows
						) 

# Link against the libraries
TARGET_LINK_LIBRARIES(	${PROJECT_NAME}

						${UNIT_TEST_WINDOWS}
						${CITY_HASH}

						${TBB_WINDOWS}
						${TBB_MALLOC_WINDOWS}
						)
endif()




#// To enable or disable a certain feature, modify the macro definition to true or false.
#// 
#// Modifying the macro will not immediately affect your project.
#// The binary files e.g. (.lib, .a, .dll, or .so) need to be rebuilt to apply changes that have been made.

#// Frogman Engine Memory Tracker generates a memory utilization report over frames at the end of an app process.
#// The output file can be visualized as a graph image via Frogman Engine Memory Utilization Analyzer.
#// Memory tracking routines involve atomic integral sum and add operations, and its tracking frequency can be dynamically adjusted without recompiling the Engine binary.
#// Excluding this feature can improve an app performance.

#// FE::exception is designed to replace conventional C++ exception models. 
#// It logs recoverable errors and warnings with timestamps to keep track of suspicious app process flows, and it can return early if it is nested inside an if-statement.
#// Frogman Engine Exception system can be turned off by assigning "false" to this macro.

#// FE_ASSERT can be disabled by setting this macro "true" to eliminate error-checking overhead.
#// Please NOTE that FE_ASSERT aborts when circumstances are unrecoverable and critical. Therefore, precise debugging should be placed first.

ADD_COMPILE_DEFINITIONS(_USE_CMAKE_MACRO_=true)


target_compile_definitions(	${PROJECT_NAME} PRIVATE 
							$<$<CONFIG:DEBUG>:_DEBUG_MODE_=true _ENABLE_MEMORY_TRACKER_=true _ENABLE_EXCEPTION_LOG_=true _ENABLE_ASSERT_=true _ENABLE_ABORT_IF_=true _ENABLE_EXIT_=true>
							$<$<CONFIG:RELEASE>:_DEBUG_MODE_=false _ENABLE_MEMORY_TRACKER_=false _ENABLE_EXCEPTION_LOG_=false _ENABLE_ASSERT_=false _ENABLE_ABORT_IF_=false _ENABLE_EXIT_=false>
							$<$<CONFIG:RELWITHDEBINFO>:_DEBUG_MODE_=true _ENABLE_MEMORY_TRACKER_=true _ENABLE_EXCEPTION_LOG_=true _ENABLE_ASSERT_=true _ENABLE_ABORT_IF_=true _ENABLE_EXIT_=true>
							)
