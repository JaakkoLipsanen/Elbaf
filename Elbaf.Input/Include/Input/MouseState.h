#pragma once
#include <Math\Vector.h>
#include "MouseButton.h"

// cpp?
struct MouseState
{
	bool IsButtonPressed(MouseButton mouseButton) const
	{
		return IsPressed[static_cast<int>(mouseButton)];
	}

	void SetValue(int index, bool value)
	{
		this->IsPressed[index] = value;
	}

	static const int ButtonCount = 3; // middle, left & right. not supporting other mouse buttons for now (GLFW supports up to 8)
	bool IsPressed[ButtonCount];
	int ScrollWheelDelta;
	Vector2f MousePosition;
};
