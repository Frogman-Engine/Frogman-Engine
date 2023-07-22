CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


SET(FE_CORE_DEBUGGER "FE_CORE_DEBUGGER")


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases)


SOURCE_GROUP("Third-Party\\City-Hash" FILES ${_THIRD_PARTY_CITY_HASH_})
SOURCE_GROUP("FE\\core\\algorithm" FILES ${_ALGORITHM_})
SOURCE_GROUP("FE\\core\\concurrent_containers" FILES ${_CONCURRENT_CONTAINERS_})
SOURCE_GROUP("FE\\core\\concurrent_smart_pointers" FILES ${_CONCURRENT_SMART_POINTERS_})
SOURCE_GROUP("FE\\core\\containers" FILES ${_CONTAINERS_})
SOURCE_GROUP("FE\\core\\macros" FILES ${_MACROS_})
SOURCE_GROUP("FE\\core\\memory_pool" FILES ${_MEMORY_POOL_})
SOURCE_GROUP("FE\\core\\private" FILES ${_PRIVATE_})
SOURCE_GROUP("FE\\core\\smart_pointers" FILES ${_SMART_POINTERS_})
SOURCE_GROUP("FE\\core" FILES ${_CORE_})
SOURCE_GROUP("FE\\miscellaneous\\private" FILES ${_MISCELLANEOUS_PRIVATE_})
SOURCE_GROUP("FE\\miscellaneous" FILES ${_MISCELLANEOUS_})


SET(_UNIT_TEST_CODE_
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/allocator_adaptor-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/allocator-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/cstring-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/fstring-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/hash-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/iterator-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/memory_block-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/movable_scoped_ref-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/numeric-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/private-memory-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/singleton_templates-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/stack-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/queue-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/string_algorithm-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/string-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/tagged_object-unit-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/FE-Core-Unit-Test-Cases/thread-mutex-unit-test.cpp
	)
SOURCE_GROUP("unit-tests" FILES ${_UNIT_TEST_CODE_})


ADD_EXECUTABLE(	${FE_CORE_DEBUGGER} 
				${_THIRD_PARTY_CITY_HASH_}
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


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")

	if(GNU_CPP)
		TARGET_COMPILE_OPTIONS(${FE_CORE_DEBUGGER} PRIVATE
			$<$<CONFIG:DEBUG>:			-Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0 -march=avx
			$<$<CONFIG:RELWITHDEBINFO>: -Wall -Wextra Og	-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:RELEASE>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:MINSIZEREL>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
		)
	elseif(CLANG_CPP)
		TARGET_COMPILE_OPTIONS(${FE_CORE_DEBUGGER} PRIVATE
			$<$<CONFIG:DEBUG>:			-Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0 -march=avx
			$<$<CONFIG:RELWITHDEBINFO>: -Wall -Wextra Og	-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:RELEASE>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:MINSIZEREL>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
		)
	endif()


	SET_TARGET_PROPERTIES(${FE_CORE_DEBUGGER} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Linux/debug/a
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Linux/release_with_debug_info/a
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Linux/release/a
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/Linux/minimally_sized_release/a
    )


	FIND_LIBRARY(UNIT_TEST_LINUX libgtest.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Linux-Packages)


	TARGET_LINK_LIBRARIES(${FE_CORE_DEBUGGER} stdc++fs 
		${TBB_LINUX}
		${TBB_MALLOC_LINUX}
		${BOOST_STACKTRACE_LINUX}
		${UNIT_TEST_LINUX}
	)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64 Distributions")

	TARGET_COMPILE_OPTIONS(${FE_CORE_DEBUGGER} PRIVATE
        $<$<CONFIG:DEBUG>:			/WX- /W4 /MP /Od /Ob2 /Oi /Ot /Oy- /GT /MTd /Gy /arch:AVX>
        $<$<CONFIG:RELWITHDEBINFO>:	/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
        $<$<CONFIG:RELEASE>:		/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
        $<$<CONFIG:MINSIZEREL>:		/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
    )


	SET_TARGET_PROPERTIES(${FE_CORE_DEBUGGER} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Windows/debug/lib
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Windows/release_with_debug_info/lib
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Windows/release/lib
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/Windows/minimally_sized_release/lib
    )


	SET(UNIT_TEST_WINDOWS			
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Debug/gtest.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Unit-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
	)


	TARGET_LINK_LIBRARIES(${FE_CORE_DEBUGGER} 
		${TBB_WINDOWS}
		${TBB_MALLOC_WINDOWS}
		${BOOST_STACKTRACE_WINDOWS}
		${UNIT_TEST_WINDOWS}
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

#// FE_ASSERT can be disabled by removing the corresponding macro to eliminate error-checking overhead.
#// Please NOTE that FE_ASSERT aborts when circumstances are unrecoverable and critical. Therefore, precise debugging should be placed first.

ADD_COMPILE_DEFINITIONS(_USE_CMAKE_MACRO_=true)

TARGET_COMPILE_DEFINITIONS(${FE_CORE_DEBUGGER} PRIVATE
	$<$<CONFIG:DEBUG>:_DEBUG_ _ENABLE_MEMORY_TRACKER_ _ENABLE_LOG_ _ENABLE_ASSERT_ _ENABLE_ABORT_IF_ _ENABLE_EXIT_>
	$<$<CONFIG:RELWITHDEBINFO>:_RELWITHDEBINFO_ _ENABLE_LOG_ _ENABLE_ASSERT_ _ENABLE_EXIT_>
	$<$<CONFIG:RELEASE>:_RELEASE_>
	$<$<CONFIG:MINSIZEREL>:_RELEASE_>
)