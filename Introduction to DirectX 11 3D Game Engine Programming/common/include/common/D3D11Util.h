
#pragma once

#if defined(DEBUG) || defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif


#include <d3dx11.h>
//#include <xnamath.h>
#include <xnamath.h>
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
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr_debug = (x);                                      \
		if ((hr_debug) < 0)                                          \
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

#define GET_FUNCTION(mod, func_type, func_name) reinterpret_cast<func_type>(GetProcAddress(static_cast<HMODULE>(mod), func_name));

// #define XMGLOBALCONST extern CONST __declspec(selectany)
//   1. extern so there is only one copy of the variable, and not a separate
//      private copy in each .obj.
//   2. __declspec(selectany) so that the compiler does not complain about
//      multiple definitions in a .cpp file (it can pick anyone and discard 
//      the rest because they are constant--all the same).

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};

	XMGLOBALCONST XMVECTORF32 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = {0.69f, 0.77f, 0.87f, 1.0f};
}

std::string& Convert(std::string& dest, std::wstring_view src);
std::wstring& Convert(std::wstring& dest, std::string_view src);