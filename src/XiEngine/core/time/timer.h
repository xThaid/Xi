#pragma once

#include <chrono>
#include <vector>
#include <functional>

typedef void(*Action)();

class Timer
{
	friend class Time;
public:
	Timer(std::function<void(void)> action, int period);
	Timer(std::function<void(void)> action, int period, int repeatCount);
	~Timer();

	void start();
	void stop();

	void reset();

	void changePeriod(int period);

private:
	static std::vector<Timer*> timers;
	static void invokeTimers();
		
	bool enabled;

	std::function<void(void)> action;
	int period;

	int repeatCount;
	int remainingCalls;

	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;

	void invoke();
};