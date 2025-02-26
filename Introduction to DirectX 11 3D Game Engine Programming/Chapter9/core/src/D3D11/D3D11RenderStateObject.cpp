#include "D3D11RenderStateObject.h"
#include "D3D11RenderEngine.h"

#include <core/Context.h>

namespace RenderWorker
{
D3D11SamplerStateObject::D3D11SamplerStateObject(SamplerStateDesc const & desc)
    : SamplerStateObject(desc)
{
    const auto& d3d11_re = checked_cast<const D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    ID3D11Device* d3d_device = d3d11_re.D3DDevice();

    D3D11_SAMPLER_DESC d3d_desc;
    d3d_desc.Filter = D3D11Mapping::Mapping(desc.filter);
    d3d_desc.AddressU = D3D11Mapping::Mapping(desc.addr_mode_u);
    d3d_desc.AddressV = D3D11Mapping::Mapping(desc.addr_mode_v);
    d3d_desc.AddressW = D3D11Mapping::Mapping(desc.addr_mode_w);
    d3d_desc.MipLODBias = desc.mip_map_lod_bias;
    d3d_desc.MaxAnisotropy = desc.max_anisotropy;
    d3d_desc.ComparisonFunc = D3D11Mapping::Mapping(desc.cmp_func);
    d3d_desc.BorderColor[0] = desc.border_clr.r();
    d3d_desc.BorderColor[1] = desc.border_clr.g();
    d3d_desc.BorderColor[2] = desc.border_clr.b();
    d3d_desc.BorderColor[3] = desc.border_clr.a();
    d3d_desc.MinLOD = desc.min_lod;
    d3d_desc.MaxLOD = desc.max_lod;

    TIFHR(d3d_device->CreateSamplerState(&d3d_desc, sampler_state_.put()));
}

D3D11RenderStateObject::D3D11RenderStateObject(RasterizerStateDesc const & rs_desc, DepthStencilStateDesc const & dss_desc,BlendStateDesc const & bs_desc)
    : RenderStateObject(rs_desc, dss_desc, bs_desc)
{
    auto& re = checked_cast<D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    ID3D11Device* d3d_device = re.D3DDevice();

    // 光栅化状态描述
    D3D11_RASTERIZER_DESC d3d_rs_desc;
    d3d_rs_desc.FillMode = D3D11Mapping::Mapping(rs_desc.polygon_mode);             // 填充模式
    d3d_rs_desc.CullMode = D3D11Mapping::Mapping(rs_desc.cull_mode);                // 裁剪模式
    d3d_rs_desc.FrontCounterClockwise = rs_desc.front_face_ccw;                     // 是否三角形顶点按逆时针排布时为正面
    d3d_rs_desc.DepthBias = static_cast<int>(rs_desc.polygon_offset_units);         // 深度偏移相关，目前忽略
    d3d_rs_desc.DepthBiasClamp = rs_desc.polygon_offset_units;                      // 深度偏移相关，目前忽略
    d3d_rs_desc.SlopeScaledDepthBias = rs_desc.polygon_offset_factor;               // 深度偏移相关，目前忽略
    d3d_rs_desc.DepthClipEnable = rs_desc.depth_clip_enable;                        // 是否允许深度测试将范围外的像素进行裁剪，默认TRUE
    d3d_rs_desc.ScissorEnable = rs_desc.scissor_enable;                             // 是否允许指定矩形范围的裁剪，若TRUE，则需要在RSSetScissor设置像素保留的矩形区域
    d3d_rs_desc.MultisampleEnable = rs_desc.multisample_enable;                     // 是否允许多重采样
    d3d_rs_desc.AntialiasedLineEnable = false;                                      // 是否允许反走样线，仅当多重采样为FALSE时才有效
    //d3d_rs_desc.ForcedSampleCount = 0; // TODO: Add support to forced sample count
    TIFHR(d3d_device->CreateRasterizerState(&d3d_rs_desc, rasterizer_state_.put()));
}

void D3D11RenderStateObject::Active()
{
    auto& d3d11_re = checked_cast<D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    d3d11_re.RSSetState(rasterizer_state_.get());
    //d3d11_re.OMSetBlendState(blend_state_.get(), bs_desc_.blend_factor, bs_desc_.sample_mask);
}



}