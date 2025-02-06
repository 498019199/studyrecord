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
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(CreateShaderFromFile(filename, "VS", "vs_5_0", blob.put()));
    HR(re.D3DDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertex_shader_.put()));

    // 创建并绑定顶点布局
    HR(re.D3DDevice()->CreateInputLayout(inputLayouts, size,
        blob->GetBufferPointer(), blob->GetBufferSize(), input_layout_.put()));
}

void D3D11RenderMesh::CreatePixelShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(CreateShaderFromFile(filename, "PS", "ps_5_0", blob.put()));
    HR(re.D3DDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixel_shader_.put()));
}

void D3D11RenderMesh::BindShader(uint32_t stride)
{
    auto const& re = Context::Instance().RenderEngineInstance();
    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // 输入装配阶段的顶点缓冲区设置
    //UINT stride = sizeof(VertexPosColor);	// 跨越字节数
    UINT offset = 0;						// 起始偏移量
    re.D3DDeviceImmContext()->IASetVertexBuffers(0, 1, vbs_.put(), &stride, &offset);
    // 设置图元类型，设定输入布局
    re.D3DDeviceImmContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    re.D3DDeviceImmContext()->IASetInputLayout(input_layout_.get());

    re.D3DDeviceImmContext()->RSSetState(rs_.get());

    // 将更新好的常量缓冲区绑定到顶点着色器
    if(nullptr != cbs_)
        re.D3DDeviceImmContext()->VSSetConstantBuffers(0, 1, cbs_.put());
    // 将着色器绑定到渲染管线
    re.D3DDeviceImmContext()->VSSetShader(vertex_shader_.get(), nullptr, 0);
    re.D3DDeviceImmContext()->PSSetShader(pixel_shader_.get(), nullptr, 0);
}

void D3D11RenderMesh::D3D11SetDebug_Cube()
{
    // ******************
    // 设置调试对象名
    //
    D3D11SetDebugObjectName(input_layout_.get(), "VertexPosColorLayout");
    D3D11SetDebugObjectName(vbs_.get(), "VertexBuffer");
    D3D11SetDebugObjectName(ibs_.get(), "IndexBuffer");
    D3D11SetDebugObjectName(cbs_.get(), "ConstantBuffer");
    D3D11SetDebugObjectName(vertex_shader_.get(), "Cube_VS");
    D3D11SetDebugObjectName(pixel_shader_.get(), "Cube_PS");

    cb_.world = float4x4::Identity();
    cb_.view = MathWorker::Transpose(MathWorker::LookAtLH(
        float3(0.0f, 0.0f, -5.0f),
        float3(0.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)));
    cb_.proj = MathWorker::Transpose(
        MathWorker::PerspectiveFovLH(1.570796327f, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f));
}

void D3D11RenderMesh::Updata(float dt)
{
    static float phi = 0.0f, theta = 0.0f;
    phi += 0.3f * dt, theta += 0.37f * dt;

    cb_.world = MathWorker::Transpose(MathWorker::MatrixRotateX(phi) * MathWorker::MatrixRotateY(theta));
    // 更新常量缓冲区，让立方体转起来
    auto const& re = Context::Instance().RenderEngineInstance();
    D3D11_MAPPED_SUBRESOURCE mappedData;
    HR(re.D3DDeviceImmContext()->Map(cbs_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
    memcpy_s(mappedData.pData, sizeof(cb_), &cb_, sizeof(cb_));
    re.D3DDeviceImmContext()->Unmap(cbs_.get(), 0);
}
