CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


SET(FE_CORE_AVX "FE_CORE_AVX")


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


ADD_LIBRARY(${FE_CORE_AVX} STATIC
	${_THIRD_PARTY_CITY_HASH_}
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
)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	MESSAGE("Configurating The Build Environment for Linux X86-64 Distributions")

	if(GNU_CPP)
		TARGET_COMPILE_OPTIONS(${FE_CORE_AVX} PRIVATE
			$<$<CONFIG:DEBUG>:			-Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0 -march=avx
			$<$<CONFIG:RELWITHDEBINFO>: -Wall -Wextra Og	-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:RELEASE>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:MINSIZEREL>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
		)
	elseif(CLANG_CPP)
		TARGET_COMPILE_OPTIONS(${FE_CORE_AVX} PRIVATE
			$<$<CONFIG:DEBUG>:			-Wall -Wextra -g	-pthread -fno-inline-functions	-fno-unroll-loops	-fno-omit-frame-pointer -fno-exceptions -march=x86-64 -O0 -march=avx
			$<$<CONFIG:RELWITHDEBINFO>: -Wall -Wextra Og	-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:RELEASE>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
			$<$<CONFIG:MINSIZEREL>:		-Wall -Wextra		-pthread -finline-functions		-funroll-loops		-fomit-frame-pointer	-fno-exceptions -march=x86-64 -O3 -march=avx
		)
	endif()


	SET_TARGET_PROPERTIES(${FE_CORE_AVX} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Linux/debug/a
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Linux/release_with_debug_info/a
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Linux/release/a
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/Linux/minimally_sized_release/a
    )


	TARGET_LINK_LIBRARIES(${FE_CORE_AVX} stdc++fs 
		${TBB_LINUX}
		${TBB_MALLOC_LINUX}
		${BOOST_STACKTRACE_LINUX}
	)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE("Configurating The Build Environment for Windows X86-64 Distributions")

	TARGET_COMPILE_OPTIONS(${FE_CORE_AVX} PRIVATE
        $<$<CONFIG:DEBUG>:			/WX- /W4 /MP /Od /Ob2 /Oi /Ot /Oy- /GT /MTd /Gy /arch:AVX>
        $<$<CONFIG:RELWITHDEBINFO>:	/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
        $<$<CONFIG:RELEASE>:		/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
        $<$<CONFIG:MINSIZEREL>:		/WX- /W4 /MP /Ox /Ob2 /Oi /Ot /Oy /GT /MT /Gy /arch:AVX>
    )


	SET_TARGET_PROPERTIES(${FE_CORE_AVX} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Windows/debug/lib
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/Windows/release_with_debug_info/lib
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Windows/release/lib
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/Windows/minimally_sized_release/lib
    )


	TARGET_LINK_LIBRARIES(${FE_CORE_AVX} 
		${TBB_WINDOWS}
		${TBB_MALLOC_WINDOWS}
		${BOOST_STACKTRACE_WINDOWS}
	)




endif()