CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


SET(FE_TEST "FE_TEST")


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases)


SOURCE_GROUP("Third-Party\\City-Hash" FILES ${_THIRD_PARTY_CITY_HASH_})
SOURCE_GROUP("FE\\core\\algorithm" FILES ${_ALGORITHM_})
SOURCE_GROUP("FE\\core\\log" FILES ${_LOG_})
SOURCE_GROUP("FE\\core\\log\\private" FILES ${_LOG_PRIVATE_})
SOURCE_GROUP("FE\\core\\concurrent_containers" FILES ${_CONCURRENT_CONTAINERS_})
SOURCE_GROUP("FE\\core\\concurrent_smart_pointers" FILES ${_CONCURRENT_SMART_POINTERS_})
SOURCE_GROUP("FE\\core\\concurrent_smart_pointers\\private" FILES ${_CONCURRENT_SMART_POINTERS_PRIVATE_})
SOURCE_GROUP("FE\\core\\containers" FILES ${_CONTAINERS_})
SOURCE_GROUP("FE\\core\\macros" FILES ${_MACROS_})
SOURCE_GROUP("FE\\core\\memory_pool" FILES ${_MEMORY_POOL_})
SOURCE_GROUP("FE\\core\\private" FILES ${_PRIVATE_})
SOURCE_GROUP("FE\\core\\smart_pointers" FILES ${_SMART_POINTERS_})
SOURCE_GROUP("FE\\core\\smart_pointers\\private" FILES ${_SMART_POINTERS_PRIVATE_})
SOURCE_GROUP("FE\\core" FILES ${_CORE_})
SOURCE_GROUP("FE\\miscellaneous\\private" FILES ${_MISCELLANEOUS_PRIVATE_})
SOURCE_GROUP("FE\\miscellaneous" FILES ${_MISCELLANEOUS_})


SET(_TEST_CODE_
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/allocator_adaptor-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/allocator-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/cstring-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/fstring-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/hash-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/iterator-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/concurrent_memory_block-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/movable_scoped_ref-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/unique_ptr-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/utility_algorithm-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/optional-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/private-memory-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/singleton_templates-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/smart_ptr_variants-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/stack-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/queue-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/string_algorithm-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/string-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/tagged_object-test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/FE-Core-Test-Cases/function-thread-test.cpp
	)
SOURCE_GROUP("Tests" FILES ${_TEST_CODE_})


