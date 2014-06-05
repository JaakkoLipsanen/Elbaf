#include "Game.h"
#include <Diagnostics\Ensure.h>
#include <Graphics\GraphicsDevice.h>

static Game* Instance;

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

// meh!!
Game::Game()
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
	this->PreUpdate();
	// Update all systems (probably only scene manager for now)
	this->PostUpdate();

	this->PreRender();
	// Render the scene (how the heck will I do this...)
	this->PostRender();

	_graphicsDevice->SwapBuffers();
	glfwPollEvents();
}

void Game::Exit()
{
	_isExiting = true;
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

Game::~Game()
{
}
