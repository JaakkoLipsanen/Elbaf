#pragma once

#include <memory>
#include <Graphics/OpenGL/OGL.h>
#include <Graphics/OpenGL/OGL-Helper.h>
#include <Graphics/TextureFormat.h>
#include <vector>
#include <limits>
#include <Diagnostics/Ensure.h>

enum class DepthBufferFormat
{
	None,
	Depth16,
	Depth24Stencil8,
	Depth24,
	Depth32,
};

inline GLenum DepthBufferFormatToGLenum(const DepthBufferFormat& depthBufferFormat)
{
	switch (depthBufferFormat)
	{
	case DepthBufferFormat::Depth16:
		return GL_DEPTH_COMPONENT16;

	case DepthBufferFormat::Depth24Stencil8:
	case DepthBufferFormat::Depth24:
		return GL_DEPTH_COMPONENT24;

	case DepthBufferFormat::Depth32:
			return GL_DEPTH_COMPONENT32;

	default:
		throw std::exception("DepthBufferFormat::None cannot be converted to GLenum");
	}
}

class RenderTarget
{
public:
	// TODO: (To both render target and texture2D): add ability to change Sampling type (linear, near) and wrapping type (wrap, clamp)!
	static std::unique_ptr<RenderTarget> Create(int width, int height, DepthBufferFormat depthFormat = DepthBufferFormat::Depth24Stencil8, std::vector<TextureFormat> colorFormats = { TextureFormat::RBG8 })
	{
		GLuint frameBufferID;
		glGenFramebuffers(1, &frameBufferID);

		// Modifies global frame buffer. cache old and set it back?
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

		std::vector<GLuint> colorTextureIds;
		std::vector<GLenum> drawBuffers;
		for (int i = 0; i < colorFormats.size(); i++)
		{
			GLuint colorTextureID;
			glGenTextures(1, &colorTextureID); // this could be optimized; "glGenTextures(colorFormats.size())"
			glBindTexture(GL_TEXTURE_2D, colorTextureID);

			GLenum format = OGL::TextureFormatToGLenum(colorFormats[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, 0); // last 0 == "empty image"

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorTextureID, 0);
			drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
		
			colorTextureIds.push_back(colorTextureID);
		}

		GLuint depthTextureID;
		if (depthFormat == DepthBufferFormat::None)
		{
			depthTextureID = UINT_MAX;
		}
		else
		{
			glGenTextures(1, &depthTextureID);
			glBindTexture(GL_TEXTURE_2D, depthTextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, DepthBufferFormatToGLenum(depthFormat), width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0); // == last 0 == "empty buffer"
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureID, 0);
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

		return std::unique_ptr<RenderTarget>(new RenderTarget(frameBufferID, colorTextureIds, depthTextureID));
	}

	void BindRenderTarget()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
	}

	void BindColorTexture(unsigned colorTextureIndex)
	{
		Ensure::True(colorTextureIndex < _colorTextureIds.size());
		glBindTexture(GL_TEXTURE_2D, _colorTextureIds[colorTextureIndex]);
	}

	void BindColorTextureToSampler(unsigned colorTextureIndex, unsigned samplerIndex)
	{
		Ensure::True(colorTextureIndex < _colorTextureIds.size());
		glActiveTexture(OGL::SamplerIndexToGLenum(samplerIndex));
		this->BindColorTexture(colorTextureIndex);
	}

	void BindDepthTexture()
	{
		Ensure::True(this->HasDepthTexture());
		glBindTexture(GL_TEXTURE_2D, _depthTextureID);
	}

	void BindDepthTextureToSampler(unsigned samplerIndex)
	{
		Ensure::True(this->HasDepthTexture());
		glActiveTexture(OGL::SamplerIndexToGLenum(samplerIndex));
		this->BindDepthTexture();
	}

	bool HasDepthTexture() const
	{
		return _depthTextureID != UINT_MAX;
	}
	
	int ColorTextureCount() const
	{
		return _colorTextureIds.size();
	}

private:
	GLuint _framebufferID;
	std::vector<GLuint> _colorTextureIds;
	GLuint _depthTextureID;

	RenderTarget(GLuint frameBufferID, std::vector<GLuint> colorTextureIds, GLuint depthTextureID)
		: _framebufferID(frameBufferID), _colorTextureIds(colorTextureIds), _depthTextureID(depthTextureID)
	{
	}
};