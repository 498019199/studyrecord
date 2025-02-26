#include <core/WinApp.h>
#include <core/Util.h>
#include <render/RenderableHelper.h>
#include <render/RenderEffect.h>
#include <core/Context.h>
#include <render/Texture.h>
#include <math/math.h>
#include <core/World.h>

#include <filesystem>
using namespace RenderWorker;

struct Vertex7
{
    float3 pos;
    float3 normal;
    Color color;
};
class RenderableCubeTest : public Renderable
{
public:
    RenderableCubeTest(float width, float height, float depth, const Color & color)
    {
        float w2 = width / 2, h2 = height / 2, d2 = depth / 2;
        auto& rf = Context::Instance().RenderFactoryInstance();
        rls_[0] = rf.MakeRenderLayout();
        rls_[0]->TopologyType(RenderLayout::TT_TriangleList);

        std::vector<VertexElement> merged_ves;
        Vertex7 vertex[24];

        // 右面(+X面)
        vertex[0].pos = float3(w2, -h2, -d2);
        vertex[1].pos = float3(w2, h2, -d2);
        vertex[2].pos = float3(w2, h2, d2);
        vertex[3].pos = float3(w2, -h2, d2);
        // 左面(-X面)
        vertex[4].pos = float3(-w2, -h2, d2);
        vertex[5].pos = float3(-w2, h2, d2);
        vertex[6].pos = float3(-w2, h2, -d2);
        vertex[7].pos = float3(-w2, -h2, -d2);
        // 顶面(+Y面)
        vertex[8].pos = float3(-w2, h2, -d2);
        vertex[9].pos = float3(-w2, h2, d2);
        vertex[10].pos = float3(w2, h2, d2);
        vertex[11].pos = float3(w2, h2, -d2);
        // 底面(-Y面)
        vertex[12].pos = float3(w2, -h2, -d2);
        vertex[13].pos = float3(w2, -h2, d2);
        vertex[14].pos = float3(-w2, -h2, d2);
        vertex[15].pos = float3(-w2, -h2, -d2);
        // 背面(+Z面)
        vertex[16].pos = float3(w2, -h2, d2);
        vertex[17].pos = float3(w2, h2, d2);
        vertex[18].pos = float3(-w2, h2, d2);
        vertex[19].pos = float3(-w2, -h2, d2);
        // 正面(-Z面)
        vertex[20].pos = float3(-w2, -h2, -d2);
        vertex[21].pos = float3(-w2, h2, -d2);
        vertex[22].pos = float3(w2, h2, -d2);
        vertex[23].pos = float3(w2, -h2, -d2);

        for (UINT i = 0; i < 4; ++i)
        {
            // 右面(+X面)
            vertex[i].normal = float3(1.0f, 0.0f, 0.0f);
            vertex[i].color = color;

            // 左面(-X面)
            vertex[i + 4].normal = float3(-1.0f, 0.0f, 0.0f);
            vertex[i + 4].color = color;
            // 顶面(+Y面)
            vertex[i + 8].normal= float3(0.0f, 1.0f, 0.0f);
            vertex[i + 8].color = color;
            // 底面(-Y面)
            vertex[i + 12].normal = float3(0.0f, -1.0f, 0.0f);
            vertex[i + 12].color = color;
            // 背面(+Z面)
            vertex[i + 16].normal = float3(0.0f, 0.0f, 1.0f);
            vertex[i + 16].color = color;
            // 正面(-Z面)
            vertex[i + 20].normal = float3(0.0f, 0.0f, -1.0f);
            vertex[i + 20].color = color;
        }

        merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Normal, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Diffuse, 0, EF_ABGR32F));
        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(24 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        uint16_t indices[] = 
        {
            0, 1, 2, 2, 3, 0,		// 右面(+X面)
            4, 5, 6, 6, 7, 4,		// 左面(-X面)
            8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
            12, 13, 14, 14, 15, 12,	// 底面(-Y面)
            16, 17, 18, 18, 19, 16, // 背面(+Z面)
            20, 21, 22, 22, 23, 20	// 正面(-Z面)
        };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, sizeof(indices), indices);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
        currentPath += "\\Models\\Chapter9\\Cube.xml";
        effect_ = SyncLoadRenderEffect(currentPath);
        technique_ = effect_->TechniqueByName("Cube");
        effect_constant_buffer_ = effect_->CBufferByName("VSConstantBuffer");

        world_offset_ = effect_->ParameterByName("g_World")->CBufferOffset();
		view_offset_ = effect_->ParameterByName("g_View")->CBufferOffset();
		projection_offset_ = effect_->ParameterByName("g_Proj")->CBufferOffset();

        // 初始化用于VS的常量缓冲区的值
        WorldMat(*effect_constant_buffer_)= float4x4::Identity();
        ViewMat(*effect_constant_buffer_) = Transpose(LookAtLH(
            float3(0.0f, 0.0f, -5.0f),
            float3(0.0f, 0.0f, 0.0f),
            float3(0.0f, 1.0f, 0.0f)));
        ProjectionMat(*effect_constant_buffer_) = MathWorker::Transpose(
            MathWorker::PerspectiveFovLH(MathWorker::PIdiv2, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f));    
    }

    float4x4& WorldMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(world_offset_);
	}

    float4x4& ViewMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(view_offset_);
	}

    float4x4& ProjectionMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(projection_offset_);
	}

    void Update(float dt) override
    {
        static bool animateCube = true, customColor = false;
        static float phi = 0.0f, theta = 0.0f;
        phi += 0.3f * dt, theta += 0.37f * dt;
    
        auto world = MathWorker::Transpose(MathWorker::MatrixRotateX(phi) * MathWorker::MatrixRotateY(theta));
        auto worldInvTranspose = MathWorker::Transpose(MathWorker::MatrixInverse(world));
        WorldMat(*effect_constant_buffer_)= world;
    }
private:
    uint32_t world_offset_;
    uint32_t view_offset_;
    uint32_t projection_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_;
};

void Test_chapter7()
{
    auto box = new RenderableCubeTest(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().WorldInstance().AddRenderable(box);
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
    
    Test_chapter7();

    app.Run();
    return 0;
}