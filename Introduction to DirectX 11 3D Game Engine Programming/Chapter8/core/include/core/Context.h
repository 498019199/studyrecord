#pragma once
#include <core/WinApp.h>
#include <core/World.h>
#include <core/RenderFactory.h>
#include <core/RenderEngine.h>

namespace RenderWorker
{
struct RenderSettings
{
    bool    full_screen = false;
    int		left = 0;
    int		top = 0;

    int		width;
    int		height;

    uint32_t sample_count = 1;
    uint32_t sample_quality = 0;
};

class Context
{
public:
    Context() = default;
    ~Context() = default;

    static Context& Instance();

    void AppInstance(WinAPP& app);
    WinAPP& AppInstance();

    void RenderEngineInstance(RenderEngine& render_engine);
    RenderEngine& RenderEngineInstance() const;

    RenderFactory& RenderFactoryInstance();
    World& WorldInstance();
    
    void LoadConfig(const char* file_name);
private:
    static std::unique_ptr<Context> instance_;
    WinAPP* app_;

    RenderEngine* render_engine_;
    RenderFactoryPtr render_factory_;
    WorldPtr world_;
};

}



