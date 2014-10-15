#include "TestScene.h"
#include <Engine/Game.h>
#include <Engine/ICamera.h>
#include "DefaultCamera.h"
#include "Terrain.h"
#include <Content/Content.h>
#include <Graphics/ITexture.h>
#include "Skybox.h"
#include <Graphics/TextureHelper.h>
#include <Core/HsvColor.h>
#include <Engine/Stopwatch.h>

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
	for (auto& cube : _floatingCubes)
	{
		cube.Update();
	}

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
	std::shared_ptr<Material> terrainMaterial = std::make_shared<Material>(blankPixel, Color::White, MaterialType::Terrain);
	terrainMaterial->Tint = Color::White; // Color(40, 40, 40);

	Terrain terrain(graphicsContext);
	Stopwatch sw("Terrain gen");
	terrain.Generate();
	sw.Stop();

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			auto terrainRenderObject = std::make_shared<RenderObject>(terrain.Mesh, terrainMaterial, Vector3f::Zero);
			terrainRenderObject->Scale = Vector3f(4, 1, 4);
			terrainRenderObject->Position = Vector3f(x, 0, y) * 4 * 256;
			_renderer->AddObject(terrainRenderObject);
		}
	}

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

	 _renderer->AddObject(_skybox);
	 
	auto cubeMesh = FloatingCube::CreateMesh(graphicsContext);
	for (int i = 0; i < 50; i++)
	{
		_floatingCubes.emplace_back(
			graphicsContext,
			Vector3f(Global::Random.NextFloat(300, 4000) * (Global::Random.NextBoolean() ? 1 : -1), Global::Random.NextFloat(-350, 550), Global::Random.NextFloat(300, 4000) * (Global::Random.NextBoolean() ? 1 : -1)),
			Vector3f::One * Global::Random.NextFloat(20, 160));

		auto cubeMaterial = std::make_shared<Material>(blankPixel);
		cubeMaterial->Tint = HsvColor(Global::Random.NextFloat(0, 360), 0.8f, 0.8f).ToRgb();
		auto renderObject = std::make_shared<RenderObject>(cubeMesh, cubeMaterial, Vector3f::Zero);
		_floatingCubes[_floatingCubes.size() - 1].SetRenderHandle(renderObject);

		_renderer->AddObject(renderObject);
	} 
}