#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	// Shut min/max in windows.h
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#undef max
	#undef min
#endif
