#include "D3D11Util.h"

#include <core/Util.h>

#include <format>
#include <utility>
#include <d3dcompiler.h>

DEFINE_UUID_OF(ID3D11Resource);
DEFINE_UUID_OF(ID3D11Texture2D);

std::string CombineFileLine(std::string_view file, uint32_t line)
{
    return std::format("{}: {}", std::move(file), line);
}



HRESULT CreateShaderFromFile(const std::string& filename,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut)
{
    std::wstring swcFileName;
    Convert(swcFileName, filename);
	std::wstring strOutFile = swcFileName + L".cso";
    std::wstring InputFile = swcFileName + L".hlsl";
    return CreateShaderFromFile(strOutFile.c_str(), InputFile.c_str(), entryPoint, shaderModel, ppBlobOut);
}

HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut,
	const WCHAR* hlslFileName,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    // 寻找是否有已经编译好的顶点着色器
    if (csoFileNameInOut && D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK)
    {
        return hr;
    }
    else
    {
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // 设置 D3DCOMPILE_DEBUG 标志用于获取着色器调试信息。该标志可以提升调试体验，
        // 但仍然允许着色器进行优化操作
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // 在Debug环境下禁用优化以避免出现一些不合理的情况
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
        ID3DBlob* errorBlob = nullptr;
        hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
            dwShaderFlags, 0, ppBlobOut, &errorBlob);
        if (FAILED(hr))
        {
            if (errorBlob != nullptr)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
            }
            ReleaseCOM(errorBlob);
            return hr;
        }

        // 若指定了输出文件名，则将着色器二进制信息输出
        if (csoFileNameInOut)
        {
            return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
        }
    }

    return hr;
}

