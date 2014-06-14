#include "Screen.h"
#include <Graphics\IGraphicsDevice.h>
#include <Core\IGameWindow.h>
#include <Core\Engine.h>
#include <Graphics\IGraphicsModule.h>

static IGraphicsDevice* GetGameWindow()
{
	return IEngine::GetInstance().GetModule<IGraphicsModule>()->GetGraphicsDevice();
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