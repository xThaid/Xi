#include "timer.h"

#include <algorithm>

#include <iostream>
#include <cassert>

namespace xiengine
{
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
		previousTime = std::chrono::system_clock::now();
	}

	void Timer::stop()
	{
		enabled = false;
	}

	void Timer::reset()
	{
		remainingCalls = repeatCount;
	}

	void Timer::invoke()
	{
		if (enabled)
		{
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
			if ((now - previousTime) >= std::chrono::milliseconds(period))
			{
				previousTime = now;

				if (remainingCalls == 1)
					enabled = false;
				else if(remainingCalls > 1)
					remainingCalls--;

				action();
			}
		}
	}

}