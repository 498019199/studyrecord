#include <core/D3D11RenderFactory.h>
#include <core/Util.h>

GraphicsBufferPtr D3D11RenderFactory::MakeVertexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride)
{
	auto ret = MakeSharedPtr<D3D11GraphicsBuffer>(usage, access_hint, D3D11_BIND_VERTEX_BUFFER, size_in_byte, structure_byte_stride);
    ret->CreateHWResource(init_data);
	return ret;
}

GraphicsBufferPtr D3D11RenderFactory::MakeIndexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride)
{
	auto ret = MakeSharedPtr<D3D11GraphicsBuffer>(usage, access_hint, D3D11_BIND_INDEX_BUFFER, size_in_byte, structure_byte_stride);
    ret->CreateHWResource(init_data);
	return ret;
}

GraphicsBufferPtr D3D11RenderFactory::MakeConstantBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride)
{
	auto ret = MakeSharedPtr<D3D11GraphicsBuffer>(usage, access_hint, D3D11_BIND_CONSTANT_BUFFER, size_in_byte, structure_byte_stride);
    ret->CreateHWResource(init_data);
	return ret;
}
