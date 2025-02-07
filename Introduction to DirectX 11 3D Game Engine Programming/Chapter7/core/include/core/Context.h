#pragma once
#include <core/common.h>



class Context
{
public:
    Context() = default;
    ~Context() = default;

    static Context& Instance();

    void AppInstance(WinAPP& app);
    WinAPP& AppInstance();

    void RenderEngineInstance(D3D11RenderEngine& render_engine);
    D3D11RenderEngine& RenderEngineInstance() const;

    D3D11RenderFactory& RenderFactoryInstance();
    SceneManager& SceneMgr();
    
    void LoadConfig(const char* file_name);
private:
    static std::unique_ptr<Context> instance_;
    WinAPP* app_;

    D3D11RenderEngine* render_engine_;
    RenderFactoryPtr render_factory_;
    SceneMgrPtr scene_mgr_;
};





