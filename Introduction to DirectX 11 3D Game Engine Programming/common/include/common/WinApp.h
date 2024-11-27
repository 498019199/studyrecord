#pragma once

#include <Windows.h>
#include <cstdint>

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

class D3D11RenderDevice;

class WinAPP
{
public:
    bool CreateAppWindow(const RenderSettings& settings);
    bool InitDevice(HWND hwnd, const RenderSettings& settings);
    
    int Run();

    HWND GetHWND() const { return hwnd_; }
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
private:
    HWND hwnd_;
    uint32_t win_style_;
    float dpi_scale_ = 1.f;

    D3D11RenderDevice *device_;
};


