#include <Input\IInputModule.h>
#include <Input\Input.h>
IInputModule::IInputModule(IEngine& engine) : IModule(engine)
{
	Input::RegisterInputModule(this);
}

IInputModule::~IInputModule()
{
	Input::UnregisterInputModule();
}