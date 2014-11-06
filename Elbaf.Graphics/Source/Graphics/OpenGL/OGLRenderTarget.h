#pragma once
#include <Graphics/RenderTarget.h>
#include <Graphics/GraphicsContext.h>

namespace OGL
{
	class OGLGraphicsContext;
	class OGLRenderTarget : public RenderTarget
	{
	
	public:
		static std::unique_ptr<OGLRenderTarget> Create(OGLGraphicsContext& graphicsContext, int width, int height, DepthBufferFormat depthFormat = DepthBufferFormat::Depth24Stencil8, std::vector<TextureFormat> colorFormats = { TextureFormat::RBG8 });

		virtual ~OGLRenderTarget();
		virtual bool HasDepthTexture() const override;
		virtual int GetColorTextureCount() const override;

		virtual Texture2D& GetColorTexture(uint index) override;
		virtual Texture2D& GetDepthTexture() override;

		virtual Size GetSize() const override;
		uint GetInternalID();

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;

		explicit OGLRenderTarget(Impl* impl);
	};
}