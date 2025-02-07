#include <core/WinApp.h>
#include <core/D3D11Util.h>
#include <core/RenderableHelper.h>
#include <core/Context.h>
#include <math/math.h>
#include <core/SceneManager.h>

#include <filesystem>
extern int g_IndexCount = 0;
struct Vertex
{
	float3 pos;
	float3 normal;
	Color color;
};
const D3D11_INPUT_ELEMENT_DESC inputLayout[3] = 
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

void CreateBox()
{
    // 创建立方体网格数据
    auto box = new RenderableBox(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().SceneMgr().AddRenderable(box);
}

void CreateShere()
{
    // 创建球体网格数据，levels和slices越大，精度越高。
    auto sphere = new RenderableSphere(1.0f, 20, 20, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().SceneMgr().AddRenderable(sphere);
}

void Light()
{
	
}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1280;
    settings.height = 720;
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
	
	//Light();
    CreateBox();
    
    app.Run();
    return 0;
}