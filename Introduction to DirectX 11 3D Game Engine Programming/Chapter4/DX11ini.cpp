#include <d3d11.h>
#include <common/WinApp.h>

int main() {
    WinAPP app;
    RenderSettings settings{false, 0, 0, 1920, 1080};
    app.CreateAppWindow(settings);
    return 0;
}