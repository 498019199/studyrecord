
#include "LightHelp.hlsli"
Texture2D gTex1 : register(t0);
SamplerState gSamLinear1 : register(s0);

cbuffer VSConstantBuffer : register(b0)
{
    matrix gWorld; // matrix可以用float4x4替代。不加row_major的情况下，矩阵默认为列主矩阵，
    matrix gView;  // 可以在前面添加row_major表示行主矩阵
    matrix gProj;  // 该教程往后将使用默认的列主矩阵，但需要在C++代码端预先将矩阵进行转置。
    matrix gWorldInvTranspose;
    matrix gRotateM;
}

cbuffer PSConstantBuffer : register(b1)
{
    DirectionalLight gDirLight;
    PointLight gPointLight;
    SpotLight gSpotLight;
    Material gMaterial;
    float3 gEyePosW;
    float gPad;
}

struct VertexIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD;
};

struct VertexPosHTex
{
    float4 posH : SV_POSITION;
    float2 tex : TEXCOORD;
};

struct VertexPosTex
{
    float3 posL : POSITION;
    float2 tex : TEXCOORD;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;     // 在世界中的位置
    float3 normalW : NORMAL;    // 法向量在世界中的方向
    float2 tex1 : TEXCOORD;
    float2 tex2 : TEXCOORD;
};

