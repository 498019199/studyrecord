#include <common/Context.h>
#include <cassert>

std::unique_ptr<Context> Context::instance_;

Context& Context::Instance()
{
    if(!instance_)
    {
        if (!instance_)
		{
			instance_ = std::make_unique<Context>();
		}
    }

    return *instance_;
}

void Context::AppInstance(WinAPP& app)
{
    app_ = &app;
}

WinAPP& Context::AppInstance()
{
    assert(app_);
    return *app_;
}

void Context::RenderEngineInstance(D3D11RenderEngine& render_engine)
{
    render_engine_ = &render_engine;
}

D3D11RenderEngine& Context::RenderEngineInstance() const
{
    assert(render_engine_);
    return *render_engine_;
}

