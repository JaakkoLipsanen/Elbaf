#pragma once
#include <Graphics\OpenGL\OGL.h>
#include <string>

namespace OGL
{
	class ShaderLoadException : public std::runtime_error
	{
	public:
		explicit ShaderLoadException(std::string const& _Message)
			: runtime_error(_Message)
		{
		}

		explicit ShaderLoadException(char const* _Message)
			: runtime_error(_Message)
		{
		}
	};

	GLuint LoadShadersFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	GLuint LoadShadersFromSource(const std::string& vertexShader, const std::string& fragmentShader, const std::string& vertexShaderName = "VertexShader", const std::string& fragmentShaderName = "FragmentShader");
	GLuint LoadShaderFromSource(const std::string& source);
}