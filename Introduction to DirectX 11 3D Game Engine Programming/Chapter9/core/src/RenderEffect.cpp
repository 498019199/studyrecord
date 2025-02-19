#include <render/RenderEffect.h>
#include <core/Context.h>

#include "D3D11/D3D11RenderEngine.h"
#include "D3D11/D3D11RenderFactory.h"
#include "D3D11/D3D11Util.h"

#include <core/ResIdentifier.h>
#include <core/JsonDom.h>
#include <core/Hash.h>
#include <filesystem>

namespace RenderWorker
{
RenderEffectConstantBuffer::RenderEffectConstantBuffer(RenderEffect& effect)
{
    
}

void RenderEffectConstantBuffer::Load(const std::string& effect_name)
{
    if (!immutable_)
    {
        immutable_ = MakeSharedPtr<Immutable>();
    }
    immutable_->name = effect_name;
}

void RenderEffectConstantBuffer::Resize(uint32_t size)
{
    buff_.resize(size);
    if (size > 0)
    {
        if (!hw_buff_ || (size > hw_buff_->Size()))
        {
            auto& rf = Context::Instance().RenderFactoryInstance();
            hw_buff_ = rf.MakeConstantBuffer(BU_Dynamic, EAH_CPU_Write, size, nullptr);
        }
    }

    dirty_ = true;
}








// 计算最接近且不小于给定值的 16 的倍数
UINT AlignTo16(UINT value) 
{
    return (value + 15) & ~15;
}

RenderEffect::RenderEffect()
{
    if (!immutable_)
    {
        immutable_ = MakeSharedPtr<Immutable>();
    }
    shader_desc_ids_.fill(0);
}

uint32_t RenderEffect::AddShaderDesc(const std::string& state_name_hash, const ShaderDesc& sd)
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


    ShaderStage stage;
    if ("vertex_shader" == state_name_hash)
    {
        stage = ShaderStage::Vertex;
    }
    else if ("pixel_shader" == state_name_hash)
    {
        stage = ShaderStage::Pixel;
    }
    else if ("geometry_shader" == state_name_hash)
    {
        stage = ShaderStage::Geometry;
    }
    else if ("compute_shader" == state_name_hash)
    {
        stage = ShaderStage::Compute;
    }
    else if ("hull_shader" == state_name_hash)
    {
        stage = ShaderStage::Hull;
    }
    else
    {
        COMMON_ASSERT("domain_shader" == state_name_hash);
        stage = ShaderStage::Domain;
    }

    shader_desc_ids_[std::to_underlying(stage)] = id;
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
    auto& rf = Context::Instance().RenderFactoryInstance();
    shader_objs_.push_back(rf.MakeShaderObject());
    return index;
}

void RenderEffect::Load1(const std::string& effect_name)
{
    std::string path_file = effect_name.data();
    size_t lastIndex = path_file.rfind("\\");
    std::string package_path = path_file.substr(0, lastIndex);
    std::string name = path_file.substr(lastIndex + 1);

    uint64_t const timestamp = std::filesystem::last_write_time(package_path).time_since_epoch().count();
    ResIdentifierPtr effect_res = MakeSharedPtr<ResIdentifier>(
        name, timestamp, MakeSharedPtr<std::ifstream>(path_file.c_str(), std::ios_base::binary));
    if(!effect_res)
    {
        return ;
    }
    auto root_value = LoadJson(*effect_res);
    if (auto const* cbuffer_val = root_value.Member("cbuffer"))
    {

    }
    if (auto const* parameter_val = root_value.Member("parameter"))
    {

    }
    if (auto const* effect_val = root_value.Member("effect"))
    {
        for(auto item : effect_val->ValueObject())
        {
            auto hash = HashValue(item.first);
            const auto& Value = item.second;
            
            if(CtHash("vertex_shader") == hash)
            {

            }
            else if(CtHash("pixel_shader") == hash)
            {

            }
        }
    }

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
        ShaderDesc& sd = GetShaderDesc(shader_desc_ids_[stage_index]);
        const ShaderStage stage = static_cast<ShaderStage>(stage_index);
        ShaderStageObjectPtr shader_stage;
        if (sd.tech_pass_type == 0xFFFFFFFF)
        {
            sd.tech_pass_type = 0;
            shader_stage = rf.MakeShaderStageObject(stage);
        }

        shader_obj->AttachStage(stage, shader_stage);
    }

    for (uint32_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
    {
        ShaderDesc const& sd = GetShaderDesc(shader_desc_ids_[stage_index]);
        if (!sd.func_name.empty())
        {
            const ShaderStage stage = static_cast<ShaderStage>(stage_index);
            auto shader_stage_obj = shader_obj->Stage(stage);
            if(shader_stage_obj)
            {
                shader_stage_obj->CompileShader(*this, shader_desc_ids_);
                shader_stage_obj->CreateHwShader(*this, shader_desc_ids_);
            }
        }
    }

  	shader_obj->LinkShaders(*this);
    auto cbuff1 = cbuffers_.emplace_back(MakeSharedPtr<RenderEffectConstantBuffer>(*this)).get();
    cbuff1->Load("VSConstantBuffer");
    uint32_t size = AlignTo16(sizeof(VSConstantBuffer));
    cbuff1->Resize(size);

    auto cbuff2 = cbuffers_.emplace_back(MakeSharedPtr<RenderEffectConstantBuffer>(*this)).get();
    cbuff2->Load("PSConstantBuffer");
    size = AlignTo16(sizeof(PSConstantBuffer));
    cbuff2->Resize(size);
}

uint32_t RenderEffect::CBuffersNum() const noexcept
{
    return static_cast<uint32_t>(cbuffers_.size());
}

RenderEffectConstantBuffer* RenderEffect::CBufferByName(const std::string& name) const noexcept
{
    for (uint32_t i = 0; i < cbuffers_.size(); ++i)
    {
        if (name == cbuffers_[i]->Name())
        {
            return cbuffers_[i].get();
        }
    }
    return nullptr;
}

RenderEffectConstantBuffer* RenderEffect::CBufferByIndex(uint32_t index) const noexcept
{
    COMMON_ASSERT(index < this->CBuffersNum());
    return cbuffers_[index].get();
}
}