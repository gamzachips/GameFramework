#pragma once
#include "../Common/Level.h"

class _03_Level : public Level
{
public:
	_03_Level();
	virtual ~_03_Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

private:
	class Cube* _cube = nullptr;
	class Light* _light = nullptr;

	bool toggle = false;
};

