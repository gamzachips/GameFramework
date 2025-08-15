#pragma once
#include "Component.h"
#include "Handle.h"
#include <string>

class SpriteRenderer : public Component
{
public:
	void Render();
public:

	void SetTexture(const std::wstring& path);

private:
	TextureHandle texture;
};

