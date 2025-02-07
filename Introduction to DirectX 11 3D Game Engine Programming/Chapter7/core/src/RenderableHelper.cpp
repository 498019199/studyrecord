#include <core/RenderableHelper.h>
#include <core/D3D11RenderLayout.h>
#include <core/D3D11RenderFactory.h>
#include <core/RenderEffect.h>
#include <core/Context.h>

#include <filesystem>

RenderableBox::  RenderableBox(float width, float height, float depth, const Color & color)
{
    float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

    rls_[0] = std::make_shared<D3D11RenderLayout>();
    rls_[0]->TopologyType(D3D11RenderLayout::TT_TriangleList);

    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float4> tangents;
    std::vector<Color>  colors;
    std::vector<float2> texs;

    positions.resize(24);
    normals.resize(24);
    tangents.resize(24);
    colors.resize(24);
    texs.resize(24);

    // 右面(+X面)
    positions[0] = float3(w2, -h2, -d2);
    positions[1] = float3(w2, h2, -d2);
    positions[2] = float3(w2, h2, d2);
    positions[3] = float3(w2, -h2, d2);
    // 左面(-X面)
    positions[4] = float3(-w2, -h2, d2);
    positions[5] = float3(-w2, h2, d2);
    positions[6] = float3(-w2, h2, -d2);
    positions[7] = float3(-w2, -h2, -d2);
    // 顶面(+Y面)
    positions[8] = float3(-w2, h2, -d2);
    positions[9] = float3(-w2, h2, d2);
    positions[10] = float3(w2, h2, d2);
    positions[11] = float3(w2, h2, -d2);
    // 底面(-Y面)
    positions[12] = float3(w2, -h2, -d2);
    positions[13] = float3(w2, -h2, d2);
    positions[14] = float3(-w2, -h2, d2);
    positions[15] = float3(-w2, -h2, -d2);
    // 背面(+Z面)
    positions[16] = float3(w2, -h2, d2);
    positions[17] = float3(w2, h2, d2);
    positions[18] = float3(-w2, h2, d2);
    positions[19] = float3(-w2, -h2, d2);
    // 正面(-Z面)
    positions[20] = float3(-w2, -h2, -d2);
    positions[21] = float3(-w2, h2, -d2);
    positions[22] = float3(w2, h2, -d2);
    positions[23] = float3(w2, -h2, -d2);

    for (UINT i = 0; i < 4; ++i)
    {
        // 右面(+X面)
        normals[i] = float3(1.0f, 0.0f, 0.0f);
        tangents[i] = float4(0.0f, 0.0f, 1.0f, 1.0f);
        colors[i] = color;
        // 左面(-X面)
        normals[i + 4] = float3(-1.0f, 0.0f, 0.0f);
        tangents[i + 4] = float4(0.0f, 0.0f, -1.0f, 1.0f);
        colors[i + 4] = color;
        // 顶面(+Y面)
        normals[i + 8] = float3(0.0f, 1.0f, 0.0f);
        tangents[i + 8] = float4(1.0f, 0.0f, 0.0f, 1.0f);
        colors[i + 8] = color;
        // 底面(-Y面)
        normals[i + 12] = float3(0.0f, -1.0f, 0.0f);
        tangents[i + 12] = float4(-1.0f, 0.0f, 0.0f, 1.0f);
        colors[i + 12] = color;
        // 背面(+Z面)
        normals[i + 16] = float3(0.0f, 0.0f, 1.0f);
        tangents[i + 16] = float4(-1.0f, 0.0f, 0.0f, 1.0f);
        colors[i + 16] = color;
        // 正面(-Z面)
        normals[i + 20] = float3(0.0f, 0.0f, -1.0f);
        tangents[i + 20] = float4(1.0f, 0.0f, 0.0f, 1.0f);
        colors[i + 20] = color;
    }
    for (UINT i = 0; i < 6; ++i)
    {
        texs[i * 4] = float2(0.0f, 1.0f);
        texs[i * 4 + 1] = float2(0.0f, 0.0f);
        texs[i * 4 + 2] = float2(1.0f, 0.0f);
        texs[i * 4 + 3] = float2(1.0f, 1.0f);
    }
    auto& rf = Context::Instance().RenderFactoryInstance();
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 24, &positions[0]),
        VertexElement(VEU_Position, 0, EF_BGR32F));
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 24, &normals[0]),
		VertexElement(VEU_Normal, 0, EF_BGR32F));
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 24, &tangents[0]),
		VertexElement(VEU_Tangent, 0, EF_ABGR32F));
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 24, &texs[0]),
        VertexElement(VEU_TextureCoord, 0, EF_R32F));

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
    effect_->CreateConstant();
    effect_->AttackVertexShader(currentPath + "Light__VS");
    effect_->AttackPixelShader(currentPath + "Light__PS");
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
        VertexElement(VEU_Position, 0, EF_BGR32F));
    rls_[0]->BindVertexStream(rf.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, 
        static_cast<uint32_t>(normal_vec.size() * sizeof(normal_vec[0])), &normal_vec[0]),
		VertexElement(VEU_Normal, 0, EF_BGR32F));
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
    effect_->CreateConstant();
    effect_->AttackVertexShader(currentPath + "Light__VS");
    effect_->AttackPixelShader(currentPath + "Light__PS");
}
