
#include "cbuffers.hlsl"

struct VS_INPUT
{
    float4 position : POSITION;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 texCoords : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    float4 pos = mul(input.position, world);
    output.texCoords = pos.xyz;
    // 역행렬에서 위치는 적용안함 카메라 회전은 반영됨
    float3 pos3 = mul(pos.xyz, (float3x3) view);
    pos = mul(float4(pos3, 1.0f), projection);
    output.position = pos;
    return output;

}