#pragma once

#include <string>
#include <time.h>

namespace xiengine
{
	class Logger
	{
	public:
		static const int LEVEL_NONE;
		static const int LEVEL_ERROR;
		static const int LEVEL_WARN;
		static const int LEVEL_INFO;
		static const int LEVEL_DEBUG;
		static const int LEVEL_TRACE;

		static void setLevel(int level);

		static void error(const std::string& message);
		static void warn(const std::string& message);
		static void info(const std::string& message);
		static void debug(const std::string& message);
		static void trace(const std::string& message);

	private:
		static time_t startTime;

		static bool ERROR;
		static bool WARN;
		static bool INFO;
		static bool DEBUG;
		static bool TRACE;

		static int currentLevel;

		static void log(int level, const std::string& message);
	};
}