#pragma once
#include <memory>
#include <Core\Event.h>

class Scene { };
class IGameWindow;
class IGraphicsDevice;
class Game
{
public:
	Event<void()> Exiting = Event<void()>();

	Game();
	virtual ~Game();

	void Run();
	void Exit();
	IGameWindow* GetWindow() const;
	IGraphicsDevice* GetGraphicsDevice() const;

protected:
	virtual void Initialize() { }
	virtual void PreUpdate() { }
	virtual void PreRender() { }

	virtual void OnExiting() { }
	virtual std::unique_ptr<Scene> CreateDefaultScene() = 0;
	virtual void SetupGraphics(int* width, int* height, bool* isFullScreen) { } // should this be forced to be implemented (pure virtual)?

private:
	struct GameImpl;
	std::unique_ptr<GameImpl> _pImpl;
};

