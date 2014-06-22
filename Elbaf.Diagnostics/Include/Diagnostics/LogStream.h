#pragma once
#include <Diagnostics\Logger.h>

enum class LogType
{
	Message,
	Error,
};

class LogStream
{
public:
	LogStream(LogType logType) : _logType(logType) { }
	virtual ~LogStream() = default;

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

private:
	LogType _logType;
};