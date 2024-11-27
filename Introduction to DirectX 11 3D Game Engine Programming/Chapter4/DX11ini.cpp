#include <d3d11.h>
#include <common/WinApp.h>

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1920;
    settings.height = 1080;

    app.CreateAppWindow(settings);
    app.InitDevice(app.GetHWND(), settings);
    return 0;
}