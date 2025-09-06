
Texture2D ambientTexture : register(t0);
Texture2D diffuseTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D normalTexture : register(t3);
Texture2D opacityTexture : register(t4);
Texture2D emissiveTexture : register(t5);
Texture2D roughnessTexture : register(t6);
Texture2D metalnessTexture : register(t7);
Texture2D EnvDiffuseTexture : register(t8);
Texture2D EnvSpecularTexture : register(t9);
Texture2D LookUpTableTexture : register(t10);

SamplerState linearSampler : register(s0);
SamplerState clampSampler : register(s1);

#include "cbuffers.hlsl"


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

float CalculateD(float3 normal, float3 halfVector, float roughness);
float3 CalculateF(float3 baseColor, float3 halfVector, float3 viewVector, float metalness);
float CalculateG(float k, float3 normal, float3 viewVector);

//PS
float4 PS(PS_INPUT input) : SV_Target
{
    
    float4 finalColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    float3 normal = normalize(input.normal);
    float3 viewDir = normalize((float3) cameraPosition - (float3) input.worldPosition);
    float3 lightVector = normalize(-light_direction);
    float3 halfVector = normalize(lightVector + viewDir);
    
    //////////////////////////     Normal    ////////////////////////////////
    if (hasNormalMap)
    {
        float3 normalTangentSpace = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
        float3x3 worldTransform = float3x3(input.tangent, cross(input.normal, input.tangent), input.normal);
        normal = normalize(mul(normalTangentSpace, worldTransform));
    }
    
    //////////////////////////     Ambient    ////////////////////////////////
   if(hasAmbientMap)
    {
        float4 ambientColor
    = ambientTexture.Sample(linearSampler, input.texCoord);
        finalColor += ambientColor;
    }
    else
    {
        finalColor += materialColor * 0.01;
    }

    float roughness, metalness;
    
    if(hasRoughnessMap)
        roughness = roughnessTexture.Sample(linearSampler, input.texCoord);
    else
        roughness = materialRoughness;
    if (hasMetalnessMap)
        metalness = metalnessTexture.Sample(linearSampler, input.texCoord);
    else
        metalness = materialMetalness;
   
    
    //////////////////////////     Specular   ////////////////////////////////
    
    float3 specularColor;
    if(hasSpecularMap)
    {
        specularColor = specularTexture.Sample(linearSampler, input.texCoord).rgb;
        finalColor = pow(finalColor, 1.0f / GAMMA);
    }
    else
    {
        specularColor = materialColor;
    }
        
    float3 diffuseColor;
    if (hasDiffuseMap)
    {
        diffuseColor = diffuseTexture.Sample(linearSampler, input.texCoord).rgb;
        finalColor = pow(finalColor, 1.0f / GAMMA);
    }
    else
    {
        diffuseColor = materialColor;
    }
    
    float k;
    if (isDirect == 1)
        k = pow(roughness + 1, 2) / 8;
    else
        k = pow(roughness, 2) / 2;
    
    float d = CalculateD(normal, halfVector, roughness);
    float3 f = CalculateF(diffuseColor.rgb, halfVector, viewDir, metalness);
    float g = CalculateG(k, normal, viewDir);
    
    float3 specularBRDF = (d * f * g) / (4 * saturate(dot(normal, lightVector)) * saturate(dot(normal, viewDir)));

 
    //////////////////////////     Diffuse   ////////////////////////////////

    float3 diffuseBRDF = diffuseColor * (float3(1.f, 1.f, 1.f) - f) / PI;
    finalColor += float4((specularBRDF + diffuseBRDF) * light_radiance * 3 * saturate(dot(normal, lightVector)), 0);  

    
    
    //////////////////////////     Opacity    ////////////////////////////////
    
    if(hasOpacityMap)
    {
        float4 opacity = opacityTexture.Sample(linearSampler, input.texCoord);
        finalColor.a = opacity.a;
    }
    
    //////////////////////////     Emissive    ////////////////////////////////
    
    if (hasEmissiveMap)
    {
        float3 E = normalize(cameraPosition - input.worldPosition);

        float value = saturate(dot(E, normal));
        float emissive = 1.0f - value;

        emissive = smoothstep(0.0f, 1.0f, emissive);
        emissive = pow(emissive, 2);

        float4 emissiveColor = emissiveTexture.Sample(linearSampler, input.texCoord) * emissive;
        
        finalColor += emissiveColor;
    }
    
    finalColor = pow(finalColor, GAMMA);
    return finalColor;
}

float CalculateD(float3 normal, float3 halfVector, float roughness)
{
    float ncrossh = saturate(dot(normal, halfVector));
    float numerator = roughness * roughness;
    float denominator = PI * pow((pow(ncrossh, 2) * (numerator - 1) + 1), 2);
    return numerator / denominator;
}

float3 CalculateF(float3 baseColor, float3 halfVector, float3 viewVector, float metalness)
{
    float3 rgb = float3(0.04, 0.04, 0.04);
    float3 f0 = lerp(rgb, baseColor, metalness);
    float3 f = f0 + (1 - f0) * pow(1 - saturate(dot(halfVector, viewVector)), 5);
    return f;
}

float CalculateG(float k, float3 normal, float3 viewVector)
{
    float numerator = saturate(dot(normal, viewVector));
    float denominator = saturate(dot(normal, viewVector)) * (1 - k) + k;
    return numerator / denominator;
    
}