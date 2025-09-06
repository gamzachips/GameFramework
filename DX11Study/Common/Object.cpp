#include "pch.h"
#include "Object.h"
#include "Transform.h"
#include "Camera.h"
#include "World.h"
#include "Component.h"
#include "MeshRenderer.h"
#include "SkyboxRenderer.h"


Object::Object()
{

}

Object::~Object()
{
	for (Component* component : _components)
	{
		delete component;
	}
}

void Object::Init()
{
	for (Component* component : _components)
	{
		component->Init();
	}

}

void Object::Update(float deltaTime)
{
	if (_isActive == false) return;

	_transform.UpdateTransform();

	for (Component* component : _components)
	{
		component->Update(deltaTime);
	}
}

void Object::Render(ComPtr<ID3D11DeviceContext> dc)
{
	if (_isActive == false) return;

	if (_meshRenderer)
		_meshRenderer->Render(dc);

	if (_skyboxRenderer)
		_skyboxRenderer->Render(dc);
}

void Object::AddComponent(Component* component)
{
	if (_meshRenderer == nullptr)
		_meshRenderer = dynamic_cast<MeshRenderer*>(component);

	if (_skyboxRenderer == nullptr)
		_skyboxRenderer = dynamic_cast<SkyboxRenderer*>(component);

	_components.push_back(component);
	component->SetOwner(this);
}


