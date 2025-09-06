#include "pch.h"
#include "World.h"
#include "Level.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "StaticMesh.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Camera.h"

World::World()
{
	
	_inputManager = new InputManager;
	_timeManager = new TimeManager;
	_resourceManager = new ResourceManager;
}

World::~World()
{
	delete _inputManager;
	delete _timeManager;
	delete _resourceManager;
	delete _nowLevel;
}

void World::Init()
{
	_renderer.Init();
	_inputManager->Init();
	_timeManager->Init();
	_resourceManager->Init();
	_nowLevel->Init(GetDevice());

}

void World::Update()
{
	_inputManager->Update();
	_timeManager->Update();
	_nowLevel->Update(_timeManager->GetDeltaTime());
	MoveCamera();
	RotateCamera();
}

void World::Render()
{
	_renderer.RenderBegin();
	RenderBeginImGUI();
	_nowLevel->Render(GetDeviceContext());
	RenderEndImGUI();
	_renderer.RenderEnd();

}

void World::RenderBeginImGUI()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize({ 500, 400 });
}

void World::RenderEndImGUI()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

Camera* World::GetCamera()
{
	return _nowLevel->GetCamera();
}

LightData& World::GetLightData()
{
	return _nowLevel->GetLightData();
}

void World::MoveCamera()
{

	if (_inputManager->GetButtonPressed(KeyType::W))
	{
		GetCamera()->AddInputVector(GetCamera()->GetForward());
	}
	else if (_inputManager->GetButtonPressed(KeyType::S))
	{
		GetCamera()->AddInputVector(-GetCamera()->GetForward());
	}
	if (_inputManager->GetButtonPressed(KeyType::D))
	{
		GetCamera()->AddInputVector(GetCamera()->GetRight());
	}
	else if (_inputManager->GetButtonPressed(KeyType::A))
	{
		GetCamera()->AddInputVector(-GetCamera()->GetRight());
	}


}

void World::RotateCamera()
{
	if (_inputManager->GetButtonPressed(KeyType::RightMouse))
	{
		Vector2 mouseMove = _inputManager->GetMouseMovement();
		GetCamera()->AddRotateInputVector({ mouseMove.y * 0.1f, mouseMove.x * 0.1f, 0.f } );
	}
}
