#include "Platform.h"

#if OPENGL

#include "OpenGL\OGL.h"
#include "OpenGL\GraphicsModule.h"

std::unique_ptr<IGraphicsModule> Platform::Graphics::CreateDefaultGraphicsModule(IEngine& engine)
{
	return std::unique_ptr<IGraphicsModule>(new OGL::GraphicsModule(engine));
}

void Platform::Graphics::RunMessagePump()
{
	glfwPollEvents();
}

RendererAPI Platform::Graphics::GetCurrentRendererAPI()
{
	return RendererAPI::OpenGL;
}

#endif