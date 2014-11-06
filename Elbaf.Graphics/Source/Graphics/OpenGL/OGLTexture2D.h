#pragma once
#include <Graphics\Texture.h>
#include <Graphics/OpenGL/OGL.h>

enum class TextureFormat;
namespace OGL
{
	class OGLTexture2D : public Texture2D
	{
	public:
		static std::unique_ptr<OGLTexture2D> Load(const Image& textureData);
		static std::unique_ptr<OGLTexture2D> LoadInternal(int width, int height, GLint internalFormat, GLenum format, GLenum dataType, GLvoid* data);

		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
		virtual TextureFormat GetTextureFormat() const override;

		virtual void Bind() override;
		virtual void BindToSampler(unsigned int samplerIndex) override;

		virtual ~OGLTexture2D() override;

		/* INTERNAL */
		uint GetInternalID();

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;
		explicit OGLTexture2D(Impl* pImpl);
	};
}