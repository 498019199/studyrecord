#include <base/WinApp.h>
#include <common/Util.h>
#include <render/RenderableHelper.h>
#include <render/RenderEffect.h>
#include <base/Context.h>
#include <render/Texture.h>
#include <math/math.h>
#include <base/World.h>

#include <filesystem>
using namespace RenderWorker;

#define CHPATER_USE_IMGUISE 1
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

class GeometryShaderWinApp1 : public WinAPP
{
public:
    virtual void ImguiUpdate(float dt) override
    {
        // 这里添加
        ImGui_ImplDX11_NewFrame();     
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        // --------

        WinAppUpdate(dt);

        // 可以在这之前调用ImGui的UI部分
        // Direct3D 绘制部分
        Context::Instance().WorldInstance().UpdateScene(frame_time_);	

        // 下面这句话会触发ImGui在Direct3D的绘制
        // 因此需要在此之前将后备缓冲区绑定到渲染管线上
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    void WinAppUpdate(float dt)
    {
        static bool animateCube = true, customColor = false;
        static float phi = 0.0f, theta = 0.0f, phi2 = 0.0f;
        phi += 0.3f * dt, theta += 0.37f * dt, phi2 -= 0.01f;
        float const scaler = dt * 10;
    
        auto& wd = Context::Instance().WorldInstance();
        // 获取IO事件
        ImGuiIO& io = ImGui::GetIO();
        
        if (ImGui::Begin("Tree Billboard"))
        {

            ImGui::Checkbox("Enable Alpha-To-Coverage", &m_EnableAlphaToCoverage);
            if (ImGui::Checkbox("Enable Fog", &m_FogEnabled))
            {
                
            }

            if(m_FogEnabled)
            {
                static int curr_item = 0;
                static const char* modes[] = 
                {
                    "Daytime",
                    "Dark Night",
                };
                if (ImGui::Combo("Fog Mode", &curr_item, modes, ARRAYSIZE(modes)))
                {
                    m_IsNight = (curr_item == 1);
                    if(m_IsNight)
                    {
                        // 黑夜模式下变为逐渐黑暗
                    }
                    else
                    {
                        // 白天模式则对应雾效
                    }
                }

                if (ImGui::SliderFloat("Fog Range", &m_FogRange, 15.0f, 175.0f, "%.0f"))
                {

                }

                float fog_start = m_IsNight ? 5.0f : 15.0f;
                ImGui::Text("Fog: %.0f-%.0f", fog_start, m_FogRange + fog_start);
            }
        }
    
        ImGui::End();
        ImGui::Render();
    }

private:
    bool m_FogEnabled;										    // 是否开启雾效
    bool m_IsNight;											    // 是否黑夜
    bool m_EnableAlphaToCoverage;							    // 是否开启Alpha-To-Coverage
    float m_FogRange;										    // 雾效范围
};

int main() {
    GeometryShaderWinApp1 app;
    RenderSettings settings;
    settings.width = 1280;
    settings.height = 720;
    Context::Instance().AddResource("//Models//Chapter9//");
    Context::Instance().LoadConfig("");
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
    Context::Instance().WorldInstance().BeginWorld();
    
    //CreateScene1();

    app.Run();
    return 0;
}