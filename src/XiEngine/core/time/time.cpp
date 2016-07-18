#include "time.h"

#include "../core.h"

#include "timer.h"
#include <iostream>

namespace xiengine
{ 
	Time::Time()
	{
		deltaTime = 0.0f;
		elapsedTime = 0.0f;
		previousTime = std::chrono::system_clock::now();
	}

	float Time::getDeltaTime()
	{
		Core* core = Core::getCurrentCore();
		if (core != nullptr) return core->time->deltaTime;
		return 0.0f;
	}

	float Time::getElapsedTime()
	{
		Core* core = Core::getCurrentCore();
		if (core != nullptr) return core->time->elapsedTime;
		return 0.0f;
	}

	void Time::reset()
	{
		previousTime = std::chrono::system_clock::now();
		deltaTime = 0.0f;
		elapsedTime = 0.0f;
	}

	void Time::update(bool invokeTimers)
	{
		currentTime = std::chrono::system_clock::now();

		std::chrono::duration<float, std::milli> delta = currentTime - previousTime;
		deltaTime = delta.count();

		elapsedTime += (currentTime - previousTime).count();

		if (invokeTimers)
			Timer::invokeTimers();
	}
}