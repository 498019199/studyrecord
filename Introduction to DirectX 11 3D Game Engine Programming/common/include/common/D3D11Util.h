
#pragma once

#if defined(DEBUG) || defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif


#include <d3d11_4.h>
#include <dxgi1_6.h>
//#include <xnamath.h>
//#include <dxerr.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <vector>


//---------------------------------------------------------------------------------------
// Simple d3d error checker for book demos.
//---------------------------------------------------------------------------------------
// Throw error message
std::string CombineFileLine(std::string_view file, uint32_t line);
#define TMSG(msg) throw std::runtime_error(msg)

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		if ((hr) < 0)                                          \
		{                                                      \
			TMSG(CombineFileLine(__FILE__, __LINE__)); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 


//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

//---------------------------------------------------------------------------------------
// Convenience macro for deleting objects.
//---------------------------------------------------------------------------------------

#define SafeDelete(x) { delete x; x = 0; }