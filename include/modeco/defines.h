// Useful defines

#ifndef _MODECO_DEFINES_H
#define _MODECO_DEFINES_H

#ifdef _WIN32
	#define PLAT_WIN32

	#ifdef _WIN64
		#define PLAT_WIN64
	#endif
#endif

#ifdef __linux__
	#define PLATFORM_LINUX
#endif

// Compiler detection
#ifdef _MSC_VER
	#define CC_MSVC
#endif

#if defined(__GNUC__) && !defined(__clang__)
	#define CC_GCC
#endif

#ifdef __clang__
	#define CC_CLANG
#endif

// Debug flags (vaguely inspired by Neversoft)

#ifdef _DEBUG
	// Enable every existing debug flag on debug builds

	// This debug option enables extended checking of stuff in mcommon.
	// Can also be used in your code if wanted.
	#define DOPT_ASSERT
#endif

// else a developer can #define DOPT_xxx
// before including Mcommon includes.

#endif