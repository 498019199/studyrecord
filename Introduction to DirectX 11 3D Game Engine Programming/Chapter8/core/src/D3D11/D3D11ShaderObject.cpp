#include <core/Context.h>

#include "D3D11ShaderObject.h"
#include "D3D11RenderFactory.h"
#include "D3D11GraphicsBuffer.h"
#include "D3D11RenderEngine.h"
#include "D3D11RenderStateObject.h"
#include "D3D11RenderView.h"

namespace RenderWorker
{
D3D11ShaderStageObject::D3D11ShaderStageObject(ShaderStage stage)
    : ShaderStageObject(stage)
{
}

void D3D11ShaderStageObject::CompileShader(RenderEffect const& effect,
            const std::array<uint32_t, ShaderStageNum>& shader_desc_ids)
{
    uint32_t const shader_desc_id = shader_desc_ids[std::to_underlying(stage_)];
    const auto& sd = effect.GetShaderDesc(shader_desc_id);

    com_ptr<ID3DBlob> stripped_blob;
    switch(stage_)
    {
        case ShaderStage::Vertex:
            TIFHR(CreateShaderFromFile(sd.profile.c_str(), "VS", "vs_5_0", stripped_blob.put()));
            break;
        case ShaderStage::Pixel:
            TIFHR(CreateShaderFromFile(sd.profile.c_str(), "PS", "ps_5_0", stripped_blob.put()));
            break;
    }
    
    uint8_t const * p = static_cast<uint8_t const *>(stripped_blob->GetBufferPointer());
	shader_code_.assign(p, p + stripped_blob->GetBufferSize());
}

void D3D11ShaderStageObject::CreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids)
{
    if (!shader_code_.empty())
    {
        //const ShaderDesc& sd = effect.GetShaderDesc(shader_desc_ids[std::to_underlying(stage_)]);
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

void D3D11VertexShaderStageObject::StageSpecificCreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids)
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

void D3D11PixelShaderStageObject::StageSpecificCreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids)
{
    const auto& re = checked_cast<D3D11RenderEngine const&>(Context::Instance().RenderEngineInstance());
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

void D3D11ShaderObject::Bind(const RenderEffect& effect)
{
    auto& re = checked_cast<D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());

    auto const& vs_stage = this->Stage(ShaderStage::Vertex);
    re.VSSetShader(vs_stage ? checked_cast<D3D11ShaderStageObject&>(*vs_stage).HwVertexShader() : nullptr);

    auto const& ps_stage = this->Stage(ShaderStage::Pixel);
	re.PSSetShader(ps_stage ? checked_cast<D3D11ShaderStageObject&>(*ps_stage).HwPixelShader() : nullptr);

    for (size_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
    {
        const ShaderStage stage = static_cast<ShaderStage>(stage_index);
        const auto* shader_stage = checked_cast<D3D11ShaderStageObject*>(this->Stage(static_cast<ShaderStage>(stage)).get());
        if (!shader_stage)
        {
            continue;
        }

        //ID3D11Buffer* d3d11_cbuffs[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
    }


    
    
    auto sm = checked_cast<D3D11SamplerStateObject&>(*effect.sm_).D3DSamplerState();
    re.D3DDeviceImmContext()->PSSetSamplers(0, 1, &sm);

    auto d3d_srv = checked_cast<D3D11ShaderResourceView&>(*effect.srv_).RetrieveD3DShaderResourceView();
    re.D3DDeviceImmContext()->PSSetShaderResources(0, 1, &d3d_srv);

    auto* cb1 = effect.CBufferByIndex(0);
    auto d3d11_cbuff_vs = checked_cast<D3D11GraphicsBuffer*>(cb1->HWBuff().get())->D3DBuffer();
    re.D3DDeviceImmContext()->VSSetConstantBuffers(0, 1, &d3d11_cbuff_vs);

    auto* cb2 = effect.CBufferByIndex(1);
    auto d3d11_cbuff_ps = checked_cast<D3D11GraphicsBuffer*>(cb2->HWBuff().get())->D3DBuffer();
    re.D3DDeviceImmContext()->PSSetConstantBuffers(1, 1, &d3d11_cbuff_ps);
}

void D3D11ShaderObject::Unbind()
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
    for (size_t stage = 0; stage < ShaderStageNum; ++stage)
    {
        const auto* shader_stage = checked_cast<D3D11ShaderStageObject*>(this->Stage(static_cast<ShaderStage>(stage)).get());
        if (nullptr == shader_stage)
        {
            continue;
        }
        if (shader_stage->ShaderCodeBlob().empty())
        {
            continue;
        }
    }
}

}