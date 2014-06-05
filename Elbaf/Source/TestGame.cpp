#include "TestGame.h"
#include <memory>
#include "Core\Scene.h"


TestGame::TestGame()
{
}

std::unique_ptr<Scene> TestGame::CreateDefaultScene()
{
	return nullptr;
}

TestGame::~TestGame()
{
}
