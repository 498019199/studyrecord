#pragma once
#include <core/GraphicsBuffer.h>

namespace RenderWorker
{

class RenderFactory
{
public:
    RenderFactory();
    virtual ~RenderFactory() noexcept;

    virtual GraphicsBufferPtr MakeVertexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) = 0;
    virtual GraphicsBufferPtr MakeIndexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) = 0;
    virtual GraphicsBufferPtr MakeConstantBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) = 0;
};
using RenderFactoryPtr = std::shared_ptr<RenderFactory>;
}
