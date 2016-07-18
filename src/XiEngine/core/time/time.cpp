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
		previousTime = std::chrono::high_resolution_clock::now();
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
		previousTime = std::chrono::high_resolution_clock::now();
		deltaTime = 0.0f;
		elapsedTime = 0.0f;
	}

	void Time::update()
	{
		Timer::invokeTimers();
	}

	void Time::updateDelta()
	{
		currentTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float, std::milli> delta = currentTime - previousTime;
		deltaTime = delta.count() ;
		elapsedTime += delta.count();

		previousTime = currentTime;
	}
}