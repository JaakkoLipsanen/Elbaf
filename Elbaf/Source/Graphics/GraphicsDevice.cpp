#include "GraphicsDevice.h"
#include "Graphics.h"
#include "GameWindow.h"
#include <Core\Math\FlaiMath.h>
#include <Core\Game.h>
 

GraphicsDevice::GraphicsDevice(Game const& game) : _game(game)
{
	if (!glfwInit())
	{
		Logger::LogError("GraphicsDevice: Couldn't initialize GLFW");
		throw std::logic_error("Couldn't initialize GLFW");
	}

	glfwSetErrorCallback([](int, const char* message)
	{
		Logger::LogError("GLFW Error: " + std::string(message));
	});
}

void GraphicsDevice::Terminate()
{
	_game.GetWindow()._window;
	glfwTerminate();
}

void GraphicsDevice::Initialize()
{
	if (glewInit() != GLEW_OK) {
		Logger::LogError("GraphicsDevice: Failed to initialize GLEW");
		throw std::logic_error("Couldn't initialize GLEW");
	}
}

void GraphicsDevice::SwapBuffers()
{
	_game.GetWindow().SwapBuffers();
}

void GraphicsDevice::SetResolution(Size size)
{
	_game.GetWindow().SetWindowSize(size);
}

void GraphicsDevice::Clear(Color const& color)
{
	static const float DefaultDepthValue = 1.0f;
	static const int DefaultStencilValue = 0;

	this->Clear(ClearOptions::All, color, DefaultDepthValue, DefaultStencilValue);
}

void GraphicsDevice::Clear(ClearOptions clearOptions, Color const& color, float depth, int stencil)
{
	glClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
	glClearDepth(FlaiMath::Clamp(depth, 0.0f, 1.0f));
	glClearStencil(stencil);

	glClear(GetClearMask(clearOptions));
}

GraphicsDevice::~GraphicsDevice()
{
}
