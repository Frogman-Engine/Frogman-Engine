SET(CMAKE_CXX_STANDARD_REQUIRED ON)


MESSAGE("
Available -D macro options:
-DLEAVE_OUT_ALL_EXCEPTIONS 
-DENABLE_MEMORY_TRACKER 
-DMEMORY_POOL_FE_STRINGS 
-DMEMORY_POOL_FE_SMART_PTR_PROPERTIES

This project uses AVX as a default SIMD option.
Define a cmake macro if you want to change the setting.
SIMD options:
-DAVX
-DAVX2
-DAVX512

")


IF(NOT ((CMAKE_CXX_STANDARD EQUAL 17) OR (CMAKE_CXX_STANDARD EQUAL 20) OR (CMAKE_CXX_STANDARD EQUAL 23)))
    MESSAGE(FATAL_ERROR "Frogman Engine supports C++ 17, C++ 20, and C++ 23")
ENDIF()


FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR)


IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64")
	ADD_COMPILE_OPTIONS(/D_WINDOWS_X86_64_)
	STRING(REPLACE "\\" "\\\\" OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR "${OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR}")


	IF(DEFINED LEAVE_OUT_ALL_EXCEPTIONS)
		MESSAGE("Enabled the option: LEAVE_OUT_ALL_EXCEPTIONS")
		ADD_COMPILE_OPTIONS(/D_HAS_EXCEPTIONS=0 /DBOOST_NO_EXCEPTIONS)
	ENDIF()

	IF(DEFINED ENABLE_MEMORY_TRACKER)
		MESSAGE("Enabled the option: ENABLE_MEMORY_TRACKER")
		ADD_COMPILE_OPTIONS(/D_ENABLE_MEMORY_TRACKER_)
	ENDIF()

	IF(DEFINED MEMORY_POOL_FE_STRINGS)
		MESSAGE("Enabled the option: MEMORY_POOL_FE_STRINGS")
		ADD_COMPILE_OPTIONS(/D_MEMORY_POOL_FE_STRINGS_)
	ENDIF()

	IF(DEFINED MEMORY_POOL_FE_SMART_PTR_PROPERTIES)
		MESSAGE("Enabled the option: MEMORY_POOL_FE_SMART_PTR_PROPERTIES")
		ADD_COMPILE_OPTIONS(/D_MEMORY_POOL_FE_UNIQUE_PTR_PROPERTIES_ /D_MEMORY_POOL_FE_EXCLUSIVE_PTR_PROPERTIES_)
	ENDIF()


	# /Zc:__cplusplus: C++ version macro option
	# /WX: Treat warnings as errors 
	# /W4: Warning level 4
	# /MP: Multi-processor compilation4
	# /GF: Eliminate duplicate strings
	# /GT: Enable fiber-safe Thread Local Storage 
	# /MTd: Multi-threaded Debug Static std C++ library
	# /Gy: Enable function-level linking 
	# /GL: Whole program optimization
	# /Od: Disable optimization 
	# /Ot: Favor fast code 
	# /Os: Favor small code
	# /Ob0: Disable inline function expansion 
	# /Oi: Generate intrinsic functions
	# /Oy-: Disable frame pointer omission  
	# /Gr: Enable calling convention fastcall
	# /GR: Enable RTTI

	# Common Compile Options
	ADD_COMPILE_OPTIONS(/std:c17 /Zc:__cplusplus /WX /W4 /MP /GF /GT /Gy /GL /Oi /Gr /GR)

	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		MESSAGE("Building the project with 'Debug' mode.")
		ADD_COMPILE_OPTIONS(/D_DEBUG_ /D_ENABLE_ASSERT_ /D_ENABLE_ABORT_IF_ /D_ENABLE_LOG_ /D_ENABLE_EXIT_)
		ADD_COMPILE_OPTIONS(/Od /Ob0 /Ot /Oy- /MTd	/guard:cf /fp:except /sdl /JMC)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		MESSAGE("Building the project with 'Release With Debug Information' mode.")
		ADD_COMPILE_OPTIONS(/D_RELWITHDEBINFO_ /D_DEBUG_ /D_ENABLE_ASSERT_ /D_ENABLE_ABORT_IF_ /D_ENABLE_LOG_ /D_ENABLE_EXIT_)
		ADD_COMPILE_OPTIONS(/Ox /Ob2 /Ot /Oy- /MT /guard:cf /fp:except /sdl /JMC)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE("Building the project with 'Release' mode.")
		ADD_COMPILE_OPTIONS(/D_RELEASE_)
		ADD_COMPILE_OPTIONS(/Ox /Ob2 /Ot /Oy /MT)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
		MESSAGE("Building the project with 'Minimally Sized Release' mode.")
		ADD_COMPILE_OPTIONS(/D_RELEASE_ /D_MINSIZEREL_)
		ADD_COMPILE_OPTIONS(/Ox /Ob2 /Os /Oy /MT)

	ELSE()
		MESSAGE(FATAL_ERROR "Something went wrong with the build mode selection.")
	ENDIF()


	ADD_LINK_OPTIONS(/MACHINE:X64 /INCREMENTAL:NO /LTCG /PROFILE )


	IF(DEFINED AVX2)
		ADD_COMPILE_OPTIONS(/arch:AVX2)
		MESSAGE("AVX-2 has been selected.")

	ELSEIF(DEFINED AVX512)
		ADD_COMPILE_OPTIONS(/arch:AVX512)
		MESSAGE("AVX-512 has been selected.")

	ELSE()
		ADD_COMPILE_OPTIONS(/arch:AVX)
		MESSAGE("AVX has been selected.")
	ENDIF()


	IF(CMAKE_CXX_STANDARD EQUAL 17)
		ADD_COMPILE_OPTIONS(/std:c++17)
		MESSAGE("C++17 has been selected.")

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 20)
		ADD_COMPILE_OPTIONS(/std:c++20)
		MESSAGE("C++20 has been selected.")

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 23)
		ADD_COMPILE_OPTIONS(/std:c++23)
		MESSAGE("C++23 has been selected.")
	ENDIF()


ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")
	ADD_COMPILE_OPTIONS(-D_LINUX_X86_64_)
	MESSAGE("CMake detected a C++ compiler at: ${CMAKE_CXX_COMPILER}")
	STRING(FIND "${CMAKE_CXX_COMPILER}" "clang" CLANG_COMPILER)
	STRING(FIND "${CMAKE_CXX_COMPILER}" "g" GCC_COMPILER)

    IF(CLANG_COMPILER GREATER -1)
		ADD_COMPILE_OPTIONS(-D_CLANG_=1)
		MESSAGE("The detected C++ compiler is clang++")
    ELSEIF(GCC_COMPILER GREATER -1)
	 	ADD_COMPILE_OPTIONS(-D_GNUC_=1)
		MESSAGE("The detected C++ compiler is g++")
    ELSE()
        MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C++ compilers nor Clang C++ compilers")
    ENDIF()
	

	IF(DEFINED LEAVE_OUT_ALL_EXCEPTIONS)
		MESSAGE("Enabled the option: LEAVE_OUT_ALL_EXCEPTIONS")
		ADD_COMPILE_OPTIONS(-D_HAS_EXCEPTIONS=0 -DBOOST_NO_EXCEPTIONS)
	ENDIF()

	IF(DEFINED ENABLE_MEMORY_TRACKER)
		MESSAGE("Enabled the option: ENABLE_MEMORY_TRACKER")
		ADD_COMPILE_OPTIONS(-D_ENABLE_MEMORY_TRACKER_)
	ENDIF()

	IF(DEFINED MEMORY_POOL_FE_STRINGS)
		MESSAGE("Enabled the option: MEMORY_POOL_FE_STRINGS")
		ADD_COMPILE_OPTIONS(-D_MEMORY_POOL_FE_STRINGS_)
	ENDIF()

	IF(DEFINED MEMORY_POOL_FE_SMART_PTR_PROPERTIES)
		MESSAGE("Enabled the option: MEMORY_POOL_FE_SMART_PTR_PROPERTIES")
		ADD_COMPILE_OPTIONS(-D_MEMORY_POOL_FE_UNIQUE_PTR_PROPERTIES_ -D_MEMORY_POOL_FE_EXCLUSIVE_PTR_PROPERTIES_)
	ENDIF()


    # Common Compile Options
	ADD_COMPILE_OPTIONS(-Wall -Wextra -march=x86-64 -Wno-unknown-pragmas)

	
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		MESSAGE("Building the project with 'Debug' mode.")
		ADD_COMPILE_OPTIONS(-D_DEBUG_ -D_ENABLE_ASSERT_ -D_ENABLE_ABORT_IF_ -D_ENABLE_LOG_ -D_ENABLE_EXIT_)
		ADD_COMPILE_OPTIONS(-g  -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -O0)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		MESSAGE("Building the project with 'Release With Debug Information' mode.")
		ADD_COMPILE_OPTIONS(-D_RELWITHDEBINFO_ -D_DEBUG_ -D_ENABLE_ASSERT_ -D_ENABLE_ABORT_IF_ -D_ENABLE_LOG_ -D_ENABLE_EXIT_)
		ADD_COMPILE_OPTIONS(-finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE("Building the project with 'Release' mode.")
		ADD_COMPILE_OPTIONS(-D_RELEASE_)
		ADD_COMPILE_OPTIONS(-finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)

	ELSEIF(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
		MESSAGE("Building the project with 'Minimally Sized Release' mode.")
		ADD_COMPILE_OPTIONS(-D_RELEASE_ -D_MINSIZEREL_)
		ADD_COMPILE_OPTIONS(-finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)
		
	ELSE()
		MESSAGE(FATAL_ERROR "Something went wrong with the build mode selection.")
	ENDIF()
	

	ADD_LINK_OPTIONS(-ldl -pthread)


	IF(DEFINED AVX2)
		ADD_COMPILE_OPTIONS(-mavx2 -D_AVX2_=1)
		MESSAGE("AVX-2 has been selected.")

	ELSEIF(DEFINED AVX512)
		ADD_COMPILE_OPTIONS(-mavx512 -D_AVX512_=1)
		MESSAGE("AVX-512 has been selected.")

	ELSE()
		ADD_COMPILE_OPTIONS(-mavx -D_AVX_=1)
		MESSAGE("AVX has been selected.")

	ENDIF()


	IF(CMAKE_CXX_STANDARD EQUAL 17)
		ADD_COMPILE_OPTIONS(-std=c++17)
		MESSAGE("C++17 has been selected.")

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 20)
		ADD_COMPILE_OPTIONS(-std=c++20)
		MESSAGE("C++20 has been selected.")

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 23)
		ADD_COMPILE_OPTIONS(-std=c++23)
		MESSAGE("C++23 has been selected.")
	ENDIF()

ELSE()
MESSAGE(FATAL_ERROR "System not selected")
ENDIF()