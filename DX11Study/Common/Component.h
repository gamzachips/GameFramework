#pragma once

class Object;

class Component
{
public:
	Component() {}
	virtual ~Component() {}
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(ComPtr<ID3D11DeviceContext> dc) = 0;

	void SetOwner(Object* owner) { _owner = owner; }
	Object* GetOwner() { return _owner; }

private:
	Object* _owner = nullptr;
};

