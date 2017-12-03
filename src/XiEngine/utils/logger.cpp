#include "logger.h"

#include <iostream>


const int Logger::LEVEL_NONE = 6;
const int Logger::LEVEL_ERROR = 5;
const int Logger::LEVEL_WARN = 4;
const int Logger::LEVEL_INFO = 3;
const int Logger::LEVEL_TRACE = 2;
const int Logger::LEVEL_DEBUG = 1;

bool Logger::ERROR_LVL = currentLevel <= LEVEL_ERROR;
bool Logger::WARN_LVL = currentLevel <= LEVEL_WARN;
bool Logger::INFO_LVL = currentLevel <= LEVEL_INFO;
bool Logger::TRACE_LVL = currentLevel <= LEVEL_TRACE;
bool Logger::DEBUG_LVL = currentLevel <= LEVEL_DEBUG;

time_t Logger::startTime = time(0);

int Logger::currentLevel = LEVEL_INFO;

void Logger::setLevel(int level)
{
	Logger::currentLevel = level;
	ERROR_LVL = level <= LEVEL_ERROR;
	WARN_LVL = level <= LEVEL_WARN;
	INFO_LVL = level <= LEVEL_INFO;
	TRACE_LVL = level <= LEVEL_TRACE;
	DEBUG_LVL = level <= LEVEL_DEBUG;
}

void Logger::error(const std::string& message)
{
	if (ERROR_LVL) log(LEVEL_ERROR, message);
}

void Logger::warn(const std::string& message)
{
	if (WARN_LVL) log(LEVEL_WARN, message);
}

void Logger::info(const std::string& message)
{
	if (INFO_LVL) log(LEVEL_INFO, message);
}

void Logger::trace(const std::string& message)
{
	if (TRACE_LVL) log(LEVEL_TRACE, message);
}

void Logger::debug(const std::string& message)
{
	if (DEBUG_LVL) log(LEVEL_DEBUG, message);
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
	case LEVEL_TRACE:
		out.append("TRACE");
		break;
	case LEVEL_DEBUG:
		out.append("DEBUG");
		break;
	}
	out.append("] ");
	out.append(message);
	std::cout << out << std::endl;
}