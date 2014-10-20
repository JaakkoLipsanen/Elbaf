#include <Graphics\OpenGL\OGLShader.h>

#include <map>
#include <Graphics\OpenGL\OGL-ShaderLoader.h>
#include <Diagnostics\Logger.h>
#include <Graphics\ShaderSource.h>

class OGL::OGLShader::Impl
{
public:
	GLuint ProgramID;
	explicit Impl(GLuint programID) : ProgramID(programID) { }

	GLint GetUniformLocation(const std::string& name)
	{
		auto key = _uniformLocations.find(name);
		if (key != _uniformLocations.end()) // found!
		{
			return key->second;
		}

		// not cached yet
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

OGL::OGLShader::OGLShader(Impl* pImpl) : _pImpl(pImpl) { }
OGL::OGLShader::~OGLShader()
{
	glDeleteProgram(_pImpl->ProgramID);
}

std::unique_ptr<OGL::OGLShader> OGL::OGLShader::Load(const ShaderSource& shaderSource)
{
	GLuint programID = OGL::LoadShaderFromSource(shaderSource.GetParsedSource());
	return std::unique_ptr<OGLShader>(new OGLShader(new Impl(programID)));
}

void OGL::OGLShader::Bind()
{
	glUseProgram(_pImpl->ProgramID);
}

/* PARAMETER SETTERS */
void OGL::OGLShader::SetParameter(std::string const& valueName, const float& value)
{
	glUniform1f(_pImpl->GetUniformLocation(valueName), value);
}

void OGL::OGLShader::SetTextureSampler(std::string const& valueName, int index)
{
	glUniform1i(_pImpl->GetUniformLocation(valueName), index);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector2f& value)
{
	glUniform2f(_pImpl->GetUniformLocation(valueName), value.x, value.y);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector3f& value)
{
	glUniform3f(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector4f& value)
{
	glUniform4f(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z, value.w);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const int& value)
{
	glUniform1i(_pImpl->GetUniformLocation(valueName), value);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector2i& value)
{
	glUniform2i(_pImpl->GetUniformLocation(valueName), value.x, value.y);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector3i& value)
{
	glUniform3i(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Vector4i& value)
{
	glUniform4i(_pImpl->GetUniformLocation(valueName), value.x, value.y, value.z, value.w);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Matrix2x2& value) // bool transpose
{
	glUniformMatrix2fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Matrix3x3& value) // bool transpose
{
	glUniformMatrix3fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}

void OGL::OGLShader::SetParameter(std::string const& valueName, const Matrix4x4& value) // bool transpose
{
	glUniformMatrix4fv(_pImpl->GetUniformLocation(valueName), 1, GL_FALSE, &value[0][0]);
}


/* PARAMETER GETTERS */
float OGL::OGLShader::GetFloat(std::string const& valueName) const
{
	float value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), &value);
	return value;
}

Matrix4x4 OGL::OGLShader::GetMatrix4x4(std::string const& valueName) const
{
	Matrix4x4 matrix;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&matrix));
	return matrix;
}

int OGL::OGLShader::GetInt(std::string const& valueName) const
{
	int value;
	glGetUniformiv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), &value);
	return value;
}

Vector2f OGL::OGLShader::GetVector2f(std::string const& valueName) const
{
	Vector2f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}

Vector3f OGL::OGLShader::GetVector3f(std::string const& valueName) const
{
	Vector3f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}

Vector4f OGL::OGLShader::GetVector4f(std::string const& valueName) const
{
	Vector4f value;
	glGetUniformfv(_pImpl->ProgramID, _pImpl->GetUniformLocation(valueName), reinterpret_cast<float*>(&value));
	return value;
}