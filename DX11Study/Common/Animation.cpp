#include "pch.h"
#include "Animation.h"

void Animation::ProcessAnimation(aiAnimation* anim)
{
	_name = std::string(anim->mName.C_Str());
	_duration = anim->mDuration / anim->mTicksPerSecond;
	_frameCount = anim->mDuration * anim->mTicksPerSecond;
	_deltaTime = 1.0 / anim->mTicksPerSecond;

	for (int j = 0; j < anim->mNumChannels; j++)
	{
		aiNodeAnim* nodeAnim = anim->mChannels[j];

		NodeAnim aNode;
		aNode.nodeName = std::string(nodeAnim->mNodeName.C_Str());

		for (int k = 0; k < nodeAnim->mNumPositionKeys; k++)
		{
			aiVectorKey key = nodeAnim->mPositionKeys[k];
			aNode.positionKeys.push_back(KeyFrame{ key.mTime,
				Vector3(key.mValue.x, key.mValue.y, key.mValue.z) });
		}

		for (int k = 0; k < nodeAnim->mNumRotationKeys; k++)
		{
			aiQuatKey key = nodeAnim->mRotationKeys[k];
			aNode.rotationKeys.push_back(KeyFrame{ key.mTime,
				{}, Quaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w) });
		}

		for (int k = 0; k < nodeAnim->mNumScalingKeys; k++)
		{
			aiVectorKey key = nodeAnim->mScalingKeys[k];
			aNode.scalingKeys.push_back(KeyFrame{ key.mTime,
				Vector3(key.mValue.x, key.mValue.y, key.mValue.z) });
		}

		_aNodes.push_back(aNode);
	}
}
