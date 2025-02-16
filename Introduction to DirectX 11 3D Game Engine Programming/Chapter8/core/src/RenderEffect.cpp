#include <core/RenderEffect.h>
#include <core/Context.h>

#include "D3D11/D3D11RenderEngine.h"
#include "D3D11/D3D11RenderFactory.h"
#include "D3D11/D3D11Util.h"

namespace RenderWorker
{
RenderEffect::RenderEffect()
{
    if (!immutable_)
    {
        immutable_ = MakeSharedPtr<Immutable>();
    }
}

uint32_t RenderEffect::AddShaderDesc(const ShaderDesc& sd)
{
    for (uint32_t i = 0; i < immutable_->shader_descs.size(); ++i)
    {
        if (immutable_->shader_descs[i] == sd)
        {
            return i;
        }
    }

    uint32_t id = static_cast<uint32_t>(immutable_->shader_descs.size());
    immutable_->shader_descs.push_back(sd);
    return id;
}

ShaderDesc& RenderEffect::GetShaderDesc(uint32_t id) noexcept
{
    COMMON_ASSERT(id < immutable_->shader_descs.size());
    return immutable_->shader_descs[id];
}

ShaderDesc const& RenderEffect::GetShaderDesc(uint32_t id) const noexcept
{
    COMMON_ASSERT(id < immutable_->shader_descs.size());
    return immutable_->shader_descs[id];
}

uint32_t RenderEffect::AddShaderObject()
{
    uint32_t index = static_cast<uint32_t>(shader_objs_.size());
    shader_objs_.push_back(Context::Instance().RenderFactoryInstance().MakeShaderObject());
    return index;
}

void RenderEffect::Load(const std::string& file_path)
{
    if (!immutable_)
    {
        immutable_ = MakeSharedPtr<Immutable>();
    }
    shader_obj_index_ = AddShaderObject();

    auto& rf = Context::Instance().RenderFactoryInstance();
    auto const & shader_obj = this->GetShaderObject();
    for (uint32_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
    {
        if(stage_index >= shader_desc_ids_.size())
        {
            break;
        }
        ShaderDesc& sd = GetShaderDesc(shader_desc_ids_[stage_index]);
        const ShaderStage stage = static_cast<ShaderStage>(stage_index);
        ShaderStageObjectPtr shader_stage;
        if (sd.tech_pass_type == 0xFFFFFFFF)
        {
            shader_stage = rf.MakeShaderStageObject(stage);
        }

        shader_obj->AttachStage(stage, shader_stage);
    }

    for (uint32_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
    {
        ShaderDesc const& sd = GetShaderDesc(shader_desc_ids_[stage_index]);
        if (!sd.func_name.empty())
        {
            ShaderStage const stage = static_cast<ShaderStage>(stage_index);
            shader_obj->Stage(stage)->CreateHwShader(*this, shader_desc_ids_);
        }
    }
}
    
// // 计算最接近且不小于给定值的 16 的倍数
// UINT AlignTo16(UINT value) {
//     return (value + 15) & ~15;
// }
// void RenderEffect::CreateConstant()
// {
//     auto const& re = Context::Instance().RenderEngineInstance();
//     D3D11_RASTERIZER_DESC wireframeDesc;
// 	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
// 	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
// 	wireframeDesc.CullMode = D3D11_CULL_BACK;
// 	wireframeDesc.FrontCounterClockwise = false;
// 	wireframeDesc.DepthClipEnable = true;
//     TIFHR(re.D3DDevice()->CreateRasterizerState(&wireframeDesc, rasterizer_state_.put()));

//     // 设置常量缓冲区描述
//     uint32_t size = AlignTo16(sizeof(VSConstantBuffer));
//     auto& rf = Context::Instance().RenderFactoryInstance();
//     vs_hw_buff_ = rf.MakeConstantBuffer(BU_Dynamic, EAH_CPU_Write, size, nullptr);

//     size = AlignTo16(sizeof(PSConstantBuffer));
//     ps_hw_buff_ = rf.MakeConstantBuffer(BU_Dynamic, EAH_CPU_Write, size, nullptr);
// }

// void RenderEffect::AttackVertexShader(const std::string& filename)
// {
//     // 创建顶点着色器
//     auto const& re = Context::Instance().RenderEngineInstance();
//     TIFHR(CreateShaderFromFile(filename, "VS", "vs_5_0", vertex_blob_.put()));
//     TIFHR(re.D3DDevice()->CreateVertexShader(vertex_blob_->GetBufferPointer(), vertex_blob_->GetBufferSize(), nullptr, vertex_shader_.put()));
// }

// void RenderEffect::AttackPixelShader(const std::string& filename)
// {
//     auto const& re = Context::Instance().RenderEngineInstance();
//     TIFHR(CreateShaderFromFile(filename, "PS", "ps_5_0", pixel_blob_.put()));
//     TIFHR(re.D3DDevice()->CreatePixelShader(pixel_blob_->GetBufferPointer(), pixel_blob_->GetBufferSize(), nullptr, pixel_shader_.put()));
// }

// void RenderEffect::Active() const
// {
//     auto& re = Context::Instance().RenderEngineInstance();
//     re.RSSetState(rasterizer_state_.get());
// }
}