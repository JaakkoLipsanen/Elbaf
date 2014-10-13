#pragma once

#include <memory>
#include <Graphics/OpenGL/OGL.h>
#include <Graphics/OpenGL/OGL-Helper.h>

enum class DepthBufferFormat
{
	None,
	Depth16,
	Depth24Stencil8,
	Depth32,
};


class RenderTarget
{
public:
	static std::unique_ptr<RenderTarget> Create(int width, int height, DepthBufferFormat format = DepthBufferFormat::Depth24Stencil8)
	{
		GLuint frameBufferID;
		glGenFramebuffers(1, &frameBufferID);

		// Modifies global frame buffer. cache old and set it back?
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

		GLuint colorTextureID;
		glGenTextures(1, &colorTextureID);
		glBindTexture(GL_TEXTURE_2D, colorTextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0); // last 0 == "empty image"

		// Poor filtering ???
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		
		// The depth buffer
	/*	GLuint depthTextureID;
		glGenRenderbuffers(1, &depthTextureID);
		glBindRenderbuffer(GL_RENDERBUFFER, depthTextureID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTextureID);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureID, 0);
		*/

		GLuint depthTextureID;
		glGenTextures(1, &depthTextureID);
		glBindTexture(GL_TEXTURE_2D, depthTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0); // == last 0 == "empty buffer"
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureID, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureID, 0);

		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0); // todo: what if "no frame buffer" (== 0) was not bound when this was called? it should be cached
			throw std::exception("Error creating render target");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // todo: what if "no frame buffer" (== 0) was not bound when this was called? it should be cached

		return std::unique_ptr<RenderTarget>(new RenderTarget(frameBufferID, colorTextureID, depthTextureID));
	}

	void BindRenderTarget()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
	}

	void BindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, _colorTextureID);
	}

	void BindTextureToSampler(unsigned samplerIndex)
	{
		glActiveTexture(OGL::SamplerIndexToGLenum(samplerIndex));
		this->BindTexture();
	}

	GLuint DepthTextureID()
	{
		return _depthTextureID;
	}

private:
	GLuint _framebufferID;
	GLuint _colorTextureID;
	GLuint _depthTextureID;

	RenderTarget(GLuint frameBufferID, GLuint colorTextureID, GLuint depthTextureID)
		: _framebufferID(frameBufferID), _colorTextureID(colorTextureID), _depthTextureID(depthTextureID)
	{
	}
};