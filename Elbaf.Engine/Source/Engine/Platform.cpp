#include "Platform.h"

#include <Core\IEngine.h>
#include <Engine\TimeModule.h>

std::unique_ptr<TimeModule> Platform::Engine::CreateTimeModule(IEngine& engine)
{
	return std::unique_ptr<TimeModule>(new TimeModule(engine));
}