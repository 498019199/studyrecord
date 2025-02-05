#pragma once
#include <common/macro.h>
#include <Windows.h>
#include <cstdint>
#include <list>

class Timer;
class D3D11RenderEngine;
struct RenderSettings;
class D3D11RenderMesh;

class WinAPP
{
public:
    WinAPP();
    ~WinAPP();
    
    bool CreateAppWindow(const RenderSettings& settings);
    bool InitDevice(HWND hwnd, const RenderSettings& settings);
    
    int Run();

    HWND GetHWND() const { return hwnd_; }

    void AddActor(D3D11RenderMesh* obj);
    bool RemoveActor(D3D11RenderMesh* obj);
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
    void CalculateFrameStats();

    void UpdateScene(float dt);
private:
    // Stats
    bool is_paused = false;

    uint32_t	left_;
    uint32_t	top_;
    uint32_t	width_;
    uint32_t	height_;
    HWND hwnd_;
    uint32_t win_style_;
    float dpi_scale_ = 1.f;

    D3D11RenderEngine *device_;
    std::list<D3D11RenderMesh*> obj_mgr;
};









