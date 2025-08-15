#pragma once
#include <string>

class Renderer
{
	friend class Game;
	friend class ResourceManager;
private:
	void Init();

	//void DrawBitmap(TextureHandle handle);
	//void DrawtextString(std::string text);
	
	const ComPtr<ID2D1RenderTarget> GetRenderTarget() const { return renderTarget; }
private:
	ComPtr<ID2D1Factory1> factory;
	ComPtr<ID2D1RenderTarget> renderTarget;
};

