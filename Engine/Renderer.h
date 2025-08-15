#pragma once
#include <string>

struct TextureHandle;

class Renderer
{
	friend class Engine;
	friend class ResourceManager;
	friend class SpriteRenderer;
private:
	void Init();
	void DrawTexture(TextureHandle _handle, Vector2 _pos, float _scale = 1.f);
	
	const ComPtr<ID2D1RenderTarget> GetRenderTarget() const { return renderTarget; }
private:
	ComPtr<ID2D1Factory1> factory;
	ComPtr<ID2D1HwndRenderTarget> renderTarget;
};

