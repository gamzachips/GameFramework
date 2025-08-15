#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	QueryPerformanceCounter(&qPrevCounter);
	QueryPerformanceFrequency(&qFrequency);
}

void TimeManager::Update()
{
	LARGE_INTEGER qNowCounter;
	QueryPerformanceCounter(&qNowCounter);
	deltaTime = (qNowCounter.QuadPart - qPrevCounter.QuadPart) / float(qFrequency.QuadPart);
}
