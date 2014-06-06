#include "DefaultScene.h"
#include <Core\Game.h>
#include <Core\Input.h>

DefaultScene::DefaultScene()
{
}

void DefaultScene::Update()
{
}

void DefaultScene::Initialize()
{
}

void DefaultScene::Render()
{
	_graphicsDevice.Clear(Color::RoyalBlue);
	if (Input::IsKeyPressed(KeyCode::LeftShift))
	{
		_graphicsDevice.Clear(Color::Red);
	}
}

DefaultScene::~DefaultScene()
{
}
