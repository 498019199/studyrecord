#pragma once
#include <core/Texture.h>
#include <core/common.h>

#include "D3D11Util.h"

namespace RenderWorker
{
class D3D11Texture: public Texture
{
public:
    D3D11Texture(TextureType type, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint);

    ID3D11Resource* D3DResource() const noexcept;
    void DeleteHWResource() override;
    bool HWResourceReady() const override;
    
protected:
    void GetD3DFlags(D3D11_USAGE& usage, UINT& bind_flags, UINT& cpu_access_flags, UINT& misc_flags);

protected:
    ID3D11Device*				d3d_device_;
    ID3D11DeviceContext*		d3d_imm_ctx_;
    DXGI_FORMAT dxgi_fmt_;

    ID3D11ResourcePtr d3d_texture_;
};


class D3D11Texture2D final : public D3D11Texture
{
public:
    D3D11Texture2D(uint32_t width, uint32_t height, uint32_t numMipMaps, uint32_t array_size, ElementFormat format, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint);
    explicit D3D11Texture2D(ID3D11Texture2DPtr const & d3d_tex);

    void CreateHWResource(std::span<ElementInitData const> init_data, float4 const * clear_value_hint) override;

private:
    uint32_t width_;
    uint32_t height_;
};
}