#pragma once

#include <core/common.h>
#include <core/ElementFormat.h>
#include <core/D3D11Util.h>

enum BufferUsage
{
    BU_Static,
    BU_Dynamic
};

enum BufferAccess
{
    BA_Read_Only,
    BA_Write_Only,
    BA_Read_Write,
    BA_Write_No_Overwrite
};

class D3D11GraphicsBuffer
{
public:
	D3D11GraphicsBuffer(BufferUsage usage, uint32_t access_hint, uint32_t bind_flags,
			uint32_t size_in_byte, uint32_t structure_byte_stride);

    void CreateHWResource(void const * init_data);
    void DeleteHWResource();

    void GetD3DFlags(D3D11_USAGE& usage, UINT& cpu_access_flags, UINT& bind_flags, UINT& misc_flags);

    void* Map(BufferAccess ba);
    void Unmap();

    ID3D11Buffer* D3DBuffer() const
    {
        return d3d_buffer_.get();
    }
    uint32_t Size() const noexcept
    {
        return size_in_byte_;
    }
private:
    BufferUsage usage_;
    uint32_t access_hint_;

    uint32_t size_in_byte_;
    uint32_t structure_byte_stride_;

    ID3D11Device* d3d_device_;
    ID3D11DeviceContext* d3d_imm_ctx_;

    ID3D11BufferPtr d3d_buffer_;
    uint32_t bind_flags_;
};


