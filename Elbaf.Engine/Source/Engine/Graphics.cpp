#include <Engine/Graphics.h>
#include <Engine/Game.h>
#include <Graphics/GraphicsModule.h>

IGraphicsContext& Graphics::GetContext()
{
	return Game::GetInstance().GetGraphicsContext();
}