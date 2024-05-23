CMAKE_MINIMUM_REQUIRED(VERSION 3.27.0...3.29.3)
INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/../../Source/CMakeLists/predefined-settings.cmake") # INCLUDE() must be placed at the top line of a CMakeLists.txt script


PROJECT(FE_TEST
        VERSION 0.0
        DESCRIPTION "A group of executable test code binaries"
        LANGUAGES CXX)

IF(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
    MESSAGE(FATAL_ERROR "Test code can only be built for debugging")
ENDIF()


ADD_COMPILE_DEFINITIONS(BENCHMARK_STATIC_DEFINE)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Tools/Google-Test/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Tools/Benchmark/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Source)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/include)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

    SET(BOOST_STACKTRACE 
    $<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/debug/libboost_stacktrace_basic.a>
    $<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_stacktrace_basic.a>
    $<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_stacktrace_basic.a>
    $<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_stacktrace_basic.a>
    )

    SET(BOOST_CHRONO 
    $<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/debug/libboost_chrono.a>
    $<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_chrono.a>
    $<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_chrono.a>
    $<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Linux/clang-10/release/libboost_chrono.a>
    )

    
ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")

    SET(BOOST_STACKTRACE 
    $<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/debug/libboost_stacktrace_windbg_cached-vc143-mt-gd-x64-1_85.lib>
    $<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_stacktrace_basic-vc143-mt-x64-1_85.lib>
    $<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_stacktrace_noop-vc143-mt-x64-1_85.lib>
    $<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_stacktrace_noop-vc143-mt-x64-1_85.lib>
    )

    SET(BOOST_CHRONO 
    $<$<CONFIG:DEBUG>:			${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/debug/libboost_chrono-vc143-mt-gd-x64-1_85.lib>
    $<$<CONFIG:RELWITHDEBINFO>: ${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_chrono-vc143-mt-x64-1_85.lib>
    $<$<CONFIG:RELEASE>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_chrono-vc143-mt-x64-1_85.lib>
    $<$<CONFIG:MINSIZEREL>:		${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Libraries/boost-1.85.0/lib/Windows/VS2022-v143/release/libboost_chrono-vc143-mt-x64-1_85.lib>
    )

ENDIF()




SET(FE_CORE_PREREQUISITES
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/miscellaneous/configuration.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/macros/macro_definitions.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/macros/attributes.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/types.hxx 
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/private/debug.h
)
ADD_SUBDIRECTORY(FE.core.prerequisites)

SET(FE_CORE_TYPE_TRAITS ${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/type_traits.hxx)
ADD_SUBDIRECTORY(FE.core.type_traits)

SET(FE_CORE_ALGORITHM_UTILITY 
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/algorithm/utility.hxx
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/private/strlen.hxx
)
ADD_SUBDIRECTORY(FE.core.algorithm.utility)   

SET(FE_CORE_LOG
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/log/macros.h

${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/log/logger.hpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/log/private/logger.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/algorithm/string.hxx
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/iterator.hxx
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/memory.hxx
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/algorithm/math.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/algorithm/private/math.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/clock.hpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/private/clock.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/thread.hpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/private/thread.cpp

${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/log/format_string.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/log/private/format_string.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/memory_metrics.h
)
ADD_SUBDIRECTORY(FE.core.log)




IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
ADD_DEPENDENCIES("FE.core.type_traits" "FE.core.prerequisites")
ADD_DEPENDENCIES("FE.core.algorithm.utility" "FE.core.type_traits")
ADD_DEPENDENCIES("FE.core.log" "FE.core.algorithm.utility")
ENDIF()

