//可渲染对象类 头文件
#pragma once
#include <core/common.h>
#include <core/D3D11RenderEngine.h>

class D3D11Renderable
{
public:
    struct ConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };
public:
    D3D11Renderable();
    ~D3D11Renderable();
    
    D3D11RenderLayout& GetRenderLayout() const;
	D3D11RenderLayout& GetRenderLayout(uint32_t lod) const;

	RenderEffect* GetRenderEffect();

    void Render();
protected:
    int32_t active_lod_ = 0;
    std::vector<RenderLayoutPtr> rls_;
    RenderEffectPtr effect_;
};

