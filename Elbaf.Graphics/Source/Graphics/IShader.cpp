#include "IShader.h"

#if OPENGL
#include <Graphics\OpenGL\Shader.h>
std::unique_ptr<IShader> IShader::Load(std::string const& vertexFilePath, std::string const& fragmentFilePath)
{
	return OGL::Shader::Load(vertexFilePath, fragmentFilePath);
}
#endif