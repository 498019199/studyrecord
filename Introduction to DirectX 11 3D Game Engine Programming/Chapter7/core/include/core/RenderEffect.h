#pragma once
#include <core/common.h>

class RenderEffect
{
public:
    struct VSConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };

    void CreateConstant();
    void AttackVertexShader(const std::string& filename);
    void AttackPixelShader(const std::string& filename);

    const GraphicsBufferPtr& HWBuff() const noexcept
    {
        return hw_buff_;
    }

    ID3D11VertexShader* GetVertexShader()
    {
        return vertex_shader_.get();
    }
    ID3D11PixelShader* GetPixelShader()
    {
        return pixel_shader_.get();
    }
private:
    com_ptr<ID3D11VertexShader>  vertex_shader_;	// 顶点着色器
    com_ptr<ID3D11PixelShader> pixel_shader_;	    // 像素着色器

    GraphicsBufferPtr hw_buff_; // 常量缓冲区
};


