#pragma once
#include <iostream>

// todo: this should be made into a singleton (which, however, still has static public API :P)
class Logger
{
	Logger() = delete;
public:
	static void LogMessage(const std::string& message, bool addNewLine = true);
	static void LogError(const std::string& message , bool addNewLine = true);

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
};