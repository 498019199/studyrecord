#include <base/World.h>
#include <base/Context.h>
#include <base/WinApp.h>
#include <render/RenderEffect.h>
#include <render/Renderable.h>

#include "../D3D11/D3D11GraphicsBuffer.h"
#include "../D3D11/D3D11RenderEngine.h"

namespace RenderWorker
{

World::World()
{
}

World::~World()
{
    if(controller_)
    {
        controller_->DetachCamera();
    }
}

void World::BeginWorld()
{
}

void World::AddRenderable(Renderable* obj)
{
    COMMON_ASSERT(obj);
    const RenderEffect* obj_eff = obj->GetRenderEffect();
    COMMON_ASSERT(obj_eff);

    const RenderTechnique* obj_tech = obj->GetRenderTechnique();
    bool found = false;
    for (auto& items : render_queue_)
    {
        if (items.first == obj_tech)
        {
            items.second.push_back(obj);
            found = true;
            break;
        }
    }
    if (!found)
    {
        render_queue_.emplace_back(obj_tech, std::vector<Renderable*>(1, obj));
    }
}

void World::UpdateScene(float dt)
{
    auto& re = Context::Instance().RenderEngineInstance();
    re.BeginRender();
    for (auto& items : render_queue_)
    {
        for (auto const & item : items.second)
        {
            item->Render();
        }
    }
    re.EndRender();

    for (auto& items : render_queue_)
    {
        for (auto const & item : items.second)
        {
            item->Update(dt);
        }
    }
}
}