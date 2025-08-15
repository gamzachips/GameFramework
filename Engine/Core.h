#pragma once

#include <memory>
#include "Game.h"

class Core
{

public:
	void Initialize(Game* _game);
	void Update();
	void Render();
	void Destroy();

private:
	Game* game;
};

