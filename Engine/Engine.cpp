#include "pch.h"
#include "Engine.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Renderer.h"


std::unique_ptr<TimeManager> Engine::timeManager;
std::unique_ptr<InputManager> Engine::inputManager;
std::unique_ptr<ResourceManager> Engine::resourceManager;
std::unique_ptr<Renderer> Engine::renderer;
std::unique_ptr<Game> Engine::game;


bool Engine::Initialize(const WindowDesc& _desc)
{
	window = std::make_unique<Window>(_desc);
	if (!window->Initialize())
		return false;

	timeManager = std::make_unique<TimeManager>();
	inputManager = std::make_unique<InputManager>();
	resourceManager = std::make_unique<ResourceManager>();
	renderer = std::make_unique<Renderer>();

	timeManager->Init();
	resourceManager->Init();
	renderer->Init();

	return true;
}

void Engine::Run()
{
	isRunning = true;
	while (isRunning)
	{
		if (!window->Update())
			break;

		inputManager->Update();
		timeManager->Update();
		game->Update();

		renderer->GetRenderTarget().Get()->BeginDraw();
		game->Render();
		renderer->GetRenderTarget().Get()->EndDraw();

	}
}

int Engine::ShutDown()
{
	return window->Destroy();
}
