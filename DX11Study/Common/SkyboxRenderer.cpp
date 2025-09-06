#include "pch.h"
#include "SkyboxRenderer.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "D3DRenderer.h"
#include "Shader.h"
#include "World.h"
#include "Camera.h"
#include "Texture.h"
#include "Environment.h"
#include "GameApp.h"
#include "SkyboxCube.h"
#include "Object.h"

SkyboxRenderer::SkyboxRenderer(ComPtr<ID3D11Device> device)
{
	_device = device;
}

SkyboxRenderer::~SkyboxRenderer()
{
	if (_wvpBuffer)
		delete _wvpBuffer;
}

void SkyboxRenderer::Init()
{
	_cube = new SkyboxCube(_device);

	CreateInputLayout(_cube->GetVS()->GetBlob());
	_wvpBuffer = new ConstantBuffer;
	_wvpBuffer->Create(sizeof(WVPData), _device);

}

void SkyboxRenderer::Update(float deltaTime)
{
}

void SkyboxRenderer::Render(ComPtr<ID3D11DeviceContext> dc)
{
	if (_env == nullptr) return;

	_deviceContext = dc; 

	//Create WVP Buffer
	WVPData wvpData;
	Matrix world, view, projection;

	wvpData.world = GetOwner()->GetTransform()._transform;

	GameApp::GetWorld()->GetCamera()->GetViewMatrix(view);
	GameApp::GetWorld()->GetCamera()->GetProjectionMatrix(projection);

	wvpData.view = XMMatrixTranspose(view);
	wvpData.projection = XMMatrixTranspose(projection);

	_deviceContext->UpdateSubresource(_wvpBuffer->GetComPtr().Get(), 0, nullptr, &wvpData, 0, 0);
	
	const unsigned int stride = _cube->GetVertexBuffer()->GetStride();
	const unsigned int offset = _cube->GetVertexBuffer()->GetOffset();
	_deviceContext->IASetVertexBuffers(0, 1, _cube->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(_cube->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	_deviceContext->IASetInputLayout(_inputLayout.Get());
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_deviceContext->VSSetShader(_cube->GetVS()->Get().Get(), nullptr, 0);
	_deviceContext->VSSetConstantBuffers(0, 1, _wvpBuffer->GetComPtr().GetAddressOf());

	_deviceContext->PSSetShader(_cube->GetPS()->Get().Get(), nullptr, 0);
	_deviceContext->PSSetSamplers(0, 1, Texture::GetLinearSampler().GetAddressOf());
	_deviceContext->PSSetShaderResources(0, 1, _env->GetCubeMap()->GetTextRV().GetAddressOf());


	if (_cube->GetIndexBuffer() != nullptr)
		dc->DrawIndexed(_cube->GetIndexBuffer()->GetCount(), 0, 0);
	else
		dc->Draw(_cube->GetVertexBuffer()->GetCount(), 0);

}


void SkyboxRenderer::CreateInputLayout(ComPtr<ID3DBlob> vsBlob)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	const int count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	_device->CreateInputLayout(layout, count, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
		_inputLayout.GetAddressOf());
}
