#pragma once
#include <Graphics\Texture.h>

namespace OGL
{
	class OGLTexture2D : public Texture2D
	{
	public:
		static std::unique_ptr<OGLTexture2D> Load(const Image& textureData);

		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
		virtual void Bind() override;
		virtual void BindToSampler(unsigned int samplerIndex) override;

		virtual ~OGLTexture2D() override;

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;
		explicit OGLTexture2D(Impl* pImpl);
	};
}