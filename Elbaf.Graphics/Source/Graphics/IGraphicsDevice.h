#pragma once
#include <Graphics/IMonitor.h>

#include <vector>
#include <memory>

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

	virtual std::unique_ptr<const IMonitor> GetPrimaryMonitor() const = 0;
	virtual std::vector<std::unique_ptr<const IMonitor>> GetAllMonitors() const = 0;

	virtual void OpenWindow(const WindowDescription& windowDescription) = 0;
	virtual void RunMessagePump() = 0; // meh, this really doesn't belong here :(

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Terminate() = 0;
};