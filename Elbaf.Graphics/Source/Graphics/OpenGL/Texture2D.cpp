#include "Texture2D.h"
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\TextureFormat.h>
#include <Graphics\Image.h>
#include <Graphics\OpenGL\OGL-Helper.h>

struct OGL::Texture2D::PImpl
{
	GLuint TextureID;
	int Width;
	int Height;

	PImpl(GLuint textureID, int width, int height) : TextureID(textureID), Width(width), Height(height) { }
};

std::unique_ptr<OGL::Texture2D> OGL::Texture2D::Load(std::unique_ptr<Image> textureData)
{
//	PImpl* pImpl = new PImpl()
	GLuint format = OGL::TextureFormatToGLenum(textureData->Format);

	// Generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, textureData->Width, textureData->Height, 0, format, GL_UNSIGNED_BYTE, textureData->ImageData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return std::unique_ptr<OGL::Texture2D>(new Texture2D(new PImpl(texture, textureData->Width, textureData->Height)));
}

int OGL::Texture2D::GetWidth() const
{
	return _pImpl->Width;
}

int OGL::Texture2D::GetHeight() const
{
	return _pImpl->Height;
}

void OGL::Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _pImpl->TextureID);
}

void OGL::Texture2D::BindToSampler(unsigned samplerIndex)
{
	glActiveTexture(OGL::SamplerIndexToGLenum(samplerIndex));
	this->Bind();
}

OGL::Texture2D::Texture2D(PImpl* pImpl) : _pImpl(pImpl)
{
}

// required for PImpl
OGL::Texture2D::~Texture2D() { }