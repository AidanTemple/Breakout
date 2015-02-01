#pragma region Include Statements
#include <Windows.h>
#include "FrameManager.h"
#pragma endregion

FrameManager::FrameManager()
{

}

FrameManager::~FrameManager()
{

}

void FrameManager::Initialise(int fps)
{
	QueryPerformanceFrequency(&freqTime);
	QueryPerformanceCounter(&curTime);
	QueryPerformanceCounter(&prevTime);

	// Initialise the FPS frame time information
	reqFPS = fps;

	// Determines the number of intervals in the given timer, per frame at the requested rate
	intervalsPerFrame = ((float)freqTime.QuadPart / reqFPS);
}

int FrameManager::FramesToUpdate()
{
	// Determine the number of frames that need to be updated since the last update call
	int framesToUpdate = 0;
	QueryPerformanceCounter(&curTime);

	timeSinceLastUpdate = (float)curTime.QuadPart - (float)prevTime.QuadPart;
	framesToUpdate = (int)(timeSinceLastUpdate / intervalsPerFrame);

	// If no frames are being updated then use the previous timer count
	if(framesToUpdate != 0)
	{
		QueryPerformanceCounter(&prevTime);
	}

	return framesToUpdate;
}