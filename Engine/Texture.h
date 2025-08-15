#pragma once
#include "Resource.h"

class Texture :  public Resource
{
public:
	Texture(ComPtr<ID2D1Bitmap> _bitmap);
	virtual  ~Texture();
private:
	ComPtr<ID2D1Bitmap> bitmap;
};

