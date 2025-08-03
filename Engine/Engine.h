#pragma once
#include "Window.h"
#include "Core.h"
#include <memory>

class Game;

class Engine
{
public:
	bool Initialize(const WindowDesc& _desc, std::unique_ptr<Game> _game);
	void Run();
	int ShutDown();

private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Core> core;
	bool isRunning = false;
};

