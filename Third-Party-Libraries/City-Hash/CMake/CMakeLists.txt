CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


# Set Project Name
PROJECT(CITY_HASH)

SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_STANDARD 20)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include)


SET(_CITY_HASH_
	${CMAKE_CURRENT_SOURCE_DIR}/../include/city.h
	${CMAKE_CURRENT_SOURCE_DIR}/../include/city.cc
	${CMAKE_CURRENT_SOURCE_DIR}/../include/citycrc.h
	)
SOURCE_GROUP("city_hash" FILES ${_CITY_HASH_})



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


ADD_COMPILE_OPTIONS(-pthread -finline-functions -msse4.2 -march=x86-64 -O3)


# Add the executable target
ADD_LIBRARY(${PROJECT_NAME} STATIC
			${_CITY_HASH_}
			)

# Set the output directory for the executable
# Set the output directory for the executable based on build mode
# Set the output directory for the executable based on build mode
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Binaries/Linux/Release/a)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
message("Configurating The Build Environment for Windows X86-64")


ADD_LIBRARY(${PROJECT_NAME} STATIC
			${_CITY_HASH_}
			)

# Set the output directory for the executable
# Set the output directory for the executable based on build mode
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Binaries/Windows)


TARGET_COMPILE_OPTIONS(	${PROJECT_NAME} PRIVATE 
						$<$<CONFIG:DEBUG>:/std:c++20 /WX- /W4 /MP /Od /Ob2 /Oi /Ot /Oy- /GT /MTd /Gy>
						$<$<CONFIG:RELEASE>:/std:c++20 /WX- /W4 /MP /O2 /Ob2 /Oi /Ot /Oy /GT /MT /Gy>
						)
endif()