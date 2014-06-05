#pragma once
#include <memory>
#include "Event.h"
#include "Scene.h"
#include <Graphics\GameWindow.h>
#include <Graphics\Color.h>
#include <Graphics\GraphicsDevice.h>

class Game
{
	bool _hasStarted = false;
	bool _isExiting = false;

protected:
	std::unique_ptr<GameWindow> _window; // pointer because window isn't created immediately
	std::unique_ptr<GraphicsDevice> _graphicsDevice;

public:
	 Event<void()> Exiting = Event<void()>();

private:
	void InitializeGraphics();
	void Tick();

protected:
	virtual void Initialize() { }
	virtual void PreUpdate()
	{
		_graphicsDevice->Clear(Color::RoyalBlue); // by default clear the backbuffer
	}

	virtual void PostUpdate() { }
	virtual void PreRender() { }
	virtual void PostRender() { }

	virtual void OnExiting() { }
	virtual std::unique_ptr<Scene> CreateDefaultScene() = 0;
	virtual void SetupGraphics(int* width, int* height);

public:
	Game();
	virtual ~Game();

	void Run();
	void Exit();
    GameWindow& GetWindow() const;
};

