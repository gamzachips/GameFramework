#pragma once
class TimeManager
{
	friend class Game;
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

