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
    
    void UpdateScene(float dt);

    void AddRenderable(D3D11Renderable* node);
private:
    ConstantBuffer cb_;

    SceneNode scene_root_;
    std::vector<D3D11Renderable*> all_scene_nodes_;
};

