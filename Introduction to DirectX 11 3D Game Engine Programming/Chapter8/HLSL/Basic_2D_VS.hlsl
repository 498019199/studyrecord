#include "Basic.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    matrix viewProj = mul(gView, gProj);
    float4 posW = mul(float4(vIn.posL, 1.0f), gWorld);

    vOut.posH = mul(posW, viewProj);
    vOut.posW = posW.xyz;
    vOut.normalW = mul(vIn.normalL, (float3x3) gWorldInvTranspose);

    // 旋转
    vOut.tex2 = mul(float4(vIn.tex, 0.f, 1.f), gRotateM);
    vOut.tex1 = vIn.tex;
    return vOut;
}
