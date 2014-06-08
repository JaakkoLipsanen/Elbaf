#pragma once
#include <memory>
#include <Graphics\IGraphicsModule.h>
#include <Graphics\RendererAPI.h>

class IGraphicsModule;
namespace Platform
{
	namespace Graphics
	{
		std::unique_ptr<IGraphicsModule> CreateDefaultGraphicsModule(Engine& engine);
		RendererAPI GetCurrentRendererAPI();
		void RunMessagePump(); // this sucks. this belongs to Engine or Core, but I don't want them to access OpenGL/GLFW stuff.. damn!! 
	}
}