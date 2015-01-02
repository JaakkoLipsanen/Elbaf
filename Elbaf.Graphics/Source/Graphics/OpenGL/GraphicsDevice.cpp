#include <Graphics\OpenGL\GraphicsDevice.h>

#include <Core\Event.h>
#include <Core\WindowDescription.h>
#include <Diagnostics\Logger.h>
#include <Diagnostics\Ensure.h>

#include <Graphics\RendererAPI.h>
#include <Graphics\OpenGL\OGLGraphicsContext.h>
#include <Graphics\OpenGL\GameWindow.h>
#include "Monitor.h"

// move to own file? If I were to add more event's here, then I guess other OGL classes might want to access them
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

/* Implementation */
class OGL::GraphicsDevice::Impl
{
public:
	OGL::OGLGraphicsContext Context;
	OGL::GameWindow Window;

	Impl() : Window(), Context(Window)
	{
		this->InitializeGLFW();
		OGL::GLFW::WindowResized += CreateFunction(this, &Impl::OnResized);
	}

	void OpenWindow(const WindowDescription& windowDescription)
	{
		this->Window.Open(windowDescription); // pass WindowDescription to Open?
		OGL::GLFW::InitializeCallbacks(Window.GetGLFWwindow());
		this->InitializeGLEW(); // glew must be initialized after opening window (= after creating glfw context)
	}

	void Terminate()
	{
		OGL::GLFW::UninitializeCallbacks(this->Window.GetGLFWwindow());
		this->Window.Terminate();
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

	void InitializeGLEW()
	{
		glewExperimental = GL_TRUE; // required for some stuff
		if (glewInit() != GLEW_OK)
		{
			Logger::LogError("GraphicsModule: Failed to initialize GLEW: ");
			throw std::logic_error("Couldn't initialize GLEW");
		}
	}

	void OnResized(int w, int h)
	{
		this->Context.ResetViewport();
	}
};

/* API */
OGL::GraphicsDevice::GraphicsDevice() : _pImpl(new Impl) { }
OGL::GraphicsDevice::~GraphicsDevice() = default;

IGameWindow& OGL::GraphicsDevice::GetGameWindow()
{
	return _pImpl->Window;
}

GraphicsContext& OGL::GraphicsDevice::GetContext()
{
	return _pImpl->Context;
}

std::unique_ptr<const IMonitor> OGL::GraphicsDevice::GetPrimaryMonitor() const
{
	return std::unique_ptr<const IMonitor>(new OGL::Monitor(glfwGetPrimaryMonitor()));
}

std::vector<std::unique_ptr<const IMonitor>> OGL::GraphicsDevice::GetAllMonitors() const
{
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);

	std::vector<std::unique_ptr<const IMonitor>> allMonitors;
	for (int i = 0; i < count; i++)
	{
		allMonitors.push_back(std::unique_ptr<const IMonitor>(new OGL::Monitor(monitors[i])));
	}

	return allMonitors;
}

RendererAPI OGL::GraphicsDevice::GetRendererAPI() const
{
	return RendererAPI::OpenGL;
}

void OGL::GraphicsDevice::OpenWindow(const WindowDescription& windowDescription)
{
	_pImpl->OpenWindow(windowDescription);
}

void OGL::GraphicsDevice::RunMessagePump()
{
	glfwPollEvents();
}

void OGL::GraphicsDevice::BeginFrame()
{
}

void OGL::GraphicsDevice::EndFrame()
{
	// _pImpl->Window->SwapBuffers(); ?
	glfwSwapBuffers(_pImpl->Window.GetGLFWwindow());
}

void OGL::GraphicsDevice::Terminate()
{
	Ensure::NotNull(_pImpl.get(), "GraphicsModule has been terminated.");
	_pImpl->Terminate();
	_pImpl.reset(nullptr);
}