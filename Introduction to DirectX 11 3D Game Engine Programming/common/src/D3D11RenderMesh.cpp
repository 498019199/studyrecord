#include <common/D3D11RenderMesh.h>
#include <common/Context.h>

D3D11RenderMesh::D3D11RenderMesh()
{
    
}

D3D11RenderMesh::~D3D11RenderMesh()
{
    
}

void D3D11RenderMesh::CreateConstant()
{
    // 设置常量缓冲区描述
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(cbs_);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // 新建常量缓冲区，不使用初始数据
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&cbd, nullptr, cbs_.put()));
}

void D3D11RenderMesh::CreateVertexBuffer(void const * init_data, int size_in_byte)
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = size_in_byte;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = init_data;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&vbd, &vinitData, vbs_.put()));
}

void D3D11RenderMesh::CreateIndecxBuffer(void const * init_data, int size_in_byte)
{
    // 设置索引缓冲区描述
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = size_in_byte;
    vbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

    // 新建索引缓冲区
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = init_data;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&vbd, &vinitData, vbs_.put()));

    // 输入装配阶段的索引缓冲区设置
    re.D3DDeviceImmContext()->IASetIndexBuffer(vbs_.get(), DXGI_FORMAT_R32_UINT, 0);
}

void D3D11RenderMesh::CreateVertexShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;

    // 创建顶点着色器
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(CreateShaderFromFile(filename, "VS", "vs_5_0", blob.put()));
    HR(re.D3DDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertex_shader_.put()));
}

void D3D11RenderMesh::CreatePixelShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(CreateShaderFromFile(filename, "PS", "ps_5_0", blob.put()));
    HR(re.D3DDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixel_shader_.put()));
}

void D3D11RenderMesh::BindShader()
{
    auto const& re = Context::Instance().RenderEngineInstance();
    // 将更新好的常量缓冲区绑定到顶点着色器
    re.D3DDeviceImmContext()->VSSetConstantBuffers(0, 1, cbs_.put());
    // 将着色器绑定到渲染管线
    re.D3DDeviceImmContext()->VSSetShader(vertex_shader_.get(), nullptr, 0);
    re.D3DDeviceImmContext()->PSSetShader(pixel_shader_.get(), nullptr, 0);
}

void D3D11RenderMesh::Updata(float dt)
{
    
}
