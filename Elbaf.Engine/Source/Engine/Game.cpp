#include "Game.h"
#include <Core\Diagnostics.h>
#include <Core\IGameWindow.h>
#include <Graphics\IGraphicsModule.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\Platform.h>

struct Game::GameImpl
{
	GameImpl(Game& game) : _game(game) { }

	bool IsRunning = false;
	bool IsExiting = false;
	std::unique_ptr<IGraphicsModule> GraphicsModule;

	void Run()
	{
		Ensure::False(this->IsRunning);
		this->IsRunning = true;

		this->InitializeModules();
		_game.Initialize();
		Logger::LogMessage("Running Game..");
		while (!this->GraphicsModule->GetGameWindow()->IsExiting() || this->IsExiting)
		{
			this->Tick();
		}

		_game.OnExiting();
		_game.Exiting.Invoke();
		this->GraphicsModule->Terminate();
		Logger::LogMessage("Exiting Game");
	}

	void InitializeModules()
	{
		this->GraphicsModule = Platform::Graphics::CreateDefaultGraphicsModule(_game);
		this->GraphicsModule->Initialize();

		int screenWidth = 1280, screenHeight = 720;
		bool isFullScreen = false;
		_game.SetupGraphics(&screenWidth, &screenHeight, &isFullScreen);

		Ensure::True(screenWidth > 0 && screenHeight > 0);
		this->GraphicsModule->OpenWindow(Size(screenWidth, screenHeight), "Game", isFullScreen);
	}

	void Tick()
	{
		Platform::Graphics::RunMessagePump();

		this->BeginFrame();
		_game.PreUpdate();
		this->GraphicsModule->Update();
		
		_game.PreRender();
		this->EndFrame();
	}

	void BeginFrame()
	{
		this->GraphicsModule->BeginFrame();
	}

	void EndFrame()
	{
		this->GraphicsModule->EndFrame();
	}

private:
	Game& _game;
};

Game::Game() : _pImpl(new GameImpl(*this)) { }
Game::~Game() = default;

void Game::Run()
{
	_pImpl->Run();
}

void Game::Exit()
{
	_pImpl->IsExiting = true;
}

IGameWindow* Game::GetWindow() const
{
	return _pImpl->GraphicsModule->GetGameWindow();
}

IGraphicsDevice* Game::GetGraphicsDevice() const
{
	return _pImpl->GraphicsModule->GetGraphicsDevice();
}

// TODO: instead of this, implementing only specific template stuff's could be better (though not sure if possible, since virtual etc)
IModule* Game::GetModule(type_info typeInfo) const
{
	if (typeInfo == typeid(IGraphicsModule))
	{
		return _pImpl->GraphicsModule.get();
	}

	throw std::logic_error("Not implemented yet/invalid type");
}