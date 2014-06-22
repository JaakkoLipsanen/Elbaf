#pragma once
#include <memory>
#include <Core\IModule.h>

struct WindowDescription;
class IGraphicsDevice;
class IEngine;
class IGraphicsContext;
class IGameWindow;

// todo: why does this have to be outside of the class (and can't be in "private "part)? if this not, then GetGraphicsDevice-implementation gives an error (can't cast from GraphicsDevice* to IGraphicsDevice*)
class GraphicsModule : public IModule
{
public:
	GraphicsModule(IEngine& engine, const WindowDescription& windowDescription);
	virtual ~GraphicsModule();

	virtual void Initialize();
	virtual void Terminate();
	virtual void EndFrame();
	virtual IGraphicsContext& GetGraphicsDevice() const;
	virtual IGameWindow& GetGameWindow() const;

private:
	std::unique_ptr<IGraphicsDevice> _graphicsDevice;
};