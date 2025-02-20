#include <core/Context.h>

#include "D3D11ShaderObject.h"
#include "D3D11RenderFactory.h"
#include "D3D11GraphicsBuffer.h"
#include "D3D11RenderEngine.h"
#include "D3D11RenderStateObject.h"
#include "D3D11RenderView.h"

namespace
{
using namespace RenderWorker;

class D3D11ShaderParameterSrvUpdater final
{
public:
    D3D11ShaderParameterSrvUpdater(
        std::tuple<void*, uint32_t, uint32_t>& srvsrc, ID3D11ShaderResourceView*& srv, RenderEffectParameter const& param)
        : srvsrc_(srvsrc), srv_(srv), param_(param)
    {
    }

    void operator()()
    {
        ShaderResourceViewPtr srv;
        param_.Value(srv);
        if (srv)
        {
            if (srv->TextureResource())
            {
                srvsrc_ = std::make_tuple(srv->TextureResource().get(),
                    srv->FirstArrayIndex() * srv->TextureResource()->MipMapsNum() + srv->FirstLevel(),
                    srv->ArraySize() * srv->NumLevels());
            }
            else
            {
                COMMON_ASSERT(srv->BufferResource());
                srvsrc_ = std::make_tuple(srv->BufferResource().get(), 0, 1);
            }

            srv_ = checked_cast<D3D11ShaderResourceView&>(*srv).RetrieveD3DShaderResourceView();
        }
        else
        {
            std::get<0>(srvsrc_) = nullptr;
            srv_ = nullptr;
        }
    }

private:
    std::tuple<void*, uint32_t, uint32_t>& srvsrc_;
    ID3D11ShaderResourceView*& srv_;
    RenderEffectParameter const& param_;
};
}

namespace RenderWorker
{
D3D11ShaderStageObject::D3D11ShaderStageObject(ShaderStage stage)
    : ShaderStageObject(stage)
{
}

void D3D11ShaderStageObject::CompileShader(const RenderEffect& effect, const RenderTechnique& tech, const RenderPass& pass,
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

    for (auto const & pbs : param_binds_)
    {
        for (auto const & pb : pbs)
        {
            pb.update();
        }
    }

    for (size_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
    {
        const ShaderStage stage = static_cast<ShaderStage>(stage_index);
        const auto* shader_stage = checked_cast<D3D11ShaderStageObject*>(this->Stage(static_cast<ShaderStage>(stage)).get());
        if (!shader_stage)
        {
            continue;
        }

        if (!srvs_[stage_index].empty())
        {
            // 绑定着色器资源
            re.SetShaderResources(stage, srvsrcs_[stage_index], srvs_[stage_index]);
        }

        if (!d3d_immutable_->samplers_[stage_index].empty())
        {
            // 绑定取样器
            re.SetSamplers(stage, d3d_immutable_->samplers_[stage_index]);
        }

        auto const& cbuff_indices = shader_stage->CBufferIndices();
        if(cbuff_indices.empty())
        {
            continue;
        }
        ID3D11Buffer* d3d11_cbuffs[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        for (uint32_t i = 0; i < cbuff_indices.size(); ++i)
        {
            // 刷新常量
            auto* cb = effect.CBufferByIndex(cbuff_indices[i]);
            cb->Update();
            d3d11_cbuffs[i] = checked_cast<D3D11GraphicsBuffer*>(cb->HWBuff().get())->D3DBuffer();
        }

        re.SetConstantBuffers(stage, MakeSpan(d3d11_cbuffs, cbuff_indices.size()));
    }
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

        auto const& shader_desc = shader_stage->GetD3D11ShaderDesc();
        d3d_immutable_->samplers_[stage].resize(shader_desc.num_samplers);
        srvsrcs_[stage].resize(shader_desc.num_srvs, std::make_tuple(static_cast<void*>(nullptr), 0, 0));
        srvs_[stage].resize(shader_desc.num_srvs);

        for (size_t i = 0; i < shader_desc.res_desc.size(); ++i)
        {
            RenderEffectParameter* p = effect.ParameterByName(shader_desc.res_desc[i].name);
            COMMON_ASSERT(p);

            uint32_t offset = shader_desc.res_desc[i].bind_point;
            if (D3D_SIT_SAMPLER == shader_desc.res_desc[i].type)
            {
                SamplerStateObjectPtr sampler;
                p->Value(sampler);
                if (sampler)
                {
                    // 获取取样器
                    d3d_immutable_->samplers_[stage][offset] = checked_cast<D3D11SamplerStateObject&>(*sampler).D3DSamplerState();
                }
            }
            else
            {
                // 获取着色器资源
                param_binds_[stage].push_back(GetBindFunc(static_cast<ShaderStage>(stage), offset, *p));
            }
        }
    }
}

D3D11ShaderObject::ParameterBind D3D11ShaderObject::GetBindFunc(ShaderStage stage, uint32_t offset, RenderEffectParameter const& param)
{
    uint32_t const stage_index = std::to_underlying(stage);

    ParameterBind ret;
    ret.param = &param;
    ret.offset = offset;

    switch (param.Type())
    {
    case REDT_bool:
    case REDT_uint:
    case REDT_int:
    case REDT_float:
    case REDT_uint2:
    case REDT_uint3:
    case REDT_uint4:
    case REDT_int2:
    case REDT_int3:
    case REDT_int4:
    case REDT_float2:
    case REDT_float3:
    case REDT_float4:
    case REDT_float4x4:
    case REDT_sampler:
        break;

    case REDT_texture1D:
    case REDT_texture2D:
    case REDT_texture2DMS:
    case REDT_texture3D:
    case REDT_textureCUBE:
    case REDT_texture1DArray:
    case REDT_texture2DArray:
    case REDT_texture2DMSArray:
    case REDT_texture3DArray:
    case REDT_textureCUBEArray:
    case REDT_buffer:
    case REDT_structured_buffer:
    case REDT_consume_structured_buffer:
    case REDT_append_structured_buffer:
    case REDT_byte_address_buffer:
        ret.update = D3D11ShaderParameterSrvUpdater(srvsrcs_[stage_index][offset], srvs_[stage_index][offset], param);
        break;

    case REDT_rw_texture1D:
    case REDT_rw_texture2D:
    case REDT_rw_texture3D:
    case REDT_rw_texture1DArray:
    case REDT_rw_texture2DArray:
    case REDT_rasterizer_ordered_texture1D:
    case REDT_rasterizer_ordered_texture1DArray:
    case REDT_rasterizer_ordered_texture2D:
    case REDT_rasterizer_ordered_texture2DArray:
    case REDT_rasterizer_ordered_texture3D:
    case REDT_rw_buffer:
    case REDT_rw_structured_buffer:
    case REDT_rw_byte_address_buffer:
    case REDT_rasterizer_ordered_buffer:
    case REDT_rasterizer_ordered_structured_buffer:
    case REDT_rasterizer_ordered_byte_address_buffer:
        //ret.update = D3D11ShaderParameterUavUpdater(uavsrcs_[offset], uavs_[offset], uav_init_counts_[offset], param);
        break;

    default:
        KFL_UNREACHABLE("Invalid type");
    }

    return ret;
}

}