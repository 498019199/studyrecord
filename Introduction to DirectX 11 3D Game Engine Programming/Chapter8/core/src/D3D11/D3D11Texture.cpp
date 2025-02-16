#include <core/D3D11Texture.h>
#include <core/Context.h>
#include <core/ElementFormat.h>
#include <core/D3D11RenderEngine.h>

D3D11Texture::D3D11Texture(TextureType type, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint)
{
    if (access_hint & EAH_GPU_Write)
    {
        COMMON_ASSERT(!(access_hint & EAH_CPU_Read));
        COMMON_ASSERT(!(access_hint & EAH_CPU_Write));
    }

    const auto& re = Context::Instance().RenderEngineInstance();
    d3d_device_ = re.D3DDevice();
    d3d_imm_ctx_ = re.D3DDeviceImmContext();
}

// ID3D11Resource* D3D11Texture::D3DResource() const noexcept
// {
//     return d3d_texture_.get();
// }

// void D3D11Texture::DeleteHWResource()
// {
//     d3d_texture_.reset();
// }

// bool D3D11Texture::HWResourceReady() const 
// {
//     return d3d_texture_.get() ? true : false;
// }