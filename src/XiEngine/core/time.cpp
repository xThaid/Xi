#include "time.h"

#include "core.h"

#include <algorithm>

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

std::vector<Timer*> Timer::timers;

void Timer::invokeTimers()
{
	for (auto& timer : timers)
		timer->invoke();
}

Timer::Timer(std::function<void(void)> action, int period) :
	action(action),
	period(period),
	repeatCount(0),
	remainingCalls(0)
{
	enabled = false;
	timers.push_back(this);
}

Timer::Timer(std::function<void(void)> action, int period, int repeatCount) :
	action(action),
	period(period),
	repeatCount(repeatCount),
	remainingCalls(repeatCount)
{
	if (period == 0)
		throw;

	enabled = false;
	timers.push_back(this);
}

Timer::~Timer()
{
	timers.erase(std::find(timers.begin(), timers.end(), this));
}

void Timer::start()
{
	enabled = true;
	previousTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
	enabled = false;
}

void Timer::reset()
{
	remainingCalls = repeatCount;
}

void Timer::changePeriod(int period)
{
	this->period = period;
}

void Timer::invoke()
{
	if (enabled)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
		if ((now - previousTime) >= std::chrono::milliseconds(period))
		{
			previousTime = now;

			if (remainingCalls == 1)
				enabled = false;
			else if (remainingCalls > 1)
				remainingCalls--;

			action();
		}
	}
}