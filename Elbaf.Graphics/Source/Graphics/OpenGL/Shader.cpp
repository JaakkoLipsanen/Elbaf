#include "Shader.h"
#include <Graphics\OpenGL\OGL-ShaderLoader.h>

void OGL::Shader::ApplyShader()
{
	glUseProgram(_programID);
}

std::unique_ptr<IShader> OGL::Shader::Load(std::string const& vertexFilePath, std::string const& fragmentFilePath)
{
	GLuint programID = OGL::LoadShaders(vertexFilePath, fragmentFilePath);
	return std::unique_ptr<Shader>(new Shader(programID));
}

OGL::Shader::~Shader()
{
	glDeleteProgram(_programID);
}