#include "TestScene.h"
#include <Engine/Game.h>
#include <Engine/ICamera.h>
#include "DefaultCamera.h"
#include "Terrain.h"
#include <Content/Content.h>
#include <Graphics/Texture.h>
#include "Skybox.h"
#include <Graphics/TextureHelper.h>
#include <Core/HsvColor.h>
#include <Engine/Stopwatch.h>
#include <memory>
#include <Input/Input.h>
#include <Engine/ISceneManager.h>

void TestScene::OnEntering()
{
	auto& graphicsContext = this->GetGame().GetGraphicsContext();
	_renderer.reset(new Renderer(graphicsContext));
	_camera.reset(new DefaultCamera);
	_renderer->SetCamera(_camera.get());

	this->CreateObjects();


	_font = Content::LoadFont(this->GetGame().GetGraphicsContext(), "F:\\Users\\Jaakko\\Desktop\\ArvoRegular.ttf", 32);
	//_fontRenderer.reset(new FontRenderer(this->GetGame().GetGraphicsContext()));
}

void TestScene::PostUpdate()
{
	_camera->Update();
	_skybox->Position = _camera->GetPosition();
	_renderer->PostUpdate();

	if (Input::IsNewKeyPress(KeyCode::Space))
	{
		this->GetSceneManager().LoadScene(std::unique_ptr<TestScene>(new TestScene));
	}
}

void TestScene::PostRender()
{
	_renderer->Render();
	//_fontRenderer->DrawText2D(*_font, "Vertices: " + std::to_string(_renderer->GetFrameVertexCount()), Vector2f(Screen::GetSize().Width - 8, 8), Color::White * 0.5f, TextCorner::TopRight);
}

void TestScene::CreateObjects()
{
	auto& graphicsContext = this->GetGame().GetGraphicsContext();

	/* Terrain */
	std::shared_ptr<Texture2D> blankPixel = std::move(TextureHelper::CreateBlankTexture(graphicsContext));

	/* Skybox */
	Skybox skybox(graphicsContext);
	skybox.Generate();

	std::shared_ptr<Texture2D> skyTexture = std::move(Content::LoadTexture("F:/Users/Jaakko/Desktop/Skybox1.png"));
	std::shared_ptr<Material> skyboxMaterial = std::make_shared<Material>(skyTexture);
	skyboxMaterial->Tint = Color::White;

	_skybox = std::make_shared<RenderObject>(skybox.Mesh, skyboxMaterial, _camera->GetPosition());
	_skybox->UseDepth = false;
	_skybox->UseCulling = false;
	_skybox->RenderOrder = -1000;

	_renderer->AddObject(_skybox);

	auto cubeMesh = FloatingCube::CreateMesh(graphicsContext);
	auto floorMaterial = std::make_shared<Material>(blankPixel, Color::White, MaterialType::Terrain);
	floorMaterial->Tint = Color::White;

	auto floor = std::make_shared<RenderObject>(cubeMesh, floorMaterial, Vector3f::Zero);
	floor->Scale = Vector3f(1000, 1, 1000);
	_renderer->AddObject(floor);

	auto cubeMaterial = std::make_shared<Material>(blankPixel, Color::White, MaterialType::Terrain);
	auto cube = std::make_shared<RenderObject>(cubeMesh, cubeMaterial, Vector3f::Zero);
	cube->Scale = Vector3f(25, 50, 25);
	_renderer->AddObject(cube);

	/*for (int i = 0; i < 8; i++)
	{
		FloatingCube cube2(
			graphicsContext,
			Vector3f(Global::Random.NextFloat(-500, 500) * (Global::Random.NextBoolean() ? 1 : -1), Global::Random.NextFloat(80, 350), Global::Random.NextFloat(-500, 500) * (Global::Random.NextBoolean() ? 1 : -1)),
			Vector3f::One * Global::Random.NextFloat(20, 60));

		auto cubeMaterial2 = std::make_shared<Material>(blankPixel, Color::White, MaterialType::Terrain);
		cubeMaterial2->Tint = HsvColor(Global::Random.NextFloat(0, 360), 0.8f, 0.8f).ToRgb();
		auto renderObject = std::make_shared<RenderObject>(cubeMesh, cubeMaterial2, Vector3f::Zero);
		cube2.SetRenderHandle(renderObject);

		_renderer->AddObject(renderObject);
	}*/
}