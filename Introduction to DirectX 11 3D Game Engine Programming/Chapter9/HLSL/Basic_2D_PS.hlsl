#include "Basic.hlsli"

// 像素着色器(2D)
float4 PS(VertexPosHTex pIn) : SV_Target
{
    float4 color = gTex1.Sample(gSamLinear1, pIn.tex);
    clip(color.a - 0.1f);
    return color;
}