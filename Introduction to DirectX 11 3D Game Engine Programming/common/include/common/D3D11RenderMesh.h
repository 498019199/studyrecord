#pragma once
#include <common/D3D11RenderEngine.h>
#include <common/com_ptr.h>
class D3D11RenderMesh
{
public:
    D3D11RenderMesh();
    ~D3D11RenderMesh();

    void CreateConstant();
    void CreateVertexBuffer(void const * init_data, int size_in_byte);
    void CreateIndecxBuffer(void const * init_data, int size_in_byte);

    void CreateVertexShader(const std::string& filename);
    void CreatePixelShader(const std::string& filename);

    void BindShader();

    void Updata(float dt);
private:
    std::wstring filename_;
    
    com_ptr<ID3D11Buffer> vbs_; // 顶点缓冲区
	com_ptr<ID3D11Buffer> ibs_; // 索引缓冲区
    com_ptr<ID3D11Buffer> cbs_; // 常量缓冲区

    com_ptr<ID3D11VertexShader>  vertex_shader_;	// 顶点着色器
    com_ptr<ID3D11PixelShader> pixel_shader_;	    // 像素着色器
};


