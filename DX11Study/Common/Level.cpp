#include "pch.h"
#include "Level.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"

Level::~Level()
{
	delete _camera;
}

void Level::Init(ComPtr<ID3D11Device> device)
{
	for (Object* object : _objects)
	{
		object->Init();
	}
	_camera = new Camera;
}

void Level::Update(float deltaTime)
{
	for (Object* object : _objects)
	{
		object->Update(deltaTime);
	}
	_camera->Update(deltaTime);
}

void Level::Render(ComPtr<ID3D11DeviceContext> dc)
{
	for (Object* object : _objects)
	{
		object->Render(dc);
	}
}
