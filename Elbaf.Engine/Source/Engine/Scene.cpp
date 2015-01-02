#include <Engine/Scene.h>
#include <Diagnostics/Ensure.h>
#include <Engine/SceneModule.h>

Scene::Scene() : _game(nullptr), _sceneModule(nullptr) { }
Scene::~Scene() { }

ISceneManager& Scene::GetSceneManager()
{
	Ensure::NotNull(_sceneModule, "Scene is not yet initialized!");
	return *_sceneModule;
}

Game& Scene::GetGame()
{
	Ensure::NotNull(_game, "Scene is not yet initialized!");
	return *_game;
}

void Scene::Initialize(Game& game, SceneModule& sceneModule)
{
	_game = &game;
	_sceneModule = &sceneModule;
	this->OnEntering();
}

void Scene::Terminate()
{
	this->OnExiting();
}

void Scene::UpdateInternal()
{
	this->PreUpdate();
	this->Update();
	this->PostUpdate();
}

void Scene::RenderInternal()
{
	this->PreRender();
	this->Render();
	this->PostRender();
}