#include <common/WinApp.h>
#include <common/D3D11Util.h>

#include <common/macro.h>
#include <math/math.h>

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace MathWorker;

int main() 
{
    WinAPP app;
    RenderSettings settings;
    settings.width = 1920;
    settings.height = 1080;
    app.CreateAppWindow(settings);
    app.InitDevice(app.GetHWND(), settings);
    app.Run();
    return 0;
}