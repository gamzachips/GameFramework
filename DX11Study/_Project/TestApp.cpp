#include "../Common/pch.h"
#include "TestApp.h"
#include "_08_Level.h"
#include "../Common/World.h"



TestApp::TestApp(HINSTANCE hInstance) : GameApp(hInstance)
{
	GetWorld()->ChangeLevel<_08_Level>();

}

TestApp::~TestApp()
{
	UnInitImGUI();

}

bool TestApp::Initialize(UINT Width, UINT Height)
{
	__super::Initialize(Width, Height);

	InitImGUI();

	return true;
}

void TestApp::Update()
{
	__super::Update();

}

void TestApp::Render()
{
	__super::Render();
}

void TestApp::InitImGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX11_Init(GetWorld()->GetDevice().Get(), GetWorld()->GetDeviceContext().Get());
}

void TestApp::UnInitImGUI()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK TestApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	return __super::WndProc(hWnd, message, wParam, lParam);
}
