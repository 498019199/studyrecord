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
        merged_ves.emplace_back(VertexElement(VEU_TextureCoord, 0, EF_ABGR32F));

        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(4 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        indice_vec = { 0, 1, 2, 2, 3, 0 };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
            static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        auto floor = RenderablePlane(20.0f, 20.0f, 5.0f, 5.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));

        auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
        effect_ = SyncLoadRenderEffect("box2D.xml");


        auto currentPath2 = std::filesystem::current_path().parent_path().parent_path().string();
        auto src1_tex_param = effect_->ParameterByName("src1_tex");
        *src1_tex_param = SyncLoadTexture(DDS, EAH_GPU_Read | EAH_Immutable);
    }
};

struct Vertex8
{
    float3 pos;
    float3 normal;
    float2 tex;
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

        effect_ = SyncLoadRenderEffect("box3D.xml");
        technique_ = effect_->TechniqueByName("Basic_3D");

        auto currentPath2 = std::filesystem::current_path().parent_path().parent_path().string();
        const std::string file_path1 = currentPath2 + "\\Models\\Chapter9\\" + "WireFence.dds";
        auto src1_tex_param = effect_->ParameterByName("src1_tex");
        *src1_tex_param = SyncLoadTexture(file_path1, EAH_GPU_Read | EAH_Immutable);


        // ******************
        // 初始化默认光照
        // 方向光
        auto cbuff = (effect_->CBufferByName("PSConstantBuffer")) ;
        directional_light_offset_ = effect_->ParameterByName("directional_light")->CBufferOffset();
        point_light_offset_ = effect_->ParameterByName("point_light")->CBufferOffset();
        spot_light_offset_ = effect_->ParameterByName("spot_light")->CBufferOffset();
        material_offset_ = effect_->ParameterByName("material")->CBufferOffset();
        eys_pos_offset_ = effect_->ParameterByName("eyePos")->CBufferOffset();
        
        DirectionalLight(*cbuff).ambient_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
        DirectionalLight(*cbuff).diffuse_ = float4(0.8f, 0.8f, 0.8f, 1.0f);
        DirectionalLight(*cbuff).specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        DirectionalLight(*cbuff).direction_ = float3(-0.577f, -0.577f, 0.577f);
        // 点光
        PointLight(*cbuff).pos_ = float3(0.0f, 0.0f, -10.0f);
        PointLight(*cbuff).ambient_ = float4(0.3f, 0.3f, 0.3f, 1.0f);
        PointLight(*cbuff).diffuse_ = float4(0.7f, 0.7f, 0.7f, 1.0f);
        PointLight(*cbuff).specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        PointLight(*cbuff).att_ = float3(0.0f, 0.1f, 0.0f);
        PointLight(*cbuff).range_ = 25.0f;
        // 聚光灯
        SpotLight(*cbuff).pos_ = float3(0.0f, 0.0f, -5.0f);
        SpotLight(*cbuff).direction_ = float3(0.0f, 0.0f, 1.0f);
        SpotLight(*cbuff).ambient_ = float4(0.0f, 0.0f, 0.0f, 1.0f);
        SpotLight(*cbuff).diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        SpotLight(*cbuff).specular_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        SpotLight(*cbuff).att_ = float3(1.0f, 0.0f, 0.0f);
        SpotLight(*cbuff).spot_ = 12.0f;
        SpotLight(*cbuff).range_ = 10000.0f;

        // 初始化用于PS的常量缓冲区的值
        SetMaterial(*cbuff).ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        SetMaterial(*cbuff).diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        SetMaterial(*cbuff).specular_ = float4(0.5f, 0.5f, 0.5f, 5.0f);

        // // 初始化用于VS的常量缓冲区的值
        // vs_cb_.world = float4x4::Identity();
        // vs_cb_.view = Transpose(LookAtLH(
        //     float3(0.0f, 0.0f, -5.0f),
        //     float3(0.0f, 0.0f, 0.0f),
        //     float3(0.0f, 1.0f, 0.0f)));
        // vs_cb_.proj = MathWorker::Transpose(MathWorker::PerspectiveFovLH(MathWorker::PIdiv2, Context::Instance().AppInstance().AspectRatio(), 1.f, 1000.f));    
        // vs_cb_.worldInvTranspose = float4x4::Identity();


        // // 使用默认平行光
        // ps_cb_.directional_light = default_directional_light_;
        // // 注意不要忘记设置此处的观察位置，否则高亮部分会有问题
        // ps_cb_.eyePos = float4(0.0f, 0.0f, -5.0f, 0.0f);
    }

    DirectionalLightSource& DirectionalLight(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<DirectionalLightSource>(directional_light_offset_);
	}

    PointLightSource& PointLight(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<PointLightSource>(point_light_offset_);
	}

    SpotLightSource& SpotLight(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<SpotLightSource>(spot_light_offset_);
	}

    Material& SetMaterial(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<Material>(material_offset_);
	}

    float3& EysPos(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float3>(eys_pos_offset_);
	}

    void Update(float dt) override
    {
        
    }
private:
    uint32_t directional_light_offset_;
    uint32_t point_light_offset_;
    uint32_t spot_light_offset_;
    uint32_t material_offset_;
    uint32_t eys_pos_offset_;
};

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

        effect_ = SyncLoadRenderEffect("Cube.xml");
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

        effect_constant_buffer_->Dirty(true);
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

void CreateScene()
{
    // // 初始化地板
    // auto floor = new RenderablePlaneTex(20.0f, 20.0f, 5.0f, 5.0f, "floor.dds");
    // Context::Instance().WorldInstance().AddRenderable(floor);

    // // 初始化墙体
    // for (int i = 0; i < 4; ++i)
    // {
    //     auto wal = new RenderablePlaneTex(20.0f, 8.0f, 5.0f, 1.5f, "brick.dds");
    //     Context::Instance().WorldInstance().AddRenderable(wal);
    // }

    // 初始化篱笆盒
    auto box = new RenderableBoxTex(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f));
    Context::Instance().WorldInstance().AddRenderable(box);
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