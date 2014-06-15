#include "GraphicsModule.h"
#include "GraphicsDevice.h"
#include "OGL.h"
#include <Core\Diagnostics\Logger.h>
#include <Core\IGameWindow.h>
#include <Core\Size.h>
#include <Graphics\OpenGL\GameWindow.h>
#include <Core\Diagnostics\Ensure.h>
#include <Graphics\CompareFunction.h>
#include <vector>

namespace OGL
{
	namespace GLFW
	{
		Event<void(int, int)> WindowResized;
		void InitializeCallbacks(GLFWwindow* window)
		{
			glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				OGL::GLFW::WindowResized.Invoke(width, height);
			});
		}

		void UninitializeCallbacks(GLFWwindow* window)
		{
			glfwSetWindowSizeCallback(window, nullptr);
			OGL::GLFW::WindowResized.Clear();
		}
	}
}

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
		OGL::GLFW::InitializeCallbacks(this->Window->GetGLFWwindow());
		this->InitializeGLEW(); // meh.. test if this is possible to initialize in Initialize(). In tutorials, this was always after window creating so I dont know..

		this->Device.reset(new OGL::GraphicsDevice(this->Window->GetGLFWwindow()));

		// okay.. it'd be great if I could put this code out of the platform dependent code. One way would be to make GraphicsModule non-inheritable, and instead make it to have platform dependent "IGraphicsModuleImpl" or something.
		// and then this kind of stuff could be put in the non-inheritable graphics module!
		this->Device->SetDepthTestEnabled(true);
		this->Device->SetDepthFunction(CompareFunction::Less);
		this->Device->SetCullFace(CullFace::Back);
		this->Device->SetCullMode(CullMode::CounterClockwise);

		OGL::GLFW::WindowResized += CreateFunction(this, &GraphicsModuleImpl::Resized);
	}

	void Resized(int w, int h)
	{
		this->Device->ResetViewport();
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
		glewExperimental = GL_TRUE; // 
		if (glewInit() != GLEW_OK)
		{
			Logger::LogError("GraphicsModule: Failed to initialize GLEW: ");
			throw std::logic_error("Couldn't initialize GLEW");
		}
	}
};

OGL::GraphicsModule::GraphicsModule(IEngine& engine) : IGraphicsModule(engine), _pImpl(new GraphicsModuleImpl)
{
}

void OGL::GraphicsModule::Initialize()
{	
	Ensure::NotNull(_pImpl.get(), "GraphicsModule has been terminated.");
	_pImpl->Initialize();
}

void OGL::GraphicsModule::Terminate()
{
	Ensure::NotNull(_pImpl.get(), "GraphicsModule has been terminated.");
	OGL::GLFW::UninitializeCallbacks(_pImpl->Window->GetGLFWwindow());
	_pImpl->Window->Destroy();
	_pImpl.reset(nullptr);
}

IGameWindow* OGL::GraphicsModule::GetGameWindow() const
{
	return _pImpl->Window.get();
}

void OGL::GraphicsModule::EndFrame()
{
	// _pImpl->Window->SwapBuffers(); ?
	glfwSwapBuffers(_pImpl->Window->GetGLFWwindow());
}

IGraphicsDevice* OGL::GraphicsModule::GetGraphicsDevice() const
{
	return _pImpl->Device.get();
}

void OGL::GraphicsModule::OpenWindow(Size const& size, std::string const& title, bool isFullScreen)
{
	_pImpl->OpenWindow(size, title, isFullScreen);
}