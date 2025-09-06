
#include "cbuffers.hlsl"

struct VS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD0;
    float3 tangent : TANGENT;
    int4 boneIds : TEXCOORD1;
    float4 weights : TEXCOORD2;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD1;
    float2 texCoord : TEXCOORD0;
    float4 worldPosition : TEXCOORD2;
    float3 tangent : TEXCOORD3;

};
//#define VERTEX_SKINNING

//VS
VS_OUTPUT VS(VS_INPUT input)
{
    float4x4 matWorld;
#ifdef VERTEX_SKINNING
    matWorld = mul(input.weights.x, palleteArray[input.boneIds.x]);
    matWorld += mul(input.weights.y, palleteArray[input.boneIds.y]);
    matWorld += mul(input.weights.z, palleteArray[input.boneIds.z]);
    matWorld += mul(input.weights.w, palleteArray[input.boneIds.w]);
    matWorld += world;
#else
    matWorld = world;
#endif
    
    VS_OUTPUT output;
    output.worldPosition = mul(input.position, matWorld);
    output.position = mul(output.worldPosition, view);
    output.position = mul(output.position, projection);
    output.normal = normalize(mul(input.normal, (float3x3) matWorld));
    output.texCoord = input.texCoord;
    output.tangent = normalize(mul(input.tangent, (float3x3) matWorld));
    return output;
}
