#pragma once


class Animation
{
public:
	std::string _name {};
	double _duration {}; //��ü ���� �ð�
	int _frameCount = 0;
	double _deltaTime;
	bool _loop = true;
	std::vector<NodeAnim> _aNodes;

	void ProcessAnimation(aiAnimation* anim);
};

