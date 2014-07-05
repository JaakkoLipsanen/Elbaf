#include <Engine/Scene.h>

Scene::Scene() { }
Scene::~Scene() { }

void Scene::Initialize()
{
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