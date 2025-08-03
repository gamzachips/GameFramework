#pragma once

#include <SDKDDKVer.h>
#include <windows.h>

#define MAX_LOADSTRING 100


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct WindowDesc
{
	HINSTANCE instance;
	int cmdShow;
	const WCHAR* title;
	const WCHAR* windowClass;
	HICON icon;
	HICON iconSmall;
};

class Window
{
public:
	Window(const WindowDesc& _desc);
	~Window();

	int Initialize();
	bool Update();
	int Destroy();

private:
	ATOM MyRegisterClass(HINSTANCE _hInstance);
	BOOL InitInstance(HINSTANCE, int);

private:
	HINSTANCE hInstance;                                // 현재 인스턴스입니다.
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	HICON hIcon;
	HICON hIconSmall;
	int cmdShow;
	MSG msg;
};

