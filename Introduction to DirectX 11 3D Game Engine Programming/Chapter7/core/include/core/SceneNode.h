#pragma once
#include <core/common.h>
#include <vector>

// 场景上对象位置描述
class SceneNode
{
public:
    SceneNode* Parent() const;
	std::vector<SceneNodePtr> const & Children() const;

    const float4x4& TransformToWorld() const;
    //rotator GetRotation() const;
    //float3 GetPosition() const;
    
    void SetPosition(const float3& pos);
    void SetRotation(const rotator& rot);
private:
    float4x4 xform_to_parent_; // xform 父节点转换矩阵

    SceneNode* parent_ = nullptr;
	std::vector<SceneNodePtr> children_;
};



