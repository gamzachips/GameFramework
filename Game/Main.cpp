#include <windows.h>
#include "Engine.h"
#include "Resource.h"
#include "MyGame.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    Engine engine;

    WindowDesc desc;
    desc.instance = hInstance;
    desc.cmdShow = nCmdShow;
    desc.icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    desc.iconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    desc.title = L"대환장 게임즈 2.0";
    desc.windowClass = L"BugFixPlz";
    
    if (!engine.Initialize(desc, std::make_unique<MyGame>()))
        return -1;

    engine.Run();

    if (!engine.ShutDown())
        return -1;

    CoUninitialize();

    return 0;
}
