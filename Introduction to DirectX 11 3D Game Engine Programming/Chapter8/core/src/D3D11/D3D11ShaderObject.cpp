#include "D3D11ShaderObject.h"

namespace RenderWorker
{
D3D11ShaderStageObject::D3D11ShaderStageObject(ShaderStage stage)
    : ShaderStageObject(stage)
{
}

std::span<uint8_t const> D3D11ShaderStageObject::ShaderCodeBlob() const
{
    return MakeSpan(shader_code_);
}

D3D11VertexShaderStageObject::D3D11VertexShaderStageObject()
    : D3D11ShaderStageObject(ShaderStage::Vertex)
{
    is_available_ = true;
}

D3D11PixelShaderStageObject::D3D11PixelShaderStageObject()
    : D3D11ShaderStageObject(ShaderStage::Pixel)
{
    is_available_ = true;
}




D3D11ShaderObject::D3D11ShaderObject()
    : D3D11ShaderObject(MakeSharedPtr<Immutable>(), MakeSharedPtr<D3D11Immutable>())
{
}

D3D11ShaderObject::D3D11ShaderObject(std::shared_ptr<Immutable> immutable, std::shared_ptr<D3D11Immutable> d3d_immutable) noexcept
    :ShaderObject(std::move(immutable)), d3d_immutable_(std::move(d3d_immutable))
{
    
}

std::span<uint8_t const> D3D11ShaderObject::VsCode() const
{
    return checked_cast<D3D11ShaderStageObject&>(*this->Stage(ShaderStage::Vertex)).ShaderCodeBlob();
}

uint32_t D3D11ShaderObject::VsSignature() const noexcept
{
    return checked_cast<D3D11VertexShaderStageObject&>(*this->Stage(ShaderStage::Vertex)).VsSignature();
}

void D3D11ShaderObject::DoLinkShaders(RenderEffect& effect)
{
    
}

}