#include "KeyboardState.h"
#include <memory>

bool KeyboardState::IsKeyPressed(KeyCode keyCode)
{
	return _isPressed[static_cast<int>(keyCode)];
}

KeyboardState const KeyboardState::Copy()
{
	KeyboardState copy = *this; // is this necessary...?
	return copy;
}