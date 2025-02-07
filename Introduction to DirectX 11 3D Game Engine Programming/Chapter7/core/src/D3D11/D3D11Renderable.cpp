#include <core/D3D11Renderable.h>
#include <core/D3D11RenderLayout.h>
#include <core/Context.h>

D3D11Renderable::D3D11Renderable()
    :rls_(1), active_lod_(-1)
{
}

D3D11Renderable::~D3D11Renderable()
{
}

D3D11RenderLayout& D3D11Renderable::GetRenderLayout() const
{
	return this->GetRenderLayout(active_lod_);
}

D3D11RenderLayout& D3D11Renderable::GetRenderLayout(uint32_t lod) const
{
    return *rls_[lod];
}
