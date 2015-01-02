#include <Engine/Monitor.h>
#include <Engine/Game.h>
#include <Graphics/GraphicsModule.h>

std::unique_ptr<const IMonitor> Monitor::GetPrimaryMonitor()
{
	return Game::GetInstance().GetModule<GraphicsModule>().GetPrimaryMonitor();
}

std::vector<std::unique_ptr<const IMonitor>> Monitor::GetAllMonitors()
{
	return Game::GetInstance().GetModule<GraphicsModule>().GetAllMonitors();
}