namespace RenderWorker
{

DXGI_FORMAT D3D11Mapping::MappingFormat(ElementFormat format)
{
    switch (format)
    {
    case EF_A8:
        return DXGI_FORMAT_A8_UNORM;

    case EF_R5G6B5:
        return DXGI_FORMAT_B5G6R5_UNORM;

    case EF_A1RGB5:
        return DXGI_FORMAT_B5G5R5A1_UNORM;

    case EF_ARGB4:
        return DXGI_FORMAT_B4G4R4A4_UNORM;

    case EF_R8:
        return DXGI_FORMAT_R8_UNORM;

    case EF_SIGNED_R8:
        return DXGI_FORMAT_R8_SNORM;

    case EF_GR8:
        return DXGI_FORMAT_R8G8_UNORM;

    case EF_SIGNED_GR8:
        return DXGI_FORMAT_R8G8_SNORM;

    case EF_ARGB8:
        return DXGI_FORMAT_B8G8R8A8_UNORM;

    case EF_ABGR8:
        return DXGI_FORMAT_R8G8B8A8_UNORM;

    case EF_SIGNED_ABGR8:
        return DXGI_FORMAT_R8G8B8A8_SNORM;

    case EF_A2BGR10:
        return DXGI_FORMAT_R10G10B10A2_UNORM;

    case EF_SIGNED_A2BGR10:
        return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

    case EF_R8UI:
        return DXGI_FORMAT_R8_UINT;

    case EF_R8I:
        return DXGI_FORMAT_R8_SINT;

    case EF_GR8UI:
        return DXGI_FORMAT_R8G8_UINT;

    case EF_GR8I:
        return DXGI_FORMAT_R8G8_SINT;

    case EF_ABGR8UI:
        return DXGI_FORMAT_R8G8B8A8_UINT;

    case EF_ABGR8I:
        return DXGI_FORMAT_R8G8B8A8_SINT;

    case EF_A2BGR10UI:
        return DXGI_FORMAT_R10G10B10A2_UINT;

    case EF_R16:
        return DXGI_FORMAT_R16_UNORM;

    case EF_SIGNED_R16:
        return DXGI_FORMAT_R16_SNORM;

    case EF_GR16:
        return DXGI_FORMAT_R16G16_UNORM;

    case EF_SIGNED_GR16:
        return DXGI_FORMAT_R16G16_SNORM;

    case EF_ABGR16:
        return DXGI_FORMAT_R16G16B16A16_UNORM;

    case EF_SIGNED_ABGR16:
        return DXGI_FORMAT_R16G16B16A16_SNORM;

    case EF_R16UI:
        return DXGI_FORMAT_R16_UINT;

    case EF_R16I:
        return DXGI_FORMAT_R16_SINT;

    case EF_GR16UI:
        return DXGI_FORMAT_R16G16_UINT;

    case EF_GR16I:
        return DXGI_FORMAT_R16G16_SINT;

    case EF_ABGR16UI:
        return DXGI_FORMAT_R16G16B16A16_UINT;

    case EF_ABGR16I:
        return DXGI_FORMAT_R16G16B16A16_SINT;

    case EF_R32UI:
        return DXGI_FORMAT_R32_UINT;

    case EF_R32I:
        return DXGI_FORMAT_R32_SINT;

    case EF_GR32UI:
        return DXGI_FORMAT_R32G32_UINT;

    case EF_GR32I:
        return DXGI_FORMAT_R32G32_SINT;

    case EF_BGR32UI:
        return DXGI_FORMAT_R32G32B32_UINT;

    case EF_BGR32I:
        return DXGI_FORMAT_R32G32B32_SINT;

    case EF_ABGR32UI:
        return DXGI_FORMAT_R32G32B32A32_UINT;

    case EF_ABGR32I:
        return DXGI_FORMAT_R32G32B32A32_SINT;

    case EF_R16F:
        return DXGI_FORMAT_R16_FLOAT;

    case EF_GR16F:
        return DXGI_FORMAT_R16G16_FLOAT;

    case EF_B10G11R11F:
        return DXGI_FORMAT_R11G11B10_FLOAT;

    case EF_ABGR16F:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;

    case EF_R32F:
        return DXGI_FORMAT_R32_FLOAT;

    case EF_GR32F:
        return DXGI_FORMAT_R32G32_FLOAT;

    case EF_BGR32F:
        return DXGI_FORMAT_R32G32B32_FLOAT;

    case EF_ABGR32F:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    case EF_BC1:
        return DXGI_FORMAT_BC1_UNORM;

    case EF_BC2:
        return DXGI_FORMAT_BC2_UNORM;

    case EF_BC3:
        return DXGI_FORMAT_BC3_UNORM;

    case EF_BC4:
        return DXGI_FORMAT_BC4_UNORM;

    case EF_SIGNED_BC4:
        return DXGI_FORMAT_BC4_SNORM;

    case EF_BC5:
        return DXGI_FORMAT_BC5_UNORM;

    case EF_SIGNED_BC5:
        return DXGI_FORMAT_BC5_SNORM;

    case EF_BC6:
        return DXGI_FORMAT_BC6H_UF16;

    case EF_SIGNED_BC6:
        return DXGI_FORMAT_BC6H_SF16;

    case EF_BC7:
        return DXGI_FORMAT_BC7_UNORM;

    case EF_D16:
        return DXGI_FORMAT_D16_UNORM;

    case EF_D24S8:
        return DXGI_FORMAT_D24_UNORM_S8_UINT;

    case EF_X24G8:
        return DXGI_FORMAT_X24_TYPELESS_G8_UINT;

    case EF_D32F:
        return DXGI_FORMAT_D32_FLOAT;
        
    case EF_ARGB8_SRGB:
        return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

    case EF_ABGR8_SRGB:
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

    case EF_BC1_SRGB:
        return DXGI_FORMAT_BC1_UNORM_SRGB;

    case EF_BC2_SRGB:
        return DXGI_FORMAT_BC2_UNORM_SRGB;

    case EF_BC3_SRGB:
        return DXGI_FORMAT_BC3_UNORM_SRGB;

    case EF_BC7_SRGB:
        return DXGI_FORMAT_BC7_UNORM_SRGB;

    default:
        KFL_UNREACHABLE("Invalid format");
    }

}

ElementFormat D3D11Mapping::MappingFormat(DXGI_FORMAT format)
{
    switch (format)
    {
    case DXGI_FORMAT_A8_UNORM:
        return EF_A8;

    case DXGI_FORMAT_B5G6R5_UNORM:
        return EF_R5G6B5;

    case DXGI_FORMAT_B5G5R5A1_UNORM:
        return EF_A1RGB5;

    case DXGI_FORMAT_B4G4R4A4_UNORM:
        return EF_ARGB4;

    case DXGI_FORMAT_R8_UNORM:
        return EF_R8;

    case DXGI_FORMAT_R8_SNORM:
        return EF_SIGNED_R8;

    case DXGI_FORMAT_R8G8_UNORM:
        return EF_GR8;

    case DXGI_FORMAT_R8G8_SNORM:
        return EF_SIGNED_GR8;

    case DXGI_FORMAT_B8G8R8A8_UNORM:
        return EF_ARGB8;

    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return EF_ABGR8;

    case DXGI_FORMAT_R8G8B8A8_SNORM:
        return EF_SIGNED_ABGR8;

    case DXGI_FORMAT_R10G10B10A2_UNORM:
        return EF_A2BGR10;

    case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        return EF_SIGNED_A2BGR10;

    case DXGI_FORMAT_R8_UINT:
        return EF_R8UI;

    case DXGI_FORMAT_R8_SINT:
        return EF_R8I;

    case DXGI_FORMAT_R8G8_UINT:
        return EF_GR8UI;

    case DXGI_FORMAT_R8G8_SINT:
        return EF_GR8I;

    case DXGI_FORMAT_R8G8B8A8_UINT:
        return EF_ABGR8UI;

    case DXGI_FORMAT_R8G8B8A8_SINT:
        return EF_ABGR8I;

    case DXGI_FORMAT_R10G10B10A2_UINT:
        return EF_A2BGR10UI;

    case DXGI_FORMAT_R16_UNORM:
        return EF_R16;

    case DXGI_FORMAT_R16_SNORM:
        return EF_SIGNED_R16;

    case DXGI_FORMAT_R16G16_UNORM:
        return EF_GR16;

    case DXGI_FORMAT_R16G16_SNORM:
        return EF_SIGNED_GR16;

    case DXGI_FORMAT_R16G16B16A16_UNORM:
        return EF_ABGR16;

    case DXGI_FORMAT_R16G16B16A16_SNORM:
        return EF_SIGNED_ABGR16;

    case DXGI_FORMAT_R16_UINT:
        return EF_R16UI;

    case DXGI_FORMAT_R16_SINT:
        return EF_R16I;

    case DXGI_FORMAT_R16G16_UINT:
        return EF_GR16UI;

    case DXGI_FORMAT_R16G16_SINT:
        return EF_GR16I;

    case DXGI_FORMAT_R16G16B16A16_UINT:
        return EF_ABGR16UI;

    case DXGI_FORMAT_R16G16B16A16_SINT:
        return EF_ABGR16I;

    case DXGI_FORMAT_R32_UINT:
        return EF_R32UI;

    case DXGI_FORMAT_R32_SINT:
        return EF_R32I;

    case DXGI_FORMAT_R32G32_UINT:
        return EF_GR32UI;

    case DXGI_FORMAT_R32G32_SINT:
        return EF_GR32I;

    case DXGI_FORMAT_R32G32B32_UINT:
        return EF_BGR32UI;

    case DXGI_FORMAT_R32G32B32_SINT:
        return EF_BGR32I;

    case DXGI_FORMAT_R32G32B32A32_UINT:
        return EF_ABGR32UI;

    case DXGI_FORMAT_R32G32B32A32_SINT:
        return EF_ABGR32I;

    case DXGI_FORMAT_R16_FLOAT:
        return EF_R16F;

    case DXGI_FORMAT_R16G16_FLOAT:
        return EF_GR16F;

    case DXGI_FORMAT_R11G11B10_FLOAT:
        return EF_B10G11R11F;

    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return EF_ABGR16F;

    case DXGI_FORMAT_R32_FLOAT:
        return EF_R32F;

    case DXGI_FORMAT_R32G32_FLOAT:
        return EF_GR32F;

    case DXGI_FORMAT_R32G32B32_FLOAT:
        return EF_BGR32F;

    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return EF_ABGR32F;

    case DXGI_FORMAT_BC1_UNORM:
        return EF_BC1;

    case DXGI_FORMAT_BC2_UNORM:
        return EF_BC2;

    case DXGI_FORMAT_BC3_UNORM:
        return EF_BC3;

    case DXGI_FORMAT_BC4_UNORM:
        return EF_BC4;

    case DXGI_FORMAT_BC4_SNORM:
        return EF_SIGNED_BC4;

    case DXGI_FORMAT_BC5_UNORM:
        return EF_BC5;

    case DXGI_FORMAT_BC5_SNORM:
        return EF_SIGNED_BC5;

    case DXGI_FORMAT_BC6H_UF16:
        return EF_BC6;

    case DXGI_FORMAT_BC6H_SF16:
        return EF_SIGNED_BC6;

    case DXGI_FORMAT_BC7_UNORM:
        return EF_BC7;

    case DXGI_FORMAT_D16_UNORM:
        return EF_D16;

    case DXGI_FORMAT_D24_UNORM_S8_UINT:
        return EF_D24S8;

    case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        return EF_X24G8;

    case DXGI_FORMAT_D32_FLOAT:
        return EF_D32F;

    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        return EF_ARGB8_SRGB;

    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        return EF_ABGR8_SRGB;

    case DXGI_FORMAT_BC1_UNORM_SRGB:
        return EF_BC1_SRGB;

    case DXGI_FORMAT_BC2_UNORM_SRGB:
        return EF_BC2_SRGB;

    case DXGI_FORMAT_BC3_UNORM_SRGB:
        return EF_BC3_SRGB;

    case DXGI_FORMAT_BC7_UNORM_SRGB:
        return EF_BC7_SRGB;

    default:
        KFL_UNREACHABLE("Invalid format");
    }
}

D3D11_FILTER D3D11Mapping::Mapping(TexFilterOp filter)
{
	switch (filter)
    {
    case TFO_Min_Mag_Mip_Point:
        return D3D11_FILTER_MIN_MAG_MIP_POINT;

    case TFO_Min_Mag_Point_Mip_Linear:
        return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;

    case TFO_Min_Point_Mag_Linear_Mip_Point:
        return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;

    case TFO_Min_Point_Mag_Mip_Linear:
        return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;

    case TFO_Min_Mag_Linear_Mip_Point:
        return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

    case TFO_Min_Mag_Mip_Linear:
        return D3D11_FILTER_MIN_MAG_MIP_LINEAR;

    case TFO_Anisotropic:
        return D3D11_FILTER_ANISOTROPIC;

    case TFO_Cmp_Min_Mag_Mip_Point:
        return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

    case TFO_Cmp_Min_Mag_Point_Mip_Linear:
        return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;

    case TFO_Cmp_Min_Point_Mag_Linear_Mip_Point:
        return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;

    case TFO_Cmp_Min_Point_Mag_Mip_Linear:
        return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;

    case TFO_Cmp_Min_Mag_Linear_Mip_Point:
        return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;

    case TFO_Cmp_Min_Mag_Mip_Linear:
        return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

    case TFO_Cmp_Anisotropic:
        return D3D11_FILTER_COMPARISON_ANISOTROPIC;

    default:
        KFL_UNREACHABLE("Invalid texture filter operation");
    }
}

D3D11_TEXTURE_ADDRESS_MODE D3D11Mapping::Mapping(TexAddressingMode mode)
{
    switch (mode)
    {
    case TAM_Clamp:
        return D3D11_TEXTURE_ADDRESS_CLAMP;

    case TAM_Wrap:
        return D3D11_TEXTURE_ADDRESS_WRAP;

    case TAM_Mirror:
        return D3D11_TEXTURE_ADDRESS_MIRROR;

    case TAM_Border:
        return D3D11_TEXTURE_ADDRESS_BORDER;

    default:
        KFL_UNREACHABLE("Invalid texture addressing mode");
    }
}

D3D11_COMPARISON_FUNC D3D11Mapping::Mapping(CompareFunction func)
{
    switch (func)
    {
    case CF_AlwaysFail:
        return D3D11_COMPARISON_NEVER;

    case CF_AlwaysPass:
        return D3D11_COMPARISON_ALWAYS;

    case CF_Less:
        return D3D11_COMPARISON_LESS;

    case CF_LessEqual:
        return D3D11_COMPARISON_LESS_EQUAL;

    case CF_Equal:
        return D3D11_COMPARISON_EQUAL;

    case CF_NotEqual:
        return D3D11_COMPARISON_NOT_EQUAL;

    case CF_GreaterEqual:
        return D3D11_COMPARISON_GREATER_EQUAL;

    case CF_Greater:
        return D3D11_COMPARISON_GREATER;

    default:
        KFL_UNREACHABLE("Invalid compare function");
    }
}

void D3D11Mapping::Mapping(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, uint32_t stream, std::span<const VertexElement> vet,
    RenderLayout::stream_type type, uint32_t freq)
{
    elements.resize(vet.size());
    uint16_t elem_offset = 0;

    for (uint32_t i = 0; i < elements.size(); ++ i)
    {
        VertexElement const & vs_elem = vet[i];

			D3D11_INPUT_ELEMENT_DESC& element = elements[i];
			element.SemanticIndex = vs_elem.usage_index;
			element.Format = D3D11Mapping::MappingFormat(vs_elem.format);
			element.InputSlot = static_cast<WORD>(stream);
			element.AlignedByteOffset = elem_offset;
        if (RenderLayout::ST_Geometry == type)
        {
            element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            element.InstanceDataStepRate = 0;
        }
        else
        {
            COMMON_ASSERT(RenderLayout::ST_Instance == type);
            element.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
            element.InstanceDataStepRate = freq;
        }

        switch (vs_elem.usage)
        {
            // Vertex xyzs
        case VEU_Position:
            element.SemanticName = "POSITION";
            break;

            // Normal
        case VEU_Normal:
            element.SemanticName = "NORMAL";
            break;

            // Vertex colors
        case VEU_Diffuse:
            element.SemanticName = "COLOR";
            break;

            // Vertex speculars
        case VEU_Specular:
            element.SemanticName = "COLOR";
            break;

            // Blend Weights
        case VEU_BlendWeight:
            element.SemanticName = "BLENDWEIGHT";
            break;

            // Blend Indices
        case VEU_BlendIndex:
            element.SemanticName = "BLENDINDICES";
            if (EF_ABGR8 == vs_elem.format)
            {
                element.Format = DXGI_FORMAT_R8G8B8A8_UINT;
            }
            break;

            // Do texture coords
        case VEU_TextureCoord:
            element.SemanticName = "TEXCOORD";
            break;

        case VEU_Tangent:
            element.SemanticName = "TANGENT";
            break;

        case VEU_Binormal:
            element.SemanticName = "BINORMAL";
            break;
        }

        elem_offset = static_cast<uint16_t>(elem_offset + vs_elem.element_size());
    }
}

D3D11_PRIMITIVE_TOPOLOGY D3D11Mapping::Mapping(RenderLayout::topology_type tt)
{
    switch (tt)
    {
    case RenderLayout::TT_PointList:
        return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;

    case RenderLayout::TT_LineList:
        return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

    case RenderLayout::TT_LineStrip:
        return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;

    case RenderLayout::TT_TriangleList:
        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    case RenderLayout::TT_TriangleStrip:
        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

    case RenderLayout::TT_LineList_Adj:
        return D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;

    case RenderLayout::TT_LineStrip_Adj:
        return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;

    case RenderLayout::TT_TriangleList_Adj:
        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;

    case RenderLayout::TT_TriangleStrip_Adj:
        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;

    case RenderLayout::TT_1_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_2_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_3_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_4_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_5_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_6_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_7_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_8_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_9_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_10_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_11_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_12_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_13_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_14_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_15_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_16_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_17_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_18_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_19_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_20_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_21_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_22_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_23_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_24_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_25_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_26_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_27_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_28_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_29_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_30_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_31_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST;

    case RenderLayout::TT_32_Ctrl_Pt_PatchList:
        return D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST;

    default:
        KFL_UNREACHABLE("Invalid topology type");
    }
}
}