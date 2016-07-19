#include "logger.h"

#include <iostream>

namespace xiengine
{
	const int Logger::LEVEL_NONE = 6;
	const int Logger::LEVEL_ERROR = 5;
	const int Logger::LEVEL_WARN = 4;
	const int Logger::LEVEL_INFO = 3;
	const int Logger::LEVEL_DEBUG = 2;
	const int Logger::LEVEL_TRACE = 1;

	bool Logger::ERROR = currentLevel <= LEVEL_ERROR;
	bool Logger::WARN = currentLevel <= LEVEL_WARN;
	bool Logger::INFO = currentLevel <= LEVEL_INFO;
	bool Logger::DEBUG = currentLevel <= LEVEL_DEBUG;
	bool Logger::TRACE = currentLevel <= LEVEL_TRACE;

	time_t Logger::startTime = time(0);

	int Logger::currentLevel = LEVEL_INFO;

	void Logger::setLevel(int level)
	{
		Logger::currentLevel = level;
		ERROR = level <= LEVEL_ERROR;
		WARN = level <= LEVEL_WARN;
		INFO = level <= LEVEL_INFO;
		DEBUG = level <= LEVEL_DEBUG;
		TRACE = level <= LEVEL_TRACE;
	}

	void Logger::error(const std::string& message)
	{
		if (ERROR) log(LEVEL_ERROR, message);
	}

	void Logger::warn(const std::string& message)
	{
		if (WARN) log(LEVEL_WARN, message);
	}

	void Logger::info(const std::string& message)
	{
		if (INFO) log(LEVEL_INFO, message);
	}

	void Logger::debug(const std::string& message)
	{
		if (DEBUG) log(LEVEL_DEBUG, message);
	}

	void Logger::trace(const std::string& message)
	{
		if (TRACE) log(LEVEL_TRACE, message);
	}

	void Logger::log(int level, const std::string& message)
	{
		std::string out;

		int timeInSec = (int) difftime(time(0), startTime);
		int minutes = timeInSec / 60;
		int seconds = timeInSec % 60;
		
		out.append("[");
		if (minutes < 10) out.append("0");
		out.append(std::to_string(minutes));
		out.append(":");
		if (seconds < 10) out.append("0");
		out.append(std::to_string(seconds));
		out.append("] [");

		switch (level) 
		{
		case LEVEL_ERROR:
			out.append("ERROR");
			break;
		case LEVEL_WARN:
			out.append("WARN");
			break;
		case LEVEL_INFO:
			out.append("INFO");
			break;
		case LEVEL_DEBUG:
			out.append("DEBUG");
			break;
		case LEVEL_TRACE:
			out.append("TRACE");
			break;
		}
		out.append("] ");
		out.append(message);
		std::cout << out << std::endl;
	}
}