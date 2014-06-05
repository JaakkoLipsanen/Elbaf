#pragma once
#include <string>

// todo: this should be made into a singleton (which, however, still has static public API :P)
class Logger
{
	Logger() = delete;
public:
	static void LogMessage(const std::string& message, bool addNewLine = true);
	static void LogError(const std::string& message , bool addNewLine = true);
};