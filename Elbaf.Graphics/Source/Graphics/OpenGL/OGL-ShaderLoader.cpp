#include <Graphics\OpenGL\OGL-ShaderLoader.h>

#include <vector>
#include <Core\File.h>
#include <Diagnostics\Logger.h>

static void CompileShader(GLuint& shaderID, const std::string& shaderCode, const std::string filePath)
{
	Logger::LogMessage("Compiling shader (" + filePath + ")... ", false);

	char const* shaderCorePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderCorePointer, nullptr); // sets the source to the shader objcet
	glCompileShader(shaderID);

	// Check Vertex Shader
	GLint compileStatus = GL_FALSE;
	int errorMessageLength;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorMessageLength);
	if (errorMessageLength > 1 && compileStatus == GL_FALSE)
	{
		std::vector<char> errorMessage(errorMessageLength + 1);
		glGetShaderInfoLog(shaderID, errorMessageLength, nullptr, &errorMessage[0]);
		Logger::LogError("\nError Compiling Shader (" + filePath + "): " + std::string(errorMessage.data()));
		return;
	}

	Logger::LogMessage("Success!");
}

static void LinkShaders(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
	Logger::LogMessage("Linking the shaders... ", false);
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	GLint compileStatus = GL_FALSE;
	int errorMessageLength = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &compileStatus);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorMessageLength);
	if (errorMessageLength > 1 && compileStatus == GL_FALSE)
	{
		std::vector<char> errorMessage(errorMessageLength + 1);
		glGetProgramInfoLog(programID, errorMessageLength, nullptr, &errorMessage[0]);
		Logger::LogError("\nError Linking Program: " + std::string(errorMessage.data()));
	}

	// delete the shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	Logger::LogMessage("Success!");
	Logger::LogMessage("");
}

GLuint OGL::LoadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	// Create the shaders 
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	CompileShader(vertexShaderID, File::ReadAllLines(vertexFilePath), vertexFilePath);
	CompileShader(fragmentShaderID, File::ReadAllLines(fragmentFilePath), vertexFilePath);

	GLuint programID = glCreateProgram();
	LinkShaders(programID, vertexShaderID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return programID;
}