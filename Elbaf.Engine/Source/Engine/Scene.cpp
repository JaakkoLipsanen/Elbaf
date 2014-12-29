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