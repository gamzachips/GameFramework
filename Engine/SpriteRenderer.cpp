#include "pch.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "Renderer.h"


void SpriteRenderer::Render()
{
	Engine::GetRenderer()->DrawTexture(texture, Vector2(0, 0));
}

void SpriteRenderer::SetTexture(const std::wstring& path)
{
	texture = Engine::GetResourceManager()->GetOrLoadTexture(path);
}
