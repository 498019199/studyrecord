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
        merged_ves.emplace_back(VertexElement(VEU_TextureCoord, 0, EF_GR32F));

        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(4 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        indice_vec = { 0, 1, 2, 2, 3, 0 };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
            static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        effect_ = SyncLoadRenderEffect("box2D.xml");
        technique_ = effect_->TechniqueByName("Basic_2D");

        auto src1_tex_param = effect_->ParameterByName("src1_tex");
        *src1_tex_param = SyncLoadTexture(DDS, EAH_GPU_Read | EAH_Immutable);

        effect_constant_buffer_ = effect_->CBufferByName("VSConstantBuffer");
        world_offset_ = effect_->ParameterByName("gWorld")->CBufferOffset();
		view_offset_ = effect_->ParameterByName("gView")->CBufferOffset();
		projection_offset_ = effect_->ParameterByName("gProj")->CBufferOffset();
        world_inv_transpose_offset_ = effect_->ParameterByName("gWorldInvTranspose")->CBufferOffset();

        auto& camera = Context::Instance().WorldInstance().camera_;
        ProjectionMat(*effect_constant_buffer_) = MathWorker::Transpose(camera->ProjMatrix());  
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

    float4x4& WorldInvTransposeMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(world_inv_transpose_offset_);
	}

    void Update(float dt) override
    {
        auto world = MathWorker::Transpose(TransformToWorld());
        auto worldInvTranspose = MathWorker::Transpose(MathWorker::Inverse(world));
        WorldMat(*effect_constant_buffer_)= world;
        WorldInvTransposeMat(*effect_constant_buffer_) = worldInvTranspose;

        auto& camera = Context::Instance().WorldInstance().camera_;
        ViewMat(*effect_constant_buffer_) = MathWorker::Transpose(camera->ViewMatrix());
        effect_constant_buffer_->Dirty(true);
    }
private:
    uint32_t world_offset_;
    uint32_t view_offset_;
    uint32_t projection_offset_;
    uint32_t world_inv_transpose_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_;
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
    RenderableBoxTex(float width, float height, float depth, const Color & color, const std::string& DDS, const std::string& Mode)
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
        technique_ = effect_->TechniqueByName(Mode);

        auto src1_tex_param = effect_->ParameterByName("src1_tex");
        *src1_tex_param = SyncLoadTexture(DDS, EAH_GPU_Read | EAH_Immutable);

        // ******************
        // 初始化默认光照
        // 方向光
        effect_constant_buffer_ps_ = (effect_->CBufferByName("PSConstantBuffer")) ;
        directional_light_offset_ = effect_->ParameterByName("gDirLight")->CBufferOffset();
        point_light_offset_ = effect_->ParameterByName("gPointLight")->CBufferOffset();
        spot_light_offset_ = effect_->ParameterByName("gSpotLight")->CBufferOffset();
        material_offset_ = effect_->ParameterByName("gMaterial")->CBufferOffset();
        eys_pos_offset_ = effect_->ParameterByName("gEyePosW")->CBufferOffset();
        
        // 初始化默认光照
        // 方向光
        DirectionalLight(*effect_constant_buffer_ps_).ambient_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).diffuse_ = float4(0.8f, 0.8f, 0.8f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).direction_ = float3(-0.577f, -0.577f, 0.577f);
        // 点光
        PointLight(*effect_constant_buffer_ps_).pos_ = float3(0.0f, 15.0f, -0.0f);
        PointLight(*effect_constant_buffer_ps_).ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).diffuse_ = float4(0.6f, 0.6f, 0.6f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).specular_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).att_ = float3(0.0f, 0.1f, 0.0f);
        PointLight(*effect_constant_buffer_ps_).range_ = 25.0f;
        // // 聚光灯
        // SpotLight(*effect_constant_buffer_ps_).pos_ = float3(0.0f, 0.0f, -5.0f);
        // SpotLight(*effect_constant_buffer_ps_).direction_ = float3(0.0f, 0.0f, 1.0f);
        // SpotLight(*effect_constant_buffer_ps_).ambient_ = float4(0.0f, 0.0f, 0.0f, 1.0f);
        // SpotLight(*effect_constant_buffer_ps_).diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        // SpotLight(*effect_constant_buffer_ps_).specular_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        // SpotLight(*effect_constant_buffer_ps_).att_ = float3(1.0f, 0.0f, 0.0f);
        // SpotLight(*effect_constant_buffer_ps_).spot_ = 12.0f;
        // SpotLight(*effect_constant_buffer_ps_).range_ = 10000.0f;

        // 初始化用于PS的常量缓冲区的值
        SetMaterial(*effect_constant_buffer_ps_).ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        SetMaterial(*effect_constant_buffer_ps_).diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        SetMaterial(*effect_constant_buffer_ps_).specular_ = float4(0.5f, 0.5f, 0.5f, 5.0f);

        // 使用默认平行光
        // ps_cb_.directional_light = default_directional_light_;
        // // 注意不要忘记设置此处的观察位置，否则高亮部分会有问题
        EysPos(*effect_constant_buffer_ps_) = float4(0.0f, 0.0f, 0.0f, 0.0f);

        // // 初始化用于VS的常量缓冲区的值
        effect_constant_buffer_vs_ = (effect_->CBufferByName("VSConstantBuffer")) ;
        world_offset_ = effect_->ParameterByName("gWorld")->CBufferOffset();
		view_offset_ = effect_->ParameterByName("gView")->CBufferOffset();
		projection_offset_ = effect_->ParameterByName("gProj")->CBufferOffset();
        world_inv_transpose_offset_ = effect_->ParameterByName("gWorldInvTranspose")->CBufferOffset();
        WorldMat(*effect_constant_buffer_vs_)= float4x4::Identity();
        WorldInvTransposeMat(*effect_constant_buffer_vs_) = float4x4::Identity();
        ViewMat(*effect_constant_buffer_vs_) = float4x4::Identity();

        auto& camera = Context::Instance().WorldInstance().camera_;
        ProjectionMat(*effect_constant_buffer_vs_) = MathWorker::Transpose(camera->ProjMatrix());  
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

    float4x4& WorldInvTransposeMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(world_inv_transpose_offset_);
	}

    void Update(float dt) override
    {
        auto world = MathWorker::Transpose(TransformToWorld());
        auto worldInvTranspose = MathWorker::Transpose(MathWorker::Inverse(world));
        WorldMat(*effect_constant_buffer_vs_)= world;
        WorldInvTransposeMat(*effect_constant_buffer_vs_) = worldInvTranspose;

        auto& camera = Context::Instance().WorldInstance().camera_;
        ViewMat(*effect_constant_buffer_vs_) = MathWorker::Transpose(camera->ViewMatrix());
        
        EysPos(*effect_constant_buffer_ps_) = camera->EyePos();
        effect_constant_buffer_vs_->Dirty(true);
        effect_constant_buffer_ps_->Dirty(true);
    }
