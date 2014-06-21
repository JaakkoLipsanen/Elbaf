#pragma once
#include "Logger.h"

enum class LogType
{
	Message,
	Error,
};

class LogStream
{
public:
	template<typename T>
	LogStream& operator<<(const T& value)
	{
		if (_logType == LogType::Message)
		{
			Logger::LogMessage(value, false);
		}
		else
		{
			Logger::LogError(value, false);
		}

		return *this;
	}

	LogStream(LogType logType) : _logType(logType) { }
private:
	LogType _logType;
};