
#pragma once

namespace RenderWorker
{

class RenderEngine
{
public:
    RenderEngine();
    virtual ~RenderEngine() noexcept;

    virtual void EndRender() const = 0;
};
}