#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID2D1Bitmap> _bitmap)
	: bitmap(_bitmap)
{

}

Texture::~Texture()
{
}
