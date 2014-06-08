#include "Game.h"
#include <Core\Diagnostics.h>
#include <Core\IGameWindow.h>
#include <Graphics\IGraphicsModule.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\Platform.h>

struct Game::GameImpl
{
	GameImpl(Game& game) : _owner(game) { }

	bool IsRunning = false;
	bool IsExiting = false;
	std::unique_ptr<IGraphicsModule> GraphicsModule;

	void Run()
	{
		Ensure::False(this->IsRunning);
		this->IsRunning = true;

		this->InitializeModules();
		_owner.Initialize();
		Logger::LogMessage("Running Game..");
		while (!this->GraphicsModule->GetGameWindow()->IsExiting() || this->IsExiting)
		{
			this->Tick();
		}

		_owner.OnExiting();
		_owner.Exiting.Invoke();
		this->GraphicsModule->Terminate();
		Logger::LogMessage("Exiting Game");
	}

	void InitializeModules()
	{
		this->GraphicsModule = Platform::Graphics::CreateDefaultGraphicsModule();
		this->GraphicsModule->Initialize();

		int screenWidth = 1280, screenHeight = 720;
		bool isFullScreen = false;
		_owner.SetupGraphics(&screenWidth, &screenHeight, &isFullScreen);

		Ensure::True(screenWidth > 0 && screenHeight > 0);
		this->GraphicsModule->OpenWindow(Size(screenWidth, screenHeight), "Game", isFullScreen);
	}

	void Tick()
	{
		Platform::Graphics::RunMessagePump();

		this->BeginFrame();
		_owner.PreUpdate();
		this->GraphicsModule->Update();
		
		_owner.PreRender();
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
	Game& _owner;
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