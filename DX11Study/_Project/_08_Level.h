#pragma once
#include "../Common/Level.h"

class _08_Level : public Level
{
public:
	_08_Level();
	virtual ~_08_Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

private:
	ComPtr<ID3D11Device> _device;
	Object* _gun;
	Object* _sphere;
	Object* _skyboxObj;

	bool hasDiffuse = false;
	bool hasRoughness = false;
	bool hasMetalness = false;
	bool onIBL = true;

	//Vector4 color = { 0.9f, 0.75f, 0.f ,1.f };
	Vector4 color = { 1.0f, 1.0f, 1.0f ,1.0f };
	float roughness = 0.1f;
	float metalness = 1.0f;

};

