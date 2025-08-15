#pragma once
#include "Window.h"
#include "Game.h"

class TimeManager;
class InputManager;
class RenderManager;
class ResourceManager;
class Renderer;

template<typename T>
concept GameType = std::is_base_of_v<Game, T>;

class Engine
{
public:
	bool Initialize(const WindowDesc& _desc);
	template<GameType T>
	void StartGame();
	void Run();
	int ShutDown();

	static TimeManager* GetTimeManager() { return timeManager.get(); }
	static InputManager* GetInputManager() { return inputManager.get(); }
	static ResourceManager* GetResourceManager() { return resourceManager.get(); }
	static Renderer* GetRenderer() { return renderer.get(); }
	static Game* GetGame() { return game.get(); }

private:
	std::unique_ptr<Window> window;
	bool isRunning = false;

	static std::unique_ptr<TimeManager> timeManager;
	static std::unique_ptr<InputManager> inputManager;
	static std::unique_ptr<ResourceManager> resourceManager;
	static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<Game> game;
};

template<GameType T>
inline void Engine::StartGame()
{
	game = std::make_unique<T>();
	game->Init();
}
