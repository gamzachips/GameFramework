#include "pch.h"
#include "Core.h"


void Core::Initialize(Game* _game)
{
	game = _game;
	game->Init();
}

void Core::Update()
{
	game->Update();
}

void Core::Render()
{
	game->Render();
}

void Core::Destroy()
{
}
