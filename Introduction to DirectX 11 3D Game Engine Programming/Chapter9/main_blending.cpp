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

struct VertexPosNormalTex
{
    float3 pos;
    float3 normal;
    float2 tex;
};
class RenderablePlaneTex : public Renderable
{
public:
    RenderablePlaneTex(float width, float depth, float texU, float texV, const std::string& DDS)
    {
        auto& rf = Context::Instance().RenderFactoryInstance();
        rls_[0] = rf.MakeRenderLayout();
        rls_[0]->TopologyType(RenderLayout::TT_TriangleList);

        std::vector<VertexElement> merged_ves;
        VertexPosNormalTex vertex[4];
        std::vector<uint16_t> indice_vec;

        vertex[0].pos = float3(-width / 2, 0.0f, -depth / 2);
        vertex[0].normal = float3(0.0f, 1.0f, 0.0f);
        vertex[0].tex = float2(0.0f, texV);

        vertex[1].pos = float3(-width / 2, 0.0f, depth / 2);
        vertex[1].normal = float3(0.0f, 1.0f, 0.0f);
        vertex[1].tex = float2(0.0f, 0.0f);

        vertex[2].pos = float3(width / 2, 0.0f, depth / 2);
        vertex[2].normal = float3(0.0f, 1.0f, 0.0f);
        vertex[2].tex = float2(texU, 0.0f);

        vertex[3].pos = float3(width / 2, 0.0f, -depth / 2);
        vertex[3].normal = float3(0.0f, 1.0f, 0.0f);
        vertex[3].tex = float2(texU, texV);

        merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Normal, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Diffuse, 0, EF_ABGR32F));

        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(4 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        indice_vec = { 0, 1, 2, 2, 3, 0 };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
            static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        auto floor = RenderablePlane(20.0f, 20.0f, 5.0f, 5.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));

        auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
        currentPath += "\\Chapter9\\HLSL\\";
        effect_ = MakeSharedPtr<RenderEffect>();
        ShaderDesc desc1;
        desc1.func_name = "VS";
        desc1.profile = currentPath + "Basic_2D_VS";
        desc1.tech_pass_type = 0xFFFFFFFF;
        effect_->AddShaderDesc("vertex_shader", desc1);
        desc1.func_name = "PS";
        desc1.profile = currentPath + "Basic_2D_PS";
        effect_->AddShaderDesc("pixel_shader", desc1);
        effect_->Load(currentPath);

        SamplerStateDesc desc;
        desc.addr_mode_u = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_v = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_w = TexAddressingMode::TAM_Wrap;
        desc.filter = TexFilterOp::TFO_Min_Mag_Mip_Linear;
        desc.max_anisotropy ;
        desc.min_lod = 0.f;
        desc.max_lod = std::numeric_limits<float>::max();
        desc.mip_map_lod_bias = 0;
        desc.cmp_func = CompareFunction::CF_AlwaysFail;
        effect_->sm1_ = rf.MakeSamplerStateObject(desc);

        const std::string file_path1 = Context::Instance().GetResourcePath() + DDS;
        auto tex1 = LoadTexture(file_path1, EAH_GPU_Read | EAH_Immutable);
        effect_->srv1_ = rf.MakeTextureSrv(tex1);
    }
};

class RenderableBoxTex : public Renderable
{
public:
    RenderableBoxTex(float width, float height, float depth, const Color & color)
    {
        float w2 = width / 2, h2 = height / 2, d2 = depth / 2;
        auto& rf = Context::Instance().RenderFactoryInstance();
        rls_[0] = rf.MakeRenderLayout();
        rls_[0]->TopologyType(RenderLayout::TT_TriangleList);

        std::vector<VertexElement> merged_ves;
        Vertex8 vertex[24];

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
            // 左面(-X面)
            vertex[i + 4].normal = float3(-1.0f, 0.0f, 0.0f);
            // 顶面(+Y面)
            vertex[i + 8].normal= float3(0.0f, 1.0f, 0.0f);
            // 底面(-Y面)
            vertex[i + 12].normal = float3(0.0f, -1.0f, 0.0f);
            // 背面(+Z面)
            vertex[i + 16].normal = float3(0.0f, 0.0f, 1.0f);
            // 正面(-Z面)
            vertex[i + 20].normal = float3(0.0f, 0.0f, -1.0f);
        }

        for (UINT i = 0; i < 6; ++i)
        {
            vertex[i * 4].tex = float2(0.0f, 1.0f);
            vertex[i * 4 + 1].tex = float2(0.0f, 0.0f);
            vertex[i * 4 + 2].tex = float2(1.0f, 0.0f);
            vertex[i * 4 + 3].tex = float2(1.0f, 1.0f);
        }

        merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_Normal, 0, EF_BGR32F));
        merged_ves.emplace_back(VertexElement(VEU_TextureCoord, 0, EF_GR32F));
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
        currentPath += "\\Chapter8\\HLSL\\";
        effect_ = MakeSharedPtr<RenderEffect>();
        ShaderDesc desc1;
        desc1.func_name = "VS";
        desc1.profile = currentPath + "Basic_2D_VS";
        desc1.tech_pass_type = 0xFFFFFFFF;
        effect_->AddShaderDesc("vertex_shader", desc1);
        desc1.func_name = "PS";
        desc1.profile = currentPath + "Basic_2D_PS";
        effect_->AddShaderDesc("pixel_shader", desc1);
        effect_->Load(currentPath);


        SamplerStateDesc desc;
        desc.addr_mode_u = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_v = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_w = TexAddressingMode::TAM_Wrap;
        desc.filter = TexFilterOp::TFO_Min_Mag_Mip_Linear;
        desc.max_anisotropy ;
        desc.min_lod = 0.f;
        desc.max_lod = std::numeric_limits<float>::max();
        desc.mip_map_lod_bias = 0;
        desc.cmp_func = CompareFunction::CF_AlwaysFail;
        effect_->sm1_ = rf.MakeSamplerStateObject(desc);

        const std::string file_path1 = Context::Instance().GetResourcePath() + "WireFence.dds";
        auto tex1 = LoadTexture(file_path1, EAH_GPU_Read | EAH_Immutable);
        effect_->srv1_ = rf.MakeTextureSrv(tex1);

        desc.addr_mode_u = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_v = TexAddressingMode::TAM_Wrap;
        desc.addr_mode_w = TexAddressingMode::TAM_Wrap;
        desc.filter = TexFilterOp::TFO_Min_Mag_Mip_Linear;
        desc.max_anisotropy ;
        desc.min_lod = 0.f;
        desc.max_lod = std::numeric_limits<float>::max();
        desc.mip_map_lod_bias = 0;
        desc.cmp_func = CompareFunction::CF_AlwaysFail;
        effect_->sm2_ = rf.MakeSamplerStateObject(desc);
    }
};

void CreateScene()
{
    // 初始化地板
    auto floor = new RenderablePlaneTex(20.0f, 20.0f, 5.0f, 5.0f, "floor.dds");

    // 初始化墙体
    RenderablePlaneTex* wall[4];
    for (int i = 0; i < 4; ++i)
    {
        wall[i] = new RenderablePlaneTex(20.0f, 8.0f, 5.0f, 1.5f, "brick.dds");
    }

    // 初始化篱笆盒
    auto box = new RenderableBoxTex(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f));
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
    

    app.Run();
    return 0;
}