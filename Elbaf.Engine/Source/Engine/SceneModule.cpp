#include <Engine\SceneModule.h>
#include <Engine\Game.h>
#include <Engine\Scene.h>
#include <Diagnostics/Ensure.h>

SceneModule::SceneModule(Game& game) : IModule(game) { }
SceneModule::~SceneModule() = default;

void SceneModule::Initialize()
{
}

void SceneModule::Terminate()
{
}

void SceneModule::Update()
{
	Ensure::NotNull(_currentScene.get());
	_currentScene->UpdateInternal();
}

void SceneModule::Render()
{
	_currentScene->RenderInternal();
}

void SceneModule::LoadScene(std::unique_ptr<Scene> scene)
{
	if (_currentScene.get() != nullptr)
	{
		_currentScene->Terminate();
	}

	Ensure::NotNull(scene.get());
	_currentScene.reset(scene.release());

	Game* game = static_cast<Game*>(&_engine);
	_currentScene->Initialize(*game, *this);
}

Scene& SceneModule::GetCurrentScene()
{
	return *_currentScene;
}