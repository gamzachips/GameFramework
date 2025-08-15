#pragma once
class Component
{
	friend class Object;
public:
	virtual void Awake();
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void Render();

	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

protected:
	bool enabled = true;
	Object* gameObject = nullptr;
};

