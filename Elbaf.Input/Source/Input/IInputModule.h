#pragma once
#include <Core\IModule.h>
#include <memory>
#include <Input\MouseState.h>

class type_info;
class IInputSystem;
struct KeyboardState;

class IInputModule : public IModule
{
public:
	explicit IInputModule(Engine& engine);
	virtual ~IInputModule();

	virtual const KeyboardState& GetKeyboardState() = 0;
	virtual const KeyboardState& GetPreviousKeyboardState() = 0;
	virtual const MouseState& GetMouseState() = 0;
	virtual const MouseState& GetPreviousMouseState() = 0;
};