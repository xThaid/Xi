#include "time.h"

#include "core.h"

#include <algorithm>

Time::Time() :
	deltaTime_(0.0f),
	elapsedTime_(0.0f)
{
	previousTime_ = std::chrono::high_resolution_clock::now();
}

Time::~Time()
{
}

float Time::getDeltaTime()
{
	return Core::getCurrentCore()->time->deltaTime_;
}

float Time::getElapsedTime()
{
	return Core::getCurrentCore()->time->elapsedTime_;
}

void Time::reset()
{
	previousTime_ = std::chrono::high_resolution_clock::now();
	deltaTime_ = 0.0f;
	elapsedTime_ = 0.0f;
}

void Time::update()
{
	Timer::invokeTimers();
}

void Time::updateDelta()
{
	currentTime_ = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> delta = currentTime_ - previousTime_;
	deltaTime_ = delta.count() ;
	elapsedTime_ += delta.count();

	previousTime_ = currentTime_;
}

std::vector<Timer*> Timer::timers_;

void Timer::invokeTimers()
{
	for (auto& timer : timers_)
		timer->invoke();
}

Timer::Timer(std::function<void(void)> action, int period) :
	action_(action),
	period_(period),
	repeatCount_(0),
	remainingCalls_(0),
	enabled_(false)
{
	timers_.push_back(this);
}

Timer::Timer(std::function<void(void)> action, int period, int repeatCount) :
	action_(action),
	period_(period),
	repeatCount_(repeatCount),
	remainingCalls_(repeatCount),
	enabled_(false)
{
	timers_.push_back(this);
}

Timer::~Timer()
{
	timers_.erase(std::find(timers_.begin(), timers_.end(), this));
}

void Timer::start()
{
	enabled_ = true;
	previousTime_ = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
	enabled_ = false;
}

void Timer::reset()
{
	remainingCalls_ = repeatCount_;
}

void Timer::changePeriod(int period)
{
	period_ = period;
}

void Timer::invoke()
{
	if (enabled_)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
		if ((now - previousTime_) >= std::chrono::milliseconds(period_))
		{
			previousTime_ = now;

			if (remainingCalls_ == 1)
				enabled_ = false;
			else if (remainingCalls_ > 1)
				remainingCalls_--;

			action_();
		}
	}
}