#pragma once
#include <string>

class IGraphicsContext;
class IGameWindow;
struct Size;
struct WindowDescription;

class IGraphicsDevice
{
public:
	IGraphicsDevice() = default;
	virtual ~IGraphicsDevice() { }

	virtual IGameWindow& GetGameWindow() = 0;
	virtual IGraphicsContext& GetContext() = 0;
	virtual void OpenWindow(const WindowDescription& windowDescription) = 0;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Terminate() = 0;
};