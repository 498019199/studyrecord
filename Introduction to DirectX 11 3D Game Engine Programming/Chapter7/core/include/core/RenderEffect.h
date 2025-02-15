#pragma once
#include <core/common.h>

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

struct ConstantBuffer
{
    float4x4 world;//16*4=64
    float4x4 view;//128
    float4x4 proj;//192

    uint32_t useCustomColor;//198
    Color color;//214
};

class RenderEffect
{
public:
    void CreateConstant();
    void AttackVertexShader(const std::string& filename);
    void AttackPixelShader(const std::string& filename);

    const GraphicsBufferPtr& HWBuff() const noexcept
    {
        return hw_buff_;
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

    GraphicsBufferPtr hw_buff_; // 常量缓冲区
};







