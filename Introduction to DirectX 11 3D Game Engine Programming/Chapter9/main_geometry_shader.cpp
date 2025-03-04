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
    RenderableTriangle2()
    {
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

        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(3 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        // indice_vec = { 0, 1, 2 };
        // auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        //     static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        // rls_[0]->BindIndexStream(ib, EF_R16UI);

        effect_ = SyncLoadRenderEffect("Triangle.xml");
        technique_ = effect_->TechniqueByName("Basic_2D");

        effect_constant_buffer_ = effect_->CBufferByName("VSConstantBuffer");
        mvp_offset_ = effect_->ParameterByName("mvp")->CBufferOffset();

        // 初始化用于VS的常量缓冲区的值
        auto view_mat = LookAtLH(
            float3(0.0f, 0.0f, -5.0f),
            float3(0.0f, 0.0f, 0.0f),
            float3(0.0f, 1.0f, 0.0f));
        auto proj_mat = MathWorker::PerspectiveFovLH(MathWorker::PI / 3.f, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f);  
        MVPdMat(*effect_constant_buffer_) = proj_mat * view_mat;
    }

    float4x4& MVPdMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(mvp_offset_);
	}

private:
    uint32_t mvp_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_;
};

void CreateScene()
{
    auto tri = new RenderableTriangle2();
    Context::Instance().WorldInstance().AddRenderable(tri);
}

int main() {
    WinAPP app;
    RenderSettings settings;
    settings.width = 1280;
    settings.height = 720;
    Context::Instance().AddResource("//Models//Chapter9//");
    Context::Instance().LoadConfig("");
    app.CreateAppWindow(settings);
	Context::Instance().AppInstance(app);
    app.InitDevice(app.GetHWND(), settings);
    Context::Instance().WorldInstance().BeginWorld();
    
    //Test_chapter7();
    CreateScene();

    app.Run();
    return 0;
}