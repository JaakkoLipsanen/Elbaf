#pragma once
#include <string>
#include <memory>

// todo: support for tesslation & geometry shaders etc?
struct IShader
{
	static std::unique_ptr<IShader> Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);

	// todo: set variable (float, matrix etc)
	virtual void ApplyShader() = 0;
	virtual ~IShader() { }

};