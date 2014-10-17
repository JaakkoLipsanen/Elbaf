#pragma once
#include <string>

class GraphicsContext;
class IGameWindow;
struct Size;
struct WindowDescription;
enum class RendererAPI;

class IGraphicsDevice
{
public:
	IGraphicsDevice() = default;
	virtual ~IGraphicsDevice() { }

	virtual IGameWindow& GetGameWindow() = 0;
	virtual GraphicsContext& GetContext() = 0; 
	virtual RendererAPI GetRendererAPI() const = 0;
	virtual void OpenWindow(const WindowDescription& windowDescription) = 0;
	virtual void RunMessagePump() = 0; // meh, this really doesn't belong here :(

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Terminate() = 0;
};