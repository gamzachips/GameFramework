#include "pch.h"
#include "World.h"

Object* World::CreateObject()
{
	std::unique_ptr<Object> newObject = std::make_unique<Object>(this);
	newObject->Awake();
	objects.push_back(std::move(newObject));
	return objects.back().get();
}

void World::RemoveObject(Object* _object)
{
	_object->state = ObjectState::PendingDestroy;
}

void World::Init()
{

}

void World::Update()
{
	for (const auto& object : objects)
	{
		if(object->GetIsActive())
			object->Update();
	}

	for (const auto& object : objects)
	{
		if (object->GetIsActive())
			object->FixedUpdate();
	}

	for (const auto& object : objects)
	{
		if (object->GetIsActive())
			object->LateUpdate();
	}

	for (auto it = objects.begin(); it!= objects.end();)
	{
		if ((*it)->state == ObjectState::PendingDestroy)
		{
			(*it)->OnDestroy();
			it = objects.erase(it);
		}
		else
		{
			++it;
		}	
	}
}

void World::Render()
{
	//TODO: zorder Á¤·Ä 

	for (const auto& object : objects)
	{
		if (object->GetIsActive())
			object->Render();
	}
}
