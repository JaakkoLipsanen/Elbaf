#include "Scene.h"
#include <Core\Game.h>

Scene::Scene() : _game(Game::GetInstance()), _graphicsDevice(_game.GetGraphicsDevice())
{
}