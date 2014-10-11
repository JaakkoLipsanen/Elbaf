#include <Content\ImageLoader.h>
#include <Diagnostics\Logger.h>
#include <Content\PNG-Loader.h>


#include <Content/FontLoader.h>

//std::unique_ptr<Image> Content::LoadImage(std::string const& filePath)
//{
//	TextureFormat textureFormat;
//	void* data = nullptr;
//	int width, height;
//	if (!ReadPNG(filePath, &width, &height, &textureFormat, &data)) // todo: check file extension for other types?
//	{
//		Logger::LogError("Error loading texture (" + filePath + "): Could not load the texture");
//		free(data); // free the data, in case anything was allocated into it (lets hope that it wasn't already freed :P )
//		return std::unique_ptr<Image>(nullptr);
//	}
//
//	return std::unique_ptr<Image>(new Image(data, width, height, textureFormat));
//	/*	GLuint format = (textureFormat == TextureFormat::RBGA) ? GL_RGBA : GL_RGB;
//
//	// Generate the OpenGL texture object
//	GLuint texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, format, width,height, 0, format, GL_UNSIGNED_BYTE, data);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	*/
//	//return texture;
//}
//
//std::unique_ptr<Font> Content::LoadFont(IGraphicsContext& graphicsContext, std::string const& fontPath, int fontSize)
//{
//}