#ifndef _FE_CONFIGURATION_H_
#define _FE_CONFIGURATION_H_
// To enable or disable a certain feature, modify the macro definition to true or false.
// 
// Modifying the macro will not immediately affect your project.
// The binary files e.g. (.lib, .a, .dll, or .so) need to be rebuilt to apply changes that have been made.

#if _USE_CMAKE_MACRO_ == false

// Frogman Engine Memory Tracker generates a memory utilization report over frames at the end of an app process.
// The output file can be visualized as a graph image via Frogman Engine Memory Utilization Analyzer.
// Memory tracking routines involve atomic integral sum and add operations, and its tracking frequency can be dynamically adjusted without recompiling the Engine binary.
// Excluding this feature can improve an app performance.
#define _ENABLE_MEMORY_TRACKER_ true


// FE::exception is designed to replace conventional C++ exception models. 
// It logs recoverable errors and warnings with timestamps to keep track of suspicious app process flows, and it can return early if it is nested inside an if-statement.
// Frogman Engine Exception system can be turned off by assigning "false" to this macro.
#define _ENABLE_EXCEPTION_HISTORY_ true


// FE_ASSERT can be disabled by setting this macro "true" to eliminate error-checking overhead.
// Please NOTE that FE_ASSERT aborts when circumstances are unrecoverable and critical. Therefore, precise debugging should be placed first.
#define _ENABLE_ASSERT_ true
#define _ENABLE_ABORT_IF_ true

#define _ENABLE_EXIT_ true

#endif

#endif 