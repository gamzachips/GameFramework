#include "pch.h"
#include "Renderer.h"
#include "Handle.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "Window.h"

void Renderer::Init()
{
    //Create Factory
	HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, factory.GetAddressOf()));

    RECT rc;
    GetClientRect(Window::GetHWND(), &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top
    );

    //Create RenderTarget
    HR(factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(Window::GetHWND(), size),
        &renderTarget
    ));

}

void Renderer::DrawTexture(TextureHandle _handle, Vector2 _pos, float _scale)
{
    Texture* texture = Engine::GetResourceManager()->GetTexture(_handle);

    D2D1_POINT_2F dpiPos;
    float dpiX, dpiY;
    renderTarget->GetDpi(&dpiX, &dpiY);
    dpiPos.x = _pos.x * (96.f / dpiX);
    dpiPos.y = _pos.y * (96.f / dpiY);

    D2D1_SIZE_F size = texture->bitmap->GetSize();
    D2D1_RECT_F destRect{};
    destRect.left = dpiPos.x - size.width  * _scale / 2;
    destRect.right = dpiPos.x + size.width * _scale / 2;
    destRect.top = dpiPos.y - size.height * _scale / 2;
    destRect.bottom = dpiPos.y + size.height * _scale / 2;
    
    renderTarget->DrawBitmap(texture->bitmap.Get(), &destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
}
