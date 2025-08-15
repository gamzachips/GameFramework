#include "MyGame.h"
#include "SpriteRenderer.h"

void MyGame::Init()
{
	World* testWorld = CreateWorld("Test");
	SetWorld("Test");

	Object* obj = testWorld->CreateObject();
	SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
	sr->SetTexture(L"lofi.png");
}
