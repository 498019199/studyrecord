#pragma once
#include <render/RenderFactory.h>

namespace RenderWorker
{

class D3D11RenderFactory: public RenderFactory
{
public:
    D3D11RenderFactory();

    RenderLayoutPtr MakeRenderLayout() override;
    ShaderObjectPtr MakeShaderObject() override;
    ShaderStageObjectPtr MakeShaderStageObject(ShaderStage stage) override;

    GraphicsBufferPtr MakeVertexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) override;
    GraphicsBufferPtr MakeIndexBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) override;
    GraphicsBufferPtr MakeConstantBuffer(BufferUsage usage, uint32_t access_hint, uint32_t size_in_byte, void const * init_data,
        uint32_t structure_byte_stride = 0) override;

private:
	D3D11RenderFactory(D3D11RenderFactory const & rhs);
	D3D11RenderFactory& operator=(D3D11RenderFactory const & rhs);
};
}
