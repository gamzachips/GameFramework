#include "pch.h"
#include "Renderer.h"

void Renderer::Init()
{
	HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, factory.GetAddressOf()));

}
