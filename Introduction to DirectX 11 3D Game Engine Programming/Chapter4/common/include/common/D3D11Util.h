#pragma once

#if defined(DEBUG) || defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif


#include <d3d11.h>
#include <common/macro.h>
#include <math/math.h>
#include <d3dcompiler.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <vector>
using namespace MathWorker;

struct RenderSettings
{
    bool    full_screen = false;
    int		left = 0;
	int		top = 0;

    int		width;
    int		height;

    uint32_t sample_count = 1;
	uint32_t sample_quality = 0;
};

#ifdef _DEBUG
	#define COMMON_ASSERT(val) assert(val)
#else
	#define COMMON_ASSERT(val) 
#endif//_DEBUG



//---------------------------------------------------------------------------------------
// Simple d3d error checker for book demos.
//---------------------------------------------------------------------------------------
// Throw error message
std::string CombineFileLine(std::string_view file, uint32_t line);
#define TMSG(msg) throw std::runtime_error(msg)

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef TIFHR
	#define TIFHR(x)                                              \
	{                                                          \
		HRESULT hr_debug = (x);                                      \
		if ((hr_debug) < 0)                                          \
		{                                                      \
			TMSG(CombineFileLine(__FILE__, __LINE__)); \
		}                                                      \
	}
	#endif
#else
	#ifndef TIFHR
	#define TIFHR(x) (x)
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

#define GET_FUNCTION(mod, func_type, func_name) reinterpret_cast<func_type>(GetProcAddress(static_cast<HMODULE>(mod), func_name));

// #define XMGLOBALCONST extern CONST __declspec(selectany)
//   1. extern so there is only one copy of the variable, and not a separate
//      private copy in each .obj.
//   2. __declspec(selectany) so that the compiler does not complain about
//      multiple definitions in a .cpp file (it can pick anyone and discard 
//      the rest because they are constant--all the same).

std::string& Convert(std::string& dest, std::wstring_view src);
std::wstring& Convert(std::wstring& dest, std::string_view src);