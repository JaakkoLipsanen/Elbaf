#pragma once

struct KeyboardState;
struct MouseState;
class IInputProvider
{
public:
	IInputProvider() = default;
	virtual ~IInputProvider() = default;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Terminate() = 0;

	// TouchState maybe?
	// Get(Custom)InputSystem?
	virtual const KeyboardState& GetKeyboardState() const = 0;
	virtual const KeyboardState& GetPreviousKeyboardState() const = 0;
	virtual const MouseState& GetMouseState() const = 0;
	virtual const MouseState& GetPreviousMouseState() const = 0;

};