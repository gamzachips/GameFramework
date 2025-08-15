#pragma once
#include "World.h"
#include <memory>
#include <unordered_map>
#include <string>

class TimeManager;
class InputManager;
class ResourceManager;
class Renderer;

class Game
{
	friend class Core;
public:
	Game();
	virtual ~Game();

	World* CreateWorld(std::string _name);
	void SetWorld(std::string _name);
	void DontDestroyOnLoad(Object* _object);

	const TimeManager* GetTimeManager() const { return timeManager.get(); }
	const InputManager* GetInputManager() const { return inputManager.get(); }
	const ResourceManager* GetResourceManager() const { return resourceManager.get(); }
	const Renderer* GetRenderer() const { return renderer.get(); }

private:
	void Init();
	void Update();
	void Render();

	void ChangeWorld();

private:
	std::unordered_map<std::string, std::unique_ptr<World>> worlds;
	std::unique_ptr<World> persistentWorld = nullptr;

	World* nowWorld = nullptr;
	World* nextWorld = nullptr;

	std::unique_ptr<TimeManager> timeManager;
	std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<Renderer> renderer;
};

