#pragma once
#include <string>
#include <memory>
#include <Math\Vector.h>
#include <Math\Matrix.h>

// todo: support for tesslation & geometry shaders etc?
struct IShader
{
	static std::unique_ptr<IShader> Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);

	// todo: set variable (float, matrix etc)
	virtual void ApplyShader() = 0;
	virtual ~IShader() { }

	virtual void SetValue(const std::string& valueName, const float& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector2f& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector3f& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector4f& value) = 0;

	virtual void SetValue(const std::string& valueName, const int& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector2i& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector3i& value) = 0;
	virtual void SetValue(const std::string& valueName, const Vector4i& value) = 0;

	virtual void SetValue(const std::string& valueName, const  Matrix2x2& value) = 0; // bool transpose
	virtual void SetValue(const std::string& valueName, const Matrix3x3& value) = 0; // bool transpose
	virtual void SetValue(const std::string& valueName, const Matrix4x4& value) = 0; // bool transpose

	/*
	virtual void SetValue(const std::string& valueName, uint32 value) = 0;
	virtual void SetValue(const std::string& valueName, Vector2u value) = 0;
	virtual void SetValue(const std::string& valueName, Vector3u value) = 0;
	virtual void SetValue(const std::string& valueName, Vector4u value) = 0;
	*/

	/*
	todo: array variants (glUniform1fv, glUniform2fv, glUniform3iv etc etc)
	*/
};