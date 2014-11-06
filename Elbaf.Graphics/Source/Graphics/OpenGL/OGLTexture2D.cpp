#include <Graphics\OpenGL\OGLTexture2D.h>

#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>
#include <Graphics\TextureFormat.h>
#include <Graphics\Image.h>

class OGL::OGLTexture2D::Impl
{
public:
	GLuint TextureID;
	int Width;
	int Height;
	TextureFormat Format;

	Impl(GLuint textureID, int width, int height, TextureFormat textureFormat) : TextureID(textureID), Width(width), Height(height), Format(textureFormat) { }
};

// TODO: (To both render target and texture2D): add ability to change Sampling type (linear, near) and wrapping type (wrap, clamp)!
std::unique_ptr<OGL::OGLTexture2D> OGL::OGLTexture2D::Load(const Image& textureData)
{
	GLuint format = OGL::TextureFormatToGLenum(textureData.Format);

	// Generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.Width, textureData.Height, 0, format, GL_UNSIGNED_BYTE, textureData.ImageData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // !
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // !

	return std::unique_ptr<OGL::OGLTexture2D>(new OGLTexture2D(new Impl(texture, textureData.Width, textureData.Height, textureData.Format)));
}

std::unique_ptr<OGL::OGLTexture2D> OGL::OGLTexture2D::LoadInternal(int width, int height, GLint internalFormat, GLenum format, GLenum dataType, GLvoid* data)
{
	// Generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // !
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // !

	return std::unique_ptr<OGL::OGLTexture2D>(new OGLTexture2D(new Impl(texture, width, height, TextureFormat::None)));

}

int OGL::OGLTexture2D::GetWidth() const
{
	return _pImpl->Width;
}

int OGL::OGLTexture2D::GetHeight() const
{
	return _pImpl->Height;
}

TextureFormat OGL::OGLTexture2D::GetTextureFormat() const
{
	return _pImpl->Format;
}

void OGL::OGLTexture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _pImpl->TextureID);
}

void OGL::OGLTexture2D::BindToSampler(unsigned samplerIndex)
{
	glActiveTexture(OGL::SamplerIndexToGLenum(samplerIndex));
	this->Bind();
}

OGL::OGLTexture2D::OGLTexture2D(Impl* pImpl) : _pImpl(pImpl) { }

uint OGL::OGLTexture2D::GetInternalID()
{
	return _pImpl->TextureID;
}

OGL::OGLTexture2D::~OGLTexture2D() = default; // required for PImpl