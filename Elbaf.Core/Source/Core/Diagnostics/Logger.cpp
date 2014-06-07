#include <iostream>
#include <string>
#include "Logger.h"

// todo: write to file, and later, write to in-game console
void Logger::LogMessage(std::string const& message, bool addNewLine)
{
	std::cout << message;
	if (addNewLine)
		std::cout << "\n";
}


void Logger::LogError(std::string const& message, bool addNewLine)
{
	std::cerr << message;
	if (addNewLine)
		std::cout << "\n";
}