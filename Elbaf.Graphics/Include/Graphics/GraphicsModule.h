#pragma 
#include <Core\IModule.h>
#include <memory>
#include <vector>

struct WindowDescription;
enum class RendererAPI;
class IGraphicsDevice;
class IEngine;
class GraphicsContext;
class IGameWindow;
class IMonitor;

// todo: why does this have to be outside of the class (and can't be in "private "part)? if this not, then GetGraphicsDevice-implementation gives an error (can't cast from GraphicsDevice* to IGraphicsDevice*)
class GraphicsModule : public IModule
{
public:
	GraphicsModule(IEngine& engine, const WindowDescription& windowDescription);
	virtual ~GraphicsModule();

	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void EndFrame() override;
	virtual GraphicsContext& GetGraphicsContext() const;
	virtual IGameWindow& GetGameWindow() const;

	virtual std::unique_ptr<const IMonitor> GetPrimaryMonitor() const;
	virtual std::vector<std::unique_ptr<const IMonitor>> GetAllMonitors() const;

	void RunMessagePump(); // message pump doesn't necessarily belong here, but since I'm using GLFW... blargh!

private:
	std::unique_ptr<IGraphicsDevice> _graphicsDevice;
};