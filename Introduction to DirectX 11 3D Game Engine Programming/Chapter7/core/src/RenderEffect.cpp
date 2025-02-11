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
    hw_buff_ = rf.MakeConstantBuffer(BU_Dynamic, EAH_CPU_Write, size, nullptr);
}

void RenderEffect::AttackVertexShader(const std::string& filename)
{
    // 创建顶点着色器
    auto const& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "VS", "vs_5_0", vertex_blob_.put()));
    TIFHR(re.D3DDevice()->CreateVertexShader(vertex_blob_->GetBufferPointer(), vertex_blob_->GetBufferSize(), nullptr, vertex_shader_.put()));
}

void RenderEffect::AttackPixelShader(const std::string& filename)
{
    auto const& re = Context::Instance().RenderEngineInstance();
    TIFHR(CreateShaderFromFile(filename, "PS", "ps_5_0", pixel_blob_.put()));
    TIFHR(re.D3DDevice()->CreatePixelShader(pixel_blob_->GetBufferPointer(), pixel_blob_->GetBufferSize(), nullptr, pixel_shader_.put()));
}