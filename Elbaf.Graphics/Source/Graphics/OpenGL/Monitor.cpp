#include <Graphics/OpenGL/Monitor.h>
#include <Graphics/OpenGL/OGL.h>

struct OGL::Monitor::Impl
{
	explicit OGL::Monitor::Impl(GLFWmonitor* monitor) :
		Monitor(monitor)
	{	
	}

	const GLFWvidmode& GetVideoMode()
	{
		return *glfwGetVideoMode(this->Monitor);
	}

	GLFWmonitor* Monitor;
};

OGL::Monitor::Monitor(GLFWmonitor* monitor) :
	_pImpl(new OGL::Monitor::Impl(monitor))
{
}
OGL::Monitor::~Monitor() = default;

Size OGL::Monitor::GetSize() const
{
	return Size(_pImpl->GetVideoMode().width, _pImpl->GetVideoMode().height);
}

Vector2i OGL::Monitor::GetPosition() const
{
	int width, height; // in millimeters
	glfwGetMonitorPos(_pImpl->Monitor, &width, &height);

	return Size(width, height);
}

int OGL::Monitor::GetRefreshRate() const
{
	return _pImpl->GetVideoMode().refreshRate;
}

std::string OGL::Monitor::GetName() const
{
	return glfwGetMonitorName(_pImpl->Monitor);
}

Size OGL::Monitor::GetPhysicalSize() const
{
	int width, height; // in millimeters
	glfwGetMonitorPhysicalSize(_pImpl->Monitor, &width, &height);

	return Size(width, height);
}