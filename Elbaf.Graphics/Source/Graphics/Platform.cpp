#include "Platform.h"

#if OPENGL
#include "OpenGL\OGL.h"
void Platform::Graphics::RunMessagePump()
{
	glfwPollEvents();
}

RendererAPI Platform::Graphics::GetCurrentRendererAPI()
{
	return RendererAPI::OpenGL;
}

#endif