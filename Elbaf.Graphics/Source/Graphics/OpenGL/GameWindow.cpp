#include "GameWindow.h"
#include <Core\Diagnostics\Ensure.h>

void OGL::GameWindow::SetTitle(std::string const& title)
{
	Ensure::NotNull(window);
	glfwSetWindowTitle(window, title.c_str());
}

bool OGL::GameWindow::IsOpen() const
{
	return window != nullptr; // this isn't really true... window can be closed too if someone calls glfwTerminate (probably other ways too). This applies to this whole class (lots of nullptr checks here, eventhough they are not necessarily correct)
}

void OGL::GameWindow::Open(const Size& size, const std::string& title, bool fullScreen)
{
	Ensure::Null(window, "Window is already opened!");
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(size.Width, size.Height, title.c_str(), fullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
}

void OGL::GameWindow::Destroy()
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
}

void* OGL::GameWindow::GetInternalHandle() const
{
	return window;
}