#include <Graphics\OpenGL\OGLGraphicsContext.h>

#include <Math\Size.h>
#include <Math\FlaiMath.h>
#include <Core\Color.h>

#include <Graphics\Image.h>
#include <Graphics\ClearOptions.h>
#include <Graphics\Texture.h>

#include <Graphics\OpenGL\OGL-Helper.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\GameWindow.h>
#include <Graphics\OpenGL\OGLTexture2D.h>
#include <Graphics\OpenGL\OGLVertexBuffer.h>
#include <Graphics\OpenGL\OGLShader.h>
#include <Graphics\OpenGL\BlendState.h>
#include <Graphics/OpenGL/OGLRenderTarget.h>

class OGL::OGLGraphicsContext::Impl
{
public:
	std::shared_ptr<BlendState> BlendState;
	Impl() : BlendState(new OGL::OGLBlendState) { }
};

OGL::OGLGraphicsContext::OGLGraphicsContext(GameWindow& window) : _window(window)
{
}

OGL::OGLGraphicsContext::~OGLGraphicsContext()
{
}

/* resolution */
Size OGL::OGLGraphicsContext::GetResolution() const
{
	int width, height;
	glfwGetFramebufferSize(_window.GetGLFWwindow(), &width, &height);
	return Size(width, height);
}

void OGL::OGLGraphicsContext::ChangeResolution(Size const& newSize)
{
	glfwSetWindowSize(_window.GetGLFWwindow(), newSize.Width, newSize.Height);

	// this call could mess up state a bit. basically, if you have a custom viewport, then resize the screen. after the viewport will be fullscreen.. not a huge problem though
	this->ResetViewport(); // glViewport(0, 0, newSize.Width, newSize.Height);  would be a bit faster but meh
}

CullState& OGL::OGLGraphicsContext::GetCullState()
{
	return _cullState;
}

void OGL::OGLGraphicsContext::SetCullState(CullStatePreset const& preset)
{
	throw std::logic_error("Not implemented");
}

BlendState& OGL::OGLGraphicsContext::GetBlendState()
{
	return _blendState; // *_pImpl->BlendState.get();
}

void OGL::OGLGraphicsContext::SetBlendState(const BlendStatePreset& blendStatePreset)
{
	throw std::logic_error("Not implemented");
}

DepthState& OGL::OGLGraphicsContext::GetDepthState()
{
	return _depthState;
}

void OGL::OGLGraphicsContext::SetDepthState(DepthStatePreset const& depthStatePreset)
{
	throw std::logic_error("Not implemented");
}

/* clear */
void OGL::OGLGraphicsContext::Clear(Color const& color)
{
	static const float DefaultDepthValue = 1.0f;
	static const int DefaultStencilValue = 0;

	this->Clear(ClearOptions::All, color, DefaultDepthValue, DefaultStencilValue);
}

void OGL::OGLGraphicsContext::Clear(ClearOptions const& clearOptions, Color const& color, float depth, int stencilValue)
{
	bool wasDepthWriteEnabled = this->GetDepthState().IsDepthWriteEnabled();
	this->GetDepthState().SetDepthWriteEnabled(true); // depth write must be enabled to allow depth clearing

	glClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
	glClearDepth(FlaiMath::Clamp(depth, 0.0f, 1.0f));
	glClearStencil(stencilValue);

	glClear(OGL::GetClearMask(clearOptions));
	this->GetDepthState().SetDepthWriteEnabled(wasDepthWriteEnabled);
}

/* misc */
void OGL::OGLGraphicsContext::ResetViewport() const
{
	auto size = this->GetResolution();
	glViewport(0, 0, size.Width, size.Height); // update the viewport
}


/* draw */
void OGL::OGLGraphicsContext::DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count)
{
	glDrawArrays(OGL::PrimitiveTypeToGLenum(primitiveType), firstIndex, count);
}

/* create */
std::unique_ptr<Texture2D> OGL::OGLGraphicsContext::CreateTexture2D(const Image& textureData)
{
	return OGLTexture2D::Load(textureData);
}

std::unique_ptr<VertexBuffer> OGL::OGLGraphicsContext::CreateVertexBuffer(BufferType bufferType)
{
	return OGLVertexBuffer::Create(bufferType);
}

std::unique_ptr<Shader> OGL::OGLGraphicsContext::CreateShader(const ShaderSource& shaderSource)
{
	return OGLShader::Load(shaderSource);
}

std::unique_ptr<BlendState> OGL::OGLGraphicsContext::CreateBlendState()
{
	return std::unique_ptr<OGLBlendState>(new OGL::OGLBlendState);
}

std::unique_ptr<RenderTarget> OGL::OGLGraphicsContext::CreateRenderTarget(int width, int height, DepthBufferFormat depthFormat, std::vector<TextureFormat> colorFormats)
{
	return OGLRenderTarget::Create(*this, width, height, depthFormat, colorFormats);
}

void OGL::OGLGraphicsContext::BindRenderTarget(RenderTarget* renderTarget, bool updateViewport)
{
	GLuint framebufferID = 0; // 0 == "no framebuffer, render to backbuffer"
	if (renderTarget != nullptr)
	{
		auto oglRenderTarget = dynamic_cast<OGLRenderTarget*>(renderTarget);
		framebufferID = oglRenderTarget->GetInternalID();

		if (updateViewport)
		{
			auto size = renderTarget->GetSize();
			this->SetViewport({ 0, 0, size.Width, size.Height });
		}
	}
	else // renderTarget == nullptr
	{
		if (updateViewport)	
		{
			auto screenSize = this->GetResolution();
			this->SetViewport({ 0, 0, screenSize.Width, screenSize.Height });
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
}

void OGL::OGLGraphicsContext::SetViewport(Rectangle rectangle)
{
	glViewport(rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height);
}