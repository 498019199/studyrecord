#pragma once
#include <common/macro.h>
#include <common/Timer.h>
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

    float AspectRatio() const { return static_cast<float>(width_) / height_; }
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
    void CalculateFrameStats();

    void UpdateScene(float dt);
private:
    // Stats
    uint32_t total_num_frames_ = 0;
    float	fps_ = 0.f;
    float	accumulate_time_ = 0.f;
    uint32_t num_frames_ = 0;

    float app_time_ = 0.f;
	float frame_time_ = 0.f;
    Timer timer_;
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









