#pragma once
#include <Graphics\IShader.h>
#include <Graphics\OpenGL\OGL.h>
#include <string>
#include <memory>

namespace OGL
{
	class Shader : public IShader
	{
	public:
		virtual void ApplyShader() override;

		static std::unique_ptr<IShader> Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);

		virtual ~Shader() override;


	private:
		Shader(GLuint id) : _programID(id) { }
		GLuint _programID;
	};
}