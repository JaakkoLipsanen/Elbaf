#include "TestScene.h"
#include <Engine/Game.h>
#include <Engine/ICamera.h>
#include "DefaultCamera.h"
#include "Terrain.h"
#include <Content/Content.h>
#include <Graphics/ITexture.h>
#include "Skybox.h"
#include <Graphics/TextureHelper.h>

void TestScene::OnEntering()
{
	auto& graphicsContext = this->GetGame().GetGraphicsContext();
	_renderer.reset(new TestRenderer(graphicsContext));
	_camera.reset(new DefaultCamera);
	_renderer->SetCamera(_camera.get());

	this->CreateObjects();
}

void TestScene::PostUpdate()
{
	_camera->Update();
	_skybox->Position = _camera->GetPosition();
	_renderer->PostUpdate();
}

void TestScene::PostRender()
{
	_renderer->Render();
}

void TestScene::CreateObjects()
{
	auto& graphicsContext = this->GetGame().GetGraphicsContext();

	/* Terrain */
	std::shared_ptr<ITexture2D> blankPixel = std::move(TextureHelper::CreateBlankTexture(graphicsContext));
	std::shared_ptr<Material> terrainMaterial = std::make_shared<Material>(blankPixel);
	terrainMaterial->Tint = Color::White; // Color(40, 40, 40);

	Terrain terrain(graphicsContext);
	terrain.Generate();
	_renderer->AddObject(std::make_shared<RenderObject>(terrain.Mesh, terrainMaterial, Vector3f::Zero));

	/* Skybox */
	Skybox skybox(graphicsContext);
	skybox.Generate();

	std::shared_ptr<ITexture2D> skyTexture = std::move(Content::LoadTexture("F:/Users/Jaakko/Desktop/Skybox1.png"));
	std::shared_ptr<Material> skyboxMaterial = std::make_shared<Material>(skyTexture);
	skyboxMaterial->Tint = Color::White;

	_skybox = std::make_shared<RenderObject>(skybox.Mesh, skyboxMaterial, _camera->GetPosition());
	_skybox->UseDepth = false;
	_skybox->UseCulling = false;
	_skybox->RenderOrder = -1000;

	//	_renderer->AddObject(_skybox);
}