#include "IInputModule.h"
#include <Input\Input.h>
IInputModule::IInputModule(Engine& engine) : IModule(engine)
{
	Input::RegisterInputModule(this);
}

IInputModule::~IInputModule()
{
	Input::UnregisterInputModule();
}