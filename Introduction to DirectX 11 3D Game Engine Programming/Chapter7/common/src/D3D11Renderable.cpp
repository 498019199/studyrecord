#include <core/D3D11Renderable.h>
#include <core/RenderLayout.h>
#include <core/Context.h>

D3D11Renderable::D3D11Renderable()
    :rls_(1), active_lod_(-1)
{
}

D3D11Renderable::~D3D11Renderable()
{
}

RenderLayout& D3D11Renderable::GetRenderLayout() const
{
	return this->GetRenderLayout(active_lod_);
}

RenderLayout& D3D11Renderable::GetRenderLayout(uint32_t lod) const
{
    return *rls_[lod];
}

void D3D11Renderable::CreateConstant()
{
    // 设置常量缓冲区描述
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // 新建常量缓冲区，不使用初始数据
    auto const& re = Context::Instance().RenderEngineInstance();
    HR(re.D3DDevice()->CreateBuffer(&cbd, nullptr, cbs_.put()));
}

void D3D11Renderable::CreateVertexBuffer(void const * init_data, int size_in_byte)
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

void D3D11Renderable::CreateIndecxBuffer(void const * init_data, int size_in_byte)
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
    HR(re.D3DDevice()->CreateBuffer(&vbd, &vinitData, ibs_.put()));
}