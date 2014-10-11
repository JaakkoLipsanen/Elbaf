#pragma once
#include <string>
#include <Core/File.h>

// okay doing this in an api-independent and flexible way is hard.. (heck, doing this even OpenGL-only and flexible way is impossible! I'm fucked!)
struct ShaderSource
{
	const std::string VertexShader;
	const std::string FragmentShader;

	// just meta-data, path name
	const std::string VertexShaderName;
	const std::string FragmentShaderName;

	static ShaderSource FromFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		return ShaderSource(File::ReadAllLines(vertexShaderPath), File::ReadAllLines(fragmentShaderPath), vertexShaderPath, fragmentShaderPath);
	}

	static ShaderSource FromSource(const std::string& vertexShader, const std::string& fragmentShader)
	{
		return ShaderSource(vertexShader, fragmentShader, "VertexShader", "FragmentShader");
	}

private:
	ShaderSource(const std::string& vertexShader, const std::string& fragmentShader, const std::string& vertexShaderName, const std::string& fragmentShaderName)
		: VertexShader(vertexShader), FragmentShader(fragmentShader), VertexShaderName(vertexShaderName), FragmentShaderName(fragmentShaderName)
	{
	}
};