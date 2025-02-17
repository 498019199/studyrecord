#pragma once
//可渲染对象类 头文件

#include <core/common.h>
#include <render/RenderEffect.h>
#include <render/RenderLayout.h>

namespace RenderWorker
{

class Renderable
{
public:
    struct ConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };
public:
    Renderable();
    ~Renderable();
    
    RenderLayout& GetRenderLayout() const;
	RenderLayout& GetRenderLayout(uint32_t lod) const;

	RenderEffect* GetRenderEffect();

    void Render();
protected:
    int32_t active_lod_ = 0;
    std::vector<RenderLayoutPtr> rls_;
    RenderEffectPtr effect_;
};
using RenderablePtr = std::shared_ptr<RenderWorker::Renderable>;
}