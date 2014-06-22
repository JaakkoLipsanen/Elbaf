#pragma once
#include <Graphics\OpenGL\OGL.h>
#include <string>

namespace OGL
{
	GLuint LoadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
}