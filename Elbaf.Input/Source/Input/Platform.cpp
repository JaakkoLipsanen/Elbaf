#include <Input\Platform.h>

#include <Input\GLFW\InputModule.h>
#include <Input\IInputModule.h>
#include <Diagnostics\Logger.h>
#include <Core\IEngine.h>

std::unique_ptr<IInputModule> Platform::Input::CreateDefaultInputModule(IEngine& engine)
{
	return std::unique_ptr<IInputModule>(new GLFW::InputModule(engine));
}