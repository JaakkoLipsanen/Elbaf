#pragma once
#include <Core\IModule.h>
#include <Core\Size.h>

class IGameWindow;
class IGraphicsDevice;

// plaa plee ploo?
class IGraphicsModule : public IModule
{
public:
	virtual IGraphicsDevice* GetGraphicsDevice() const = 0;
	virtual IGameWindow* GetGameWindow() const = 0; // okay this is here, at least for now... Window creation is tied to the graphics API (at least in GLFW), so it makes sense to be here!

	virtual void OpenWindow(const Size& size = Size(1280, 720), const std::string& title = "Game", bool isFullScreen = false) = 0;

protected:
	explicit IGraphicsModule(Engine& engine);
};