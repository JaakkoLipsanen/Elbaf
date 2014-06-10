#pragma once
#include "KeyCode.h"
#include <Input\IInputModule.h>

struct KeyboardState
{
	bool IsKeyPressed(KeyCode keyCode) const
	{
		return this->IsPressed[static_cast<int>(keyCode)];
	}

	static const int KeyCount = static_cast<int>(KeyCode::RightSuper) + 1;
	bool IsPressed[KeyCount];
};
