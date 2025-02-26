#pragma once

#include <render/GraphicsBuffer.h>
#include <render/ElementFormat.h>
#include "D3D11Util.h"

namespace RenderWorker
{

class D3D11GraphicsBuffer: public GraphicsBuffer
{
public:
	D3D11GraphicsBuffer(BufferUsage usage, uint32_t access_hint, uint32_t bind_flags,
			uint32_t size_in_byte, uint32_t structure_byte_stride);

    void CreateHWResource(void const * init_data) override;
    void DeleteHWResource() override;
    bool HWResourceReady() const override;

    void UpdateSubresource(uint32_t offset, uint32_t size, void const * data) override;

    void GetD3DFlags(D3D11_USAGE& usage, UINT& cpu_access_flags, UINT& bind_flags, UINT& misc_flags);

    void* Map(BufferAccess ba);
    void Unmap();

    ID3D11Buffer* D3DBuffer() const
    {
        return d3d_buffer_.get();
    }
private:


    ID3D11Device* d3d_device_;
    ID3D11DeviceContext* d3d_imm_ctx_;

    ID3D11BufferPtr d3d_buffer_;
    uint32_t bind_flags_;
};
}
