#pragma once

#include <core/Renderable.h>

class RenderableTriangle : public Renderable
{

};

class RenderableBox : public Renderable
{
public:
    RenderableBox(float width, float height, float depth, const Color & color);
};

class RenderableTriSphere : public Renderable
{

};