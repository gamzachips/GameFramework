#include "pch.h"
#include "SkeletalMesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Animation.h"
#include "Node.h"
#include "Model.h"




void SkeletalMesh::ProcessMesh(aiMesh* mesh)
{
	_vertices.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vector3 position{}, normal{}, tangent{};
		Vector2 texCoord = { 0,0 };

		aiVector3D aiPosition = mesh->mVertices[i];
		aiVector3D aiNormal = mesh->mNormals[i];
		aiVector3D aiTexCoord = mesh->mTextureCoords[0][i];
		aiVector3D aiTangent = mesh->mTangents[i];

		position = { aiPosition.x, aiPosition.y, aiPosition.z };
		if (mesh->HasNormals())
		{
			normal = { aiNormal.x, aiNormal.y, aiNormal.z };
		}

		if (mesh->HasTextureCoords(0))
		{
			texCoord = { aiTexCoord.x, aiTexCoord.y };
		}

		if (mesh->HasTangentsAndBitangents())
		{
			tangent = { aiTangent.x, aiTangent.y, aiTangent.z };
		}

		
		_vertices.push_back(VertexSkeletalData{ position, normal, texCoord, tangent });
	}

	_vertexBuffer = new VertexBuffer;
	

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			_indices.push_back(face.mIndices[j]);
		}
	}

	if (_indices.size() > 0)
	{
		_indexBuffer = new IndexBuffer;
		_indexBuffer->Create(_indices, _device);
	}

	_materialIndex = mesh->mMaterialIndex;

	_model->_bones.reserve(mesh->mNumBones);
	//Bone 처리
	for (int i = 0; i < mesh->mNumBones; i++)
	{
		aiBone* bone = mesh->mBones[i];
		int index = _model->PushBone(bone);
		_boneIdxes.push_back(index);
		
		for (int j = 0; j < bone->mNumWeights; j++)
		{
			unsigned int vertexId = bone->mWeights[j].mVertexId; //이 본이 영향을 주는 정점id
			float weight = bone->mWeights[j].mWeight;

			_vertices[vertexId].AddIdAndWeight(index, weight); //정점에 영향주는 본의 id, weight
		}
	}

	for (auto vertex : _vertices)
		vertex.NormalizeWeights();

	_vertexBuffer->Create(_vertices, _device);

}
