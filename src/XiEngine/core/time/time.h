#pragma once

#include <chrono>

class Time
{
public:
	Time();

	static float getDeltaTime();
	static float getElapsedTime();

	void reset();
	void update();
	void updateDelta();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	float deltaTime;
	float elapsedTime;
};
