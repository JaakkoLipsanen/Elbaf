#include <Graphics\OpenGL\OGL-ShaderLoader.h>

#include <vector>
#include <Core\File.h>
#include <Diagnostics\Logger.h>
#include <Core/StringHelper.h>

static void CompileShader(GLuint& shaderID, const std::string& shaderCode, const std::string name)
{
	Logger::LogMessage("Compiling shader (" + name + ")... ", false);

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
		Logger::LogError("\nError Compiling Shader (" + name + "): " + std::string(errorMessage.data()) + "\n\n" + shaderCode + "\n");
		return;
	}

	Logger::LogMessage("Success!");
}

static void LinkShaders(GLuint programID, std::vector<GLuint> shaderIds)
{
	for (auto& id : shaderIds)
	{
		glAttachShader(programID, id);
	}

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

	for (auto& id : shaderIds)
	{
		glDeleteShader(id);
	}
}

std::vector<std::string> GetPreprocessorParameters(const std::string& source, int index, int* endIndex)
{
	if (source[index] != '#' || source[index + 1] != '(')
	{
		*endIndex = -1;
		return{};
	}

	int preprocessorContentStart = index + 2;
	for (int i = preprocessorContentStart; i < source.size(); i++)
	{
		if (source[i] == ')')
		{
			*endIndex = i + 1; // i + 1 == character after ')'

			std::vector<std::string> parameters;
			int currentStartIndex = preprocessorContentStart;
			bool isInsideString = false;
			bool hasContent = false;
			for (int j = preprocessorContentStart; j < *endIndex; j++)
			{
				if (source[j] == '"')
				{
					isInsideString = !isInsideString;
				}

				if (source[j] != ' ' && source[j] != '\n')
				{
					if (!hasContent) currentStartIndex = j;
					hasContent = true;
				}

				if (source[j] == ' ' && !isInsideString && hasContent)
				{
					if (j == currentStartIndex + 1) continue;
					parameters.push_back(source.substr(currentStartIndex, j - currentStartIndex));
					currentStartIndex = j;
					hasContent = false;
				}
			}

			if (currentStartIndex < i - 1 && hasContent)
			{
				parameters.push_back(source.substr(currentStartIndex, i - currentStartIndex));
			}

			return parameters;
		}
	}

	*endIndex = -1;
	return { };
}

struct ShaderData
{
	std::string Source;
	GLint PartType;
	std::string Name;

	ShaderData(std::string source, GLint partID, std::string name = "") :
		Source(source), PartType(partID), Name(name)
	{
	}
};

std::vector<ShaderData> ParseShader(std::string source);
GLuint OGL::LoadShaderFromSource(std::string const& source)
{
	auto parsed = ParseShader(source);
	if (parsed.size() == 0)
	{
		throw OGL::ShaderLoadException("Error parsing the source: no programs found");
	}

	std::vector<GLuint> shaderIds;
	for (auto& x : parsed)
	{
		auto id = glCreateShader(x.PartType);
		CompileShader(id, x.Source, x.Name);
		shaderIds.push_back(id);
	}

	GLuint programID = glCreateProgram();
	LinkShaders(programID, shaderIds);
	return programID;
}

// todo: there is basically no error handling here. error == you're fucked
std::vector<ShaderData> ParseShader(std::string source)
{
	std::vector<ShaderData> shaderParts;
	std::string currentSourcePart = "";
	GLint currentSourceType = -1;
	std::string currentSourceName = "";
	for (int currentIndex = 0; currentIndex < source.size(); currentIndex++)
	{
		if (source[currentIndex] == '#')
		{
			if (source[currentIndex + 1] == '(')
			{
				int endIndex;
				std::vector<std::string> preprocessorParamaters = GetPreprocessorParameters(source, currentIndex, &endIndex);
				if (endIndex == -1)
				{
					std::cout << "err" << "\n";
					continue; // wtf should i do :P ??
				}

				if (preprocessorParamaters.size() == 1)
				{
					if (preprocessorParamaters[0] == "vertex-shader" || preprocessorParamaters[0] == "fragment-shader")
					{
						currentSourcePart = StringHelper::Trim(currentSourcePart);
						if (currentSourceType != -1)
						{
							shaderParts.emplace_back(currentSourcePart, currentSourceType, currentSourceName);
						}

						currentSourcePart = "";
						currentSourceType = (preprocessorParamaters[0] == "vertex-shader" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
					}

					currentIndex = endIndex;
					continue;
				}
				else if (preprocessorParamaters.size() == 2)
				{
					if (preprocessorParamaters[0] == "include")
					{
						std::string fileName = preprocessorParamaters[1];
						fileName = StringHelper::Unquote(fileName);

						source = source.substr(0, currentIndex) + File::ReadAllLines(fileName) + source.substr(endIndex);
						currentIndex--;

						continue;
					}
					else if (preprocessorParamaters[0] == "name")
					{
						currentSourceName = StringHelper::Unquote(preprocessorParamaters[1]);
						currentIndex = endIndex;
					}
				}
			}
		}

		currentSourcePart += source[currentIndex];
	}

	currentSourcePart = StringHelper::Trim(currentSourcePart);
	if (currentSourceType != -1)
	{
		shaderParts.emplace_back(currentSourcePart, currentSourceType, currentSourceName);
	}

	return shaderParts;
}
