#include <core/WinApp.h>
#include <core/D3D11Util.h>
#include <core/RenderableHelper.h>
#include <core/Context.h>
#include <math/math.h>
#include <core/World.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

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

bool InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // 允许键盘控制
    io.ConfigWindowsMoveFromTitleBarOnly = true;              // 仅允许标题拖动

    // 设置Dear ImGui风格
    ImGui::StyleColorsDark();

    // 设置平台/渲染器后端
    ImGui_ImplWin32_Init(Context::Instance().AppInstance().GetHWND());
    auto re = Context::Instance().RenderEngineInstance().D3DDevice();
    auto ctx = Context::Instance().RenderEngineInstance().D3DDeviceImmContext();
    ImGui_ImplDX11_Init(re, ctx);
    return true;
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
    InitImGui();
    Context::Instance().WorldInstance().BeginWorld();
    
	//Light();
    //CreateBox();
    CreateShere();

    app.Run();
    return 0;
}