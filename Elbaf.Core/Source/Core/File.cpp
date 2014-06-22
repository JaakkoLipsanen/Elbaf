#include <Core\File.h>

#include <iostream>
#include <fstream>
#include <string>
#include <Diagnostics\Logger.h>

std::string File::ReadAllLines(std::string const& filePath)
{
	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open())
	{
		Logger::LogError("Could not open file " + filePath + "!");
		return "";
	}

	std::string code = "";
	std::string line;
	while (getline(fileStream, line))
	{
		code += line + "\n";
	}

	fileStream.close();
	return code;
}