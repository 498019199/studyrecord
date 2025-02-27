#include <core/SceneNode.h>

namespace RenderWorker
{

SceneNode* SceneNode::Parent() const
{
    return parent_;    
}

void SceneNode::TransformToParent(const float4x4& mat)
{
    xform_to_parent_ = mat;
    inv_xform_to_parent_ = MathWorker::Inverse(mat);
}

void SceneNode::TransformToWorld(const float4x4& mat)
{
    if (parent_)
    {
        xform_to_parent_ = mat * parent_->InverseTransformToWorld();
    }
    else
    {
        xform_to_parent_ = mat;
    }
    inv_xform_to_parent_ = MathWorker::Inverse(mat);
}

const float4x4& SceneNode::TransformToParent() const
{
    return xform_to_parent_;
}

const float4x4& SceneNode::InverseTransformToParent() const
{
    return inv_xform_to_parent_;
}

const float4x4& SceneNode::TransformToWorld() const
{
    if(nullptr == parent_)
    {
        return xform_to_parent_;
    }
    else
    {
        auto* parent = Parent();
        xform_to_world_ = xform_to_parent_;
        while (nullptr != parent)
        {
            xform_to_world_ *= parent->TransformToParent();
            parent = parent->Parent();
        }
        return xform_to_world_;
    }
}

const float4x4& SceneNode::InverseTransformToWorld() const
{
    if (parent_ == nullptr)
    {
        return inv_xform_to_parent_;
    }
    else
    {
        inv_xform_to_world_ = MathWorker::Inverse(TransformToWorld());
        return inv_xform_to_world_;
    }
}

void SceneNode::Update(float dt)
{
    
}

}