#pragma once
#include <core/Util.h>

#include <array>
#include <memory>

namespace RenderWorker
{
class RenderEffect;

enum class ShaderStage
{
    Vertex,
    Pixel,
    Geometry,
    Compute,
    Hull,
    Domain,

    NumStages,
};
uint32_t constexpr ShaderStageNum = std::to_underlying(ShaderStage::NumStages);

class ShaderStageObject
{
public:
    explicit ShaderStageObject(ShaderStage stage) noexcept;
    virtual ~ShaderStageObject() noexcept;

    bool Validate() const noexcept
    {
        return is_validate_;
    }

    bool HWResourceReady() const noexcept
    {
        return hw_res_ready_;
    }
protected:
    const ShaderStage stage_;

    bool is_validate_ = false;
    bool hw_res_ready_ = false;
};

using ShaderStageObjectPtr = std::shared_ptr<ShaderStageObject>;

class ShaderObject;
struct Immutable;
using ShaderObjectPtr = std::shared_ptr<ShaderObject>;
class ShaderObject
{ 
public:
    ShaderObject();
    explicit ShaderObject(std::shared_ptr<Immutable> immutable) noexcept;
    virtual ~ShaderObject() noexcept;

    void AttachStage(ShaderStage stage, const ShaderStageObjectPtr&  shader_stage);
    const ShaderStageObjectPtr&  Stage(ShaderStage stage) const noexcept;

    void LinkShaders(RenderEffect& effect);

private:
    virtual void DoLinkShaders(RenderEffect& effect) = 0;

protected:
    struct Immutable
    {
        std::array<ShaderStageObjectPtr, ShaderStageNum> shader_stages_;
        bool is_validate_;
    };
    const std::shared_ptr<Immutable> immutable_;
    bool shader_stages_dirty_ = true;
    bool hw_res_ready_ = false;
};

}