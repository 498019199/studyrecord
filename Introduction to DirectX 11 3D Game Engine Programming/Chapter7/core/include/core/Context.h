#pragma once
#include <memory>

class WinAPP;
class D3D11RenderEngine;

class Context
{
public:
    Context() = default;
    ~Context() = default;

    static Context& Instance();

    void AppInstance(WinAPP& app);
    WinAPP& AppInstance();

    void RenderEngineInstance(D3D11RenderEngine& render_engine);
    D3D11RenderEngine& RenderEngineInstance();
private:
    static std::unique_ptr<Context> instance_;
    WinAPP* app_;
    D3D11RenderEngine* render_engine_;
};
