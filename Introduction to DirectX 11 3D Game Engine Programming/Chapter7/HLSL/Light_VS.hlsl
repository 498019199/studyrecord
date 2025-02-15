#include "Light.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    matrix viewProj = mul(gView, gProj);
    float4 posW = mul(float4(vIn.posL, 1.0f), gWorld);

    vOut.posH = mul(posW, viewProj);
    vOut.posW = posW.xyz;
    vOut.normalW = mul(vIn.normalL, (float3x3) gWorldInvTranspose);
    vOut.color = vIn.color; // 这里alpha通道的值默认为1.0
    return vOut;
}
