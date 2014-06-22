#pragma once
#include <memory>

class IEngine;
class TimeModule;
namespace Platform
{
	namespace Engine
	{
		void RunMessagePump();
		std::unique_ptr<TimeModule> CreateTimeModule(IEngine& engine);
	}
}