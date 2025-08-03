#include "pch.h"
#include "Core.h"


void Core::Initialize(std::unique_ptr<Game> _game)
{
	game = std::move(_game);
}

void Core::Update()
{
}

void Core::Render()
{
}

void Core::Destroy()
{
}