private:
    uint32_t directional_light_offset_;
    uint32_t point_light_offset_;
    uint32_t spot_light_offset_;
    uint32_t material_offset_;
    uint32_t eys_pos_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_ps_;

    uint32_t world_offset_;
    uint32_t view_offset_;
    uint32_t projection_offset_;
    uint32_t world_inv_transpose_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_vs_;
};

class RenderableWater : public Renderable
{
public:
    RenderableWater(float width, float depth, float texU, float texV, const std::string& DDS)
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
        merged_ves.emplace_back(VertexElement(VEU_TextureCoord, 0, EF_GR32F));

        auto vb = rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, static_cast<uint32_t>(4 * sizeof(vertex[0])), &vertex[0]);
        rls_[0]->BindVertexStream(vb, merged_ves);

        indice_vec = { 0, 1, 2, 2, 3, 0 };
        auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
            static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
        rls_[0]->BindIndexStream(ib, EF_R16UI);

        effect_ = SyncLoadRenderEffect("water.xml");
        technique_ = effect_->TechniqueByName("water");

        auto src1_tex_param = effect_->ParameterByName("src1_tex");
        *src1_tex_param = SyncLoadTexture(DDS, EAH_GPU_Read | EAH_Immutable);

        effect_constant_buffer_ps_ = (effect_->CBufferByName("PSConstantBuffer")) ;
        directional_light_offset_ = effect_->ParameterByName("gDirLight")->CBufferOffset();
        point_light_offset_ = effect_->ParameterByName("gPointLight")->CBufferOffset();
        spot_light_offset_ = effect_->ParameterByName("gSpotLight")->CBufferOffset();
        material_offset_ = effect_->ParameterByName("gMaterial")->CBufferOffset();
        eys_pos_offset_ = effect_->ParameterByName("gEyePosW")->CBufferOffset();
        

        // 初始化用于PS的常量缓冲区的值
        // 初始化默认光照
        // 方向光
        DirectionalLight(*effect_constant_buffer_ps_).ambient_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).diffuse_ = float4(0.8f, 0.8f, 0.8f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).specular_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        DirectionalLight(*effect_constant_buffer_ps_).direction_ = float3(0.0f, -1.0f, 0.0f);
        // 点光
        PointLight(*effect_constant_buffer_ps_).pos_ = float3(0.0f, 15.0f, -0.0f);
        PointLight(*effect_constant_buffer_ps_).ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).diffuse_ = float4(0.6f, 0.6f, 0.6f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).specular_ = float4(0.2f, 0.2f, 0.2f, 1.0f);
        PointLight(*effect_constant_buffer_ps_).att_ = float3(0.0f, 0.1f, 0.0f);
        PointLight(*effect_constant_buffer_ps_).range_ = 25.0f;

        SetMaterial(*effect_constant_buffer_ps_).ambient_ = float4(0.5f, 0.5f, 0.5f, 1.0f);
        SetMaterial(*effect_constant_buffer_ps_).diffuse_ = float4(1.0f, 1.0f, 1.0f, 1.0f);
        SetMaterial(*effect_constant_buffer_ps_).specular_ = float4(0.8f, 0.8f, 0.8f, 32.0f);

        // 初始化用于VS的常量缓冲区的值
        effect_constant_buffer_vs_ = (effect_->CBufferByName("VSConstantBuffer")) ;
        world_offset_ = effect_->ParameterByName("gWorld")->CBufferOffset();
		view_offset_ = effect_->ParameterByName("gView")->CBufferOffset();
		projection_offset_ = effect_->ParameterByName("gProj")->CBufferOffset();
        world_inv_transpose_offset_ = effect_->ParameterByName("gWorldInvTranspose")->CBufferOffset();
        auto& camera = Context::Instance().WorldInstance().camera_;
        ProjectionMat(*effect_constant_buffer_vs_) = MathWorker::Transpose(camera->ProjMatrix());  
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

    float4x4& WorldInvTransposeMat(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float4x4>(world_inv_transpose_offset_);
	}

    Material& SetMaterial(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<Material>(material_offset_);
	}

    float3& EysPos(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<float3>(eys_pos_offset_);
	}

    DirectionalLightSource& DirectionalLight(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<DirectionalLightSource>(directional_light_offset_);
	}

    PointLightSource& PointLight(RenderEffectConstantBuffer& cbuff) const
	{
		return *cbuff.template VariableInBuff<PointLightSource>(point_light_offset_);
	}

    void Update(float dt) override
    {
        auto world = MathWorker::Transpose(TransformToWorld());
        auto worldInvTranspose = MathWorker::Transpose(MathWorker::Inverse(world));
        WorldMat(*effect_constant_buffer_vs_)= world;
        WorldInvTransposeMat(*effect_constant_buffer_vs_) = worldInvTranspose;

        auto& camera = Context::Instance().WorldInstance().camera_;
        ViewMat(*effect_constant_buffer_vs_) = MathWorker::Transpose(camera->ViewMatrix());
        
        EysPos(*effect_constant_buffer_ps_) = camera->EyePos();
        effect_constant_buffer_vs_->Dirty(true);
        effect_constant_buffer_ps_->Dirty(true);
    }
