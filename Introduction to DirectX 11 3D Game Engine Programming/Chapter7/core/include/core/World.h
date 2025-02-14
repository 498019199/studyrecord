#pragma once
#include <core/common.h>
#include <core/SceneNode.h>

class World
{
public:
    struct ConstantBuffer
    {
        float4x4 world;
        float4x4 view;
        float4x4 proj;
    };

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



