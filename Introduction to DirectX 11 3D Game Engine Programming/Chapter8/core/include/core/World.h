#pragma once
#include <core/SceneNode.h>
#include <core/Renderable.h>
#include <core/Light.h>
#include <core/RenderEffect.h>

namespace RenderWorker
{

class World
{
public:
    World();
    
    void BeginWorld();
    void UpdateScene(float dt);

    void AddRenderable(Renderable* node);
private:
    SceneNode scene_root_;
    std::vector<Renderable*> all_scene_nodes_;

public:
    bool is_wireframe_mode_{false};

    VSConstantBuffer vs_cb_;			// 用于修改用于VS的GPU常量缓冲区的变量
    PSConstantBuffer ps_cb_;			// 用于修改用于PS的GPU常量缓冲区的变量

    DirectionalLightSource default_directional_light_;					// 默认环境光
    PointLightSource default_point_light_;						// 默认点光
    SpotLightSource default_spot_light_;						    // 默认汇聚光
};
using WorldPtr = std::shared_ptr<World>;
}
