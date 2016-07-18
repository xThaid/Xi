#pragma once

#include <chrono>

namespace xiengine
{
	class Time
	{
	public:
		Time();

		static float getDeltaTime();
		static float getElapsedTime();

		void reset();
		void update(bool invokeTimers);

	private:
		std::chrono::time_point<std::chrono::system_clock> previousTime;
		std::chrono::time_point<std::chrono::system_clock> currentTime;
		float deltaTime;
		float elapsedTime;
	};
}