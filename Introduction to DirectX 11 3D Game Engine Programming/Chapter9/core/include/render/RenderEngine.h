
#pragma once
#include <render/RenderStateObject.h>

namespace RenderWorker
{

class RenderEngine
{
public:
    RenderEngine();
    virtual ~RenderEngine() noexcept;

    void SetStateObject(RenderStateObjectPtr const & rs_obj);

    virtual void EndRender() const = 0;

    // For debug only
    void ForceLineMode(bool line);
    bool ForceLineMode() const
    {
        return force_line_mode_;
    }
private:
    bool force_line_mode_; // 强制使用线框模式
    RenderStateObjectPtr cur_rs_obj_;
    RenderStateObjectPtr cur_line_rs_obj_;
};



}