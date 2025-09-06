#pragma once
#include "../Common/Level.h"

class _07_Level : public Level
{
public:
	_07_Level();
	virtual ~_07_Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

private:
	Object* _robot;
};

