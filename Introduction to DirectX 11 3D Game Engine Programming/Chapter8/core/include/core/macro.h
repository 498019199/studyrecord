#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	// Shut min/max in windows.h
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#undef max
	#undef min
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