#include "pch.h"
#include "MeshRenderer.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "D3DRenderer.h"
#include "Shader.h"
#include "Object.h"
#include "GameApp.h"
#include "World.h"
#include "Model.h"
#include "Camera.h"
#include "Material.h"
#include "StaticMesh.h"
#include "SkeletalMesh.h"
#include "Texture.h"
#include "Node.h"
#include "Animator.h"
#include "Environment.h"

//ConstantBuffer* MeshRenderer::_lightBuffer = nullptr;

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device)
{
	_device = device;
}

MeshRenderer::~MeshRenderer()
{
	if (_wvpBuffer)
		delete _wvpBuffer;

	if (_materialBuffer)
		delete _materialBuffer;

	if(_lightBuffer)
		delete _lightBuffer;

	if (_bonePalleteBuffer)
		delete _bonePalleteBuffer;
}

void MeshRenderer::Init()
{
	CreateInputLayout(_model->GetVS()->GetBlob());

	_wvpBuffer = new ConstantBuffer;
	_wvpBuffer->Create(sizeof(WVPData), _device);

	_lightBuffer = new ConstantBuffer;
	_lightBuffer->Create(sizeof(LightData), _device);

	_materialBuffer = new ConstantBuffer;
	_materialBuffer->Create(sizeof(MaterialData), _device);

	_bonePalleteBuffer = new ConstantBuffer;
	_bonePalleteBuffer->Create(sizeof(MatrixPallete), _device);

	//Blend
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_device->CreateBlendState(&blendDesc, &blendState);
}


void MeshRenderer::Update(float deltaTime)
{
	
}

void MeshRenderer::Render(ComPtr<ID3D11DeviceContext> dc)
{
	if (_model == nullptr)
		return;

	_deviceContext = dc;

	CreateLightBuffer();

	if (_model->GetSkeletalMeshes().size() > 0) {
		MatrixPallete& pallete = GetOwner()->GetComponent<Animator>()->GetBonePallete();
		dc->UpdateSubresource(_bonePalleteBuffer->GetComPtr().Get(), 0, nullptr, &pallete, 0, 0);
	}

	RenderNode(dc, _model->GetRootNode());
}

void MeshRenderer::RenderNode(ComPtr<ID3D11DeviceContext> dc, Node* node)
{
	//Constant Buffer
	CreateWVPBuffer(XMMatrixTranspose(node->globalTransform * GetOwner()->GetTransform()._transform));

	for (int i = 0; i < node->meshIdxes.size(); i++)
	{
		std::shared_ptr<StaticMesh> mesh = _model->GetStaticMeshes()[node->meshIdxes[i]];
		
		//CB
		CreateMaterialBuffer(mesh);
		//IA
		InputAssemblerStage(mesh);
		//VS
		VertexShaderStage();
		//PS
		PixelShaderStage(mesh);

		dc->OMSetBlendState(blendState.Get(), nullptr, 0xffffffff);

		if (mesh->GetIndexBuffer() != nullptr)
			dc->DrawIndexed(mesh->GetIndexBuffer()->GetCount(), 0, 0);
		else
			dc->Draw(mesh->GetVertexBuffer()->GetCount(), 0);
	}

	for (auto child : node->children)
		RenderNode(dc, child);
}



void MeshRenderer::CreateInputLayout(ComPtr<ID3DBlob> vsBlob)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 1, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	const int count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	_device->CreateInputLayout(layout, count, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
		_inputLayout.GetAddressOf());
}

