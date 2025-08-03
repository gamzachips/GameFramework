#pragma once
class Component
{
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

private:
	bool enabled = true;

};

