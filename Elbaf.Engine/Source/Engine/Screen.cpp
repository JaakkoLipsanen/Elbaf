#include <Engine\Screen.h>
#include <Graphics\IGraphicsContext.h>
#include <Core\IGameWindow.h>
#include <Core\Engine.h>
#include <Graphics\GraphicsModule.h>

static IGraphicsContext* GetGameWindow()
{
	return IEngine::GetInstance().GetModule<GraphicsModule>()->GetGraphicsDevice();
}

Size Screen::GetSize()
{
	return GetGameWindow()->GetResolution();
}

int Screen::GetWidth()
{
	return Screen::GetSize().Width;
}

int Screen::GetHeight()
{
	return Screen::GetSize().Height;
}