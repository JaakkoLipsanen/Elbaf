#pragma once
#include <string>
#include <Core/File.h>

// okay doing this in an api-independent and flexible way is hard.. (heck, doing this even OpenGL-only and flexible way is impossible! I'm fucked!)
struct ShaderSource
{

	static ShaderSource FromFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		return ShaderSource::FromSource(File::ReadAllLines(vertexShaderPath), File::ReadAllLines(fragmentShaderPath));
	}

	static ShaderSource FromSource(const std::string& vertexShader, const std::string& fragmentShader)
	{
		std::string finalSource =
			"#(vertex-shader)\n" + vertexShader + "\n#(fragment-shader)\n" + fragmentShader;

		return ShaderSource(finalSource);
	}

	static ShaderSource FromFiles(const std::string& shaderPath)
	{
		return ShaderSource(File::ReadAllLines(shaderPath));
	}

	static ShaderSource FromSource(const std::string& shaderCode)
	{
		return ShaderSource(shaderCode);
	}


	const std::string& GetParsedSource() const
	{
		return _source;
	}

private:
	ShaderSource(const std::string& shaderSource)
		: _source(shaderSource)
	{
	}


	std::string _source;
};