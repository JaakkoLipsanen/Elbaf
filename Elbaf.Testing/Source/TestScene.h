#pragma once
#include <Engine/Scene.h>
#include <memory>
#include "TestRenderer.h"
#include "DefaultCamera.h"

class TestScene : public Scene
{
protected:
	void OnEntering() override;
	void PostUpdate() override;
	void PostRender() override;

private:
	std::unique_ptr<TestRenderer> _renderer;
	std::unique_ptr<DefaultCamera> _camera;
	std::shared_ptr<RenderObject> _skybox;


	void CreateObjects();
};