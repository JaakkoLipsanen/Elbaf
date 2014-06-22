#pragma once
#include <memory>
#include <Core\IModule.h>

struct KeyboardState;
struct MouseState;

class IInputModule : public IModule
{
public:
	explicit IInputModule(IEngine& engine);
	virtual ~IInputModule();

	virtual const KeyboardState& GetKeyboardState() = 0;
	virtual const KeyboardState& GetPreviousKeyboardState() = 0;
	virtual const MouseState& GetMouseState() = 0;
	virtual const MouseState& GetPreviousMouseState() = 0;
};