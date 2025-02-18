#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	#define ZENGINE_PLATFORM_WINDOWS

	#if defined(_WIN64)
		#define ZENGINE_PLATFORM_WIN64
	#else
		#define ZENGINE_PLATFORM_WIN32
	#endif

	// Shut min/max in windows.h
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#undef max
	#undef min

	#ifndef _WIN32_WINNT_WIN7
		#define _WIN32_WINNT_WIN7 0x0601
	#endif
	#ifndef _WIN32_WINNT_WINBLUE
		#define _WIN32_WINNT_WINBLUE 0x0603
	#endif
	#ifndef _WIN32_WINNT_WIN10
		#define _WIN32_WINNT_WIN10 0x0A00
	#endif
#elif defined(__ANDROID__)
	#define ZENGINE_PLATFORM_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__)
	#define ZENGINE_PLATFORM_LINUX
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		#define ZENGINE_PLATFORM_IOS
	#else
		#define ZENGINE_PLATFORM_DARWIN
	#endif
#else
	#error "Unknown platform. The supported target platforms are Windows, Android, Linux, macOS, and iOS."
#endif

#if __cplusplus > 202002L
	// C++23 library features:
	#cmakedefine ZENGINE_CXX23_LIBRARY_TO_UNDERLYING_SUPPORT
	#cmakedefine ZENGINE_CXX23_LIBRARY_UNREACHABLE_SUPPORT
#endif

#if defined(__clang__)
#elif defined(__GNUC__)
#elif defined(_MSC_VER)
	#define ZENGINE_COMPILER_MSVC
	#define ZENGINE_COMPILER_NAME vc

	#if _MSC_VER >= 1930
		#define ZENGINE_COMPILER_VERSION 143
	#elif _MSC_VER >= 1920
		#define ZENGINE_COMPILER_VERSION 142
	#else
		#error "Unsupported compiler version. Please install VS2019 or up."
	#endif

	#if __cplusplus < 201703L
		#error "/std:c++17 must be turned on."
	#endif

	#pragma warning(disable : 4251) // STL classes are not dllexport.
	#pragma warning(disable : 4819) // Allow non-ANSI characters.
#else
	#error "Unknown compiler. Please install vc, g++, or clang."
#endif
