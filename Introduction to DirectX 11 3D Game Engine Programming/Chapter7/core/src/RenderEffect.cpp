#include <core/RenderEffect.h>
#include <core/D3D11Util.h>
#include <core/Context.h>

void RenderEffect::CreateConstant()
{
    // 设置常量缓冲区描述
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(VSConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // 新建常量缓冲区，不使用初始数据
    auto const& re = Context::Instance().RenderEngineInstance();
    TIFHR(re.D3DDevice()->CreateBuffer(&cbd, nullptr, cbs_.put()));
}

void RenderEffect::AttackVertexShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;

    // 创建顶点着色器
    auto const& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "VS", "vs_5_0", blob.put()));
    TIFHR(re.D3DDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertex_shader_.put()));
}

void RenderEffect::AttackPixelShader(const std::string& filename)
{
    com_ptr<ID3DBlob> blob;
    auto const& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "PS", "ps_5_0", blob.put()));
    TIFHR(re.D3DDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixel_shader_.put()));
}
