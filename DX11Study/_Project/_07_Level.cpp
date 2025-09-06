#include "../Common/pch.h"
#include "_07_Level.h"
#include "TestApp.h"
#include "../Common/World.h"
#include "../Common/Camera.h"
#include "../Common/Object.h"
#include "../Common/MeshRenderer.h"
#include "../Common/Material.h"
#include "../Common/Model.h"
#include "../Common/Animator.h"

_07_Level::_07_Level()
{
}

_07_Level::~_07_Level()
{
}

void _07_Level::Init(ComPtr<ID3D11Device> device)
{

	LightData light;
	SetLightData(light);

	Assimp::Importer importer; // 기본 임포트 옵션

	unsigned int importFlags = aiProcess_Triangulate |    // vertex 삼각형 으로 출력
		aiProcess_GenNormals |        // Normal 정보 생성  
		aiProcess_GenUVCoords |      // 텍스처 좌표 생성
		aiProcess_CalcTangentSpace |  // 탄젠트 벡터 생성
		aiProcess_ConvertToLeftHanded; // DX용 왼손좌표계 변환

	{
		const aiScene* scene = importer.ReadFile("../Resources/BoxHuman.fbx", importFlags);

		_robot = new Object;
		Model* model = new Model(device);

		model->LoadModel(scene);
		model->SetVS(L"Shader01.hlsl");
		model->SetPS(L"Shader01.hlsl");

		MeshRenderer* mr = new MeshRenderer(device);
		_robot->AddComponent(mr);
		mr->SetModel(model);
		
		Animator* anim = new Animator(model);
		anim->ProcessAnimations(scene);
		anim->PlayAnimation(0);
		_robot->AddComponent(anim);

		AddObject(_robot);
		//_robot->GetTransform().SetSize({ 0.1f, 0.1f, 0.1f, 0.1f });
		//_robot->GetTransform()._translation = { 0.f, 0.f, 0.f, 1.f };
	}


	__super::Init(device);
}

void _07_Level::Update(float deltaTime)
{
	__super::Update(deltaTime);

}

void _07_Level::Render(ComPtr<ID3D11DeviceContext> dc)
{
	__super::Render(dc);

	{ //ImGUI

		ImGui::Begin("Controls");

		ImGui::Text("cameraX");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraX", &GameApp::GetWorld()->GetCamera()->GetPosition().x, -1000.0f, 1000.0f);

		ImGui::Text("cameraY");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraY", &GameApp::GetWorld()->GetCamera()->GetPosition().y, -1000.0f, 1000.0f);

		ImGui::Text("cameraZ");
		ImGui::SameLine();
		ImGui::SliderFloat("##cameraZ", &GameApp::GetWorld()->GetCamera()->GetPosition().z, -1000.0f, 1000.0f);

		ImGui::End();
	}
}
