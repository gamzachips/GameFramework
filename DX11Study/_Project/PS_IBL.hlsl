#include "cbuffers.hlsl"

Texture2D ambientTexture : register(t0);
Texture2D diffuseTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D normalTexture : register(t3);
Texture2D roughnessTexture : register(t6);
Texture2D metalnessTexture : register(t7);
TextureCube EnvDiffuseTexture : register(t8);
TextureCube EnvSpecularTexture : register(t9);
Texture2D LookUpTableTexture : register(t10);

SamplerState linearSampler : register(s0);
SamplerState clampSampler : register(s1);



struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD1;
    float2 texCoord : TEXCOORD0;
    float4 worldPosition : TEXCOORD2;
    float3 tangent : TEXCOORD3;

};

#define PI 3.141592
#define GAMMA 2.2
#define N 100

float3 CalculateF(float3 f0, float NdotV);

//PS
float4 PS(PS_INPUT input) : SV_Target
{
    
    float4 finalColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    float3 normal = normalize(input.normal);
    float3 viewDir = normalize((float3) cameraPosition - (float3) input.worldPosition);
    float3 lightVector = normalize(-light_direction);
    float3 halfVector = normalize(lightVector + viewDir);
    float NdotV = saturate(dot(normal, viewDir));
    
    //////////////////////////     Normal    ////////////////////////////////
    if (hasNormalMap)
    {
        float3 normalTangentSpace = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
        float3x3 worldTransform = float3x3(input.tangent, cross(input.normal, input.tangent), input.normal);
        normal = normalize(mul(normalTangentSpace, worldTransform));
    }

    //////////////////////////     Specular & Diffuse (BRDF,IBL) ////////////////////////////////
    
    float roughness = materialRoughness;
    float metalness = materialMetalness;
    
    if (hasRoughnessMap)
        roughness = roughnessTexture.Sample(linearSampler, input.texCoord);
    if (hasMetalnessMap)
        metalness = metalnessTexture.Sample(linearSampler, input.texCoord);

    
    float3 diffuseColor = materialColor;
    if (hasDiffuseMap)
    {
        diffuseColor = diffuseTexture.Sample(linearSampler, input.texCoord).rgb;
        diffuseColor = pow(diffuseColor, 1.0f / GAMMA);
    }

    float3 f0 = lerp(float3(0.04f, 0.04f, 0.04f), diffuseColor, metalness);
    float3 f = CalculateF(f0, NdotV);

    float3 irradiance = EnvDiffuseTexture.Sample(linearSampler, N).rgb;
    float3 k_d = lerp(1.0 - f, 0.0, metalness);
    float3 diffuseIBL = k_d * diffuseColor * irradiance;

    uint specularTextureLevels, width, height;
    specularTexture.GetDimensions(0, width, height, specularTextureLevels);
    
    float3 Lr = 2 * saturate(dot(normal, viewDir)) * normal - viewDir;
    float3 prefilteredColor = EnvSpecularTexture.SampleLevel(linearSampler, Lr, roughness * specularTextureLevels).rgb;
    
    float2 specularBRDF = LookUpTableTexture.Sample(clampSampler, float2(NdotV, roughness)).rg;
    float3 specularIBL = (f0 * specularBRDF.x + specularBRDF.y) * prefilteredColor;
    
    finalColor = float4((diffuseIBL + specularIBL), 1);
    
    finalColor = pow(finalColor, GAMMA);
    return finalColor;
}

float3 CalculateF(float3 f0, float NdotV)
{
    float3 f = f0 + (1 - f0) * pow(1 - NdotV, 5);
    return f;
}
