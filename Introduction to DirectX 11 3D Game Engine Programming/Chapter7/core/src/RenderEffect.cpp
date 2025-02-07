#include <core/RenderEffect.h>
#include <core/D3D11RenderEngine.h>
#include <core/D3D11RenderFactory.h>
#include <core/D3D11Util.h>
#include <core/Context.h>

void RenderEffect::CreateConstant()
{
    // 设置常量缓冲区描述
    uint32_t size = sizeof(VSConstantBuffer);
    auto& rf = Context::Instance().RenderFactoryInstance();
    hw_buff_ = rf.MakeConstantBuffer(BU_Dynamic, 0, size, nullptr);
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
