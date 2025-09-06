#include "../Common/pch.h"
#include "_02_Level.h"
#include "TestApp.h"
#include "Cube.h"
#include "../Common/Camera.h"

_02_Level::_02_Level()
{


}

_02_Level::~_02_Level()
{
	for (int i = 0; i < 3; i++)
		delete _cubes[i];
}

void _02_Level::Init(ComPtr<ID3D11Device> device)
{


	for (int i = 0; i < 3; i++)
	{
		_cubes[i] = new Cube(device);
		AddObject(_cubes[i]);
	}
		

	for (int i = 0; i < 3; i++)
		_cubes[i]->Init();

	_cubes[1]->SetParent(_cubes[0]);
	_cubes[2]->SetParent(_cubes[1]);

	_cubes[0]->GetTransform().SetPosition({ 0,0,0,0 });
	_cubes[1]->GetTransform().SetPosition({ 0,3,0,0 });
	_cubes[2]->GetTransform().SetPosition({ 0,3,0,0 });

	_cubes[0]->SetRotateSpeed(1.f);
	_cubes[1]->SetRotateSpeed(3.f);
	_cubes[2]->SetRotateSpeed(5.f);

	for (int i = 0; i < 3; i++)
		_cubes[i]->GetTransform().SetSize({ 0.3f, 0.3f, 0.3f, 1 });

	__super::Init(device);
}

void _02_Level::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void _02_Level::Render(ComPtr<ID3D11DeviceContext> dc)
{
	__super::Render(dc);

	{ //ImGUI

		ImGui::Begin("Controls");

		// Cube1 X 슬라이더
		ImGui::Text("Cube1 X");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube1X", &_cubes[0]->GetTransform()._translation.x, -10.0f, 10.0f);

		// Cube1 Y 슬라이더
		ImGui::Text("Cube1 Y");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube1Y", &_cubes[0]->GetTransform()._translation.y, -10.0f, 10.0f);

		// Cube1 Z 슬라이더
		ImGui::Text("Cube1 Z");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube1Z", &_cubes[0]->GetTransform()._translation.z, -10.0f, 10.0f);

		// Cube2 X 슬라이더
		ImGui::Text("Cube2 X");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube2X", &_cubes[1]->GetTransform()._translation.x, -10.0f, 10.0f);

		// Cube2 Y 슬라이더
		ImGui::Text("Cube2 Y");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube2Y", &_cubes[1]->GetTransform()._translation.y, -10.0f, 10.0f);

		// Cube2 Z 슬라이더
		ImGui::Text("Cube2 Z");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube2Z", &_cubes[1]->GetTransform()._translation.z, -10.0f, 10.0f);

		// Cube3 X 슬라이더
		ImGui::Text("Cube3 X");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube3X", &_cubes[2]->GetTransform()._translation.x, -10.0f, 10.0f);

		// Cube3 Y 슬라이더
		ImGui::Text("Cube3 Y");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube3Y", &_cubes[2]->GetTransform()._translation.y, -10.0f, 10.0f);

		// Cube3 Z 슬라이더
		ImGui::Text("Cube3 Z");
		ImGui::SameLine();
		ImGui::SliderFloat("##Cube3Z", &_cubes[2]->GetTransform()._translation.z, -10.0f, 10.0f);

		// Camera X 슬라이더
		ImGui::Text("Camera X");
		ImGui::SameLine();
		ImGui::SliderFloat("##CameraX", &(GetCamera()->GetPosition().x), -10.0f, 10.0f);

		// Camera Y 슬라이더
		ImGui::Text("Camera Y");
		ImGui::SameLine();
		ImGui::SliderFloat("##CameraY", &(GetCamera()->GetPosition().y), -10.0f, 10.0f);

		// Camera Z 슬라이더
		ImGui::Text("Camera Z");
		ImGui::SameLine();
		ImGui::SliderFloat("##CameraZ", &(GetCamera()->GetPosition().z), -10.0f, 10.0f);

		ImGui::Text("FOV(degree)");
		ImGui::SameLine();
		ImGui::SliderFloat("##FOV", &(GetCamera()->GetFOV()), 0.01f, 100.0f);

		ImGui::Text("Near");
		ImGui::SameLine();
		ImGui::SliderFloat("##Near", &(GetCamera()->GetNear()), 0.01f, 100.0f);

		ImGui::Text("Far");
		ImGui::SameLine();
		ImGui::SliderFloat("##Far", &(GetCamera()->GetFar()), 0.01f, 100.0f);

		ImGui::End();
	}

}
