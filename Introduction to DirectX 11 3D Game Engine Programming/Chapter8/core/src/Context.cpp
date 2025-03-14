#include <core/Context.h>
#include <core/Util.h>
#include "D3D11/D3D11RenderFactory.h"

#include <filesystem>

namespace RenderWorker
{
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
    COMMON_ASSERT(app_);
    return *app_;
}

void Context::RenderEngineInstance(RenderEngine& render_engine)
{
    render_engine_ = &render_engine;
}

RenderEngine& Context::RenderEngineInstance() const
{
    COMMON_ASSERT(render_engine_);
    return *render_engine_;
}

RenderFactory& Context::RenderFactoryInstance()
{
    COMMON_ASSERT(render_engine_);
    return *render_factory_;
}

World& Context::WorldInstance()
{
    COMMON_ASSERT(world_);
    return *world_;
}


void Context::LoadConfig(const char* file_name)
{
    render_factory_ = MakeSharedPtr<D3D11RenderFactory>();
    COMMON_ASSERT(render_factory_);

    world_ = MakeSharedPtr<World>();
    COMMON_ASSERT(world_);

    work_path_ = std::filesystem::current_path().parent_path().parent_path().string();
    resource_path_ = work_path_ + "\\Models\\Chapter9\\";
}

const std::string& Context::GetWorkPath() const
{
    return work_path_;
}

const std::string& Context::GetResourcePath() const
{
    return resource_path_;
}

}