CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0...3.31.5)
# Copyright © 2024 to present UNKNOWN STRYKER. All Rights Reserved.
PROJECT(FE.HeaderTool
        VERSION 0.0
        DESCRIPTION "Frogman Engine Header Tool is an executable in-house tool application."
        LANGUAGES CXX)

GET_FILENAME_COMPONENT(FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
INCLUDE("${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../../CMake/predefined-settings.cmake")
INCLUDE("${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../../CMake/frogman-engine.cmake")

INCLUDE_DIRECTORIES(${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include)


SET(FHT_SOURCE_FILES
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include/error_code.hpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include/header_tool_engine.hpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include/program_options.hpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include/reflection_tree.hpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Include/vocabulary.hpp

${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/read_copyright_notice.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/header_tool_engine.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/main.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/parser.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/program_options.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/reflection_code_generator.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/symbol_counter.cpp
${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Source/tree_builder.cpp
)

ADD_FROGMAN_EXECUTABLE(${CMAKE_PROJECT_NAME} ${FHT_SOURCE_FILES})

SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${FE_HEADER_TOOL_CMAKE_CURRENT_LIST_DIR}/../Binaries"
VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${FROGMAN_FRAMEWORK_SDK})

#message(STATUS "The build files are located in: ${CMAKE_BINARY_DIR}")