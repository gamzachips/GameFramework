#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Resource.h"
#include "Handle.h"
#include "Texture.h"

class Audio;

template<typename T>
concept ResourceType = std::is_base_of_v<Resource, T>;


class ResourceManager
{
	friend class Game;
	friend class Renderer;
public:
	TextureHandle GetOrLoadTexture(const std::wstring& _path);

	bool IsValid(const TextureHandle _handle) const ;

private: //for Game
	void Init();
	void GarbageCollect(uint64_t _maxUnusedFrames);
	

	Texture* GetTexture(TextureHandle _handle) const;
	void Unload(TextureHandle _handle);
private:
	std::string NormalizePath(std::string _path);
	ComPtr<ID2D1Bitmap> LoadBitmapFromFile(const std::wstring&);

	
private:
	std::vector<std::unique_ptr<Texture>> textureSlots;
	std::vector<unsigned int> textureSlotGens; 
	std::unordered_map<std::wstring, TextureHandle> texturePath2Handle;

	std::vector<Audio*> audioSlots;
	std::vector<unsigned int> audioSlotGens;
	std::unordered_map<std::wstring, AudioHandle> audioPath2Handle;

private:
	ComPtr<IWICImagingFactory> wicFactory;

};
