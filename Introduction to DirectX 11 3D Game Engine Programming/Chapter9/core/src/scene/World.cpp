#include <core/World.h>
#include <core/Context.h>
#include <core/WinApp.h>
#include <render/RenderEffect.h>
#include <render/Renderable.h>

#include "../D3D11/D3D11GraphicsBuffer.h"
#include "../D3D11/D3D11RenderEngine.h"

namespace RenderWorker
{

World::World()
{
}

void World::BeginWorld()
{
}

void World::AddRenderable(Renderable* obj)
{
    COMMON_ASSERT(obj);
    const RenderEffect* obj_eff = obj->GetRenderEffect();
    COMMON_ASSERT(obj_eff);

    bool found = false;
    for (auto& items : render_queue_)
    {
        if (items.first == obj_eff)
        {
            items.second.push_back(obj);
            found = true;
            break;
        }
    }
    if (!found)
    {
        render_queue_.emplace_back(obj_eff, std::vector<Renderable*>(1, obj));
    }
}

void World::UpdateScene(float dt)
{
    auto& re = Context::Instance().RenderEngineInstance();
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