private:
    uint32_t directional_light_offset_;
    uint32_t point_light_offset_;
    uint32_t spot_light_offset_;
    uint32_t material_offset_;
    uint32_t eys_pos_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_ps_;

    uint32_t world_offset_;
    uint32_t view_offset_;
    uint32_t projection_offset_;
    uint32_t world_inv_transpose_offset_;
    RenderEffectConstantBuffer* effect_constant_buffer_vs_;
};

void CreateScene()
{
    auto& wd = Context::Instance().WorldInstance();
    wd.camera_ = MakeSharedPtr<Camera>();
    wd.controller_ = MakeSharedPtr<FirstPersonController>();
    wd.controller_->Scalers(0.5f, 80.f);
    wd.camera_->ProjParams(MathWorker::PI / 3, 
        Context::Instance().AppInstance().AspectRatio(), 
        0.5f, 1000.0f);
    if(wd.controller_)
    {
        wd.controller_->AttachCamera(wd.camera_);
    }
    auto movement = MathWorker::Translation(0.0f, 5.0f, -17.0f);
    wd.camera_->TransformToWorld(movement * wd.camera_->TransformToParent());

    // 初始化地板
    auto floor = new RenderablePlaneTex(20.0f, 20.0f, 5.0f, 5.0f, "floor.dds");
    Context::Instance().WorldInstance().AddRenderable(floor);
    movement = MathWorker::Translation(0.0f, -1.0f, 0.0f);
    floor->TransformToWorld(movement * floor->TransformToParent());
    floor->Update(0.f);

    // 初始化水
    auto water = new RenderableWater(20.0f, 20.0f, 10.0f, 10.0f, "water.dds");
    Context::Instance().WorldInstance().AddRenderable(water);
    movement = MathWorker::Translation(0.0f, 0.0f, 0.0f);
    water->TransformToWorld(movement * water->TransformToParent());
    water->Update(0.f);

    // 初始化墙体
    for (int i = 0; i < 4; ++i)
    {
        auto wal = new RenderablePlaneTex(20.0f, 8.0f, 5.0f, 1.5f, "brick.dds");
        Context::Instance().WorldInstance().AddRenderable(wal);
        auto rotM = MathWorker::ToMatrix(rotator(-MathWorker::PIdiv2, MathWorker::PIdiv2 * i, 0.f));
        auto moveM = MathWorker::Translation(i % 2 ? -10.0f * (i - 2) : 0.0f, 3.0f, i % 2 == 0 ? -10.0f * (i - 1) : 0.0f);
        wal->TransformToWorld(rotM * moveM * wal->TransformToParent());
        wal->Update(0.f);
    }

    // 初始化篱笆盒
    auto box = new RenderableBoxTex(2.0f, 2.0f, 2.0f, Color(1.f, 1.f, 1.f, 1.f), "WireFence.dds", "Basic_3D");
    movement = MathWorker::Translation(0.0f, -1.0f, 0.0f);
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