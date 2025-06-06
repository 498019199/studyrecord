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
        
        if (ImGui::Begin("Texture Box"))
        {
            ImGui::SameLine(0.0f, 25.0f);                       // 下一个控件在同一行往右25像素单位
    
            auto& re = Context::Instance().RenderEngineInstance();
            bool is_wireframe_mode = re.ForceLineMode();
            ImGui::Checkbox("WireFrame Mode", &is_wireframe_mode);
            if(is_wireframe_mode != re.ForceLineMode())
            {
                re.ForceLineMode(is_wireframe_mode);
            }
    
            if(wd.camera_)
            {
                auto cameraPos = wd.camera_->EyePos();
                ImGui::Text("Camera Position\n%.2f %.2f %.2f", cameraPos.x(), cameraPos.y(), cameraPos.z());
            }
    
    
            // 不允许在操作UI时操作物体
            if (!ImGui::IsAnyItemActive() && wd.controller_)
            {
                 // 鼠标左键拖动平移
                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
                {
    
                }
                // 鼠标右键拖动旋转
                else if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
                {
                    wd.controller_->RotateRel(io.MouseDelta.x * scaler, io.MouseDelta.y * scaler, 0);
                }
                // 鼠标滚轮缩放
                else if (io.MouseWheel != 0.0f)
                {
                }
                // 位移
                else if(ImGui::IsKeyPressed(ImGuiKey_W))
                {
                    wd.controller_->Move(0, 0, scaler);
                }
                else if(ImGui::IsKeyPressed(ImGuiKey_S))
                {
                    wd.controller_->Move(0, 0, -scaler);
                }
                else if(ImGui::IsKeyPressed(ImGuiKey_A))
                {
                    wd.controller_->Move(-scaler, 0, 0);
                }
                else if(ImGui::IsKeyPressed(ImGuiKey_D))
                {
                    wd.controller_->Move(scaler, 0, 0);
                }
            }
        }
    
        ImGui::End();
        ImGui::Render();
    }
};

struct VSConstantBuffer
{
    float4x4 world;//16*4=64
    float4x4 view;//128
    float4x4 proj;//192
    float4x4 worldInvTranspose;
    float4x4 RotateM;
};

struct PSConstantBuffer
{
    DirectionalLightSource directional_light;
    //·默认环境光
    PointLightSource point_light;
    //·默认点光
    SpotLightSource spot_light;
    //默认汇聚光
    Material material;
    float4 eyePos;
};


struct VertexPosColor
{
    float3 pos;
    Color color;
};
class RenderableTriangle2 : public Renderable
{
public:
    RenderableTriangle2(const std::string& EffectMode)
    {
        LodsNum(7);
        auto& rf = Context::Instance().RenderFactoryInstance();
        rls_[0] = rf.MakeRenderLayout();
        rls_[0]->TopologyType(RenderLayout::TT_TriangleList);

        std::vector<VertexElement> merged_ves;
        VertexPosColor vertex[3];
        std::vector<uint16_t> indice_vec;

        vertex[0].pos = float3(-1.0f * 3, -0.866f * 3, 0.0f);
        vertex[0].color = Color(1.0f, 0.0f, 0.0f, 1.0f);

        vertex[1].pos = float3(0.0f * 3, 0.866f * 3, 0.0f);
        vertex[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);

        vertex[2].pos = float3(1.0f * 3, -0.866f * 3, 0.0f);
        vertex[2].color = Color(0.0f, 0.0f, 1.0f, 1.0f);

        merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Diffuse, 0, EF_ABGR32F));

        auto vb = rf.MakeVertexBuffer(BU_Dynamic, EAH_GPU_Read | EAH_GPU_Write, static_cast<uint32_t>(3 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        indice_vec = { 0, 1, 2 };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
            static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        effect_ = SyncLoadRenderEffect(EffectMode);
        technique_ = effect_->TechniqueByName("Copy");
        auto& re = Context::Instance().RenderEngineInstance();
        int ByteWidth = vb->Size();
        for(int i = 1; i < 7; ++i)
        {
            ByteWidth *= 3;
            rls_[i] = rf.MakeRenderLayout();
            rls_[i]->TopologyType(RenderLayout::TT_TriangleList);
            auto vb_out = rf.MakeVertexBuffer(BU_Dynamic, EAH_GPU_Write, ByteWidth, nullptr);
            rls_[i]->BindVertexStream(vb_out, merged_ves);

            re.BindSOBuffers(rls_[i]);
            re.DoRender(*effect_, *technique_, *rls_[i - 1]);
            re.BindSOBuffers(RenderLayoutPtr());            
        }

        technique_ = effect_->TechniqueByName("Basic_2D");
        effect_constant_buffer_ = effect_->CBufferByName("VSConstantBuffer");
        mvp_offset_ = effect_->ParameterByName("mvp")->CBufferOffset();
        // 初始化用于VS的常量缓冲区的值
        auto world_mat = float4x4::Identity();
        auto view_mat = LookAtLH(
            float3(0.0f, 0.0f, -5.0f),
            float3(0.0f, 0.0f, 0.0f),
            float3(0.0f, 1.0f, 0.0f));
        auto proj_mat = MathWorker::PerspectiveFovLH(MathWorker::PI / 3.f, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f);  
        MVPdMat(*effect_constant_buffer_) = world_mat * view_mat * proj_mat;
    }

    float4x4& MVPdMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(mvp_offset_);
	}

