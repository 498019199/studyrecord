#pragma once
#include <core/Util.h>

#include <array>
#include <memory>

namespace RenderWorker
{
class RenderEffect;

struct ShaderDesc
{
    std::string profile;
    std::string func_name;
    uint64_t macros_hash;
    uint32_t tech_pass_type;

    friend bool operator==(ShaderDesc const& lhs, ShaderDesc const& rhs) noexcept
    {
        return (lhs.profile == rhs.profile) && (lhs.func_name == rhs.func_name)
            && (lhs.macros_hash == rhs.macros_hash);
    }
    friend bool operator!=(ShaderDesc const& lhs, ShaderDesc const& rhs) noexcept
    {
        return !(lhs == rhs);
    }
};

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

	virtual void CompileShader(RenderEffect const& effect,
			const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) = 0;

    virtual void CreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) = 0;

    bool Validate() const noexcept
    {
        return is_validate_;
    }

    // Pixel shader only
    virtual bool HasDiscard() const noexcept
    {
        return false;
    }

    bool HWResourceReady() const noexcept
    {
        return hw_res_ready_;
    }
protected:
    virtual void StageSpecificCreateHwShader(
        [[maybe_unused]] const RenderEffect& effect, [[maybe_unused]] const std::array<uint32_t, ShaderStageNum>& shader_desc_ids)
    {
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
    virtual ~ShaderObject() noexcept;

    void AttachStage(ShaderStage stage, const ShaderStageObjectPtr&  shader_stage);
    const ShaderStageObjectPtr&  Stage(ShaderStage stage) const noexcept;

    void LinkShaders(RenderEffect& effect);

    virtual void Bind(const RenderEffect& effect) = 0;
    virtual void Unbind() = 0;
private:
    virtual void DoLinkShaders(RenderEffect& effect) = 0;

protected:
    struct Immutable
    {
        std::array<ShaderStageObjectPtr, ShaderStageNum> shader_stages_;
        bool is_validate_;
    };

    explicit ShaderObject(std::shared_ptr<Immutable> immutable) noexcept;

protected:
    const std::shared_ptr<Immutable> immutable_;
    bool shader_stages_dirty_ = true;
    bool hw_res_ready_ = false;
};

}