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
	if (_nextSceneToLoad.get() != nullptr)
	{
		this->LoadNextScene();
	}

	Ensure::NotNull(_currentScene.get());
	_currentScene->UpdateInternal();
}

void SceneModule::Render()
{
	_currentScene->RenderInternal();
}

void SceneModule::LoadScene(std::unique_ptr<Scene> scene)
{
	_nextSceneToLoad = std::move(scene);
	if (_currentScene.get() == nullptr)
	{
		this->LoadNextScene();
	}
}

Scene& SceneModule::GetCurrentScene()
{
	return *_currentScene;
}

void SceneModule::LoadNextScene()
{
	Ensure::NotNull(_nextSceneToLoad.get(), "Next scene is null");
	if (_currentScene.get() != nullptr)
	{
		_currentScene->Terminate();
	}

	_currentScene.reset(_nextSceneToLoad.release());

	Game* game = static_cast<Game*>(&_engine);
	_currentScene->Initialize(*game, *this);
}