#pragma once
#include "KeyCode.h"
#include <Input\IInputModule.h>

struct KeyboardState
{
	static const int KeyCount = static_cast<int>(KeyCode::RightSuper) + 1;

	virtual ~KeyboardState() = default;
	bool IsKeyPressed(KeyCode keyCode);
	const KeyboardState Copy();

protected:
	bool _isPressed[KeyCount];
};
