#ifndef _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
#define _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


#define _EXIT_LOOP_ goto

#define BEGIN_NAMESPACE(NAME_P) namespace NAME_P {
#define END_NAMESPACE }

#define FORWARD_CLASS_DECLARATION(namespace_p, class_p) namespace namespace_p { class class_p; }
#define FORWARD_STRUCT_DECLARATION(namespace_p, struct_p) namespace namespace_p { struct struct_p; }
#define FORWARD_ENUM_STRUCT_DECLARATION(namespace_p, enum_struct_p) namespace namespace_p { enum struct enum_struct_p; }


#ifdef _MSC_VER
#define _VISUAL_STUDIO_CPP_ 1
#else
#define _VISUAL_STUDIO_CPP_ 0
#endif

#ifdef __clang__
#define _CLANG_ 1
#else
#define _CLANG_ 0
#endif

#ifdef __GNUC__
#define _GNUC_ 1
#else
#define _GNUC_ 0
#endif


#ifdef __x86_64
#define _X64_ 1
#elif defined(_M_X64)
#define _X64_ 1
#elif defined(_M_AMD64)
#define _X64_ 1
#else
#define _X64_ 0
#endif


#if _CLANG_ == 1 && _LINUX_64BIT_OS_ == 1 || _GNUC_ == 1 && _LINUX_64BIT_OS_ == 1
#define _FORCE_INLINE_ inline
#define _STDCALL_ 
#define _FASTCALL_

#elif _VISUAL_STUDIO_CPP_ == 1
#define _FORCE_INLINE_ __forceinline
#define _STDCALL_ __stdcall
#define _FASTCALL_ __fastcall
#endif

#define _CDECL_ __cdecl


#if _HAS_CXX20_ == 1
#define _CONSTEXPR20_ constexpr
#else
#define _CONSTEXPR20_
#endif

#if _HAS_CXX23_ == 1
#define _CONSTEXPR23_ constexpr
#else
#define _CONSTEXPR23_
#endif


#define _LOCK_FREE_ // this function is guaranteed to be lock-free
#define _MAY_USE_LOCKS_  // this function is not guaranteed to be lock-free and may use lock/signal synchronizations
#define _MAYBE_UNSAFE_ // this method maybe unsafe to call concurrently 


#if _VISUAL_STUDIO_CPP_ == 1
#include <vcruntime.h>
#endif


#endif