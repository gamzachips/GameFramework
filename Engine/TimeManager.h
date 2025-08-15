#pragma once
class TimeManager
{
	friend class Engine;
public:
	float GetDeltaTime() const { return deltaTime; }

private:
	void Init();
	void Update();

private:
	LARGE_INTEGER qPrevCounter;
	LARGE_INTEGER qFrequency;
	float deltaTime;
};

