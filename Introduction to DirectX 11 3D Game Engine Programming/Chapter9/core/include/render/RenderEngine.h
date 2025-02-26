
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

    // For debug only, 设置为绘制线框
    void ForceLineMode(bool line);
    bool ForceLineMode() const
    {
        return force_line_mode_;
    }
private:
    // 强制使用线框模式
    bool force_line_mode_ {false}; 
    RenderStateObjectPtr cur_rs_obj_;
    RenderStateObjectPtr cur_line_rs_obj_;
};



}