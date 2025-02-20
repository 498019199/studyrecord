#include <render/Renderable.h>
#include <render/RenderEffect.h>
#include <core/Context.h>

#include "D3D11/D3D11RenderLayout.h"
#include "D3D11/D3D11RenderEngine.h"

namespace RenderWorker
{


Renderable::Renderable()
    :rls_(1), active_lod_(-1)
{
}

Renderable::~Renderable()
{
}

RenderLayout& Renderable::GetRenderLayout() const
{
	return this->GetRenderLayout(active_lod_);
}

RenderLayout& Renderable::GetRenderLayout(uint32_t lod) const
{
    return *rls_[lod];
}

RenderEffect* Renderable::GetRenderEffect() const
{       
    return effect_.get();
}

RenderTechnique* Renderable::GetRenderTechnique() const
{
    return technique_;
}

void Renderable::Render()
{
    int32_t lod = 0;
    
    const auto& effect = *GetRenderEffect();
    const auto& layout = GetRenderLayout(lod);
    const auto& tech = *GetRenderTechnique();
    auto& d3d11_re = checked_cast<D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
        d3d11_re.DoRender(effect, tech, layout);
}

}