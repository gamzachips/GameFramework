#include "pch.h"
#include "Model.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Material.h"
#include "StaticMesh.h"
#include "SkeletalMesh.h"
#include "Shader.h"
#include "Node.h"


Model::~Model()
{
	if (_vs)
		delete _vs;
	if (_ps)
		delete _ps;
}

void Model::ProcessModel(const aiScene* scene)
{
	ProcessNode(scene->mRootNode, nullptr);
	
}

void Model::SetVS(const std::wstring& filePath)
{
	_vs = new VertexShader(filePath, "VS", _device);

}

void Model::SetPS(const std::wstring& filePath)
{
	_ps = new PixelShader(filePath, "PS", _device);

}

void Model::AddSkeletalMesh(std::shared_ptr<SkeletalMesh> mesh)
{
	_skeletalMeshes.push_back(mesh);
}

void Model::AddStaticMesh(std::shared_ptr<StaticMesh> mesh)
{
	_staticMeshes.push_back(mesh);
}

void Model::AddMaterial(std::shared_ptr<Material> material)
{

	_materials.push_back(material);
}
Node* Model::GetNodeByName(std::string name)
{
	return _rootNode->FindNode(name);

}

void Model::ProcessNode(const aiNode* node, Node* parent)
{
	aiMatrix4x4 aiTransform = node->mTransformation;

	Matrix transform(&aiTransform.a1);
	transform = XMMatrixTranspose(transform);
	Node* newNode = new Node(std::string(node->mName.C_Str()), transform); 

	if (parent == nullptr)
	{
		_rootNode = newNode;
	}
	else
	{
		parent->AddChild(newNode);
	}

	for (int i = 0; i < node->mNumMeshes; i++)
	{
		newNode->meshIdxes.push_back(node->mMeshes[i]);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], newNode);
	}
}

int Model::PushBone(aiBone* bone)
{
	//이미 있는 본이면 넘어감
	for (int i = 0; i < _bones.size(); i++)
	{
		if (_bones[i]->name == bone->mName.C_Str())
			return i;
	}

	_bones.push_back(new Bone(bone));
	
	return _bones.size()-1;
	
}

int Model::GetBoneIndex(std::string boneName)
{
	for (int i = 0; i < _bones.size(); i++)
	{
		if (_bones[i]->name == boneName)
			return i;
	}
	return -1;
}
