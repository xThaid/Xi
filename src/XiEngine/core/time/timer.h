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
		Timer(std::function<void(void)> action, unsigned int period);
		Timer(std::function<void(void)> action, unsigned int period, unsigned int repeatCount);
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
		unsigned int period;

		unsigned int repeatCount;
		unsigned int remainingCalls;

		std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;

		void invoke();
	};
}