#pragma once
#include <core/SceneNode.h>
#include <render/Renderable.h>
#include <render/Light.h>
#include <render/RenderEffect.h>

namespace RenderWorker
{

class World
{
public:
    World();
    
    void BeginWorld();
    void UpdateScene(float dt);

    void AddRenderable(Renderable* obj);
private:
    SceneNode scene_root_;
    std::vector<std::pair<const RenderEffect*, std::vector<Renderable*>>> render_queue_;

public:
    DirectionalLightSource default_directional_light_;					// 默认环境光
    PointLightSource default_point_light_;						// 默认点光
    SpotLightSource default_spot_light_;						    // 默认汇聚光
};
using WorldPtr = std::shared_ptr<World>;
}
