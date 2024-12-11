#pragma once
#include <common/macro.h>
#include <Windows.h>
#include <cstdint>
class Timer;
class D3D11RenderEngine;
struct RenderSettings;

class WinAPP
{
public:
    WinAPP();
    ~WinAPP();
    
    bool CreateAppWindow(const RenderSettings& settings);
    bool InitDevice(HWND hwnd, const RenderSettings& settings);
    
    int Run();

    HWND GetHWND() const { return hwnd_; }
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
private:
    uint32_t	left_;
    uint32_t	top_;
    uint32_t	width_;
    uint32_t	height_;
    HWND hwnd_;
    uint32_t win_style_;
    float dpi_scale_ = 1.f;

    D3D11RenderEngine *device_;
    Timer* timer_;
};



