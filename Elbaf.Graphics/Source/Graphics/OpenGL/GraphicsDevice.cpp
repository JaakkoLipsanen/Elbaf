#include "GraphicsDevice.h"
#include <Core\Size.h>

#include "OGL.h"
#include <Graphics\ClearOptions.h>
#include <Math\FlaiMath.h>
#include <Core\Color.h>
#include <Graphics\OpenGL\OGL-Helper.h>

OGL::GraphicsDevice::GraphicsDevice(GLFWwindow* window) : _window(window)
{
}

OGL::GraphicsDevice::~GraphicsDevice()
{
}

void OGL::GraphicsDevice::ChangeResolution(Size const& newSize)
{
	glfwSetWindowSize(_window, newSize.Width, newSize.Height);

	// this call could mess up state a bit. basically, if you have a custom viewport, then resize the screen. after the viewport will be fullscreen.. not a huge problem though
	this->ResetViewport(); // glViewport(0, 0, newSize.Width, newSize.Height);  would be a bit faster but meh
}

void OGL::GraphicsDevice::ResetViewport() const
{
	auto size = this->GetResolution();
	glViewport(0, 0, size.Width, size.Height); // update the viewport
}

bool OGL::GraphicsDevice::IsDepthTestEnabled() const
{
	return _isDepthTestEnabled;
}

void OGL::GraphicsDevice::SetDepthTestEnabled(bool isEnabled)
{
	if (_isDepthTestEnabled == isEnabled)
	{
		return;
	}

	_isDepthTestEnabled = isEnabled;
	glEnableOrDisable(GL_DEPTH_TEST, _isDepthTestEnabled);
}

CullMode OGL::GraphicsDevice::GetCullMode() const
{
	return _cullMode;
}

void OGL::GraphicsDevice::SetCullMode(CullMode cullMode)
{
	if (_cullMode != cullMode)
	{
		_cullMode = cullMode;
		glFrontFace((_cullMode == CullMode::Clockwise ? GL_CW : GL_CCW));
	}
}

CullFace OGL::GraphicsDevice::GetCullFace() const
{
	return _cullFace;
}

void OGL::GraphicsDevice::SetCullFace(CullFace cullFace)
{
	if (_cullFace != cullFace)
	{
		_cullFace = cullFace;
		glCullFace(OGL::CullFaceToGLenum(cullFace));
	}
}

CompareFunction OGL::GraphicsDevice::GetDepthFunction() const
{
	return _depthCompareFunction;
}

Size OGL::GraphicsDevice::GetResolution() const
{
	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	return Size(width, height);
}

void OGL::GraphicsDevice::SetDepthFunction(CompareFunction compareFunction)
{
	if (_depthCompareFunction == compareFunction)
	{
		return;
	}

	_depthCompareFunction = compareFunction;
	glDepthFunc(OGL::CompareFunctionToGLenum(compareFunction));
}

void OGL::GraphicsDevice::Clear(Color const& color)
{
	static const float DefaultDepthValue = 1.0f;
	static const int DefaultStencilValue = 0;

	this->Clear(ClearOptions::All, color, DefaultDepthValue, DefaultStencilValue);
}

void OGL::GraphicsDevice::Clear(ClearOptions const& clearOptions, Color const& color, float depth, int stencilValue)
{
	glClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
	glClearDepth(FlaiMath::Clamp(depth, 0.0f, 1.0f));
	glClearStencil(stencilValue);

	glClear(OGL::GetClearMask(clearOptions));
}

void OGL::GraphicsDevice::DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count)
{
	glDrawArrays(OGL::PrimitiveTypeToGLenum(primitiveType), firstIndex, count);
}