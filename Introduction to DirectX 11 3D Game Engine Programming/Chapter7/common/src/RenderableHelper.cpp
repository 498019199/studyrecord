#include <core/RenderableHelper.h>

RenderableBox::RenderableBox(float width, float height, float depth, const Color & color)
{
    float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

    rls_[0] = std::make_shared<D3D11RenderLayout>();
    rls_[0]->TopologyType(D3D11RenderLayout::TT_TriangleList);

    float3 positions[24] = {};
    float3 normals[24] = {};
    float4 tangents[24] = {};
    Color colors[24] = {};
    float2 texs[24] = {};

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
    auto const& re = Context::Instance().RenderEngineInstance();
    rls_[0]->BindVertexStream(re.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable,
        static_cast<uint32_t>(positions.size() * sizeof(positions[0])), &positions[0]),
        VertexElement(VEU_Position, 0, EF_BGR32F));
    rls_[0]->BindVertexStream(re.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable,
		static_cast<uint32_t>(normals.size() * sizeof(normals[0])), &normals[0]),
		VertexElement(VEU_Normal, 0, EF_BGR32F));
    rls_[0]->BindVertexStream(re.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable,
		static_cast<uint32_t>(tangents.size() * sizeof(tangents[0])), &tangents[0]),
		VertexElement(VEU_Tangent, 0, EF_ABGR32F));
    rls_[0]->BindVertexStream(re.MakeVertexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable,
        static_cast<uint32_t>(axises.size() * sizeof(texs[0])), &texs[0]),
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
    auto ib = re.MakeIndexBuffer(BU_Static, EAH_GPU_Read | EAH_Immutable, sizeof(indices), indices);
    rls_[0]->BindIndexStream(ib, EF_R16UI);
}