#include <core/ShaderObject.h>


namespace RenderWorker
{


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