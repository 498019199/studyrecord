#pragma once
#include <render/ShaderObject.h>
#include "D3D11Util.h"

namespace RenderWorker
{
class D3D11ShaderStageObject : public ShaderStageObject
{
public:
    explicit D3D11ShaderStageObject(ShaderStage stage);
    
    void CompileShader(const RenderEffect& effect, const RenderTechnique& tech, const RenderPass& pass,
			const std::array<uint32_t, ShaderStageNum>& shader_desc_ids) override;

    void CreateHwShader(const RenderEffect& effect, const std::array<uint32_t, ShaderStageNum>&   shader_desc_ids) override;

    std::span<uint8_t const> ShaderCodeBlob() const;

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
public:
    D3D11ShaderObject();
    D3D11ShaderObject(std::shared_ptr<Immutable> immutable, std::shared_ptr<D3D11Immutable> d3d_immutable) noexcept;
 
    void Bind(const RenderEffect& effect) override;
    void Unbind() override;

    std::span<uint8_t const> VsCode() const;
    uint32_t VsSignature() const noexcept;
    
private:
    void DoLinkShaders(RenderEffect& effect) override;

private:
    struct D3D11Immutable
    {
        std::array<std::vector<ID3D11SamplerState*>, ShaderStageNum> samplers_;
    };

public:
    D3D11ShaderObject(std::shared_ptr<Immutable> immutable, std::shared_ptr<D3D11Immutable> d3d_immutable) noexcept;

private:
    const std::shared_ptr<D3D11Immutable> d3d_immutable_;

    std::array<std::vector<std::tuple<void*, uint32_t, uint32_t>>, ShaderStageNum> srvsrcs_;
    std::array<std::vector<ID3D11ShaderResourceView*>, ShaderStageNum> srvs_;
};

}