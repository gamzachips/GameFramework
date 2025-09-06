#pragma once

#include <windows.h>

#define MAX_LOADSTRING 100

class World;

class GameApp
{
public:
	GameApp(HINSTANCE hInstance);
	virtual ~GameApp();

	static HWND m_hWnd;		//�����ʿ��ϴ� ������ ���������� ���ϱ����� ��������� �������.
	static GameApp* m_pInstance;			// �����ڿ��� �ν��Ͻ� �����͸� �����Ѵ�.

public:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WNDCLASSEXW m_wcex;
	float m_previousTime;
	float m_currentTime;
	int  m_nCmdShow;
	//GameTimer m_Timer;
	UINT m_ClientWidth;
	UINT m_ClientHeight;

	
public:
	// ������ ���� ���,����,���̱� �Ѵ�.
	virtual bool Initialize(UINT Width, UINT Height);
	virtual bool Run();
	virtual void Update();
	virtual void Render();

	static World* GetWorld() { return _world; }

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static World* _world;

};

