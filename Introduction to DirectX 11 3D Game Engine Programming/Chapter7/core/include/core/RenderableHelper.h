#pragma once

#include <core/D3D11Renderable.h>

class RenderableTriangle : public D3D11Renderable
{

};

class RenderableBox : public D3D11Renderable
{
public:
    RenderableBox(float width, float height, float depth, const Color & color);
};

class RenderableTriSphere : public D3D11Renderable
{

};