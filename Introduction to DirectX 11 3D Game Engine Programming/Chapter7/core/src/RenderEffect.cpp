#include <core/RenderEffect.h>
#include <core/D3D11RenderEngine.h>
#include <core/D3D11RenderFactory.h>
#include <core/D3D11Util.h>
#include <core/Context.h>

// 计算最接近且不小于给定值的 16 的倍数
UINT AlignTo16(UINT value) {
    return (value + 15) & ~15;
}
void RenderEffect::CreateConstant()
{
    auto const& re = Context::Instance().RenderEngineInstance();
    D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;
    TIFHR(re.D3DDevice()->CreateRasterizerState(&wireframeDesc, rasterizer_state_.put()));

    // 设置常量缓冲区描述
    uint32_t size = AlignTo16(sizeof(ConstantBuffer));
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

void RenderEffect::Active() const
{
    auto& re = Context::Instance().RenderEngineInstance();
    re.RSSetState(rasterizer_state_.get());
}
