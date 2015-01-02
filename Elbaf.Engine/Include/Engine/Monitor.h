#pragma once
#include <Graphics/IMonitor.h>

#include <memory>
#include <vector>

namespace Monitor
{
	std::unique_ptr<const IMonitor> GetPrimaryMonitor();
	std::vector<std::unique_ptr<const IMonitor>> GetAllMonitors();
}