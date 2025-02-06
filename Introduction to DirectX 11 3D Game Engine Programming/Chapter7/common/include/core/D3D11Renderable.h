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
    
    virtual RenderLayout& GetRenderLayout() const;
	virtual RenderLayout& GetRenderLayout(uint32_t lod) const;

    void CreateConstant();
    void CreateVertexBuffer(void const * init_data, int size_in_byte);
    void CreateIndecxBuffer(void const * init_data, int size_in_byte);
private:
    int32_t active_lod_ = 0;
    std::vector<RenderLayoutPtr> rls_;

    ConstantBuffer cb_;
    com_ptr<ID3D11Buffer> cbs_; // 常量缓冲区
};
