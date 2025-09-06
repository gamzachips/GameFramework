#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Node.h"
#include "SkeletalMesh.h"
#include "Model.h"

void Animator::Init()
{
	
}

void Animator::Update(float deltaTime)
{
	if (_curAnimIdx < 0 || _curAnimIdx >= _animations.size()) {
		return; 
	}

	_curTime += deltaTime;

	std::shared_ptr<Animation> curAnim = _animations[_curAnimIdx];

	if (_curTime > curAnim->_duration) //시간 초과시 애니메이션 반복 또는 종료
	{
		_curTime = 0;
		if (!curAnim->_loop)
			_curAnimIdx = -1;
	}
	
	UpdateAnimation(_model->GetRootNode());
	UpdateBonePallete();
}

void Animator::UpdateAnimation(Node* node)
{
	
	if (_curAnimIdx < 0)return;

	std::shared_ptr<Animation> curAnim = _animations[_curAnimIdx];

	auto aNodeIt = (find_if(curAnim->_aNodes.begin(), curAnim->_aNodes.end(), 
		[&](const NodeAnim& animNode) {return node->name == animNode.nodeName; }));
	
	if (aNodeIt != curAnim->_aNodes.end())
	{
		NodeAnim aNode = *aNodeIt;

		Vector3 pos = CalculatePosOrScale(aNode.positionKeys);
		Quaternion rot = CalculateRotation(aNode.rotationKeys);
		Vector3 scale = CalculatePosOrScale(aNode.scalingKeys);

		Matrix tMatrix = SimpleMath::Matrix::CreateTranslation(pos);
		Matrix rMatrix = SimpleMath::Matrix::CreateFromQuaternion(rot);
		Matrix sMatrix = SimpleMath::Matrix::CreateScale(scale);

		Matrix finalTransform = sMatrix * rMatrix * tMatrix;
		node->localTransform = finalTransform;
		
	}
	node->UpdateTransform();
	for (Node* child : node->children)
	{
		UpdateAnimation(child);
	}
	
}

void Animator::Render(ComPtr<ID3D11DeviceContext> dc)
{
}

void Animator::PlayAnimation(int index)
{
	_curAnimIdx = index;
	_curTime = 0.f;
}

void Animator::StopAnimation()
{
	_curAnimIdx = -1;
	_curTime = 0;
}

void Animator::UpdateBonePallete()
{
	std::vector<std::shared_ptr<SkeletalMesh>> meshes = _model->GetSkeletalMeshes();
	int meshSize = meshes.size();
	for (int i = 0; i < meshSize; i++)
	{
		std::shared_ptr<SkeletalMesh> mesh = meshes[i];
		std::vector<int>& boneIdxes = mesh->GetBoneIndexes();

		for (int j = 0; j < boneIdxes.size(); j++)
		{
			Bone* bone = _model->_bones[boneIdxes[j]];
			Node* boneNode = _model->GetNodeByName(bone->name);
			Matrix& boneNodeWorldTransform = boneNode->globalTransform;

			bonePallete.array[_model->GetBoneIndex(bone->name)] = XMMatrixTranspose(bone->offsetMatrix * boneNodeWorldTransform);
		}
	}
}

Vector3 Animator::CalculatePosOrScale(const std::vector<KeyFrame>& keyFrames)
{
	KeyFrame startKey, endKey;
	FindStartEndKey(keyFrames, startKey, endKey);

	double deltaTime = _animations[_curAnimIdx]->_deltaTime;
	double duration = endKey.time - startKey.time;

	double t = (_curTime - startKey.time * deltaTime) / duration;
	return SimpleMath::Vector3::Lerp(startKey.value, endKey.value, t); // 위치 보간
}

Quaternion Animator::CalculateRotation(const std::vector<KeyFrame>& keyFrames)
{
	KeyFrame startKey, endKey;
	FindStartEndKey(keyFrames, startKey, endKey);

	double deltaTime = _animations[_curAnimIdx]->_deltaTime;
	double duration = endKey.time * deltaTime - startKey.time * deltaTime;

	double t = (_curTime - startKey.time * deltaTime) / duration;
	return SimpleMath::Quaternion::Lerp(startKey.rotation, endKey.rotation, t); 
}

void Animator::FindStartEndKey(const std::vector<KeyFrame>& keyFrames, OUT KeyFrame& start, OUT KeyFrame& end)
{
	start = keyFrames[0];
	end = keyFrames[0];

	for (int i = 0; i < keyFrames.size(); i++)
	{
		if (keyFrames[i].time * _animations[_curAnimIdx]->_deltaTime < _curTime)
			start = keyFrames[i];
		if (_curTime < keyFrames[i].time * _animations[_curAnimIdx]->_deltaTime)
			end = keyFrames[i];
	}
}
