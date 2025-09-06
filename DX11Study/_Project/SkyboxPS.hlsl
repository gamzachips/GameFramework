#include "cbuffers.hlsl"

TextureCube CubeMapTexture : register(t0);
SamplerState LinearSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 texCoords : TEXCOORD0;
};

//PS
float4 PS(PS_INPUT input) : SV_Target
{
    
    return CubeMapTexture.SampleLevel(LinearSampler, normalize(input.texCoords), 1);
}

