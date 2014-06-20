#pragma once
#include <memory>
#include <Core\Event.h>
#include <Core\Engine.h>

class Scene { };
class IGameWindow;
class IGraphicsDevice;
class Game : public IEngine
{
public:
	Event<void()> BeginFrame = Event<void()>();
	Event<void()> EndFrame = Event<void()>();
	Event<void()> Exiting = Event<void()>();

	Game();
	virtual ~Game();

	void Run();
	void Exit();
	IGameWindow* GetWindow() const override;
	IGraphicsDevice* GetGraphicsDevice() const;

protected:
	virtual void Initialize() { }
	virtual void PreUpdate() { }
	virtual void PostUpdate() { }
	virtual void PreRender() { }
	virtual void PostRender() { }

	virtual void OnExiting() { }
	virtual std::unique_ptr<Scene> CreateDefaultScene() = 0;
	virtual void SetupGraphics(int* width, int* height, bool* isFullScreen) { *width = 1280; *height = 720; *isFullScreen = false; } // should this be forced to be implemented (pure virtual)?
	virtual IModule* GetModuleInner(const type_info& typeInfo) const override;

private:
	struct GameImpl;
	std::unique_ptr<GameImpl> _pImpl;
};
