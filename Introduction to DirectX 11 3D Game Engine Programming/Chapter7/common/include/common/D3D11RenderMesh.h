#pragma once
#include <common/D3D11RenderEngine.h>
#include <common/com_ptr.h>


class D3D11RenderMesh
{
    struct ConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };
public:
    D3D11RenderMesh();
    ~D3D11RenderMesh();

    void CreateConstant();
    void CreateVertexBuffer(void const * init_data, int size_in_byte);
    void CreateIndecxBuffer(void const * init_data, int size_in_byte);

    void CreateVertexShader(const std::string& filename, const D3D11_INPUT_ELEMENT_DESC* inputLayouts, int size);
    void CreatePixelShader(const std::string& filename);

    void BindShader(uint32_t stride);

    void Updata(float dt);

    void D3D11SetDebug_Cube();
private:
    std::wstring filename_;
    
    com_ptr<ID3D11Buffer> vbs_; // 顶点缓冲区
	com_ptr<ID3D11Buffer> ibs_; // 索引缓冲区
    com_ptr<ID3D11Buffer> cbs_; // 常量缓冲区

    com_ptr<ID3D11VertexShader>  vertex_shader_;	// 顶点着色器
    com_ptr<ID3D11PixelShader> pixel_shader_;	    // 像素着色器

    com_ptr<ID3D11InputLayout> input_layout_;
    com_ptr<ID3D11RasterizerState> rs_;

    ConstantBuffer cb_;
};





