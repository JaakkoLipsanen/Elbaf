#pragma once
#include <string>

namespace File
{
	std::string ReadAllLines(const std::string& filePath);
	std::string GetAbsolutePath(const std::string& path);
}