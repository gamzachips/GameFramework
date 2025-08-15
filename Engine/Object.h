#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "Component.h"

enum class ObjectState
{
	None,
	Awake,
	PendingDestroy
};

template<typename T>
concept ComponentType = std::is_base_of_v<Component, T>;

class Object 
{
	friend class World;
public:
	Object(World* _owner);
	~Object();

	void SetActive(bool _isActive) { isActive = _isActive; }
	bool IsActive() { return isActive; }

	template<ComponentType T>
	T* AddComponent();

	template<ComponentType T>
	T* GetComponent();

	//TODO : RemoveComponent

private:
	template<ComponentType T>
	size_t GetComponentTypeID();

	void Awake();
	void Init();
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render();

	void OnEnable();
	void OnDisable();
	void OnDestroy();

private:
	ObjectState state = ObjectState::None;
	World* owner = nullptr;
	bool isActive = true;
	static size_t nextComponentTypeID;

	std::vector<std::unique_ptr<Component>> components;
	std::unordered_map<size_t, std::vector<Component*>> componentsMap;

};

template<ComponentType T>
T* Object::AddComponent()
{
	std::unique_ptr<T> newComp = std::make_unique<T>();
	T* newCompPtr = newComp.get();
	components.push_back(std::move(newComp)); 
	size_t CompID = GetComponentTypeID<T>();
	componentsMap[CompID].push_back(newCompPtr);
	newCompPtr->gameObject = this;

	return newCompPtr;
}

template<ComponentType T>
inline T* Object::GetComponent()
{
	size_t CompID = GetComponentTypeID<T>();
	auto foundIt = componentsMap.find(CompID);
	if (foundIt != componentsMap.end())
	{
		if (!foundIt->second.empty())
		{
			return dynamic_cast<T*>(foundIt->second.front());
		}
	}
	return nullptr;
}

template<ComponentType T>
inline size_t Object::GetComponentTypeID()
{
	static size_t typeID = nextComponentTypeID++;
	return typeID;
}
