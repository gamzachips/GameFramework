#include "pch.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Animation.h"
#include "SkeletalMesh.h"
#include "StaticMesh.h"
#include "Material.h"
#include "Texture.h"
#include "Environment.h"

void ResourceManager::Init()
{
	importFlags = aiProcess_Triangulate |    // vertex �ﰢ�� ���� ���
		aiProcess_GenNormals |        // Normal ���� ����  
		aiProcess_GenUVCoords |      // �ؽ�ó ��ǥ ����
		aiProcess_CalcTangentSpace |  // ź��Ʈ ���� ����
		aiProcess_LimitBoneWeights |
		aiProcess_ConvertToLeftHanded; // DX�� �޼���ǥ�� ��ȯ

	importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, 0);
}

void ResourceManager::LoadFbx(std::string filePath)
{
	_loadedScene = importer.ReadFile(filePath, importFlags);
	_filePath = filePath;
}

std::shared_ptr<Model> ResourceManager::GetOrCreateModel(ComPtr<ID3D11Device> device)
{
	auto found = _modelMap.find(_filePath);
	if (found != _modelMap.end())
	{
		if (!(*found).second.expired())
			return (*found).second.lock();
	}
	else
	{
		std::shared_ptr<Model> model = std::make_shared<Model>(device);

		model->SetVS(L"VS.cso");
		model->SetPS(L"IBL_PS.cso");

		std::vector<std::shared_ptr<SkeletalMesh>> skeletalMeshes
			= GetOrCreateSkeletalMeshes(device, model);

		std::vector<std::shared_ptr<Material>> materials
			= GetOrCreateMaterials(device);

		std::vector<std::shared_ptr<StaticMesh>> staticMeshes
			= GetOrCreateStaticMeshes(device, model);

		for (int i = 0; i < skeletalMeshes.size(); i++)
			model->AddSkeletalMesh(skeletalMeshes[i]);

		for (int i = 0; i < staticMeshes.size(); i++)
			model->AddStaticMesh(staticMeshes[i]);

		for (int i = 0; i < materials.size(); i++)
			model->AddMaterial(materials[i]);

		

		_modelMap[_filePath] = model;
		model->ProcessModel(_loadedScene);

		return model;
	}
}

std::vector<std::shared_ptr<SkeletalMesh>> ResourceManager::GetOrCreateSkeletalMeshes(ComPtr<ID3D11Device> device, std::shared_ptr<Model> model)
{
	std::vector<std::shared_ptr<SkeletalMesh>> meshes;

	for (int i = 0; i < _loadedScene->mNumMeshes; i++)
	{
		if (_loadedScene->mMeshes[i]->HasBones() == false)
			return meshes;
		auto found = _skeletalMeshMap.find(_filePath + std::to_string(i));
		if (found != _skeletalMeshMap.end())
		{
			if (!(*found).second.expired())
				meshes.push_back((*found).second.lock());
		}
		else
		{
			std::shared_ptr<SkeletalMesh> mesh = std::make_shared<SkeletalMesh>(device);
			mesh->SetModel(model); 
			mesh->ProcessMesh(_loadedScene->mMeshes[i]);
			_skeletalMeshMap[_filePath + std::to_string(i)] = mesh;
			meshes.push_back(mesh);
		}
		
	}
	return meshes;
}

std::vector<std::shared_ptr<StaticMesh>> ResourceManager::GetOrCreateStaticMeshes(ComPtr<ID3D11Device> device, std::shared_ptr<Model> model)
{
	std::vector<std::shared_ptr<StaticMesh>> meshes;

	for (int i = 0; i < _loadedScene->mNumMeshes; i++)
	{
		if (_loadedScene->mMeshes[i]->HasBones() == true)
			return meshes;
		auto found = _staticMeshMap.find(_filePath + std::to_string(i));
		if (found != _staticMeshMap.end())
		{
			if (!(*found).second.expired())
				meshes.push_back((*found).second.lock());
		}
		else
		{
			std::shared_ptr<StaticMesh> mesh = std::make_shared<StaticMesh>(device);
			mesh->ProcessMesh(_loadedScene->mMeshes[i]);
			_staticMeshMap[_filePath + std::to_string(i)] = mesh;
			meshes.push_back(mesh);
		}

	}
	return meshes;
}

std::vector<std::shared_ptr<Material>> ResourceManager::GetOrCreateMaterials(ComPtr<ID3D11Device> device)
{
	std::vector<std::shared_ptr<Material>> materials;
	materials.reserve(_loadedScene->mNumMaterials);

	for (int i = 0; i < _loadedScene->mNumMaterials; i++)
	{
		auto found = _materialMap.find(_filePath + std::to_string(i));
		if (found != _materialMap.end())
		{
			if (!(*found).second.expired())
				materials.push_back((*found).second.lock());
		}
		else
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->ProcessMaterial(device, _loadedScene->mMaterials[i], _loadedScene);
			_materialMap[_filePath + std::to_string(i)] = material;
			materials.push_back(material);
		}

	}
	return materials;
}

std::shared_ptr<Environment> ResourceManager::GetOrCreateEnvironment(ComPtr<ID3D11Device> device, std::string name)
{
	auto found = _environmentMap.find(_filePath);
	if (found != _environmentMap.end())
	{
		if (!(*found).second.expired())
			return (*found).second.lock();
	}

	std::wstring wstrName;
	wstrName.assign(name.begin(), name.end());

	Texture* cubeMap = new Texture(device, wstrName + L"EnvHDR.dds");
	Texture* diffuse = new Texture(device, wstrName + L"DiffuseHDR.dds");
	Texture* specular = new Texture(device, wstrName + L"SpecularHDR.dds");
	Texture* lookUpTable = new Texture(device, wstrName + L"Brdf.dds");

	std::shared_ptr<Environment> ev = std::make_shared<Environment>(cubeMap, diffuse, specular, lookUpTable);

	_environmentMap[name] = ev;

	return ev;
}


std::shared_ptr<Animation> ResourceManager::GetOrCreateAnimation()
{
	auto found = _animationMap.find(_filePath);
	if (found != _animationMap.end())
	{
		if (!(*found).second.expired())
			return (*found).second.lock();
	}

	const aiScene* scene = importer.ReadFile(_filePath, importFlags);
	std::shared_ptr<Animation> animation = std::make_shared<Animation>();
	animation->ProcessAnimation(scene->mAnimations[0]);
	_animationMap[_filePath] = animation;
	return animation;

}



