#pragma once
#include <memory>
#include <Core/Engine.h>
#include <Engine\TimeModule.h>

namespace Platform
{
	namespace Engine
	{
		void RunMessagePump();
		std::unique_ptr<TimeModule> CreateTimeModule(IEngine& engine);
	}
}