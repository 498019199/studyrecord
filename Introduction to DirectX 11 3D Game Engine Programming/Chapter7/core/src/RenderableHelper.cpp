#include <core/RenderableHelper.h>
#include <core/D3D11RenderLayout.h>
#include <core/D3D11RenderFactory.h>
#include <core/RenderEffect.h>
#include <core/Context.h>

#include <filesystem>

struct VertexPosNormalColor
{
    float3 pos;
    float3 normal;
    Color color;
};

RenderableBox::  RenderableBox(float width, float height, float depth, const Color & color)
{
    float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

    rls_[0] = std::make_shared<D3D11RenderLayout>();
    rls_[0]->TopologyType(D3D11RenderLayout::TT_TriangleList);

    std::vector<VertexElement> merged_ves;
    VertexPosNormalColor vertex[24];

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

    merged_ves.emplace_back(VertexElement(VEU_Position, 0, EF_SIGNED_ABGR16));
    merged_ves.emplace_back(VertexElement(VEU_Normal, 0, EF_ABGR8));
    merged_ves.emplace_back(VertexElement(VEU_Diffuse, 0, EF_ABGR8));
    //merged_ves.emplace_back(VertexElement(VEU_Tangent, 0, EF_ABGR8));
    //merged_ves.emplace_back(VertexElement(VEU_TextureCoord, 0, EF_SIGNED_GR16));
    auto& rf = Context::Instance().RenderFactoryInstance();
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 24, &vertex[0]), merged_ves);

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
	currentPath += "\\Chapter7\\HLSL\\";
    effect_ = std::make_shared<RenderEffect>();
    effect_->CreateConstant();
    effect_->AttackVertexShader(currentPath + "Light_VS");
    effect_->AttackPixelShader(currentPath + "Light_PS");
}

RenderableSphere::RenderableSphere(float radius, int levels, int slices, const Color & color)
{
    uint32_t vertexCount = 2 + (levels - 1) * (slices + 1);
    uint32_t indexCount = 6 * (levels - 1) * slices;

    rls_[0] = std::make_shared<D3D11RenderLayout>();
    rls_[0]->TopologyType(D3D11RenderLayout::TT_TriangleList);

    std::vector<float3> position_vec;
    position_vec.resize(vertexCount);
    std::vector<float3>  normal_vec;
    normal_vec.resize(vertexCount);
    std::vector<float4>  tangent_vec;
    tangent_vec.resize(vertexCount);
    std::vector<float2>  texs_vec;
    texs_vec.resize(vertexCount);
    std::vector<uint16_t> indice_vec;
    indice_vec.resize(indexCount);

    float phi = 0.0f, theta = 0.0f;
    float per_phi = MathWorker::PI / levels;
    float per_theta = MathWorker::PI2 / slices;
    float x, y, z;
    int iIndex = 0;

    // 放入顶端点
    position_vec.emplace_back(float3(0.0f, radius, 0.0f));
    normal_vec.emplace_back(float3(0.0f, 1.0f, 0.0f));
    tangent_vec.emplace_back(float4(1.0f, 0.0f, 0.0f, 1.0f));
    texs_vec.emplace_back(float2(0.0f, 0.0f));
    for (int i = 1; i < levels; ++i)
    {
        phi = per_phi * i;
        // 需要slices + 1个顶点是因为 起点和终点需为同一点，但纹理坐标值不一致
        for (int j = 0; j <= slices; ++j)
        {
            theta = per_theta * j;
            x = radius * std::sinf(phi) * std::cosf(theta);
            y = radius * std::cosf(phi);
            z = radius * std::sinf(phi) * std::sinf(theta);

            // 计算出局部坐标、法向量、Tangent向量和纹理坐标
            float3 pos = float3(x, y, z);
            float3 normal = MathWorker::Normalize(pos);
            float4 tangent = float4(-sinf(theta), 0.0f, cosf(theta), 1.0f);
            float2 tex = float2(theta / MathWorker::PI2, phi / MathWorker::PI);

            position_vec.emplace_back(pos);
            normal_vec.emplace_back(normal);
            tangent_vec.emplace_back(tangent);
            texs_vec.emplace_back(tex);
        }
    }
    // 放入底端点
    position_vec.emplace_back(float3(0.0f, -radius, 0.0f));
    normal_vec.emplace_back(float3(0.0f, -1.0f, 0.0f));
    tangent_vec.emplace_back(float4(-1.0f, 0.0f, 0.0f, 1.0f));
    texs_vec.emplace_back(float2(0.0f, 1.0f));

    auto& rf = Context::Instance().RenderFactoryInstance();
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(position_vec.size() * sizeof(position_vec[0])), &position_vec[0]),
        VertexElement(VEU_Position, 0, EF_R32F));

    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(normal_vec.size() * sizeof(normal_vec[0])), &normal_vec[0]),
		VertexElement(VEU_Normal, 0, EF_BGR32F));

    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(tangent_vec.size() * sizeof(tangent_vec[0])), &tangent_vec[0]),
		VertexElement(VEU_Diffuse, 0, EF_ABGR32F));
    
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(tangent_vec.size() * sizeof(tangent_vec[0])), &tangent_vec[0]),
		VertexElement(VEU_Tangent, 0, EF_ABGR32F));

    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(texs_vec.size() * sizeof(texs_vec[0])), &texs_vec[0]),
        VertexElement(VEU_TextureCoord, 0, EF_R32F));

    // 放入索引
    if (levels > 1)
    {
        for (int j = 1; j <= slices; ++j)
        {
            indice_vec[iIndex++] = 0;
            indice_vec[iIndex++] = static_cast<uint16_t>(j % (slices + 1) + 1);
            indice_vec[iIndex++] = static_cast<uint16_t>(j);
        }
    }
    for (int i = 1; i < levels - 1; ++i)
    {
        for (int j = 1; j <= slices; ++j)
        {
            indice_vec[iIndex++] = static_cast<uint16_t>((i - 1) * (slices + 1) + j);
            indice_vec[iIndex++] = static_cast<uint16_t>((i - 1) * (slices + 1) + j % (slices + 1) + 1);
            indice_vec[iIndex++] = static_cast<uint16_t>(i * (slices + 1) + j % (slices + 1) + 1);

            indice_vec[iIndex++] = static_cast<uint16_t>(i * (slices + 1) + j % (slices + 1) + 1);
            indice_vec[iIndex++] = static_cast<uint16_t>(i * (slices + 1) + j);
            indice_vec[iIndex++] = static_cast<uint16_t>((i - 1) * (slices + 1) + j);
        }
    }
    // 逐渐放入索引
    if (levels > 1)
    {
        for (int j = 1; j <= slices; ++j)
        {
            indice_vec[iIndex++] = static_cast<uint16_t>((levels - 2) * (slices + 1) + j);
            indice_vec[iIndex++] = static_cast<uint16_t>((levels - 2) * (slices + 1) + j % (slices + 1) + 1);
            indice_vec[iIndex++] = static_cast<uint16_t>((levels - 1) * (slices + 1) + 1);
        }
    }
    auto ib = rf.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(indice_vec.size() * sizeof(indice_vec[0])), &indice_vec[0]);
    rls_[0]->BindIndexStream(ib, EF_R16UI);

	auto currentPath = std::filesystem::current_path().parent_path().parent_path().string();
	currentPath += "\\Chapter7\\HLSL\\";
    effect_ = std::make_shared<RenderEffect>();
    effect_->CreateConstant();
    effect_->AttackVertexShader(currentPath + "Light_VS");
    effect_->AttackPixelShader(currentPath + "Light_PS");
}
