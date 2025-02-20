#include <render/ShaderObject.h>


namespace RenderWorker
{

bool operator!=(const ShaderDesc::StreamOutputDecl& lhs, const ShaderDesc::StreamOutputDecl& rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator==(const ShaderDesc::StreamOutputDecl& lhs, const ShaderDesc::StreamOutputDecl& rhs) noexcept
{
    return (lhs.usage == rhs.usage) && (lhs.usage_index == rhs.usage_index)
        && (lhs.start_component == rhs.start_component) && (lhs.component_count == rhs.component_count)
        && (lhs.slot == rhs.slot);
}

bool operator!=(const ShaderDesc& lhs, const ShaderDesc& rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator==(const ShaderDesc& lhs, const ShaderDesc& rhs) noexcept
{
    return (lhs.profile == rhs.profile) && (lhs.func_name == rhs.func_name)
        && (lhs.macros_hash == rhs.macros_hash) && (lhs.so_decl == rhs.so_decl);
    
}

ShaderStageObject::ShaderStageObject(ShaderStage stage) noexcept 
    :stage_(stage)
{
}

ShaderStageObject::~ShaderStageObject() noexcept = default;




ShaderObject::ShaderObject()
    : ShaderObject(MakeSharedPtr<ShaderObject::Immutable>())
{
    
}

ShaderObject::ShaderObject(std::shared_ptr<Immutable> immutable) noexcept
    : immutable_(std::move(immutable))
{
}

ShaderObject::~ShaderObject() noexcept = default;

void ShaderObject::AttachStage(ShaderStage stage, const ShaderStageObjectPtr& shader_stage)
{
    auto& curr_shader_stage = immutable_->shader_stages_[std::to_underlying(stage)];
    if (curr_shader_stage != shader_stage)
    {
        curr_shader_stage = shader_stage;
        shader_stages_dirty_ = true;
        hw_res_ready_ = false;
    }
}

const ShaderStageObjectPtr& ShaderObject::Stage(ShaderStage stage) const noexcept
{
    return immutable_->shader_stages_[std::to_underlying(stage)];
}

void ShaderObject::LinkShaders(RenderEffect& effect)
{
    if (shader_stages_dirty_)
    {
        immutable_->is_validate_ = true;
        for (uint32_t stage_index = 0; stage_index < ShaderStageNum; ++stage_index)
        {
            ShaderStage const stage = static_cast<ShaderStage>(stage_index);
            const auto& shader_stage = this->Stage(stage);
            if (shader_stage)
            {
                immutable_->is_validate_ &= shader_stage->Validate();
            }
        }

        this->DoLinkShaders(effect);

        shader_stages_dirty_ = false;
        hw_res_ready_ = true;
    }
}

}