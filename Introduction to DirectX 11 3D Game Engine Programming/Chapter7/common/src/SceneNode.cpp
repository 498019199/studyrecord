#include <common/SceneNode.h>

const float4x4& SceneNode::TransformToWorld() const
{
    if(nullptr == parent_ )
    {
        return xform_to_parent_;
    }
}

void SceneNode::SetPosition(const float3& pos)
{
    if(nullptr == parent_ )
    {
        
    }
}

float3 SceneNode::GetPosition() const
{

}

void SceneNode::SetRotation(const rotator& rot)
{
    if(nullptr == parent_ )
    {
        
    }
}

rotator SceneNode::GetRotation() const
{

}