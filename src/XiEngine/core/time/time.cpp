#include "time.h"

#include "../core.h"

#include "timer.h"
#include <iostream>

Time::Time()
{
	deltaTime = 0.0f;
	elapsedTime = 0.0f;
	previousTime = std::chrono::high_resolution_clock::now();
}

float Time::getDeltaTime()
{
	return Core::getCurrentCore()->time->deltaTime;
}

float Time::getElapsedTime()
{
	return Core::getCurrentCore()->time->elapsedTime;
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

	std::chrono::duration<float> delta = currentTime - previousTime;
	deltaTime = delta.count() ;
	elapsedTime += delta.count();

	previousTime = currentTime;
}