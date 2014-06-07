#include "GraphicsDevice.h"
#include <Core\Size.h>

#include "OGL.h"
#include <Graphics\ClearOptions.h>
#include <Math\FlaiMath.h>
#include <Core\Color.h>

static int GetClearMask(ClearOptions clearOptions);
Size OGL::GraphicsDevice::ChangeResolution(Size const& newSize)
{
	throw std::logic_error("Not Implemented");
	return Size(0, 0);
}

OGL::GraphicsDevice::~GraphicsDevice()
{
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

	glClear(GetClearMask(clearOptions));
}

static int GetClearMask(ClearOptions clearOptions)
{
#define BIT(X)  GL_##X##_BUFFER_BIT
	static const int MapToGL[] = { BIT(COLOR), BIT(DEPTH), BIT(STENCIL), BIT(COLOR) | BIT(DEPTH) | BIT(STENCIL) };
	return MapToGL[static_cast<int>(clearOptions)];
}