private:
    uint32_t mvp_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_;
};

class RenderableSplitedSnow : public Renderable
{
public:
    RenderableSplitedSnow()
    {
        // 设置三角形顶点
        float sqrt3 = sqrtf(3.0f);
        VertexPosColor vertex[] = 
        {
            { float3(-3.0f / 4, -sqrt3 / 4, 0.0f),  Color(1.0f, 1.0f, 1.0f, 1.0f) },
            { float3(0.0f, sqrt3 / 2, 0.0f),        Color(1.0f, 1.0f, 1.0f, 1.0f) },
            { float3(0.0f, sqrt3 / 2, 0.0f),        Color(1.0f, 1.0f, 1.0f, 1.0f) },
            { float3(3.0f / 4, -sqrt3 / 4, 0.0f),   Color(1.0f, 1.0f, 1.0f, 1.0f) },
            { float3(3.0f / 4, -sqrt3 / 4, 0.0f),   Color(1.0f, 1.0f, 1.0f, 1.0f) },
            { float3(-3.0f / 4, -sqrt3 / 4, 0.0f),  Color(1.0f, 1.0f, 1.0f, 1.0f) }
        };

        
    }
};

void CreateScene1()
{
    auto tri = new RenderableTriangle2("Triangle.xml");
    Context::Instance().WorldInstance().AddRenderable(tri);
}

class GeometryShaderWinApp2 : public WinAPP
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
        if (ImGui::Begin("Stream Output"))
        {
            static int curr_item = 0;
            static const char* modes[] = {
                "Splited Triangle",
                "Splited Snow",
                "Splited Sphere"
            };
    
            if(ImGui::SliderInt("Level", &m_CurrIndex, 0, 6))
            {
                if(able_)
                {
                    able_->ActiveLod(m_CurrIndex);
                }
            }

            if (ImGui::Combo("Mode", &curr_item, modes, ARRAYSIZE(modes)))
            {
                m_ShowMode = static_cast<Mode>(curr_item);

                switch ( m_ShowMode )   
                {
                    case Mode::SplitedTriangle:
                    {
                        able_ = new RenderableTriangle2("Streamout.xml");
                        Context::Instance().WorldInstance().AddRenderable(able_);
                    }
                    break;

                    case Mode::SplitedSnow:
                    {

                    }
                    break;
                }
            }
        }
    
        if(0)
        {        
            std::vector<VertexElement> merged_ves;
            merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_BGR32F));
            merged_ves.emplace_back(VertexElement(VEU_Diffuse, 0, EF_ABGR32F));

            auto& re = Context::Instance().RenderEngineInstance();
            auto& rf = Context::Instance().RenderFactoryInstance();
            
            {
                auto rl_out = rf.MakeRenderLayout();
                rl_out->TopologyType(RenderLayout::TT_TriangleList);
                auto vb_out = rf.MakeVertexBuffer(BU_Dynamic, EAH_GPU_Write, 84 * 1 * 3, nullptr);
                rl_out->BindVertexStream(vb_out, merged_ves);
                
                re.BindSOBuffers(rl_out);
                re.DoRender(*able_->effect_, *able_->technique_, *able_->rls_[0]);
                re.BindSOBuffers(RenderLayoutPtr()); 
                

                GraphicsBufferPtr buff_cpu;
                GraphicsBuffer* buff_cpu_ptr;
                if (vb_out->AccessHint() & EAH_CPU_Read)
                {
                    buff_cpu_ptr = vb_out.get();
                }
                else
                {
                    buff_cpu = rf.MakeVertexBuffer(BU_Static, EAH_CPU_Read, vb_out->Size(), nullptr);
                    buff_cpu_ptr = buff_cpu.get();
                    vb_out->CopyToBuffer(*buff_cpu_ptr);
                }

                GraphicsBuffer::Mapper buff_mapper(*buff_cpu_ptr, BA_Read_Only);
                const VertexPosColor* buff = reinterpret_cast<const VertexPosColor*>(buff_mapper.Pointer<VertexPosColor>());
                uint32_t num_elems = 84 * 1 * 3 / sizeof(VertexPosColor);
                std::cout << "begin " << std::endl;
                for (uint32_t i = 0; i < num_elems; ++ i)
                {
                    std::cout << "position: " << i << " " << buff[i].pos.x() << "," << buff[i].pos.y() << "," << buff[i].pos.z() << "," << buff[i].pos.z() << "," 
                                << "color:" << buff[i].color.r() << "," << buff[i].color.g() << "," << buff[i].color.b() << "," << buff[i].color.a() << "," << std::endl;
                }
            }
        }
        ImGui::End();
        ImGui::Render();
    }

private:
    enum class Mode { SplitedTriangle, SplitedSnow, SplitedSphere };
    Mode m_ShowMode;											// 当前显示模式
    int m_CurrIndex {0};
    Renderable* able_{nullptr};
};

int main() {
    GeometryShaderWinApp2 app;
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