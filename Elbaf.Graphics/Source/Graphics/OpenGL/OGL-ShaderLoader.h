#pragma once
#include "OGL.h"
#include <string>

namespace OGL
{
	GLuint LoadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
}