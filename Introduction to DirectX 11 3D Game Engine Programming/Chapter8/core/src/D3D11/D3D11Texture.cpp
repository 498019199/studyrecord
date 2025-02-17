#include "D3D11Texture.h"
#include <core/Context.h>
#include <render/ElementFormat.h>
#include "D3D11RenderEngine.h"

namespace RenderWorker
{
D3D11Texture::D3D11Texture(TextureType type, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint)
    :Texture(type, sample_count, sample_quality, access_hint)
{
    if (access_hint & EAH_GPU_Write)
    {
        COMMON_ASSERT(!(access_hint & EAH_CPU_Read));
        COMMON_ASSERT(!(access_hint & EAH_CPU_Write));
    }

    const auto& d3d11_re = checked_cast<const D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    d3d_device_ = d3d11_re.D3DDevice();
    d3d_imm_ctx_ = d3d11_re.D3DDeviceImmContext();
}

ID3D11Resource* D3D11Texture::D3DResource() const noexcept
{
    return d3d_texture_.get();
}

void D3D11Texture::DeleteHWResource()
{
    d3d_texture_.reset();
}

bool D3D11Texture::HWResourceReady() const 
{
    return d3d_texture_.get() ? true : false;
}

uint32_t D3D11Texture::Width(uint32_t level) const noexcept 
{
    COMMON_ASSERT(level < mip_maps_num_);
    return 1;
}

uint32_t D3D11Texture::Height(uint32_t level) const noexcept 
{
    COMMON_ASSERT(level < mip_maps_num_);
    return 1;
}

uint32_t D3D11Texture::Depth(uint32_t level) const noexcept 
{
    COMMON_ASSERT(level < mip_maps_num_);
    return 1;
}

void D3D11Texture::GetD3DFlags(D3D11_USAGE& usage, UINT& bind_flags, UINT& cpu_access_flags, UINT& misc_flags)
{
    if (access_hint_ & EAH_Immutable)
    {
        usage = D3D11_USAGE_IMMUTABLE;
    }
    else
    {
        if ((EAH_CPU_Write | EAH_GPU_Read) == access_hint_)
        {
            usage = D3D11_USAGE_DYNAMIC;
        }
        else
        {
            if (EAH_CPU_Write == access_hint_)
            {
                if ((mip_maps_num_ != 1) || (TT_Cube == type_))
                {
                    usage = D3D11_USAGE_STAGING;
                }
                else
                {
                    usage = D3D11_USAGE_DYNAMIC;
                }
            }
            else
            {
                if (!(access_hint_ & EAH_CPU_Read) && !(access_hint_ & EAH_CPU_Write))
                {
                    usage = D3D11_USAGE_DEFAULT;
                }
                else
                {
                    usage = D3D11_USAGE_STAGING;
                }
            }
        }
    }

    bind_flags = 0;
    if ((access_hint_ & EAH_GPU_Read) || (D3D11_USAGE_DYNAMIC == usage))
    {
        bind_flags |= D3D11_BIND_SHADER_RESOURCE;
    }
    if (access_hint_ & EAH_GPU_Write)
    {
        if (IsDepthFormat(format_))
        {
            bind_flags |= D3D11_BIND_DEPTH_STENCIL;
        }
        else
        {
            bind_flags |= D3D11_BIND_RENDER_TARGET;
        }
    }
    if (access_hint_ & EAH_GPU_Unordered)
    {
        bind_flags |= D3D11_BIND_UNORDERED_ACCESS;
    }

    cpu_access_flags = 0;
    if (access_hint_ & EAH_CPU_Read)
    {
        cpu_access_flags |= D3D11_CPU_ACCESS_READ;
    }
    if (access_hint_ & EAH_CPU_Write)
    {
        cpu_access_flags |= D3D11_CPU_ACCESS_WRITE;
    }

    misc_flags = 0;
    if (access_hint_ & EAH_Generate_Mips)
    {
        bind_flags |= D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        misc_flags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
    }
}

uint32_t D3D11Texture2D::Width(uint32_t level) const noexcept 
{
    COMMON_ASSERT(level < mip_maps_num_);
    return std::max(1U, width_ >> level);
}

uint32_t D3D11Texture2D::Height(uint32_t level) const noexcept 
{
    COMMON_ASSERT(level < mip_maps_num_);
    return std::max(1U, height_ >> level);
}



}
