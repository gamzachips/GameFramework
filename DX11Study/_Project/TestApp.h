#pragma once
#include "../Common/pch.h"
#include "../Common/GameApp.h"

class TestApp : public GameApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp(); 

public:
	virtual bool Initialize(UINT Width, UINT Height) override;	// ������ ������ ���� ���� �ٸ��� �����Ƿ� ���,����,���̱⸸ �Ѵ�.

private:
	virtual void Update() override;
	virtual void Render() override;

	void InitImGUI();
	void UnInitImGUI();

	

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

