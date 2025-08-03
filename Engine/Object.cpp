#include "pch.h"
#include "Object.h"

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
}

void Object::Init()
{
}

void Object::Update()
{
	if (state == ObjectState::Awake && isActive)
	{
		Init();
	}
}

void Object::FixedUpdate()
{
}

void Object::LateUpdate()
{
}

void Object::Render()
{
}

void Object::OnEnable()
{
}

void Object::OnDisable()
{
}

void Object::OnDestroy()
{
}
