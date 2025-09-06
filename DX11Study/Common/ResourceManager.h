#pragma once

class SkeletalMesh;
class StaticMesh;
class Animation;
class Material;
class Model;
class Environment;

class ResourceManager
{
public:
	void Init();

	void LoadFbx(std::string filePath);
	//Model* CreateModel(ComPtr<ID3D11Device> device);
	std::shared_ptr<Model> GetOrCreateModel(ComPtr<ID3D11Device> device);
	std::shared_ptr<Animation> GetOrCreateAnimation();

	std::vector<std::shared_ptr<SkeletalMesh>> GetOrCreateSkeletalMeshes(ComPtr<ID3D11Device> device, std::shared_ptr<Model> model);
	std::vector<std::shared_ptr<StaticMesh>> GetOrCreateStaticMeshes(ComPtr<ID3D11Device> device, std::shared_ptr<Model> model);
	std::vector<std::shared_ptr<Material>> GetOrCreateMaterials(ComPtr<ID3D11Device> device);
	std::shared_ptr<Environment> GetOrCreateEnvironment(ComPtr<ID3D11Device> device, std::string name);

private:

	Assimp::Importer importer;
	unsigned int importFlags;

	const aiScene* _loadedScene = nullptr;
	std::string _filePath;
	std::unordered_map<std::string, std::weak_ptr<Model>> _modelMap;
	std::unordered_map<std::string, std::weak_ptr<SkeletalMesh>> _skeletalMeshMap;
	std::unordered_map<std::string, std::weak_ptr<StaticMesh>> _staticMeshMap;
	std::unordered_map<std::string, std::weak_ptr<Material>> _materialMap;
	std::unordered_map<std::string, std::weak_ptr<Animation>> _animationMap;
	std::unordered_map<std::string, std::weak_ptr<Environment>> _environmentMap;
};

