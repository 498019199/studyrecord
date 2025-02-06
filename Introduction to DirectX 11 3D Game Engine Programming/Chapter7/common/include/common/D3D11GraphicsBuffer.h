#include <common/common.h>
#include <common/ElementFormat.h>
#include <common/D3D11RenderEngine.h>

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
private:

    void GetD3DFlags(D3D11_USAGE& usage, UINT& cpu_access_flags, UINT& bind_flags, UINT& misc_flags);

    void* Map(BufferAccess ba) override;
    void Unmap() override;
private:
    BufferUsage usage_;
    uint32_t access_hint_;

    uint32_t size_in_byte_;
    uint32_t structure_byte_stride_;

    ID3D11Device1* d3d_device_;
    ID3D11DeviceContext1* d3d_imm_ctx_;

    ID3D11BufferPtr d3d_buffer_;
};


