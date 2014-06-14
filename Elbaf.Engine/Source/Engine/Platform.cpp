#include "Platform.h"
#include <Core\Engine.h>

std::unique_ptr<TimeModule> Platform::Engine::CreateTimeModule(IEngine& engine)
{
	return std::unique_ptr<TimeModule>(new TimeModule(engine));
}