#include <Engine\Game.h>

#include <Diagnostics\Logger.h>
#include <Diagnostics\Ensure.h>
#include <Core\IGameWindow.h>
#include <Engine\Platform.h>
#include <Engine\TimeModule.h>
#include <Graphics\GraphicsModule.h>
#include <Core\WindowDescription.h>
#include <Input\InputModule.h>

// very temporary!!
#include "..\..\..\Elbaf.Graphics\Source\Graphics\Platform.h"

class Game::Impl
{
public:
	Impl(Game& game) : _game(game), GraphicsModule(nullptr), InputModule(nullptr)
	{
	}

	bool IsRunning = false;
	bool IsExiting = false;
	std::unique_ptr<GraphicsModule> GraphicsModule;
	std::unique_ptr<InputModule> InputModule;
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
		while (!this->GraphicsModule->GetGameWindow().IsExiting() || this->IsExiting)
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

private:
	Game& _game;

	void InitializeModules()
	{
		WindowDescription description({ 1280, 720 }, "Game", false);
		_game.SetupWindow(description);
		this->GraphicsModule.reset(new ::GraphicsModule(_game, description));
		this->InputModule.reset(new ::InputModule(_game));
		this->TimeModule.reset(new ::TimeModule(_game)); // = Platform::Engine::CreateTimeModule(_game);

		this->GraphicsModule->Initialize();
		this->InputModule->Initialize();
		this->TimeModule->Initialize();
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
};

Game::Game() : _pImpl(new Game::Impl(*this)) { }
Game::~Game() = default;

void Game::Run()
{
	_pImpl->Run();
}

void Game::Exit()
{
	_pImpl->IsExiting = true;
}

IGameWindow& Game::GetWindow() const
{
	return _pImpl->GraphicsModule->GetGameWindow();
}

IGraphicsContext& Game::GetGraphicsContext() const
{
	return _pImpl->GraphicsModule->GetGraphicsDevice();
}

// TODO: instead of this, implementing only specific template stuff's could be better (though not sure if possible, since virtual etc)
IModule& Game::GetModuleInner(const type_info& typeInfo) const
{
	if (typeInfo == typeid(GraphicsModule))
	{
		return *(_pImpl->GraphicsModule.get());
	}
	else if (typeInfo == typeid(InputModule))
	{
		return *(_pImpl->InputModule.get());
	}
	else if (typeInfo == typeid(TimeModule))
	{
		return *(_pImpl->TimeModule.get());
	}

	throw std::logic_error("Not implemented yet/invalid type");
}