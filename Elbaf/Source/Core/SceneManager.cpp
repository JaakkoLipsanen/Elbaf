#include "SceneManager.h"
#include "Diagnostics\Ensure.h"

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
	Ensure::NotNull(newScene.get());
	if (_currentScene.get() != nullptr)
	{
		_currentScene->OnExiting();
	}

	_currentScene.reset();
	_currentScene = std::move(newScene);
	_currentScene->Initialize();
}

void SceneManager::Render()
{
	_currentScene->Render();
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}