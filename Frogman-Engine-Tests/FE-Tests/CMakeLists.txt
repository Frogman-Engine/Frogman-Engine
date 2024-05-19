CMAKE_MINIMUM_REQUIRED(VERSION 3.27.0...3.29.3)

PROJECT(FE_TEST
        VERSION 0.0
        DESCRIPTION "A group of executable test code binaries"
        LANGUAGES CXX)

IF(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
    MESSAGE(FATAL_ERROR "Test code can only be built for debugging")
ENDIF()


INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/../../Source/CMakeLists/predefined-settings.cmake")


ADD_COMPILE_DEFINITIONS(BENCHMARK_STATIC_DEFINE)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Tools/Google-Test/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Third-Party-Tools/Benchmark/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Source)


SET(PREREQUISITES
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/miscellaneous/configuration.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/macros/macro_definitions.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/macros/attributes.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/types.hxx 
${CMAKE_CURRENT_SOURCE_DIR}/../../Source/FE/core/private/debug.h
)
ADD_SUBDIRECTORY(prerequisites)


#ADD_DEPENDENCIES("FE_CORE_TEST" "FE_FRAMEWORK")