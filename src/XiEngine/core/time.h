#pragma once

#include "../precompiled.h"

class Time
{
public:
	Time();
	~Time();

	static float getDeltaTime();
	static float getElapsedTime();

	void reset();
	void update();
	void updateDelta();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime_;
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime_;
	float deltaTime_;
	float elapsedTime_;
};

class Timer
{
public:
	Timer(std::function<void(void)> action, int period);
	Timer(std::function<void(void)> action, int period, int repeatCount);
	~Timer();

	void start();
	void stop();

	void reset();

	void changePeriod(int period);

private:
	static std::vector<Timer*> timers_;
	static void invokeTimers();

	bool enabled_;

	std::function<void(void)> action_;
	int period_;

	int repeatCount_;
	int remainingCalls_;

	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime_;

	void invoke();

	friend class Time;
};