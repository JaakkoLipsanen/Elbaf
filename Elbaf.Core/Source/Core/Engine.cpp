#include "Engine.h"
#include <Core\Diagnostics\Ensure.h>

static IEngine* _instance = nullptr;
IEngine::IEngine()
{
	Ensure::Null(_instance); // must be null
	_instance = this;
}

IEngine& IEngine::GetInstance()
{
	Ensure::NotNull(_instance, "Engine is not yet initialized");
	return *_instance;
}