#include "Basic.hlsli"

// 像素着色器
float4 PS(VertexOut pIn) : SV_Target
{
    return gTex.Sample(gSamLinear, pIn.tex);
}
