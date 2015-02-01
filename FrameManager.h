#pragma region Include Statements
#pragma once
#pragma endregion

class FrameManager
{
	public:

		FrameManager(void);

		~FrameManager(void);

		void Initialise(int fps);

		int FramesToUpdate();

	private:

		LARGE_INTEGER curTime;
		LARGE_INTEGER prevTime;
		LARGE_INTEGER freqTime;

		float fps;
		float intervals;
		float timeSinceLastUpdate;
		float framesInLastSecond;
		float intervalsPerFrame;
		
		int reqFPS;
};