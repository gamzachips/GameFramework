#pragma once
#include "Mesh.h"

struct Bone {
	std::string name;  //본 이름 
	Matrix offsetMatrix; // 본의 오프셋 행렬
	
	Bone(aiBone* bone)
	{
		name = bone->mName.C_Str();
		offsetMatrix = XMMatrixTranspose(Matrix(&bone->mOffsetMatrix.a1));
	}
};

class Animation;
class Node;
class Model;

class SkeletalMesh : public Mesh
{
public:
	SkeletalMesh(ComPtr<ID3D11Device> device) : Mesh(device) {}
	~SkeletalMesh() {}

	virtual void ProcessMesh(aiMesh* mesh);

	void SetModel(std::shared_ptr<Model> model) { _model = model; }
	std::vector<int>& GetBoneIndexes() { return _boneIdxes; }
private:

	std::shared_ptr<Model> _model = nullptr;
	std::vector<int> _boneIdxes;
	std::vector<VertexSkeletalData> _vertices;

};

