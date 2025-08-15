#pragma once
#include <string>

class Util
{
public:
	static HRESULT LoadBitmapFromFile(ID2D1RenderTarget*, IWICImagingFactory*, const wchar_t*, OUT ID2D1Bitmap**);
};

