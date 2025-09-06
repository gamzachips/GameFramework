#include "../Common/pch.h"
#include "_03_Level.h"
#include "TestApp.h"
#include "Cube.h"
#include "../Common/MeshRenderer.h"
#include "../Common/Transform.h"
#include "../Common/Texture.h"
#include "../Common/World.h"
#include "../Common/Camera.h"
#include "../Common/Material.h"

_03_Level::_03_Level()
{

}

_03_Level::~_03_Level()
{

}

void _03_Level::Init(ComPtr<ID3D11Device> device)
{
	_cube = new Cube(device);
	AddObject(_cube);
	_cube->GetTransform().SetSize({ 10.0f, 10.0f, 10.0f, 10.f });

	LightData light;
	SetLightData(light);

	MeshRenderer* cubeMR = _cube->GetComponent<MeshRenderer>();
	_cube->AddComponent(cubeMR);

	__super::Init(device);
}

void _03_Level::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void _03_Level::Render(ComPtr<ID3D11DeviceContext> dc)
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


		ImGui::ColorEdit3("colorA", &GameApp::GetWorld()->GetLightData()._ambient.x);
		ImGui::ColorEdit3("colorD", &GameApp::GetWorld()->GetLightData()._diffuse.x);
		ImGui::ColorEdit3("colorS", &GameApp::GetWorld()->GetLightData()._specular.x);

		ImGui::Text("LightDirection-X");
		ImGui::SameLine();
		ImGui::SliderFloat("##LightDirectionX", &GameApp::GetWorld()->GetLightData()._direction.x, -1.0f, 1.0f);

		ImGui::Text("LightDirection-Y");
		ImGui::SameLine();
		ImGui::SliderFloat("##LightDirectionY", &GameApp::GetWorld()->GetLightData()._direction.y, -1.0f, 1.0f);

		ImGui::Text("LightDirection-Z");
		ImGui::SameLine();
		ImGui::SliderFloat("##LightDirectionZ", &GameApp::GetWorld()->GetLightData()._direction.z, -1.0f, 1.0f);

		ImGui::Text("Cube Yaw Rotate");
		ImGui::SameLine();
		ImGui::SliderFloat("##CubeYaw", &_cube->GetTransform()._rotation.y, 0.0f, XMConvertToRadians(360.0f) );

		ImGui::Text("Cube Pitch Rotate");
		ImGui::SameLine();
		ImGui::SliderFloat("##CubePitch", &_cube->GetTransform()._rotation.x, 0.0f, XMConvertToRadians(360.0f));


		ImGui::End();
	}

}
