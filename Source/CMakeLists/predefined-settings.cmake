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


IF(DEFINED LEAVE_OUT_ALL_EXCEPTIONS)
	ADD_COMPILE_DEFINITIONS(_HAS_EXCEPTIONS=0 BOOST_NO_EXCEPTIONS)
	MESSAGE("Enabled the option: LEAVE_OUT_ALL_EXCEPTIONS")
ENDIF()

IF(DEFINED ENABLE_MEMORY_TRACKER)
	ADD_COMPILE_DEFINITIONS(_ENABLE_MEMORY_TRACKER_)
	MESSAGE("Enabled the option: ENABLE_MEMORY_TRACKER")
ENDIF()

IF(DEFINED MEMORY_POOL_FE_STRINGS)
	ADD_COMPILE_DEFINITIONS(_MEMORY_POOL_FE_STRINGS_)
	MESSAGE("Enabled the option: MEMORY_POOL_FE_STRINGS")
ENDIF()

IF(DEFINED MEMORY_POOL_FE_SMART_PTR_PROPERTIES)
	ADD_COMPILE_DEFINITIONS(_MEMORY_POOL_FE_UNIQUE_PTR_PROPERTIES_ _MEMORY_POOL_FE_EXCLUSIVE_PTR_PROPERTIES_)
	MESSAGE("Enabled the option: MEMORY_POOL_FE_SMART_PTR_PROPERTIES")
ENDIF()


IF(NOT (CMAKE_CXX_STANDARD EQUAL 17 OR CMAKE_CXX_STANDARD EQUAL 20 OR CMAKE_CXX_STANDARD EQUAL 23))
    MESSAGE(FATAL_ERROR "Frogman Engine supports C++ 17, C++ 20, and C++ 23")
ENDIF()


FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR)


IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64")
	ADD_COMPILE_DEFINITIONS(_WINDOWS_X86_64_)
	STRING(REPLACE "\\" "\\\\" OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR "${OS_NATIVE_CMAKE_CURRENT_SOURCE_DIR}")

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
    ADD_COMPILE_OPTIONS(/std:c17 /Zc:__cplusplus /WX /W4 /MP /GF /GT /Gy /GL /Oi /Gr /GR)
	SET(DEBUG_COMPILE_OPTIONS			/Od /Ob0 /Ot /Oy- /MTd	/guard:cf /fp:except /sdl /JMC)
	SET(RELWITHDEBINFO_COMPILE_OPTIONS	/Ox /Ob2 /Ot /Oy- /MT	/guard:cf /fp:except /sdl /JMC)
	SET(RELEASE_COMPILE_OPTIONS			/Ox /Ob2 /Ot /Oy /MT	)
	SET(MINSIZEREL_COMPILE_OPTIONS		/Ox /Ob2 /Os /Oy /MT	)
	

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
	ADD_COMPILE_DEFINITIONS(_LINUX_X86_64_)


    FIND_PROGRAM(CLANG_CXX NAMES clang-18 clang-17 clang-16 clang-15 clang-14 clang-13 clang-12 clang)
    FIND_PROGRAM(GNU_CXX NAMES gcc-14 gcc-13 gcc-12 gcc-11 gcc-10 gcc)


    IF(CLANG_CXX)
        SET(CMAKE_C_COMPILER ${CLANG_CXX})
        SET(CMAKE_CXX_COMPILER ${CLANG_CXX})
		ADD_COMPILE_DEFINITIONS(_CLANG_=1) 
    ELSEIF(GNU_CXX)
		SET(CMAKE_C_COMPILER ${GNU_CXX})
        SET(CMAKE_CXX_COMPILER ${GNU_CXX})
		ADD_COMPILE_DEFINITIONS(_GNUC_=1)
    ELSE()
        MESSAGE(FATAL_ERROR "Could Not Find Any of Executable GNU C compilers nor Clang C compilers")
    ENDIF()
	

    # Common Compile Options
    ADD_COMPILE_OPTIONS(-Wall -Wextra -march=x86-64 -pthread)
    SET(DEBUG_COMPILE_OPTIONS           -g  -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -O0)
    SET(RELWITHDEBINFO_COMPILE_OPTIONS      -finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)
    SET(RELEASE_COMPILE_OPTIONS	            -finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)
    SET(MINSIZEREL_COMPILE_OPTIONS          -finline-functions		-funroll-loops		-fomit-frame-pointer	-O3)
    

	IF(DEFINED AVX2)
		ADD_COMPILE_OPTIONS(-mavx2)
		MESSAGE("AVX-2 has been selected.")
		ADD_COMPILE_DEFINITIONS(_AVX2_=1) 

	ELSEIF(DEFINED AVX512)
		ADD_COMPILE_OPTIONS(-mavx512)
		MESSAGE("AVX-512 has been selected.")
		ADD_COMPILE_DEFINITIONS(_AVX512_=1) 

	ELSE()
		ADD_COMPILE_OPTIONS(-mavx)
		MESSAGE("AVX has been selected.")
		ADD_COMPILE_DEFINITIONS(_AVX_=1)

	ENDIF()


	IF(CMAKE_CXX_STANDARD EQUAL 17)
		ADD_COMPILE_OPTIONS(-std=c++17)
		MESSAGE("C++17 has been selected.")
		ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 20)
		ADD_COMPILE_OPTIONS(-std=c++20)
		MESSAGE("C++20 has been selected.")
		ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)
		ADD_COMPILE_DEFINITIONS(_HAS_CXX20_=1)

	ELSEIF(CMAKE_CXX_STANDARD EQUAL 23)
		ADD_COMPILE_OPTIONS(-std=c++23)
		MESSAGE("C++23 has been selected.")
		ADD_COMPILE_DEFINITIONS(_HAS_CXX17_=1)
		ADD_COMPILE_DEFINITIONS(_HAS_CXX20_=1)
		ADD_COMPILE_DEFINITIONS(_HAS_CXX23_=1)
	ENDIF()


ENDIF()