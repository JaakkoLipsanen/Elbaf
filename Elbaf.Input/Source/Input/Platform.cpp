#include "Platform.h"
#include <Input\GLFW\InputModule.h>
#include <Input\IInputModule.h>
#include <Core\Diagnostics\Logger.h>
#include <Core\Engine.h>

std::unique_ptr<IInputModule> Platform::Input::CreateDefaultInputModule(Engine& engine)
{
	return std::unique_ptr<IInputModule>(new GLFW::InputModule(engine));
}