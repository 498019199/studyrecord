#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

//---------------------------------------------------------------------------------------
// Simple d3d error checker for book demos.
//---------------------------------------------------------------------------------------
// Throw error message
std::string RenderWorker::CombineFileLine(std::string_view file, uint32_t line);
#define TMSG(msg) throw std::runtime_error(msg)

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef TIFHR
	#define TIFHR(hr)                                              \
	{                                                          \
		if ((hr) < 0)                                          \
		{                                                      \
			TMSG(CombineFileLine(__FILE__, __LINE__)); \
		}                                                      \
	}
	#endif
#else
	#ifndef TIFHR
	#define TIFHR(hr) (hr)
	#endif
#endif 
