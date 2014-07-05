#include <Engine\Screen.h>

#include <Graphics\IGraphicsContext.h>
#include <Graphics\GraphicsModule.h>
#include <Core\IEngine.h>

static IGraphicsContext& GetGraphicsContext()
{
	return IEngine::GetInstance().GetModule<GraphicsModule>().GetGraphicsContext();
}

Size Screen::GetSize()
{
	return GetGraphicsContext().GetResolution();
}

int Screen::GetWidth()
{
	return Screen::GetSize().Width;
}

int Screen::GetHeight()
{
	return Screen::GetSize().Height;
}