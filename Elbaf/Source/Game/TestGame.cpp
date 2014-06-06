#include "TestGame.h"
#include <memory>
#include "Core\Scene.h"
#include <Game\DefaultScene.h>


TestGame::TestGame()
{
}

std::unique_ptr<Scene> TestGame::CreateDefaultScene()
{
	return std::unique_ptr<Scene>(new DefaultScene); // std::make_unique<Scene>(new DefaultScene);
}

TestGame::~TestGame()
{
}