ADD_EXECUTABLE(	${FE_TEST} 
				${_THIRD_PARTY_CITY_HASH_}
				main.cpp
				${_ALGORITHM_}
				${_LOG_}
				${_LOG_PRIVATE_}
				${_CONCURRENT_CONTAINERS_}
				${_CONCURRENT_SMART_POINTERS_}
				${_CONCURRENT_SMART_POINTERS_PRIVATE_}
				${_CONTAINERS_}
				${_MACROS_}
				${_MEMORY_POOL_} 
				${_PRIVATE_}
				${_SMART_POINTERS_}
				${_SMART_POINTERS_PRIVATE_}
				${_CORE_}
				${_MISCELLANEOUS_PRIVATE_}
				${_MISCELLANEOUS_}
				${_TEST_CODE_}
				)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")

	ADD_COMPILE_DEFINITIONS(__AVX__=1)

	if(GNU_CPP)
		TARGET_COMPILE_OPTIONS(${FE_TEST} PRIVATE
			$<$<CONFIG:DEBUG>:			${DEBUG_COMPILE_OPTIONS} 			-mavx>
			$<$<CONFIG:RELWITHDEBINFO>: ${RELWITHDEBINFO_COMPILE_OPTIONS}	-mavx>
			$<$<CONFIG:RELEASE>:		${RELEASE_COMPILE_OPTIONS} 			-mavx>
			$<$<CONFIG:MINSIZEREL>:		${MINSIZEREL_COMPILE_OPTIONS} 		-mavx>
		)
	elseif(CLANG_CPP)
		TARGET_COMPILE_OPTIONS(${FE_TEST} PRIVATE
			$<$<CONFIG:DEBUG>:			${DEBUG_COMPILE_OPTIONS} 			-mavx>
			$<$<CONFIG:RELWITHDEBINFO>: ${RELWITHDEBINFO_COMPILE_OPTIONS} 	-mavx>
			$<$<CONFIG:RELEASE>:		${RELEASE_COMPILE_OPTIONS} 			-mavx>
			$<$<CONFIG:MINSIZEREL>:		${MINSIZEREL_COMPILE_OPTIONS} 		-mavx>
		)
	endif()


	SET_TARGET_PROPERTIES(${FE_TEST} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG 			${CMAKE_CURRENT_SOURCE_DIR}/Linux/debug/a
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Linux/release_with_debug_info/a
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE 		${CMAKE_CURRENT_SOURCE_DIR}/Linux/release/a
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL 	${CMAKE_CURRENT_SOURCE_DIR}/Linux/minimally_sized_release/a
    )

	SET(UNIT_TEST_LINUX			
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Linux-Packages/libgtest.a>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Linux-Packages/libgtest.a>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Linux-Packages/libgtest.a>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Linux-Packages/libgtest.a>
	)

	TARGET_LINK_LIBRARIES(${FE_TEST} 
		stdc++fs 
		${TBB_LINUX}
		${TBB_MALLOC_LINUX}
		${BOOST_STACKTRACE_LINUX}
		${UNIT_TEST_LINUX}
		${FE_FRAMEWORK_LINUX}
	)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64 Distributions")

	TARGET_COMPILE_OPTIONS(${FE_TEST} PRIVATE
        $<$<CONFIG:DEBUG>:			${DEBUG_COMPILE_OPTIONS} 			/arch:AVX>
        $<$<CONFIG:RELWITHDEBINFO>:	${RELWITHDEBINFO_COMPILE_OPTIONS} 	/arch:AVX>
        $<$<CONFIG:RELEASE>:		${RELEASE_COMPILE_OPTIONS} 			/arch:AVX>
        $<$<CONFIG:MINSIZEREL>:		${MINSIZEREL_COMPILE_OPTIONS} 		/arch:AVX>
    )


	SET_TARGET_PROPERTIES(${FE_TEST} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG 			${CMAKE_CURRENT_SOURCE_DIR}/Windows/debug
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Windows/release_with_debug_info
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE 		${CMAKE_CURRENT_SOURCE_DIR}/Windows/release
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL 	${CMAKE_CURRENT_SOURCE_DIR}/Windows/minimally_sized_release
    )


	SET(UNIT_TEST_WINDOWS			
		$<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Windows-Packages/lib/Debug/gtest.lib>
		$<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
		$<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
		$<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../../Frogman-Engine-Tests/Unit-Test-Windows-Packages/lib/Release/gtest.lib>
	)


	TARGET_LINK_LIBRARIES(${FE_TEST} 
		${TBB_WINDOWS}
		${TBB_MALLOC_WINDOWS}
		${BOOST_STACKTRACE_WINDOWS}
		${UNIT_TEST_WINDOWS}
		${FE_FRAMEWORK_WINDOWS}
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

TARGET_COMPILE_DEFINITIONS(${FE_TEST} PRIVATE
	$<$<CONFIG:DEBUG>:			_HAS_EXCEPTIONS=0 _DEBUG_					_ENABLE_EXCEPTION_LOG_ _ENABLE_ASSERT_ _ENABLE_ABORT_IF_ _ENABLE_LOG_ _ENABLE_CONDITIONAL_LOG_ _ENABLE_FE_CHECK_ONCE_> #_ENABLE_MEMORY_TRACKER_
	$<$<CONFIG:RELWITHDEBINFO>:	_HAS_EXCEPTIONS=0 _RELWITHDEBINFO_			_ENABLE_EXCEPTION_LOG_ _ENABLE_ASSERT_ _ENABLE_ABORT_IF_ _ENABLE_LOG_ _ENABLE_CONDITIONAL_LOG_ _ENABLE_FE_CHECK_ONCE_>
	$<$<CONFIG:RELEASE>:		_HAS_EXCEPTIONS=0 _RELEASE_				>
	$<$<CONFIG:MINSIZEREL>:		_HAS_EXCEPTIONS=0 _RELEASE_ _MINSIZEREL_>
)