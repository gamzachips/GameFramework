#pragma once
#include "Component.h"


class ConstantBuffer;

class Texture;
class Light;
class Model;
class Node;
class Material;
class Mesh;
class Environment;

class MeshRenderer : public Component
{
public:
	MeshRenderer(ComPtr<ID3D11Device> device);
	virtual ~MeshRenderer();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

	void RenderNode(ComPtr<ID3D11DeviceContext> dc,Node* node);
	void SetModel(std::shared_ptr<Model> model) { _model = model; }
	void SetEnvironment(std::shared_ptr<Environment> env) { _env = env; }
	std::shared_ptr<Model> GetModel() { return _model; }
private:
	void CreateInputLayout(ComPtr<ID3DBlob> vsBlob);

	void InputAssemblerStage(std::shared_ptr<Mesh> mesh);
	void VertexShaderStage();
	void PixelShaderStage(std::shared_ptr<Mesh> mesh);
	void CreateWVPBuffer(Matrix world);
	void CreateLightBuffer();
	void CreateMaterialBuffer(std::shared_ptr<Mesh> mesh);

private:
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	ComPtr<ID3D11BlendState> blendState;

	ConstantBuffer* _materialBuffer = nullptr;
	ConstantBuffer* _wvpBuffer = nullptr;
	ConstantBuffer* _bonePalleteBuffer = nullptr;
	ConstantBuffer* _lightBuffer;

	std::shared_ptr<Model> _model = nullptr;
	std::shared_ptr<Environment> _env = nullptr;
};

