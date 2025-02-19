#pragma once

#include <d3d11_1.h>
#include <core/com_ptr.h>
#include <core/macro.h>
#include <core/common.h>

#include <render/ElementFormat.h>
#include <render/RenderLayout.h>
#include <render/Texture.h>
#include <render/ShaderObject.h>
#include <render/RenderStateObject.h>
namespace RenderWorker
{
    using ID3D11DevicePtr = com_ptr<ID3D11Device>;
    using ID3D11DeviceContextPtr = com_ptr<ID3D11DeviceContext>;
    using IDXGISwapChainPtr = com_ptr<IDXGISwapChain>;
    using ID3D11BufferPtr = com_ptr<ID3D11Buffer>;
    using ID3D11InputLayoutPtr = com_ptr<ID3D11InputLayout>;

    using ID3D11VertexShaderPtr = com_ptr<ID3D11VertexShader>;
    using ID3D11PixelShaderPtr = com_ptr<ID3D11PixelShader>;
	using ID3D11ResourcePtr = com_ptr<ID3D11Resource>;
	using ID3D11Texture1DPtr = com_ptr<ID3D11Texture1D>;
	using ID3D11Texture2DPtr = com_ptr<ID3D11Texture2D>;
	using ID3D11Texture3DPtr = com_ptr<ID3D11Texture3D>;
	using ID3D11TextureCubePtr = com_ptr<ID3D11Texture2D>;
    using ID3D11RenderTargetViewPtr = com_ptr<ID3D11RenderTargetView>;
	using ID3D11DepthStencilViewPtr = com_ptr<ID3D11DepthStencilView>;
    using ID3D11InputLayoutPtr = com_ptr<ID3D11InputLayout>;
    using ID3D11SamplerStatePtr = com_ptr<ID3D11SamplerState>;
	using ID3D11ShaderResourceViewPtr = com_ptr<ID3D11ShaderResourceView>;
    using ID3D11RasterizerStatePtr = com_ptr<ID3D11RasterizerState>;
    using ID3D11BlendStatePtr = com_ptr<ID3D11BlendState1>;
    using ID3D11DepthStencilStatePtr = com_ptr<ID3D11DepthStencilState>;
}

//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }



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




namespace RenderWorker
{

class D3D11Mapping final
{
public:
    static DXGI_FORMAT MappingFormat(ElementFormat format);
    static ElementFormat MappingFormat(DXGI_FORMAT d3dfmt);

    static D3D11_FILTER Mapping(TexFilterOp filter);
    static D3D11_TEXTURE_ADDRESS_MODE Mapping(TexAddressingMode mode);
    static D3D11_COMPARISON_FUNC Mapping(CompareFunction func);

    static D3D11_PRIMITIVE_TOPOLOGY Mapping(RenderLayout::topology_type tt);
    static void Mapping(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, uint32_t stream, std::span<const VertexElement> vet,
        RenderLayout::stream_type type, uint32_t freq);
};
}