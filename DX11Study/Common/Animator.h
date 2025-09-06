#pragma once
#include "Component.h"

class Animation;
class Model;
class Node;

class Animator :  public Component
{
public:
	Animator(Model* model) : _model(model) {}
	virtual ~Animator() { }
	virtual void Init();
	virtual void Update(float deltaTime);
	void UpdateAnimation(Node* node);
	virtual void Render(ComPtr<ID3D11DeviceContext> dc);

	void AddAnimation(std::shared_ptr<Animation> animation) { _animations.push_back(animation); }
	void PlayAnimation(int index);
	void StopAnimation();
	void UpdateBonePallete();
	MatrixPallete& GetBonePallete() { return bonePallete; }
private:
	Vector3 CalculatePosOrScale(const std::vector<KeyFrame>& keyFrames);
	Quaternion CalculateRotation(const std::vector<KeyFrame>& keyFrames);
	void FindStartEndKey(const std::vector<KeyFrame>& keyFrames, OUT KeyFrame& start, OUT KeyFrame& end);
private:
	Model* _model;
	int _curAnimIdx = -1;
	double _curTime = 0;
	std::vector<std::shared_ptr<Animation>> _animations;
	MatrixPallete bonePallete;
};

