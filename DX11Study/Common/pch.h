#pragma once

const int GWinSizeX = 1920;
const int GWinSizeY = 1080;

#include <codecvt>
#include <filesystem>
#include <fstream>

// STL
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <queue>

#include <memory>

// WIN
#include <windows.h>
#include <assert.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <Directxtk/DDSTextureLoader.h>
#include <DirectXTex.h>
#include <Directxtk/WICTextureLoader.h>
#include <wrl/client.h> // For Microsoft::WRL::ComPtr

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//imgui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

//assimp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post-processing flags

//simple math
#include "../Libraries/Include/SimpleMath/SimpleMath.h"


#include "Types.h"
#include "Struct.h"
