
Texture2D ambientTexture : register(t0);
Texture2D diffuseTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D normalTexture : register(t3);
Texture2D opacityTexture : register(t4);
Texture2D emissiveTexture : register(t5);
Texture2D roughnessTexture : register(t6);
Texture2D metalnessTexture : register(t7);
TextureCube EnvDiffuseTexture : register(t8);
TextureCube EnvSpecularTexture : register(t9);
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
#define N 100

float CalculateD(float3 normal, float3 halfVector, float roughness);
float3 CalculateF(float3 baseColor, float3 halfVector, float3 viewVector, float metalness);
float3 CalculateIBLF(float3 f0, float NdotV);
float CalculateG(float k, float3 normal, float3 viewVector);

//PS
float4 PS(PS_INPUT input) : SV_Target
{

    float4 finalColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    float3 normal = normalize(input.normal);
    float3 viewDir = normalize((float3)cameraPosition - (float3)input.worldPosition);
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

    //////////////////////////     Ambient (IBL)   ////////////////////////////////
   
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

    if(onIBL == 1)
    {
        float3 f0 = lerp(float3(0.04f, 0.04f, 0.04f), diffuseColor, metalness);
        float3 f_IBL = CalculateIBLF(f0, NdotV);

        float3 irradiance = EnvDiffuseTexture.Sample(linearSampler, N).rgb;
        float3 k_d = lerp(1.0 - f_IBL, 0.0, metalness);
        float3 diffuseIBL = k_d * diffuseColor * irradiance;

        uint specularTextureLevels, width, height;
        specularTexture.GetDimensions(0, width, height, specularTextureLevels);
    
        float3 Lr = 2 * saturate(dot(normal, viewDir)) * normal - viewDir;
        float3 prefilteredColor = EnvSpecularTexture.SampleLevel(linearSampler, Lr, roughness * specularTextureLevels).rgb;
    
        float2 specularBRDF = LookUpTableTexture.Sample(clampSampler, float2(NdotV, roughness)).rg;
        specularBRDF = pow(specularBRDF, 1.0 / GAMMA);
        float3 specularIBL = (f0 * specularBRDF.x + specularBRDF.y) * prefilteredColor;
    
        finalColor = float4((diffuseIBL + specularIBL), 1);
    }


    //////////////////////////     Specular   ////////////////////////////////

    float k;
    if (isDirect == 1)
        k = pow(roughness + 1, 2) / 8;
    else
        k = pow(roughness, 2) / 2;

    float d = CalculateD(normal, halfVector, roughness);
    float3 f = CalculateF(diffuseColor.rgb, halfVector, viewDir, metalness);
    float g = CalculateG(k, normal, viewDir);

    float3 temp = (4 * saturate(dot(normal, lightVector)) * saturate(dot(normal, viewDir)));
    float3 specularBRDFLighting = (d * f * g);
    if (length(temp) != 0.f)
        specularBRDFLighting *= temp;


    //////////////////////////     Diffuse   ////////////////////////////////

    float3 diffuseBRDFLighting = diffuseColor * saturate(float3(1.f, 1.f, 1.f) - f) / PI;
	finalColor += float4((specularBRDFLighting + diffuseBRDFLighting) 
    * light_radiance * 3 * saturate(dot(normal, lightVector)), 0);

    //////////////////////////     Opacity    ////////////////////////////////

    if (hasOpacityMap)
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

float3 CalculateIBLF(float3 f0, float NdotV)
{
	float3 f = f0 + (1 - f0) * pow(1 - NdotV, 5);
	return f;
}
