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
}

void World::AddRenderable(D3D11Renderable* node)
{
    all_scene_nodes_.emplace_back(node);
}

void World::UpdateScene(float dt)
{
    static float phi = 0.0f, theta = 0.0f;
    phi += 0.3f * dt, theta += 0.37f * dt;
    cb_.world = MathWorker::Transpose(MathWorker::MatrixRotateX(phi) * MathWorker::MatrixRotateY(theta));

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

    for(auto node : all_scene_nodes_)
    {
        node->Render();
    }

    const auto& re = Context::Instance().RenderEngineInstance();
    re.EndRender();
}
