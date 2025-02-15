#include <core/World.h>
#include <core/Context.h>
#include <core/WinApp.h>
#include <core/D3D11Renderable.h>
#include <core/RenderEffect.h>
#include <core/D3D11GraphicsBuffer.h>
#include <core/D3D11RenderEngine.h>

World::World()
{
}

void World::BeginWorld()
{
    // ******************
    // 初始化默认光照
    // 方向光
    default_directional_light_.ambient_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
    default_directional_light_.diffuse_ = float4(0.8f, 0.8f, 0.8f, 1.0f);
    default_directional_light_.specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
    default_directional_light_.direction_ = float3(-0.577f, -0.577f, 0.577f);
    // 点光
    default_point_light_.pos_ = float3(0.0f, 0.0f, -10.0f);
    default_point_light_.ambient_ = float4(0.3f, 0.3f, 0.3f, 1.0f);
    default_point_light_.diffuse_ = float4(0.7f, 0.7f, 0.7f, 1.0f);
    default_point_light_.specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
    default_point_light_.att_ = float3(0.0f, 0.1f, 0.0f);
    default_point_light_.range_ = 25.0f;
    // 聚光灯
    default_spot_light_.pos_ = float3(0.0f, 0.0f, -5.0f);
    default_spot_light_.direction_ = float3(0.0f, 0.0f, 1.0f);
    default_spot_light_.ambient_ = float4(0.0f, 0.0f, 0.0f, 1.0f);
    default_spot_light_.diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
    default_spot_light_.specular_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
    default_spot_light_.att_ = float3(1.0f, 0.0f, 0.0f);
    default_spot_light_.spot_ = 12.0f;
    default_spot_light_.range_ = 10000.0f;

    // 初始化用于VS的常量缓冲区的值
    vs_cb_.world = float4x4::Identity();
    vs_cb_.view = Transpose(LookAtLH(
        float3(0.0f, 0.0f, -5.0f),
        float3(0.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)));
    vs_cb_.proj = MathWorker::Transpose(MathWorker::PerspectiveFovLH(MathWorker::PIdiv2, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f));    
    vs_cb_.worldInvTranspose = float4x4::Identity();

    // 初始化用于PS的常量缓冲区的值
    ps_cb_.material.ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
    ps_cb_.material.diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
    ps_cb_.material.specular_ = float4(0.5f, 0.5f, 0.5f, 5.0f);
    // 使用默认平行光
    ps_cb_.directional_light = default_directional_light_;
    // 注意不要忘记设置此处的观察位置，否则高亮部分会有问题
    ps_cb_.eyePos = float4(0.0f, 0.0f, -5.0f, 0.0f);
}

void World::AddRenderable(D3D11Renderable* node)
{
    all_scene_nodes_.emplace_back(node);
}

void World::UpdateScene(float dt)
{
    for(auto node : all_scene_nodes_)
    {
        auto vs_buff = node->GetRenderEffect()->HWBuff_VS();
        if(vs_buff)
        {
            VSConstantBuffer* data = static_cast<VSConstantBuffer*>(vs_buff->Map(BufferAccess::BA_Write_Only));
            if(nullptr == data)
            {
                continue;
            }
            memcpy_s(data, sizeof(vs_cb_), &vs_cb_, sizeof(vs_cb_));
            vs_buff->Unmap();
        }

        auto ps_buff = node->GetRenderEffect()->HWBuff_PS();
        if(ps_buff)
        {
            VSConstantBuffer* data = static_cast<VSConstantBuffer*>(ps_buff->Map(BufferAccess::BA_Write_Only));
            if(nullptr == data)
            {
                continue;
            }
            memcpy_s(data, sizeof(ps_cb_), &ps_cb_, sizeof(ps_cb_));
            ps_buff->Unmap();
        }
    }

    auto& re = Context::Instance().RenderEngineInstance();
    for(auto node : all_scene_nodes_)
    {
        if(is_wireframe_mode_)
        {
            const auto& effect = node->GetRenderEffect();
            effect->Active();
        }
        else
        {
            re.RSSetState(nullptr);
        }
        node->Render();
    }
    re.EndRender();
}
