#pragma once
#include <Graphics\OpenGL\OGL.h>
#include <string>

namespace OGL
{
	GLuint LoadShadersFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	GLuint LoadShadersFromSource(const std::string& vertexShader, const std::string& fragmentShader, const std::string& vertexShaderName = "VertexShader", const std::string& fragmentShaderName = "FragmentShader");
}