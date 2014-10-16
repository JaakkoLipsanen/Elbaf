#pragma once
#include <Engine/Scene.h>
#include <memory>
#include "Renderer.h"
#include "DefaultCamera.h"
#include <FloatingCube.h>

#include <Graphics/FontRenderer.h>
#include <Graphics/Font.h>

class TestScene : public Scene
{
protected:
	void OnEntering() override;
	void PostUpdate() override;
	void PostRender() override;

private:
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<DefaultCamera> _camera;
	std::shared_ptr<RenderObject> _skybox;
	std::vector<FloatingCube> _floatingCubes;

	std::unique_ptr<Font> _font;
	std::unique_ptr<FontRenderer> _fontRenderer;

	void CreateObjects();
};