void MeshRenderer::InputAssemblerStage(std::shared_ptr<Mesh> mesh)
{
	MaterialData materialData = _model->GetMaterials()[mesh->GetMaterialIndex()]->GetMaterialData();
	_deviceContext->UpdateSubresource(_materialBuffer->GetComPtr().Get(), 0, nullptr, &materialData, 0, 0);

	const unsigned int stride = mesh->GetVertexBuffer()->GetStride();
	const unsigned int offset = mesh->GetVertexBuffer()->GetOffset();
	_deviceContext->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetInputLayout(_inputLayout.Get());
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void MeshRenderer::VertexShaderStage()
{
	_deviceContext->VSSetShader(_model->GetVS()->Get().Get(), nullptr, 0);
	_deviceContext->VSSetConstantBuffers(0, 1, _wvpBuffer->GetComPtr().GetAddressOf());
	_deviceContext->VSSetConstantBuffers(3, 1, _bonePalleteBuffer->GetComPtr().GetAddressOf());
}

void MeshRenderer::PixelShaderStage(std::shared_ptr<Mesh> mesh)
{
	unsigned int materialIdx = mesh->GetMaterialIndex();
	std::shared_ptr<Material> material = _model->GetMaterials()[materialIdx];

	_deviceContext->PSSetShader(_model->GetPS()->Get().Get(), nullptr, 0);
	_deviceContext->PSSetConstantBuffers(1, 1, _lightBuffer->GetComPtr().GetAddressOf());
	_deviceContext->PSSetConstantBuffers(2, 1, _materialBuffer->GetComPtr().GetAddressOf());
	_deviceContext->PSSetSamplers(0, 1, Texture::GetLinearSampler().GetAddressOf());
	_deviceContext->PSSetSamplers(1, 1, Texture::GetClampSampler().GetAddressOf());

	if (material->GetAmbient())
	{
		_deviceContext->PSSetShaderResources(0, 1, material->GetAmbient()->GetTextRV().GetAddressOf());
	}
	if (material->GetDiffuse())
	{
		_deviceContext->PSSetShaderResources(1, 1, material->GetDiffuse()->GetTextRV().GetAddressOf());
	}
	if (material->GetSpecular())
	{
		_deviceContext->PSSetShaderResources(2, 1, material->GetSpecular()->GetTextRV().GetAddressOf());
	}
	if (material->GetNormal())
	{
		_deviceContext->PSSetShaderResources(3, 1, material->GetNormal()->GetTextRV().GetAddressOf());
	}
	if (material->GetOpacity())
	{
		_deviceContext->PSSetShaderResources(4, 1, material->GetOpacity()->GetTextRV().GetAddressOf());
	}
	if (material->GetEmissive())
	{
		_deviceContext->PSSetShaderResources(5, 1, material->GetEmissive()->GetTextRV().GetAddressOf());
	}
	if (material->GetRoughness())
	{
		_deviceContext->PSSetShaderResources(6, 1, material->GetRoughness()->GetTextRV().GetAddressOf());
	}
	if (material->GetMetalness())
	{
		_deviceContext->PSSetShaderResources(7, 1, material->GetMetalness()->GetTextRV().GetAddressOf());
	}


	if (_env)
	{
		_deviceContext->PSSetShaderResources(8, 1, _env->GetDiffuse()->GetTextRV().GetAddressOf());
		_deviceContext->PSSetShaderResources(9, 1, _env->GetSpecular()->GetTextRV().GetAddressOf());
		_deviceContext->PSSetShaderResources(10, 1, _env->GetLookUpTable()->GetTextRV().GetAddressOf());
	}
}

void MeshRenderer::CreateWVPBuffer(Matrix world)
{
	WVPData wvpData;
	wvpData.world = world;

	Matrix view, projection;
	GameApp::GetWorld()->GetCamera()->GetViewMatrix(view);
	GameApp::GetWorld()->GetCamera()->GetProjectionMatrix(projection);
	wvpData.view = XMMatrixTranspose(view);
	wvpData.projection = XMMatrixTranspose(projection);
	_deviceContext->UpdateSubresource(_wvpBuffer->GetComPtr().Get(), 0, nullptr, &wvpData, 0, 0);
}

void MeshRenderer::CreateLightBuffer()
{
	Vector3 cameraPos = GameApp::GetWorld()->GetCamera()->GetPosition();
	LightData lightData = GameApp::GetWorld()->GetLightData();
	lightData.cameraPosition = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 0.f);
	_deviceContext->UpdateSubresource(_lightBuffer->GetComPtr().Get(), 0, nullptr, &lightData, 0, 0);
	
}

void MeshRenderer::CreateMaterialBuffer(std::shared_ptr<Mesh> mesh)
{
	MaterialData materialData = _model->GetMaterials()[mesh->GetMaterialIndex()]->GetMaterialData();
	_deviceContext->UpdateSubresource(_materialBuffer->GetComPtr().Get(), 0, nullptr, &materialData, 0, 0);

}

