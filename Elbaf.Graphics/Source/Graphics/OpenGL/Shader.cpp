#include "Shader.h"
#include <Graphics\OpenGL\OGL-ShaderLoader.h>
#include <Diagnostics\Logger.h>
#include <map>
class OGL::Shader::PImpl
{
public:
	GLuint ProgramID;
	PImpl(GLuint programID) : ProgramID(programID) { }

	GLint GetUniformLocation(const std::string& name)
	{
		auto key = _uniformLocations.find(name);
		if (key != _uniformLocations.end()) // found!
		{
			return key->second;
		}

		// not cached
		GLint value = glGetUniformLocation(this->ProgramID, name.c_str());
		if (value == -1)
		{
			Logger::LogError("OGL::Shader: Trying to get uniform named '" + name + "' which doesnt exist. Setting it to -1 now");
		}

		_uniformLocations.insert(std::pair<std::string, GLint>(name, value));
		return value;
	}

private:
	std::map<std::string, GLint> _uniformLocations;
};

void OGL::Shader::ApplyShader()
{
	glUseProgram(_pImpl->ProgramID);
}

std::unique_ptr<IShader> OGL::Shader::Load(std::string const& vertexFilePath, std::string const& fragmentFilePath)
{
	GLuint programID = OGL::LoadShaders(vertexFilePath, fragmentFilePath);
	return std::unique_ptr<Shader>(new Shader(new PImpl(programID)));
}

OGL::Shader::~Shader()
{
	glDeleteProgram(_pImpl->ProgramID);
}

OGL::Shader::Shader(PImpl* pImpl) : _pImpl(pImpl) { }

/* PARAMETER SETTERS */
void OGL::Shader::SetParameter(std::string const& valueName, const float& value)
{
	glUniform1f(_pImpl->GetUniformLocation(valueName), value);
}

void OGL::Shader::SetTextureSampler(std::string const& valueName, int index)
{
	glUniform1i(_pImpl->GetUniformLocation(valueName), index);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector2f& value)
{
	glUniform2f(_pImpl->GetUniformLocation(valueName), value.x, value.y);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector3f& value)
{
	glUniform3f(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector4f& value)
{
	glUniform4f(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z, value.w);
}

void OGL::Shader::SetParameter(std::string const& valueName, const int& value)
{
	glUniform1i(_pImpl->GetUniformLocation(valueName), value);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector2i& value)
{
	glUniform2i(_pImpl->GetUniformLocation(valueName), value.x, value.y);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector3i& value)
{
	glUniform3i(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Vector4i& value)
{
	glUniform4i(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z, value.w);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Matrix2x2& value) // bool transpose
{
	glUniformMatrix2fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Matrix3x3& value) // bool transpose
{
	glUniformMatrix3fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}

void OGL::Shader::SetParameter(std::string const& valueName, const Matrix4x4& value) // bool transpose
{
	glUniformMatrix4fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}


/* PARAMETER GETTERS */
float OGL::Shader::GetFloat(std::string const& valueName) const
{
	float value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), &value);
	return value;
}

Matrix4x4 OGL::Shader::GetMatrix4x4(std::string const& valueName) const
{
	Matrix4x4 matrix;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&matrix));
	return matrix;
}

int OGL::Shader::GetInt(std::string const& valueName) const
{
	int value;
	glGetUniformiv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), &value);
	return value;
}

Vector2f OGL::Shader::GetVector2f(std::string const& valueName) const
{
	Vector2f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}

Vector3f OGL::Shader::GetVector3f(std::string const& valueName) const
{
	Vector3f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}

Vector4f OGL::Shader::GetVector4f(std::string const& valueName) const
{
	Vector4f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}