#pragma once
#include "World.h"
#include <memory>
#include <unordered_map>
#include <string>



class Game
{
	friend class Engine;
public:
	Game();
	virtual ~Game();

	World* CreateWorld(std::string _name);
	void SetWorld(std::string _name);
	void DontDestroyOnLoad(Object* _object);

private:
	virtual void Init();
	void Update();
	void Render();

	void ChangeWorld();
private:
	std::unordered_map<std::string, std::unique_ptr<World>> worlds;
	std::unique_ptr<World> persistentWorld = nullptr;

	World* nowWorld = nullptr;
	World* nextWorld = nullptr;

};

