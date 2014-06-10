#include "KeyboardState.h"
#include <memory>

bool KeyboardState::IsKeyPressed(KeyCode keyCode) const
{
	return IsPressed[static_cast<int>(keyCode)];
}

KeyboardState const KeyboardState::Copy() const
{
	KeyboardState copy = *this; // is this necessary...?
	return copy;
}