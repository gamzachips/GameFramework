#pragma once
#include "Object.h"
#include <memory>
#include <vector>

class World
{
	friend class Game;
public:
	Object* CreateObject();
	void RemoveObject(Object* _object);
private:
	void Init();
	void Update();
	void Render();

	std::vector<std::unique_ptr<Object>> objects;

};

