#include <Engine/Scene.h>

Scene::Scene() { }
Scene::~Scene() { }

Game& Scene::GetGame()
{
	return *_game;
}

void Scene::Initialize(Game& game, SceneModule& sceneModule)
{
	_game = &game;
	this->OnEntering();
}

void Scene::Terminate()
{
	this->OnExiting();
}

void Scene::Update()
{
	this->PreUpdate();
	// 'Update'
	this->PostUpdate();
}

void Scene::Render()
{
	this->PreRender();
	// 'Render'
	this->PostRender();
}