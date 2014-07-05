#include <Core\File.h>

#include <iostream>
#include <fstream>
#include <string>
#include <Diagnostics\Logger.h>
#include <Windows.h>

std::string File::ReadAllLines(std::string const& filePath)
{
	auto realPath = File::GetAbsolutePath(filePath);
	std::ifstream fileStream(realPath, std::ios::in);
	if (!fileStream.is_open())
	{
		Logger::LogError("Could not open file " + realPath + "!");
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

std::string File::GetAbsolutePath(std::string const& path)
{
	char buffer[256];
	_fullpath(buffer, path.c_str(), 256);

	return std::string(buffer);
}