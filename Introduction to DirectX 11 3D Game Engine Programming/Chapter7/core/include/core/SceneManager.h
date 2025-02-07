#pragma once
#include <core/common.h>
#include <core/SceneNode.h>

class SceneManager
{
private:
    SceneNode scene_root_;
    std::vector<SceneNode*> all_scene_nodes_;
};