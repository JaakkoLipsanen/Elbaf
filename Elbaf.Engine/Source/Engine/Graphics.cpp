#include <Engine/Graphics.h>
#include <Engine/Game.h>
#include <Graphics/GraphicsModule.h>

GraphicsContext& Graphics::GetContext()
{
	return Game::GetInstance().GetGraphicsContext();
}