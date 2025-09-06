#pragma once
#include "pch.h"

struct BasicVertexData
{
	Vector3 position = { 0, 0, 0 };
};

struct VertexData
{
	Vector3 position = { 0, 0, 0 };
	Vector3 normal = { 0, 0, 0};
	Vector2 texture{};
	Vector3 tangent{};
};

struct VertexSkeletalData
{
	Vector3 position = { 0, 0, 0 };
	Vector3 normal = { 0, 0, 0 };
	Vector2 texture{};
	Vector3 tangent{};
	int boneIds[4]{};
	float weights[4]{};

	void AddIdAndWeight(int id, float weight)
	{
		for (int i = 0; i < 4; i++)
		{
			if (weights[i] != 0.f)
				continue;

			boneIds[i] = id;
			weights[i] = weight;
			return;
		} 
	}

	void NormalizeWeights()
	{
		if (weights[0] == 0.f) return;
		
		float weightSum = 0.f;
		for (float& weight : weights)
			weightSum += weight;

		for (float& weight : weights) {
			weight /= weightSum;
		}
	}
};

struct WVPData
{
	Matrix world;
	Matrix view;
	Matrix projection;
};

struct LightData
{
	Vector3 lightRadiance = { 1,1,1 };
	int padding;
	Vector4 direction = { 0.0f, 0.0f, 1.0f, 0.0f };
	Vector4 cameraPosition;
	int isDirect = 1;
	int padding2[3];
};

struct MaterialData
{
	Vector4 materialColor = { 1.f, 1.f, 1.f ,1.f };
	int hasAmbientMap = 0;
	int hasDiffuseMap = 0;
	int hasSpecularMap = 0;
	int hasNormalMap = 0;
	int hasOpacityMap = 0;
	int hasEmissiveMap = 0;
	int hasRoughnessMap = 0;
	int hasMetalnessMap = 0;
	float roughness = 0;
	float metalness = 0;
	int onIBL = 1;
	float padding;
};

struct MatrixPallete
{
	Matrix array[128]{};
};

struct KeyFrame
{
	double time;
	Vector3 value;
	Quaternion rotation;
};

struct NodeAnim
{
	std::string nodeName;
	std::vector<KeyFrame> positionKeys;
	std::vector<KeyFrame> rotationKeys;
	std::vector<KeyFrame> scalingKeys;
};