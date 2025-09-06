#pragma once
#include "../Common/Object.h"

class Cube : public Object
{
public:
	Cube(ComPtr<ID3D11Device> device);
	virtual ~Cube();

public:
	virtual void Init();
	virtual void Update(float deltaTime);

	void SetRotateSpeed(float speed) { _rotateSpeed = speed; }

private:
	float _rotateSpeed = 1.f;
};

