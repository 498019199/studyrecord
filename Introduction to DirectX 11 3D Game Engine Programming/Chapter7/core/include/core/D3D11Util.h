#pragma once

#if defined(DEBUG) || defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif

#include <core/macro.h>
#include <core/common.h>
#include <core/ElementFormat.h>
#include <core/D3D11RenderLayout.h>

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



//
// 着色器编译相关函数
//
HRESULT CreateShaderFromFile(
	const std::string& filename,
    LPCSTR entryPoint,
    LPCSTR shaderModel,
    ID3DBlob** ppBlobOut);
// ------------------------------
// CreateShaderFromFile函数
// ------------------------------
// [In]csoFileNameInOut 编译好的着色器二进制文件(.cso)，若有指定则优先寻找该文件并读取
// [In]hlslFileName     着色器代码，若未找到着色器二进制文件则编译着色器代码
// [In]entryPoint       入口点(指定开始的函数)
// [In]shaderModel      着色器模型，格式为"*s_5_0"，*可以为c,d,g,h,p,v之一
// [Out]ppBlobOut       输出着色器二进制信息
HRESULT CreateShaderFromFile(
    const WCHAR* csoFileNameInOut,
    const WCHAR* hlslFileName,
    LPCSTR entryPoint,
    LPCSTR shaderModel,
    ID3DBlob** ppBlobOut);

class D3D11Mapping final
{
public:
    static DXGI_FORMAT MappingFormat(ElementFormat format);
    static ElementFormat MappingFormat(DXGI_FORMAT d3dfmt);

    static D3D11_PRIMITIVE_TOPOLOGY Mapping(D3D11RenderLayout::topology_type tt);
    static void Mapping(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, uint32_t stream, std::span<const VertexElement> vet,
        D3D11RenderLayout::stream_type type, uint32_t freq);
};