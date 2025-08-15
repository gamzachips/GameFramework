#include "MyGame.h"
#include "SpriteRenderer.h"

MyGame::MyGame()
{
	World* testWorld = CreateWorld("Test");
	SetWorld("Test");

	Object* obj = testWorld->CreateObject();
	SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
	sr->SetTexture(L"lofi.png");
}

MyGame::~MyGame()
{
}
