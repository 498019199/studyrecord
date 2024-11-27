#include <d3d11.h>
#include <common/WinApp.h>

void test_window()
{
     WinAPP test_app;
    RenderSettings settings;
    settings.width = 1920;
    settings.height = 1080;

    test_app.CreateAppWindow(settings);
}

int main()
{
    test_window();
    return 0;
}