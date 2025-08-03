#pragma once

#include <memory>
#include "Game.h"

class Core
{

public:
	void Initialize(std::unique_ptr<Game> _game);
	void Update();
	void Render();
	void Destroy();

private:
	std::unique_ptr<Game> game;
};

