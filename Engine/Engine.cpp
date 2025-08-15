#include "pch.h"
#include "Engine.h"
#include "Game.h"

std::unique_ptr<Game> Engine::GGame = nullptr;

bool Engine::Initialize(const WindowDesc& _desc)
{
	window = std::make_unique<Window>(_desc);
	core = std::make_unique<Core>();
	if (!window->Initialize())
		return false;
	return true;
}

void Engine::SetGame(std::unique_ptr<Game> _game)
{
	GGame = std::move(_game);
	core->Initialize(GGame.get());
}

void Engine::Run()
{
	isRunning = true;
	while (isRunning)
	{
		if (!window->Update())
			break;

		core->Update();
		core->Render();

	}
}

int Engine::ShutDown()
{
	core->Destroy();
	return window->Destroy();

}
