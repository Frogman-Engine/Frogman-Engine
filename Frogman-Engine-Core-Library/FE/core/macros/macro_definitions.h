#ifndef _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
#define _FE_CORE_MACROS_MACRO_DEFINITIONS_H_
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


#define _EXIT_LOOP_ goto

#define BEGIN_NAMESPACE(NAME_P) namespace NAME_P {
#define END_NAMESPACE }

#define CLASS_FORWARD_DECLARATION(namespace_p, class_p) namespace namespace_p { class class_p; }
#define STRUCT_FORWARD_DECLARATION(namespace_p, struct_p) namespace namespace_p { struct struct_p; }
#define ENUM_STRUCT_FORWARD_DECLARATION(namespace_p, enum_struct_p) namespace namespace_p { enum struct enum_struct_p; }

#define _SOURCE_CODE_LOCATION_ __FILE__, __func__, __LINE__


#ifdef _MSC_VER
#define _VISUAL_STUDIO_CPP_
#endif

#ifdef __clang__
#define _CLANG_ 
#endif

#ifdef __GNUC__
#define _GNUC_ 
#endif


#ifdef __x86_64
#define _X64_ 
#elif defined(_M_X64)
#define _X64_ 
#elif defined(_M_AMD64)
#define _X64_ 
#endif


#if defined(_CLANG_) && defined(_LINUX_64BIT_OS_) || defined(_GNUC_) && defined(_LINUX_64BIT_OS_)
#define _FORCE_INLINE_ inline
#define _STDCALL_ 
#define _FASTCALL_

#elif defined(_VISUAL_STUDIO_CPP_)
#define _FORCE_INLINE_ __forceinline
#define _STDCALL_ __stdcall
#define _FASTCALL_ __fastcall
#endif

#define _CDECL_ __cdecl


#ifdef _HAS_CXX20_
#define _CONSTEXPR20_ constexpr
#else
#define _CONSTEXPR20_
#endif

#ifdef _HAS_CXX23_
#define _CONSTEXPR23_ constexpr
#else
#define _CONSTEXPR23_
#endif


#define _LOCK_FREE_ // this function is guaranteed to be lock-free
#define _MAY_USE_LOCKS_  // this function is not guaranteed to be lock-free and may use lock/signal synchronizations
#define _MAYBE_UNSAFE_ // this method maybe unsafe to call concurrently 


#ifdef _VISUAL_STUDIO_CPP_
#include <vcruntime.h>
#endif


#endif