#pragma once

class IVertexBuffer;
enum class RendererAPI;
namespace Platform
{
	namespace Graphics
	{
		RendererAPI GetCurrentRendererAPI();
		void RunMessagePump(); // this sucks. this belongs to Engine or Core, but I don't want them to access OpenGL/GLFW stuff.. damn!! 
	}
}