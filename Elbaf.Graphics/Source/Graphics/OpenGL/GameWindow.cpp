#include <Graphics\OpenGL\GameWindow.h>

#include <Diagnostics\Ensure.h>
#include <Graphics\OpenGL\OGL.h>
#include <Core/WindowDescription.h>

void OGL::GameWindow::Open(const WindowDescription& description)
{
	Ensure::Null(_window, "Window is already opened!");

	const static int MultiSampleCount = 4; // todo: 4x not necessary maybe? also if I were to implement post-process AA, then making this changeable would be wise
	glfwWindowHint(GLFW_SAMPLES, MultiSampleCount);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.4. Using an earlier could be wise, Mac OSX for example doesn't support this
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, description.IsResizable);
	glfwWindowHint(GLFW_DECORATED, description.HasBorders);

	_window = glfwCreateWindow(description.Resolution.Width, description.Resolution.Height, description.Title.c_str(), description.IsFullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	glfwMakeContextCurrent(_window);
}

void OGL::GameWindow::Terminate()
{
	if (_window != nullptr)
	{
		glfwDestroyWindow(_window);
	}
}

bool OGL::GameWindow::IsOpen() const
{
	// this isn't really true... window can be closed too if someone calls glfwTerminate (probably other ways too).
	//  This applies to this whole class (somenullptr checks here, even though they are not necessarily "correct")
	return _window != nullptr; 
}

bool OGL::GameWindow::IsExiting() const
{
	Ensure::NotNull(_window, "Window is not open!");
	return glfwWindowShouldClose(_window) == GL_TRUE;
}

void OGL::GameWindow::SetPosition(Vector2i position)
{
	glfwSetWindowPos(_window, position.X, position.Y);
}

GLFWwindow* OGL::GameWindow::GetGLFWwindow() const
{
	return _window;
}

void* OGL::GameWindow::GetInternalHandle() const
{
	return _window;
}

void OGL::GameWindow::SetTitle(std::string const& title)
{
	Ensure::NotNull(_window);
	glfwSetWindowTitle(_window, title.c_str());
}