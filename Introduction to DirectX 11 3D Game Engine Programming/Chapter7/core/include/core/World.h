#pragma once
#include <core/common.h>
#include <core/SceneNode.h>
#include <core/RenderEffect.h>

class World
{
public:
    World();
    
    void BeginWorld();
    void UpdateScene(float dt);

    void AddRenderable(D3D11Renderable* node);
private:
    SceneNode scene_root_;
    std::vector<D3D11Renderable*> all_scene_nodes_;

public:
    ConstantBuffer cb_;
    bool is_wireframe_mode_{false};
};



