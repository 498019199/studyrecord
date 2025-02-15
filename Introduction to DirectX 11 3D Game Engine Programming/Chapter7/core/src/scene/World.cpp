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
    cb_.world = float4x4::Identity();
    cb_.view = Transpose(LookAtLH(
        float3(0.0f, 0.0f, -5.0f),
        float3(0.0f, 0.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)));
    cb_.proj = MathWorker::Transpose(MathWorker::PerspectiveFovLH(1.570796327f, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f));    
    cb_.useCustomColor = 0;
    cb_.color = Color(1.f, 1.f, 1.f, 1.f);
}

void World::AddRenderable(D3D11Renderable* node)
{
    all_scene_nodes_.emplace_back(node);
}

void World::UpdateScene(float dt)
{
    for(auto node : all_scene_nodes_)
    {
        auto buff = node->GetRenderEffect()->HWBuff();
        if(buff)
        {
            ConstantBuffer* data = static_cast<ConstantBuffer*>(buff->Map(BufferAccess::BA_Write_Only));
            if(nullptr == data)
            {
                continue;
            }
            memcpy_s(data, sizeof(cb_), &cb_, sizeof(cb_));
            buff->Unmap();
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
