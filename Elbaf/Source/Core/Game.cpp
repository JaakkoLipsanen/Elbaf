#include "Game.h"
#include <Diagnostics\Ensure.h>
#include <Graphics\GraphicsDevice.h>
#include <Diagnostics\Logger.h>
#include "Graphics\Graphics.h"
#include "Graphics\GameWindow.h"
static Game* Instance;

// meh!!
Game::Game() : _sceneManager(), _inputManager()
{
	if (Instance != nullptr)
	{
		Logger::LogError("Fatal Error: A instance of Game is already creating - aborting");
		Instance->Exit();
		return;
	}

	Instance = this;
}

void Game::Run()
{
	Ensure::False(_hasStarted);
	_hasStarted = true;

	this->InitializeGraphics();
	this->InitializeSystems();
	Logger::LogMessage("Running Game...");
	while (!_window->GetShouldClose() && !_isExiting)
	{
		this->Tick();
	}

	this->OnExiting();
	this->Exiting();

	_graphicsDevice->Terminate();
	Logger::LogMessage("Game Exited!");
}

void Game::Tick()
{
	// EEK! This was after the updating/rendering in tutorials etc, but it seems to me like it's wiser for it to be before...
	glfwPollEvents();
	_inputManager.Update();

	this->PreUpdate();
	_sceneManager.Update();
	// Update all systems (probably only scene manager for now)
	this->PostUpdate();

	this->PreRender();
	_sceneManager.Render();
	// Render the scene (how the heck will I do this...)
	this->PostRender();

	_graphicsDevice->SwapBuffers();
	_inputManager.OnFrameEnded();
}


Game::~Game() { }

void Game::Exit()
{
	_isExiting = true;
}

void Game::InitializeSystems()
{
	_sceneManager.ChangeScene(this->CreateDefaultScene());
	_inputManager.Initialize();
}

void Game::InitializeGraphics()
{
	Logger::LogMessage("Initializing Graphics...");
	int width, height;
	this->SetupGraphics(&width, &height);
	_graphicsDevice.reset(new GraphicsDevice(*this));
	_window.reset(new GameWindow({ width, height }, "Game"));

	if (!_window->IsCreated())
	{
		throw new std::logic_error("Couldn't create GLFW window!");
	}

	_window->MakeContextCurrent();
	_graphicsDevice->Initialize();
	Logger::LogMessage("Initialized Graphics!");
}


// default implementation, this is virtual
void Game::SetupGraphics(int* width, int* height)
{
	*width = 1280;
	*height = 720;
}

GameWindow& Game::GetWindow() const
{
	return *(_window.get());
}

GraphicsDevice& Game::GetGraphicsDevice() const
{
	return *(_graphicsDevice.get());
}

Game& Game::GetInstance()
{
	if (Instance == nullptr)
	{
		throw new std::logic_error("Game is not initialized yet");
	}

	return *Instance;
}