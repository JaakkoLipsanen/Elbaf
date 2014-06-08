#pragma once
#include <Math\Vector.h>
#include "MouseButton.h"

struct MouseState
{
	bool IsMouseButtonPressed(MouseButton mouseButton);
	bool WasMouseButtonPressed(MouseButton mouseButton);
	bool IsNewMouseButtonPress(MouseButton mouseButton);

	bool IsMouseInsideWindow();
	float GetScrollWheelDelta();
	Vector2f GetMousePosition();

	static const int ButtonCount = 3; // middle, left & right. not supporting other mouse buttons for now (GLFW supports up to 8)
};
