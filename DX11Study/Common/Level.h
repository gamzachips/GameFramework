#pragma once
#include "Object.h"

class Camera;
class Object;

class Level
{
public:
	Level() {};
	virtual ~Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

	Camera* GetCamera() { return _camera; }
	LightData& GetLightData() { return _lightData; }
	void AddObject(Object* object) { _objects.push_back(object);  }
	void PopObject() { if (!_objects.empty()) { Object* ob = _objects.back(); _objects.pop_back(); delete ob;
	} }
	void SetLightData(LightData lightData) { _lightData = lightData; }

protected:
	Camera* _camera;
	LightData _lightData;
	std::vector<Object*> _objects;
};

