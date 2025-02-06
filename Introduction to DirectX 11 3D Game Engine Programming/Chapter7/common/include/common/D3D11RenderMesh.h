#pragma once
#include <common/D3D11RenderEngine.h>
#include <common/com_ptr.h>


class D3D11RenderMesh
{

public:
    D3D11RenderMesh();
    ~D3D11RenderMesh();



    void CreateVertexShader(const std::string& filename, const D3D11_INPUT_ELEMENT_DESC* inputLayouts, int size);
    void CreatePixelShader(const std::string& filename);

    void BindShader(uint32_t stride);

    void Updata(float dt);

    void D3D11SetDebug_Cube();
private:
    std::wstring filename_;
    


    com_ptr<ID3D11VertexShader>  vertex_shader_;	// 顶点着色器
    com_ptr<ID3D11PixelShader> pixel_shader_;	    // 像素着色器

    com_ptr<ID3D11InputLayout> input_layout_;
    com_ptr<ID3D11RasterizerState> rs_;

    
};





