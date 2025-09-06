#pragma once
#include "../Common/pch.h"
#include "../Common/GameApp.h"

class TestApp : public GameApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp(); 

public:
	virtual bool Initialize(UINT Width, UINT Height) override;	// 윈도우 정보는 게임 마다 다를수 있으므로 등록,생성,보이기만 한다.

private:
	virtual void Update() override;
	virtual void Render() override;

	void InitImGUI();
	void UnInitImGUI();

	

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

