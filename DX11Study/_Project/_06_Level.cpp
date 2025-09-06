#include "../Common/pch.h"
#include "../Common/Object.h"
#include "../Common/MeshRenderer.h"
#include "../Common/StaticMesh.h"
#include "../Common/Material.h"
#include "../Common/Model.h"
#include "_06_Level.h"
#include "TestApp.h"
#include "../Common/World.h"
#include "../Common/Camera.h"
_06_Level::_06_Level()
{
}

_06_Level::~_06_Level()
{
}

void _06_Level::Init(ComPtr<ID3D11Device> device)
{

	LightData light;
	SetLightData(light);

	Assimp::Importer importer; // 기본 임포트 옵션

	unsigned int importFlags = aiProcess_Triangulate |    // vertex 삼각형 으로 출력
		aiProcess_GenNormals |        // Normal 정보 생성  
		aiProcess_GenUVCoords |      // 텍스처 좌표 생성
		aiProcess_CalcTangentSpace |  // 탄젠트 벡터 생성
		aiProcess_ConvertToLeftHanded |  // DX용 왼손좌표계 변환
		aiProcess_PreTransformVertices;   // 노드의 변환행렬을 적용한 버텍스 생성한다.  *StaticMesh로 처리할때만

	{

		const aiScene* scene = importer.ReadFile("../Resources/Tree.fbx", importFlags);

		_tree = new Object;
		Model* model = new Model(device);

		model->LoadModel(scene);
		model->SetVS(L"Shader01.hlsl");
		model->SetPS(L"Shader01.hlsl");

		MeshRenderer* mr = new MeshRenderer(device);
		_tree->AddComponent(mr);
		mr->SetModel(model);

		AddObject(_tree);
		_tree->GetTransform().SetSize({ 5.f, 5.f, 5.f, 0.f });
		_tree->GetTransform()._translation = { 15.f, 0.f, 0.f, 1.f };

	}
	{

		const aiScene* scene = importer.ReadFile("../Resources/Character.fbx", importFlags);

		_character = new Object;
		Model* model = new Model(device);

		model->LoadModel(scene);
		model->SetVS(L"Shader01.hlsl");
		model->SetPS(L"Shader01.hlsl");

		MeshRenderer* mr = new MeshRenderer(device);
		_character->AddComponent(mr);
		mr->SetModel(model);

		AddObject(_character);
		_character->GetTransform().SetSize({ 0.1f, 0.1f, 0.1f, 0.f });

	}
	{

		const aiScene* scene = importer.ReadFile("../Resources/zeldaPosed001.fbx", importFlags);

		_zelda = new Object;
		Model* model = new Model(device);

		model->LoadModel(scene);
		model->SetVS(L"Shader01.hlsl");
		model->SetPS(L"Shader01.hlsl");

		MeshRenderer* mr = new MeshRenderer(device);
		_zelda->AddComponent(mr);
		mr->SetModel(model);

		AddObject(_zelda);
		_zelda->GetTransform().SetSize({ 0.1f, 0.1f, 0.1f, 0.f });
		_zelda->GetTransform()._translation = { -15.f, 0.f, 0.f, 1.f };

	}

	__super::Init(device);

}

void _06_Level::Update(float deltaTime)
{
	__super::Update(deltaTime);


}

void _06_Level::Render(ComPtr<ID3D11DeviceContext> dc)
{
	__super::Render(dc);

	{ //ImGUI

		ImGui::Begin("Controls");

		ImGui::Text("cameraX");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraX", &GameApp::GetWorld()->GetCamera()->GetPosition().x, -100.0f, 100.0f);

		ImGui::Text("cameraY");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraY", &GameApp::GetWorld()->GetCamera()->GetPosition().y, -100.0f, 100.0f);

		ImGui::Text("cameraZ");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraZ", &GameApp::GetWorld()->GetCamera()->GetPosition().z, -100.0f, 100.0f);

		ImGui::End();
	}
}
