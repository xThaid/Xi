#pragma once

#include <chrono>
#include <vector>
#include <functional>

namespace xiengine
{
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

	private:
		static std::vector<Timer*> timers;
		static void invokeTimers();
		
		bool enabled;

		std::function<void(void)> action;
		int period;

		int repeatCount;
		int remainingCalls;

		std::chrono::time_point<std::chrono::system_clock> previousTime;

		void invoke();
	};
}