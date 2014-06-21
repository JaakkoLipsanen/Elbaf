#pragma once
#include <string>

// okay doing this in an api-independent and flexible way is hard.. (heck, doing this even OpenGL-only and flexible way is impossible! I'm fucked!)
struct ShaderSource
{
	const std::string VertexShaderPath;
	const std::string PixelShaderPath;

	ShaderSource(const std::string& vertexShaderPath, const std::string& pixelShaderPath) : 
		VertexShaderPath(vertexShaderPath), PixelShaderPath(pixelShaderPath)
	{
	}
};