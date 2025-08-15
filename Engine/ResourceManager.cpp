#include "pch.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "Renderer.h"


TextureHandle ResourceManager::GetOrLoadTexture(const std::wstring& _path)
{
	auto it = texturePath2Handle.find(_path);
	if (it != texturePath2Handle.end())
	{
		return it->second;
	}

	ComPtr<ID2D1Bitmap> bitmap = LoadBitmapFromFile(_path);
	std::unique_ptr<Texture> texture = std::make_unique<Texture>(bitmap);

	TextureHandle handle;
	bool reused = false;

	for (size_t i = 0; i < textureSlots.size(); i++)
	{
		if (textureSlots[i] == nullptr)
		{
			textureSlots[i] = std::move(texture);
			handle.index = i;
			textureSlotGens[i] += 1;
			handle.gen = textureSlotGens[i];
			reused = true;
			break;
		}
	}

	if (!reused)
	{
		textureSlots.push_back(std::move(texture));
		handle.index = textureSlots.size()-1;
		handle.gen = 0;
		textureSlotGens.push_back(0);
	}

	texturePath2Handle[_path] = handle;

	return handle;
}

bool ResourceManager::IsValid(const TextureHandle _handle) const
{
	if (_handle.index >= textureSlots.size())
		return false;
	if (_handle.gen != textureSlotGens[_handle.index])
		return false;
	return true;
}

void ResourceManager::Init()
{
	HR(CoCreateInstance(CLSID_WICImagingFactory,
		nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(wicFactory.GetAddressOf())));

}

void ResourceManager::GarbageCollect(uint64_t _maxUnusedFrames)
{
	//현재 프레임 currFrame
	//텍스처 슬롯을 돌면서 lastUsedFrame 체크 
	//프레임 차이가 maxUnusedFrames 보다 크면 Unload 호출 
}

Texture* ResourceManager::GetTexture(TextureHandle _handle) const
{
	if (IsValid(_handle))
		return textureSlots[_handle.index].get();
	return nullptr;
}

void ResourceManager::Unload(TextureHandle _handle)
{
	//_handle.index번쨰 슬롯 원소를 제거. 
	//unordered_map에서 핸들 찾아서 그 원소 제거
}

std::string ResourceManager::NormalizePath(std::string _path)
{
	return _path;
}

ComPtr<ID2D1Bitmap> ResourceManager::LoadBitmapFromFile(const std::wstring& _filename)
{
	ComPtr<IWICBitmapDecoder> decoder;

	HR(wicFactory->CreateDecoderFromFilename(
		_filename.c_str(), nullptr, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder));

	ComPtr<IWICBitmapFrameDecode> frame;
	HR(decoder->GetFrame(0, &frame));

	ComPtr<IWICFormatConverter> converter;
	HR(wicFactory->CreateFormatConverter(&converter));
	HR(converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.f,
		WICBitmapPaletteTypeCustom));

	ComPtr<ID2D1RenderTarget> rt = Engine::GGame->GetRenderer()->GetRenderTarget();

	ComPtr<ID2D1Bitmap> bitmap;
	HR(rt->CreateBitmapFromWicBitmap(converter.Get(), nullptr, bitmap.GetAddressOf()));

	return bitmap;
}
