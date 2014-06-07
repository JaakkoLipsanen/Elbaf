#include "GraphicsModule.h"
#include "GraphicsDevice.h"
#include "OGL.h"
#include <Core\Diagnostics\Logger.h>
#include <Core\IGameWindow.h>
#include <Core\Size.h>
#include <Graphics\OpenGL\GameWindow.h>
#include <Core\Diagnostics\Ensure.h>

struct OGL::GraphicsModule::GraphicsModuleImpl
{
	std::unique_ptr<OGL::GraphicsDevice> Device;
	std::unique_ptr<OGL::GameWindow> Window;

	void Initialize()
	{
		this->InitializeGLFW();
	}

	void OpenWindow(Size const& size, std::string const& title, bool isFullScreen)
	{
		this->CreateWindow(size, title, isFullScreen);
		this->InitializeGLEW(); // meh.. test if this is possible to initialize in Initialize(). In tutorials, this was always after window creating so I dont know..
	}

private:
	void InitializeGLFW()
	{
		if (!glfwInit())
		{
			Logger::LogError("GraphicsModule: Error initializing GLFW");
			throw std::logic_error("Couldn't initialize GLFW");
		}

		glfwSetErrorCallback([](int, const char* message)
		{
			Logger::LogError("GLFW Error: " + std::string(message));
		});
	}

	void CreateWindow(Size const& size, std::string const& title, bool isFullScreen)
	{
		this->Window.reset(new OGL::GameWindow);
		this->Window->Open(size, title, isFullScreen);
	}

	void InitializeGLEW()
	{
		if (glewInit() != GLEW_OK)
		{
			Logger::LogError("GraphicsModule: Failed to initialize GLEW");
			throw std::logic_error("Couldn't initialize GLEW");
		}
	}
};

OGL::GraphicsModule::GraphicsModule() : _pimpl(new GraphicsModuleImpl)
{
}

void OGL::GraphicsModule::Initialize()
{	
	Ensure::NotNull(_pimpl.get(), "GraphicsModule has been terminated.");
	_pimpl->Initialize();
}

void OGL::GraphicsModule::Terminate()
{
	Ensure::NotNull(_pimpl.get(), "GraphicsModule has been terminated.");
	_pimpl->Window->Destroy();
	_pimpl.reset(nullptr);
}

IGraphicsDevice* OGL::GraphicsModule::GetGraphicsDevice() const
{
	return _pimpl->Device.get();
}

void OGL::GraphicsModule::OpenWindow(Size const& size, std::string const& title, bool isFullScreen)
{
	_pimpl->OpenWindow(size, title, isFullScreen);
}