#pragma once

#include <string>
#include <time.h>

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

	static bool ERROR_LVL;
	static bool WARN_LVL;
	static bool INFO_LVL;
	static bool DEBUG_LVL;
	static bool TRACE_LVL;

	static int currentLevel;

	static void log(int level, const std::string& message);
};