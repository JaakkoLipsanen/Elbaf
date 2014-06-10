#pragma once
#include <Math\Vector.h>
#include "MouseButton.h"

struct MouseState
{
	bool IsMouseButtonPressed(MouseButton mouseButton) const
	{
		return IsPressed[static_cast<int>(mouseButton)];
	}

	float GetScrollWheelDelta() const
	{
		return ScrollWheelDelta;
	}

	Vector2f GetMousePosition() const
	{
		return MousePosition;
	}

	static const int ButtonCount = 3; // middle, left & right. not supporting other mouse buttons for now (GLFW supports up to 8)
	bool IsPressed[ButtonCount];
	int ScrollWheelDelta;
	Vector2f MousePosition;
};
