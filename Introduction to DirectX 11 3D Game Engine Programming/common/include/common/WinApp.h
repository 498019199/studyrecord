#pragma once

#include <Windows.h>
#include <cstdint>

struct RenderSettings
{
    bool    full_screen;
    int		left;
	int		top;

    int		width;
    int		height;

    uint32_t sample_count;
	uint32_t sample_quality;
};

class WinAPP
{
public:
    bool CreateAppWindow(const RenderSettings& settings);

    int Run();

    HWND GetHWND() const { return hwnd_; }
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
private:
    HWND hwnd_;
    uint32_t win_style_;
    float dpi_scale_ = 1.f;
};

