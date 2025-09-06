#include "../Common/pch.h"
#include "Cube.h"
#include "../Common/Shader.h"
#include "../Common/Transform.h"
#include "../Common/ConstantBuffer.h"
#include "../Common/StaticMesh.h"
#include "../Common/MeshRenderer.h"
#include "../Common/GameApp.h"
#include "../Common/World.h"
#include "../Common/Material.h"
#include "../Common/Texture.h"

Cube::Cube(ComPtr<ID3D11Device> device)
{
	StaticMesh* cubeMesh = new StaticMesh(device);

	std::vector<VertexData> cubeVertices =
	{

		// Normal Y+ (top)
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },

		// Normal Y- (bottom)
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },

		// Normal X- 
		{ Vector3(-1.0f, -1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },

		// Normal X+ 
		{ Vector3(1.0f, -1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },

		// Normal Z-
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f) },

		// Normal Z+
		{ Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f) }
		
	};
	

	std::vector<unsigned int> cubeIndices =
	{
		3,1,0, 2,1,3,
		6,4,5, 7,4,6,
		11,9,8, 10,9,11,
		14,12,13, 15,12,14,
		19,17,16, 18,17,19,
		22,20,21, 23,20,22
	};

	cubeMesh->SetVertices(cubeVertices);
	cubeMesh->SetIndices(cubeIndices);

	Material* material = new Material;

	material->SetAmbient(new Texture(device, L"ParquetFlooring05_4K_AO.dds"));
	material->SetDiffuse(new Texture(device, L"Bricks059_1K-JPG_Color.dds"));
	material->SetSpecular(new Texture(device, L"Bricks059_Specular.dds"));
	material->SetNormal(new Texture(device, L"Bricks059_1K-JPG_NormalDX.dds"));
	AddComponent(material);

	//AddComponent(mr);
}

Cube::~Cube()
{
}

void Cube::Init()
{
	__super::Init();


}

void Cube::Update(float deltaTime)
{
	__super::Update(deltaTime);

	//GetTransform().Rotate({ 0, 0, deltaTime * _rotateSpeed, 0 });
}
