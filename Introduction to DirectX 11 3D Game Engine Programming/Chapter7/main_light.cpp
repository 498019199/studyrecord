#include <core/WinApp.h>
#include <core/D3D11Util.h>
#include <core/RenderableHelper.h>
#include <core/Context.h>
#include <math/math.h>
#include <core/World.h>

#include <filesystem>
void CreateBox()
{
    // 创建立方体网格数据
    auto box = new RenderableBox(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().WorldInstance().AddRenderable(box);
}

void CreateShere()
{
    // 创建球体网格数据，levels和slices越大，精度越高。
    auto sphere = new RenderableSphere(1.0f, 20, 20, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().WorldInstance().AddRenderable(sphere);

}

void Light()
{
	
}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1280;
    settings.height = 720;
    Context::Instance().LoadConfig("");
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
    Context::Instance().WorldInstance().BeginWorld();
    
	//Light();
    //CreateBox();
    CreateShere();

    app.Run();
    return 0;
}