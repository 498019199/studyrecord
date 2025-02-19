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

D3D11RenderStateObject(const RasterizerStateDesc& rs_desc, const DepthStencilStateDesc& dss_desc, const BlendStateDesc& bs_desc)
    :RenderStateObject(rs_desc, dss_desc, bs_desc)
{
    const auto& d3d11_re = checked_cast<const D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    ID3D11Device* d3d_device = d3d11_re.D3DDevice();

    D3D11_BLEND_DESC d3d_bs_desc;
    for(int i = 0; i < 8; ++i)
    {
        
    }
}

void D3D11RenderStateObject::Active()
{
    auto& d3d11_re = checked_cast<D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    d3d11_re.RSSetState(rasterizer_state_.get());
    //d3d11_re.OMSetBlendState(blend_state_.get(), bs_desc_.blend_factor, bs_desc_.sample_mask);
}
}