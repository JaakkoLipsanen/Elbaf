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

	virtual void SetParameter(const std::string& valueName, const float& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector2f& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector3f& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector4f& value) = 0;

	virtual void SetParameter(const std::string& valueName, const int& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector2i& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector3i& value) = 0;
	virtual void SetParameter(const std::string& valueName, const Vector4i& value) = 0;

	virtual void SetParameter(const std::string& valueName, const  Matrix2x2& value) = 0; // bool transpose
	virtual void SetParameter(const std::string& valueName, const Matrix3x3& value) = 0; // bool transpose
	virtual void SetParameter(const std::string& valueName, const Matrix4x4& value) = 0; // bool transpose

	/*
	virtual void SetValue(const std::string& valueName, uint32 value) = 0;
	virtual void SetValue(const std::string& valueName, Vector2u value) = 0;
	virtual void SetValue(const std::string& valueName, Vector3u value) = 0;
	virtual void SetValue(const std::string& valueName, Vector4u value) = 0;
	*/

	/*
	todo: array variants (glUniform1fv, glUniform2fv, glUniform3iv etc etc)
	*/

	// todo: implement a lot more! At least Vector2f, Vector3f, Vector4f, int
	template<typename T>
	T GetParameter(const std::string& valueName) const; // todo: could make static_assert or enable_if? could be clearer and better error message

	template<>
	float GetParameter<float>(const std::string& valueName) const
	{
		return this->GetFloat(valueName);
	}

	template<>
	int GetParameter<int>(const std::string& valueName) const
	{
		return this->GetInt(valueName);
	}

	template<>
	Vector2f GetParameter<Vector2f>(const std::string& valueName) const
	{
		return this->GetVector2f(valueName);
	}

	template<>
	Vector3f GetParameter<Vector3f>(const std::string& valueName) const
	{
		return this->GetVector3f(valueName);
	}

	template<>
	Vector4f GetParameter<Vector4f>(const std::string& valueName) const
	{
		return this->GetVector4f(valueName);
	}

	template<>
	Matrix4x4 GetParameter<Matrix4x4>(const std::string& valueName) const
	{
		return this->GetMatrix4x4(valueName);
	}

protected:
	// todo: implement a lot more! At least Vector2f, Vector3f, Vector4f, int
	virtual float GetFloat(const std::string& valueName) const = 0;
	virtual int GetInt(const std::string& valueName) const = 0;
	virtual Vector2f GetVector2f(const std::string& valueName) const = 0;
	virtual Vector3f GetVector3f(const std::string& valueName) const = 0;
	virtual Vector4f GetVector4f(const std::string& valueName) const = 0;
	virtual Matrix4x4 GetMatrix4x4(const std::string& valueName) const = 0;
};