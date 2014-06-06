#include "DefaultScene.h"
#include <Core\Game.h>
#include <Core\Input.h>
#include "Core\Common.h"
#include <Core\Extensions\GLM.Extensions.h>

#include <glm/gtc/matrix_transform.hpp>
#include <Diagnostics\Logger.h>

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
	Logger::LogMessage(Input::GetMousePosition());
	_graphicsDevice.Clear(Color::RoyalBlue);
	if (Input::IsKeyPressed(KeyCode::LeftShift))
	{
		_graphicsDevice.Clear(Color::Red);
	}
}

DefaultScene::~DefaultScene()
{
}
