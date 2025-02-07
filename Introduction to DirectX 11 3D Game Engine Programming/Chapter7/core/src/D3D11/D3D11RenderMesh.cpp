#include <core/D3D11RenderMesh.h>
#include <core/Context.h>
#include <core/WinApp.h>
#include <core/common.h>

D3D11RenderMesh::D3D11RenderMesh()
{
    
}

D3D11RenderMesh::~D3D11RenderMesh()
{
    
}

void D3D11RenderMesh::CreateVertexShader(const std::string& filename, const D3D11_INPUT_ELEMENT_DESC* inputLayouts, int size)
{
    com_ptr<ID3DBlob> blob;

    // 创建顶点着色器
    const auto& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "VS", "vs_5_0", blob.put()));
    TIFHR(re.D3DDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertex_shader_.put()));
}

void D3D11RenderMesh::CreatePixelShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;
    const auto& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "PS", "ps_5_0", blob.put()));
    TIFHR(re.D3DDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixel_shader_.put()));
}

void D3D11RenderMesh::BindShader(uint32_t stride)
{
    //auto const& re = Context::Instance().RenderEngineInstance();
    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // // 输入装配阶段的顶点缓冲区设置
    // //UINT stride = sizeof(VertexPosColor);	// 跨越字节数
    // UINT offset = 0;						// 起始偏移量
    // re.D3DDeviceImmContext()->IASetVertexBuffers(0, 1, vbs_.put(), &stride, &offset);

    // re.D3DDeviceImmContext()->RSSetState(rs_.get());

    // // 将更新好的常量缓冲区绑定到顶点着色器
    // if(nullptr != cbs_)
    //     re.D3DDeviceImmContext()->VSSetConstantBuffers(0, 1, cbs_.put());
    // // 将着色器绑定到渲染管线
    // re.D3DDeviceImmContext()->VSSetShader(vertex_shader_.get(), nullptr, 0);
    // re.D3DDeviceImmContext()->PSSetShader(pixel_shader_.get(), nullptr, 0);
}

void D3D11RenderMesh::Updata(float dt)
{
    // static float phi = 0.0f, theta = 0.0f;
    // phi += 0.3f * dt, theta += 0.37f * dt;

    // cb_.world = MathWorker::Transpose(MathWorker::MatrixRotateX(phi) * MathWorker::MatrixRotateY(theta));
    // // 更新常量缓冲区，让立方体转起来
    // auto const& re = Context::Instance().RenderEngineInstance();
    // D3D11_MAPPED_SUBRESOURCE mappedData;
    // TIFHR(re.D3DDeviceImmContext()->Map(cbs_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
    // memcpy_s(mappedData.pData, sizeof(cb_), &cb_, sizeof(cb_));
    // re.D3DDeviceImmContext()->Unmap(cbs_.get(), 0);
}
