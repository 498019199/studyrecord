#pragma once
#include <core/SceneNode.h>
#include <core/Control.h>

#include <render/Renderable.h>
#include <render/Light.h>
#include <render/RenderEffect.h>

namespace RenderWorker
{

class World
{
public:
    World();
    ~World();
    
    void BeginWorld();
    void UpdateScene(float dt);

    void AddRenderable(Renderable* obj);
private:
    SceneNode scene_root_;
    std::vector<std::pair<const RenderTechnique*, std::vector<Renderable*>>> render_queue_;

public:
    ControllerPtr controller_;
    CameraPtr camera_;
};


using WorldPtr = std::shared_ptr<World>;
}
