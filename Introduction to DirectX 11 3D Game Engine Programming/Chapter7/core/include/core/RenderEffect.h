#pragma once
#include <core/common.h>
#include <core/Light.h>

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

class RenderEffect
{
public:
    void CreateConstant();
    void AttackVertexShader(const std::string& filename);
    void AttackPixelShader(const std::string& filename);

    const GraphicsBufferPtr& HWBuff_VS() const noexcept
    {
        return vs_hw_buff_;
    }

    const GraphicsBufferPtr& HWBuff_PS() const noexcept
    {
        return ps_hw_buff_;
    }

    ID3D11VertexShader* GetVertexShader() const
    {
        return vertex_shader_.get();
    }
    ID3D11PixelShader* GetPixelShader() const
    {
        return pixel_shader_.get();
    }

    ID3DBlob* VsCode() const
    {
        return vertex_blob_.get();
    }

    ID3DBlob* PsCode() const
    {
        return pixel_blob_.get();
    }

    void Active() const;
private:
    ID3D11VertexShaderPtr  vertex_shader_;	// 顶点着色器
    ID3D11PixelShaderPtr pixel_shader_;	    // 像素着色器
    ID3D11RasterizerStatePtr rasterizer_state_;
    com_ptr<ID3DBlob> vertex_blob_;
    com_ptr<ID3DBlob> pixel_blob_;

    GraphicsBufferPtr vs_hw_buff_; // 常量缓冲区
    GraphicsBufferPtr ps_hw_buff_; 
};







