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
private:
    ID3D11BufferPtr cbs_; // 常量缓冲区
    com_ptr<ID3D11VertexShader>  vertex_shader_;	// 顶点着色器
    com_ptr<ID3D11PixelShader> pixel_shader_;	    // 像素着色器
};


