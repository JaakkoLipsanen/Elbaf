#include "GameWindow.h"
#include <Core\Diagnostics\Ensure.h>
#include "OGL.h"
#include <iostream>
#include <Core\CursorType.h>

void OGL::GameWindow::SetTitle(std::string const& title)
{
	Ensure::NotNull(_window);
	glfwSetWindowTitle(_window, title.c_str());
}

bool OGL::GameWindow::IsOpen() const
{
	return _window != nullptr; // this isn't really true... window can be closed too if someone calls glfwTerminate (probably other ways too). This applies to this whole class (lots of nullptr checks here, eventhough they are not necessarily correct)
}

void OGL::GameWindow::Open(const Size& size, const std::string& title, bool fullScreen)
{
	Ensure::Null(_window, "Window is already opened!");
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	_window = glfwCreateWindow(size.Width, size.Height, title.c_str(), fullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	glfwMakeContextCurrent(_window);
}

bool OGL::GameWindow::IsExiting() const
{
	Ensure::NotNull(_window, "Window is not open!");
	return glfwWindowShouldClose(_window) == true;
}

void OGL::GameWindow::SetCursorType(CursorType const& cursorType)
{
	auto value = (cursorType == CursorType::Visible ? GLFW_CURSOR_NORMAL : (cursorType == CursorType::Hidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_DISABLED));
	glfwSetInputMode(_window, GLFW_CURSOR, value);
}

void OGL::GameWindow::Destroy()
{
	if (_window != nullptr)
	{
		glfwDestroyWindow(_window);
	}
}

GLFWwindow* OGL::GameWindow::GetGLFWwindow() const
{
	return _window;
}

void* OGL::GameWindow::GetInternalHandle() const
{
	return _window;
}