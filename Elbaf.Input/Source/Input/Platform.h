#pragma once
#include <memory>
#include <Input\IInputModule.h>

namespace Platform
{
	namespace Input
	{
		std::unique_ptr<IInputModule> CreateDefaultInputModule(Engine& engine);
	}
}
