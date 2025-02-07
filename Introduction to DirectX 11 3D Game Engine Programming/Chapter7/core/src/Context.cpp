#include <core/Context.h>
#include <cassert>
#include <core/D3D11RenderFactory.h>

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
    COMMON_ASSERT(render_engine_);
    return *render_engine_;
}

D3D11RenderFactory& Context::RenderFactoryInstance()
{
    COMMON_ASSERT(render_engine_);
    return *render_factory_;
}

void Context::LoadConfig(const char* file_name)
{
    render_factory_ = std::make_shared<D3D11RenderFactory>();
    COMMON_ASSERT(render_factory_);
}