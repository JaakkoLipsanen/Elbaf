#include <Graphics/OpenGL/OGLRenderTarget.h>
#include <Graphics/OpenGL/OGL.h>
#include <Graphics/OpenGL/OGL-Helper.h>
#include <Diagnostics/Ensure.h>
#include <Graphics/Image.h>
#include <Graphics/OpenGL/OGLGraphicsContext.h>
#include <Graphics/OpenGL/OGLTexture2D.h>

#include <memory>
#include <Graphics/Texture.h>



class OGL::OGLRenderTarget::Impl
{
public:
	const GLuint  FramebufferID;
	const std::vector<std::unique_ptr<OGLTexture2D>> ColorTextures;
	const std::unique_ptr<OGLTexture2D> DepthTexture;
	const Size Size;

	Impl(GLuint frameBufferID, std::vector<std::unique_ptr<OGLTexture2D>> colorTextures, std::unique_ptr<OGLTexture2D> depthTexture, ::Size size)
		: FramebufferID(frameBufferID), ColorTextures(std::move(colorTextures)), DepthTexture(std::move(depthTexture)), Size(size)
	{
	}
};


OGL::OGLRenderTarget::OGLRenderTarget(Impl* impl) : _pImpl(impl) { }
OGL::OGLRenderTarget::~OGLRenderTarget() = default;

std::unique_ptr<OGL::OGLRenderTarget> OGL::OGLRenderTarget::Create(OGLGraphicsContext& graphicsContext, int width, int height, DepthBufferFormat depthFormat, std::vector<TextureFormat> colorFormats)
{
	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);

	// Modifies global frame buffer. cache old and set it back?
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	std::vector<std::unique_ptr<OGLTexture2D>> colorTextures;
	std::vector<GLenum> drawBuffers;

	for (int i = 0; i < colorFormats.size(); i++)
	{
		// GLenum format = OGL::TextureFormatToGLenum(colorFormats[i]);
		Image emptyImage(nullptr, width, height, colorFormats[i], false);
		auto texture = graphicsContext.CreateTexture2D(emptyImage);
		auto oglTexture = std::unique_ptr<OGLTexture2D>(dynamic_cast<OGLTexture2D*>(texture.release())); // dynamic_cast<OGLTexture2D*>(texture.get());

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, oglTexture->GetInternalID(), 0);

		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
		colorTextures.push_back(std::move(oglTexture));
	}

	std::unique_ptr<OGLTexture2D> depthTexture;
	if (depthFormat == DepthBufferFormat::None)
	{
		depthTexture = nullptr;
	}
	else
	{
		depthTexture = OGLTexture2D::LoadInternal(width, height, DepthBufferFormatToGLenum(depthFormat), GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture->GetInternalID(), 0);
	}

	if (drawBuffers.size() != 0)
	{
		glDrawBuffers(1, drawBuffers.data());
	}
	else
	{
		glDrawBuffer(GL_NONE);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // todo: what if "no frame buffer" (== 0) was not bound when this was called? it should be cached
		throw std::exception("Error creating render target");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // todo: what if "no frame buffer" (== 0) was not bound when this was called? it should be cached

	return std::unique_ptr<OGL::OGLRenderTarget>(new OGL::OGLRenderTarget(new Impl(frameBufferID, std::move(colorTextures), std::move(depthTexture), Size(width, height))));
}

bool OGL::OGLRenderTarget::HasDepthTexture() const
{
	return _pImpl->DepthTexture.get() != nullptr;
}

int OGL::OGLRenderTarget::GetColorTextureCount() const
{
	return _pImpl->ColorTextures.size();
}

Texture2D& OGL::OGLRenderTarget::GetColorTexture(uint index)
{
	Ensure::True(index < this->GetColorTextureCount());
	return *_pImpl->ColorTextures[index];
}

Texture2D& OGL::OGLRenderTarget::GetDepthTexture()
{
	Ensure::True(this->HasDepthTexture());
	return *_pImpl->DepthTexture;
}

Size OGL::OGLRenderTarget::GetSize() const
{
	return _pImpl->Size;
}

uint OGL::OGLRenderTarget::GetInternalID()
{
	return _pImpl->FramebufferID;
}