#include "pch.h"
#include "Engine.h"
#include "Game.h"

Game* GGame = nullptr;

bool Engine::Initialize(const WindowDesc& _desc, std::unique_ptr<Game> _game)
{
	window = std::make_unique<Window>(_desc);
	core = std::make_unique<Core>();
	if (!window->Initialize())
		return false;
	core->Initialize(std::move(_game));

	GGame = _game.get();

	return true;
}

void Engine::Run()
{
	isRunning = true;
	while (isRunning)
	{
		if (!window->Update())
			break;


	}
}

int Engine::ShutDown()
{
	core->Destroy();
	return window->Destroy();

}
