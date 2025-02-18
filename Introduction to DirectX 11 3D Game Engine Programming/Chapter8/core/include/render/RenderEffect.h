#pragma once
#include <render/GraphicsBuffer.h>
#include <render/ShaderObject.h>
#include <render/Light.h>
#include <render/RenderStateObject.h>
#include <render/Texture.h>
#include <render/RenderView.h>

#include <vector>
namespace RenderWorker
{


enum PolygonMode
{
    PM_Point,
    PM_Line,
    PM_Fill
};

struct VSConstantBuffer
{
    float4x4 world;//16*4=64
    float4x4 view;//128
    float4x4 proj;//192
    float4x4 worldInvTranspose;
};

struct PSConstantBuffer
{
    DirectionalLightSource directional_light;				// 默认环境光
    PointLightSource point_light;						// 默认点光
    SpotLightSource spot_light;						    // 默认汇聚光
    Material material;
    float4 eyePos;
};

class RenderEffectConstantBuffer
{
public:
    explicit RenderEffectConstantBuffer(RenderEffect& effect);
    void Load(const std::string& name);
    void Resize(uint32_t size);
    
    const std::string& Name() const noexcept
    {
        return immutable_->name;
    }

    const GraphicsBufferPtr& HWBuff() const noexcept
    {
        return hw_buff_;
    }
private:
    struct Immutable final
    {
        std::string name;
        //size_t name_hash;
    };
    std::shared_ptr<Immutable> immutable_;

    GraphicsBufferPtr hw_buff_; //常量缓冲区
    std::vector<uint8_t> buff_;
    bool dirty_ = true;
};





using RenderEffectConstantBufferPtr = std::shared_ptr<RenderEffectConstantBuffer>;

class RenderEffect
{
public:
    RenderEffect();
    
    void Load(const std::string& file_path);

    uint32_t AddShaderDesc(const std::string& state_name_hash, ShaderDesc const & sd);
    ShaderDesc& GetShaderDesc(uint32_t id) noexcept;
    ShaderDesc const& GetShaderDesc(uint32_t id) const noexcept;

    uint32_t AddShaderObject();

    const ShaderObjectPtr& ShaderObjectByIndex(uint32_t n) const noexcept
    {
        COMMON_ASSERT(n < shader_objs_.size());
        return shader_objs_[n];
    }

    const ShaderObjectPtr& GetShaderObject() const noexcept
    {
        return ShaderObjectByIndex(shader_obj_index_);
    }
    
    uint32_t CBuffersNum() const noexcept;
    RenderEffectConstantBuffer* CBufferByName(const std::string& name) const noexcept;
    RenderEffectConstantBuffer* CBufferByIndex(uint32_t index) const noexcept;
private:
    struct Immutable final
    {
        std::vector<ShaderDesc> shader_descs;
    };
    std::shared_ptr<Immutable> immutable_;
    std::array<uint32_t, ShaderStageNum> shader_desc_ids_;

    std::vector<RenderEffectConstantBufferPtr> cbuffers_;

    uint32_t shader_obj_index_{0};
    std::vector<ShaderObjectPtr> shader_objs_;

public:
    SamplerStateObjectPtr sm_;
    ShaderResourceViewPtr srv_;
};











using RenderEffectPtr = std::shared_ptr<RenderEffect>;
}