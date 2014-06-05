#include "GameWindow.h"

static GLFWwindow* CreateWindow(Size& size, std::string& title, bool isFullScreen)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return glfwCreateWindow(size.Width, size.Height, title.c_str(), isFullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
}

GameWindow::GameWindow(Size size, std::string title, bool isFullScreen)
: _window(CreateWindow(size, title, isFullScreen))
{
	if (_window.get() == nullptr)
	{
		Logger::LogError("Failed to create GLFW window");
	}
}

Size GameWindow::GetWindowSize() const
{
	int width, height;
	glfwGetWindowSize(_window.get(), &width, &height);
	return Size(width, height);
}

void GameWindow::SetWindowSize(const Size& size)
{
	glfwSetWindowSize(_window.get(), size.Width, size.Height);
}

bool GameWindow::GetShouldClose() const
{
	return glfwWindowShouldClose(_window.get());
}

void GameWindow::SetShouldClose(bool value)
{
	glfwSetWindowShouldClose(_window.get(), value);
}

std::string GameWindow::GetTitle() const
{
	throw new std::exception("Not implemented"); // todo: is it even possible to get this? if not, caching obviously works
}

void GameWindow::SetTitle(std::string const& title)
{
	glfwSetWindowTitle(_window.get(), title.c_str());
}

void GameWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(_window.get());
}

void GameWindow::SwapBuffers()
{
	glfwSwapBuffers(_window.get());
}

bool GameWindow::IsCreated() const
{
	return _window.get() != nullptr;
}

GameWindow::~GameWindow()
{
}
