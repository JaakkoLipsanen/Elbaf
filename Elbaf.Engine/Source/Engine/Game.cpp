#include "Game.h"
#include <Core\Diagnostics.h>
#include <Core\IGameWindow.h>
#include <Graphics\IGraphicsModule.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\Platform.h>
#include <Input\IInputModule.h>
#include <Input\KeyCode.h>
#include <Input\Platform.h>
#include <Engine\Platform.h>

struct Game::GameImpl
{
	GameImpl(Game& game) : _game(game), GraphicsModule(nullptr), InputModule(nullptr) { }

	bool IsRunning = false;
	bool IsExiting = false;
	std::unique_ptr<IGraphicsModule> GraphicsModule;
	std::unique_ptr<IInputModule> InputModule;
	std::unique_ptr<TimeModule> TimeModule;

	void Run()
	{
		Ensure::False(this->IsRunning);
		this->IsRunning = true;

		// initialize
		this->InitializeModules();
		_game.Initialize();

		// run!
		Logger::LogMessage("Running Game..");
		while (!this->GraphicsModule->GetGameWindow()->IsExiting() || this->IsExiting)
		{
			// todo: fps limiting or something? i mean 60fps lock etc. and fixedupdate?
			this->Tick();
		}

		// exit :( !
		_game.OnExiting();
		_game.Exiting.Invoke();
		this->GraphicsModule->Terminate();
		Logger::LogMessage("Exiting Game");
	}

	void InitializeModules()
	{
		this->GraphicsModule = Platform::Graphics::CreateDefaultGraphicsModule(_game);
		this->GraphicsModule->Initialize();
		this->OpenWindow();	 // okay open window in this point. basically so that other modules can access it (at least Input needs it when using GLFW)

		this->InputModule = Platform::Input::CreateDefaultInputModule(_game);
		this->InputModule->Initialize();

		this->TimeModule = Platform::Engine::CreateTimeModule(_game);
		this->TimeModule->Initialize();
	}

	void OpenWindow()
	{
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
		this->TimeModule->Update();
		this->GraphicsModule->Update();
		this->InputModule->Update();
		
		_game.PreRender();
		this->EndFrame();
	}

	void BeginFrame()
	{
		_game.BeginFrame.Invoke();
		this->GraphicsModule->BeginFrame();
		this->InputModule->BeginFrame();
		this->TimeModule->BeginFrame();
	}

	void EndFrame()
	{
		this->GraphicsModule->EndFrame();
		this->InputModule->EndFrame();
		this->TimeModule->EndFrame();
		_game.EndFrame.Invoke();
	}

private:
	Game& _game;
};

Game::Game() : _pImpl(new Game::GameImpl(*this)) { }
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
IModule* Game::GetModuleInner(const type_info& typeInfo) const
{
	if (typeInfo == typeid(IGraphicsModule))
	{
		return _pImpl->GraphicsModule.get();
	}
	else if (typeInfo == typeid(IInputModule))
	{
		return _pImpl->InputModule.get();
	}
	else if (typeInfo == typeid(TimeModule))
	{
		return _pImpl->TimeModule.get();
	}

	throw std::logic_error("Not implemented yet/invalid type");
}