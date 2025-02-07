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

class RenderableSphere : public D3D11Renderable
{
public:
    RenderableSphere(float radius, int levels, int slices, const Color & color);
};

class RenderablePlane : public D3D11Renderable
{
public:
    RenderablePlane(float width, float depth, float texU, float texV, const Color & color);
};



class RenderDecal : public D3D11Renderable
{
public:
    
};
