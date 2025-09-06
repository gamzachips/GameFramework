#pragma once


class Animation
{
public:
	std::string _name {};
	double _duration {}; //전체 실행 시간
	int _frameCount = 0;
	double _deltaTime;
	bool _loop = true;
	std::vector<NodeAnim> _aNodes;

	void ProcessAnimation(aiAnimation* anim);
};

