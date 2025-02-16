#pragma once
#include <core/Texture.h>

class D3D11Texture: public Texture
{
public:
    D3D11Texture(TextureType type, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint);

    ID3D11Resource* D3DResource() const noexcept;
    void DeleteHWResource();
    bool HWResourceReady() const;
    
protected:
    ID3D11Device*				d3d_device_;
    ID3D11DeviceContext*		d3d_imm_ctx_;
    DXGI_FORMAT dxgi_fmt_;

    //ID3D11ResourcePtr d3d_texture_;
};


