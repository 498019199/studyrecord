#include <core/Context.h>

#include "D3D11ShaderObject.h"
#include "D3D11RenderFactory.h"
#include "D3D11RenderEngine.h"

namespace RenderWorker
{
D3D11ShaderStageObject::D3D11ShaderStageObject(ShaderStage stage)
    : ShaderStageObject(stage)
{
}

void D3D11ShaderStageObject::CreateHwShader(const RenderEffect& effect, const std::vector<uint32_t>& shader_desc_ids)
{
    if (!shader_code_.empty())
    {
        ShaderDesc const& sd = effect.GetShaderDesc(shader_desc_ids[std::to_underlying(stage_)]);
        is_validate_ = true;
        this->StageSpecificCreateHwShader(effect, shader_desc_ids);
    }
    else
    {
        is_validate_ = false;
        this->ClearHwShader();
    }

    hw_res_ready_ = true;
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

void D3D11VertexShaderStageObject::ClearHwShader()
{
    vertex_shader_.reset();
}

void D3D11VertexShaderStageObject::StageSpecificCreateHwShader(const RenderEffect& effect, const std::vector<uint32_t>&  shader_desc_ids)
{
    auto const& re = checked_cast<D3D11RenderEngine const&>(Context::Instance().RenderEngineInstance());
    auto d3d_device = re.D3DDevice();

    if (FAILED(d3d_device->CreateVertexShader(shader_code_.data(), shader_code_.size(), nullptr, vertex_shader_.put())))
    {
        is_validate_ = false;
    }
}

D3D11PixelShaderStageObject::D3D11PixelShaderStageObject()
    : D3D11ShaderStageObject(ShaderStage::Pixel)
{
    is_available_ = true;
}

void D3D11PixelShaderStageObject::ClearHwShader()
{
    pixel_shader_.reset();
}

void D3D11PixelShaderStageObject::StageSpecificCreateHwShader(const RenderEffect& effect, const std::vector<uint32_t>&  shader_desc_ids)
{
    auto const& re = checked_cast<D3D11RenderEngine const&>(Context::Instance().RenderEngineInstance());
    auto d3d_device = re.D3DDevice();
    if (FAILED(d3d_device->CreatePixelShader(shader_code_.data(), shader_code_.size(), nullptr, pixel_shader_.put())))
    {
        is_validate_ = false;
    }
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