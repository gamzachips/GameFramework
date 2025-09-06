#pragma once
#include "../Common/Level.h"

class Object;
class _06_Level : public Level
{
public:
	_06_Level();
	virtual ~_06_Level();
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

private:
	Object* _tree;
	Object* _character;
	Object* _zelda;
};

