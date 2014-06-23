#include <Graphics\OpenGL\GraphicsContext.h>

#include <Math\Size.h>
#include <Math\FlaiMath.h>
#include <Core\Color.h>

#include <Graphics\Image.h>
#include <Graphics\ClearOptions.h>
#include <Graphics\ITexture.h>

#include <Graphics\OpenGL\OGL-Helper.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\GameWindow.h>
#include <Graphics\OpenGL\Texture2D.h>
#include <Graphics\OpenGL\VertexBuffer.h>
#include <Graphics\OpenGL\Shader.h>
#include <Graphics\OpenGL\BlendState.h>

class OGL::GraphicsContext::Impl
{
public:
	std::shared_ptr<IBlendState> BlendState;
	Impl() : BlendState(new OGL::BlendState) { }
};

OGL::GraphicsContext::GraphicsContext(GameWindow& window) : _window(window)
{
}

OGL::GraphicsContext::~GraphicsContext()
{
}

/* resolution */
Size OGL::GraphicsContext::GetResolution() const
{
	int width, height;
	glfwGetFramebufferSize(_window.GetGLFWwindow(), &width, &height);
	return Size(width, height);
}

void OGL::GraphicsContext::ChangeResolution(Size const& newSize)
{
	glfwSetWindowSize(_window.GetGLFWwindow(), newSize.Width, newSize.Height);

	// this call could mess up state a bit. basically, if you have a custom viewport, then resize the screen. after the viewport will be fullscreen.. not a huge problem though
	this->ResetViewport(); // glViewport(0, 0, newSize.Width, newSize.Height);  would be a bit faster but meh
}

ICullState& OGL::GraphicsContext::GetCullState()
{
	return _cullState;
}

void OGL::GraphicsContext::SetCullState(CullStatePreset const& preset)
{
	throw std::logic_error("Not implemented");
}

IBlendState& OGL::GraphicsContext::GetBlendState()
{
	return _blendState; // *_pImpl->BlendState.get();
}

void OGL::GraphicsContext::SetBlendState(const BlendStatePreset& blendStatePreset)
{
	throw std::logic_error("Not implemented");
}

IDepthState& OGL::GraphicsContext::GetDepthState()
{
	return _depthState;
}

void OGL::GraphicsContext::SetDepthState(DepthStatePreset const& depthStatePreset)
{
	throw std::logic_error("Not implemented");
}

/* clear */
void OGL::GraphicsContext::Clear(Color const& color)
{
	static const float DefaultDepthValue = 1.0f;
	static const int DefaultStencilValue = 0;

	this->Clear(ClearOptions::All, color, DefaultDepthValue, DefaultStencilValue);
}

void OGL::GraphicsContext::Clear(ClearOptions const& clearOptions, Color const& color, float depth, int stencilValue)
{
	glClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
	glClearDepth(FlaiMath::Clamp(depth, 0.0f, 1.0f));
	glClearStencil(stencilValue);

	glClear(OGL::GetClearMask(clearOptions));
}

/* misc */
void OGL::GraphicsContext::ResetViewport() const
{
	auto size = this->GetResolution();
	glViewport(0, 0, size.Width, size.Height); // update the viewport
}


/* draw */
void OGL::GraphicsContext::DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count)
{
	glDrawArrays(OGL::PrimitiveTypeToGLenum(primitiveType), firstIndex, count);
}

/* create */
std::unique_ptr<ITexture2D> OGL::GraphicsContext::CreateTexture2D(std::unique_ptr<Image> textureData)
{
	return Texture2D::Load(std::move(textureData));
}

std::unique_ptr<IVertexBuffer> OGL::GraphicsContext::CreateVertexBuffer(BufferType bufferType)
{
	return VertexBuffer::CreateVertexBuffer(bufferType);
}

std::unique_ptr<IShader> OGL::GraphicsContext::CreateShader(const ShaderSource& shaderSource)
{
	return Shader::Load(shaderSource);
}

std::unique_ptr<IBlendState> OGL::GraphicsContext::CreateBlendState()
{
	return std::unique_ptr<BlendState>(new OGL::BlendState);
}