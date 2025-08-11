#include "pch.h"
#include "Object.h"

size_t Object::nextComponentTypeID = 0;

Object::Object(World* _owner)
{
	owner = _owner;
}

Object::~Object()
{
}

void Object::Awake()
{
	state = ObjectState::Awake;

	for (const auto& comp: components)
	{
		if (comp->enabled)
			comp->Awake();
	}
}

void Object::Init()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->Init();
	}
}

void Object::Update()
{
	if (state == ObjectState::Awake && isActive)
	{
		Init();
	}

	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->Update();
	}
}

void Object::FixedUpdate()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->FixedUpdate();
	}
}

void Object::LateUpdate()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->LateUpdate();
	}
}

void Object::Render()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->Render();
	}
}

void Object::OnEnable()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->OnEnable();
	}
}

void Object::OnDisable()
{
	for (const auto& comp : components)
	{
		if (comp->enabled)
			comp->OnDisable();
	}
}

void Object::OnDestroy()
{
	for (const auto& comp: components)
	{
		if (comp->enabled)
			comp->OnDestroy();
	}
}
