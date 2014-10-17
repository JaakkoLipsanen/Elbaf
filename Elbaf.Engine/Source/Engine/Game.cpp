#include <Engine\Game.h>

#include <Diagnostics\Logger.h>
#include <Diagnostics\Ensure.h>
#include <Core\IGameWindow.h>
#include <Engine\Platform.h>
#include <Engine\TimeModule.h>
#include <Graphics\GraphicsModule.h>
#include <Core\WindowDescription.h>
#include <Input\InputModule.h>
#include <Engine\Scene.h>
#include <Engine/SceneModule.h>
#include <Content/ContentModule.h>

class Game::Impl
{
public:
	explicit Impl(Game& game) : _game(game) { }

	bool IsRunning = false;
	bool IsExiting = false;
	std::unique_ptr<GraphicsModule> GraphicsModule;
	std::unique_ptr<InputModule> InputModule;
	std::unique_ptr<TimeModule> TimeModule;
	std::unique_ptr<SceneModule> SceneModule;
	std::unique_ptr<ContentModule> ContentModule;

	void Run()
	{
		Ensure::False(this->IsRunning);
		this->IsRunning = true;

		// initialize!
		this->InitializeModules();
		_game.Initialize();

		// run!
		Logger::LogMessage("Running Game..");
		while (!this->GraphicsModule->GetGameWindow().IsExiting() || this->IsExiting)
		{
			// todo: fps limiting or something? i mean 60fps lock etc. and fixedupdate?
			this->Tick();
		}

		// exit!
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
		this->SceneModule.reset(new ::SceneModule(_game));
		this->ContentModule.reset(new ::ContentModule(_game));

		this->GraphicsModule->Initialize();
		this->InputModule->Initialize();
		this->TimeModule->Initialize();
		this->SceneModule->Initialize();
		this->ContentModule->Initialize();

		this->SceneModule->LoadScene(_game.CreateDefaultScene());
	}

	void Tick()
	{
		this->GraphicsModule->RunMessagePump();

		this->BeginFrame();
		_game.PreUpdate();
		this->TimeModule->Update();
		this->GraphicsModule->Update();
		this->InputModule->Update();
		this->SceneModule->Update();
		this->ContentModule->Update();
		_game.PostUpdate();

		_game.PreRender();
		this->SceneModule->Render(); // todo: should rendering happen in SceneModule::Update? that would be a "more correct" approach maybe...? 
		_game.PostRender();

		this->EndFrame();
	}

	void BeginFrame()
	{
		_game.BeginFrame.Invoke();
		this->GraphicsModule->BeginFrame();
		this->InputModule->BeginFrame();
		this->TimeModule->BeginFrame();
		this->SceneModule->BeginFrame();
		this->ContentModule->BeginFrame();
	}

	void EndFrame()
	{
		this->GraphicsModule->EndFrame();
		this->InputModule->EndFrame();
		this->TimeModule->EndFrame();
		this->SceneModule->EndFrame();
		this->ContentModule->EndFrame();

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

GraphicsContext& Game::GetGraphicsContext() const
{
	return _pImpl->GraphicsModule->GetGraphicsContext();
}

Game& Game::GetInstance()
{
	return static_cast<Game&>(IEngine::GetInstance());
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
	else if (typeInfo == typeid(SceneModule))
	{
		return *(_pImpl->SceneModule.get());
	}
	else if (typeInfo == typeid(ContentModule))
	{
		return *(_pImpl->ContentModule.get());
	}

	throw std::logic_error("Not implemented yet/invalid type");
}