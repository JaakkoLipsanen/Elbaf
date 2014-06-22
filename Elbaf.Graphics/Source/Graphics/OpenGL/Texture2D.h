#pragma once
#include <Graphics\ITexture.h>

namespace OGL
{
	class Texture2D : public ITexture2D
	{
	public:
		static std::unique_ptr<Texture2D> Load(std::unique_ptr<Image> textureData);

		virtual int GetWidth() const override;
		virtual int GetHeight() const override;
		virtual void Bind() override;
		virtual void BindToSampler(unsigned int samplerIndex) override;

		virtual ~Texture2D() override;

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;
		explicit Texture2D(Impl* pImpl);
	};
}