#pragma once

#include "D3DRenderer.h"

class InputManager;
class TimeManager;
class ResourceManager;
class Camera;
class Level;

class World
{
public:
	World();
	~World();

	void Init();
	void Update();
	void Render();
public:
	Camera* GetCamera();
	LightData& GetLightData();
	InputManager* GetInputManager() { return _inputManager; }
	ResourceManager* GetResourceManager() { return _resourceManager; }
	ComPtr<ID3D11Device> GetDevice() { return _renderer.GetDevice(); }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _renderer.GetDeviceContext(); }

	void MoveCamera();
	void RotateCamera();

	template<typename T>
	void ChangeLevel()
	{
		if (_nowLevel)
			delete _nowLevel;
		_nowLevel = new T;
	}

private:
	void RenderBeginImGUI();
	void RenderEndImGUI();


private:
	D3DRenderer _renderer;
	Level* _nowLevel = nullptr;

	InputManager* _inputManager;
	TimeManager* _timeManager;
	ResourceManager* _resourceManager;
};

