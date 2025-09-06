#pragma once

#include "Transform.h"

class Component;
class MeshRenderer;
class SkyboxRenderer;

class Object
{
public:
	Object();
	virtual ~Object();


public:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);
	void SetIsActive(bool b) { _isActive = b; }

	void SetParent(Object* parent) {
		this->_transform.parent = &(parent->_transform);
	}

	Transform& GetTransform() { return _transform; }

	void AddComponent(Component* component);

	template<typename T>
	T* GetComponent()
	{
		if (dynamic_cast<T*>(_meshRenderer))
			return dynamic_cast<T*>(_meshRenderer);
		else
		{
			for (Component* component : _components)
			{
				T* t = dynamic_cast<T*>(component);
				if (t != nullptr)
					return t;
			}
		}
	}
	
protected:
	std::vector<Component*> _components;
	Transform _transform {};
	MeshRenderer* _meshRenderer = nullptr;
	SkyboxRenderer* _skyboxRenderer = nullptr;
	bool _isActive = true;

};

