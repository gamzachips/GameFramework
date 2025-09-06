#pragma once
#include "Component.h"

class ConstantBuffer;
class Environment;
class SkyboxCube;

class SkyboxRenderer : public Component
{
public:
	SkyboxRenderer(ComPtr<ID3D11Device> device);
	virtual ~SkyboxRenderer();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

	void SetEnvironment(std::shared_ptr<Environment> env) { _env = env; }
private:
	void CreateInputLayout(ComPtr<ID3DBlob> vsBlob);

private:
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	ComPtr<ID3D11BlendState> blendState;
	ComPtr<ID3D11DepthStencilState> _depthStencilStateSkybox;

	ConstantBuffer* _wvpBuffer = nullptr;
	std::shared_ptr<Environment> _env = nullptr;
	SkyboxCube* _cube = nullptr;
};

