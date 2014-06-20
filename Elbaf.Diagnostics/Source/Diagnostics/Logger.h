#pragma once
#include <iostream>
#include "LogStream.h"


class LogStream;
// todo: this should be made into a singleton (which, however, still has static public API :P)
namespace Logger
{
	template<typename T>
	static void LogMessage(const T& value, bool addNewLine = true)
	{
		std::cout << value;
		if (addNewLine)
			std::cout << "\n";
	}

	template<typename T>
	static void LogError(const T& value, bool addNewLine = true)
	{
		std::cerr << value;
		if (addNewLine)
			std::cerr << "\n";
	}

	static LogStream MessageStream = LogStream(LogType::Message);;
};