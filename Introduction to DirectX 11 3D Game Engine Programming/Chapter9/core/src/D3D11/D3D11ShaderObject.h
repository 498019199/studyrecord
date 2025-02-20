#pragma once
#include <render/ShaderObject.h>
#include "D3D11Util.h"
#include <functional>

namespace RenderWorker
{
class RenderEffectParameter;

struct D3D11ShaderDesc
{
    struct ConstantBufferDesc
    {
        struct VariableDesc
        {
            std::string name;
            uint32_t start_offset;
            uint8_t type;
            uint8_t rows;
            uint8_t columns;
            uint16_t elements;
        };
        std::vector<VariableDesc> var_desc;

        std::string name;
        size_t name_hash;
        uint32_t size = 0;
    };
    std::vector<ConstantBufferDesc> cb_desc;

    uint16_t num_samplers = 0;
    uint16_t num_srvs = 0;
    uint16_t num_uavs = 0;

    struct BoundResourceDesc
    {
        std::string name;
        uint8_t type;
        uint8_t dimension;
        uint16_t bind_point;
    };
    std::vector<BoundResourceDesc> res_desc;
};

class D3D11ShaderStageObject : public ShaderStageObject
{
public:
    explicit D3D11ShaderStageObject(ShaderStage stage);
    
    void CompileShader(const RenderEffect& effect, const RenderTechnique& tech, const RenderPass& pass,
			const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) override;

    void CreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>&   shader_desc_ids) override;

    std::span<uint8_t const> ShaderCodeBlob() const;

    const D3D11ShaderDesc& GetD3D11ShaderDesc() const noexcept
    {
        return shader_desc_;
    }

    const std::vector<uint8_t>& CBufferIndices() const noexcept
    {
        return cbuff_indices_;
    }
    virtual ID3D11VertexShader* HwVertexShader() const noexcept
    {
        return nullptr;
    }
    virtual ID3D11PixelShader* HwPixelShader() const noexcept
    {
        return nullptr;
    }
private:
    virtual void ClearHwShader() = 0;
  
protected:
	bool is_available_;
    std::vector<uint8_t> shader_code_;

    D3D11ShaderDesc shader_desc_;
    std::vector<uint8_t> cbuff_indices_;
};

class D3D11VertexShaderStageObject final : public D3D11ShaderStageObject
{
public:
    D3D11VertexShaderStageObject();

    uint32_t VsSignature() const noexcept
    {
        return vs_signature_;
    }
    
    ID3D11VertexShader* HwVertexShader() const noexcept override
    {
        return vertex_shader_.get();
    }

private:
    void ClearHwShader() override;
    void StageSpecificCreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) override;

private:
    ID3D11VertexShaderPtr vertex_shader_;
    uint32_t vs_signature_;
};

class D3D11PixelShaderStageObject final : public D3D11ShaderStageObject
{
public:
    D3D11PixelShaderStageObject();

    ID3D11PixelShader* HwPixelShader() const noexcept override
    {
        return pixel_shader_.get();
    }

private:
    void ClearHwShader() override;
    void StageSpecificCreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) override;

private:
    ID3D11PixelShaderPtr pixel_shader_;
    bool has_discard_ = true;
};

struct D3D11Immutable;
class D3D11ShaderObject final : public ShaderObject
{
    struct D3D11Immutable
    {
        std::array<std::vector<ID3D11SamplerState*>, ShaderStageNum> samplers_;
    };

    struct ParameterBind
    {
        const RenderEffectParameter* param;
        uint32_t offset;
        std::function<void()> update;
    };
public:
    D3D11ShaderObject();
    D3D11ShaderObject(std::shared_ptr<Immutable> immutable, std::shared_ptr<D3D11Immutable> d3d_immutable) noexcept;
 
    // 绑定资源
    void Bind(const RenderEffect& effect) override;
    // 解除资源
    void Unbind() override;

    std::span<uint8_t const> VsCode() const;
    uint32_t VsSignature() const noexcept;
private:

    // 绑定着色器资源
    void DoLinkShaders(RenderEffect& effect) override;

    ParameterBind GetBindFunc(ShaderStage stage, uint32_t offset, RenderEffectParameter const& param);
private:
    const std::shared_ptr<D3D11Immutable> d3d_immutable_;

    std::array<std::vector<ParameterBind>, ShaderStageNum> param_binds_;

    std::array<std::vector<std::tuple<void*, uint32_t, uint32_t>>, ShaderStageNum> srvsrcs_;
    std::array<std::vector<ID3D11ShaderResourceView*>, ShaderStageNum> srvs_;
};

}