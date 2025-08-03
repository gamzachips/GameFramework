#pragma once

enum class ObjectState
{
	None,
	Awake,
	PendingDestroy
};

class Object 
{
	friend class World;
public:
	Object(World* _owner);
	~Object();

	void SetActive(bool _isActive) { isActive = _isActive; }
	bool GetIsActive() { return isActive; }

private:
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
};

