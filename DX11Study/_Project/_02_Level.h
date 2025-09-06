#pragma once
#include "../Common/Level.h"

class Cube;

class _02_Level : public Level
{
public:
	_02_Level();
	virtual ~_02_Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

private:
	Cube* _cubes[3];
};

