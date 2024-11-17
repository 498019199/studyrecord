#pragma one

struct RenderSettings
{
    int		width;
    int		height;
};

class WinAPP
{
    void CreateAppWindow(const RenderSettings& settings);

    int Run();
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    
private:
    HWND hwnd_;
};

