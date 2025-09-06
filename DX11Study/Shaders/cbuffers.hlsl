
cbuffer ConstantBuffer : register(b0) //vs
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
};

cbuffer LightBuffer : register(b1) //ps
{
    float3 light_radiance;
    int padding;
    float4 light_direction;
    float4 cameraPosition;
    int isDirect;
    int padding2[3];
};


cbuffer MaterialProperties : register(b2) //ps
{
    float4 materialColor;
    int hasAmbientMap;
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasOpacityMap;
    int hasEmissiveMap;
    int hasRoughnessMap;
    int hasMetalnessMap;
    float materialRoughness;
    float materialMetalness;
    float padding3[2];
};


cbuffer MatrixPallete : register(b3) //vs
{
    float4x4 palleteArray[128];
}

