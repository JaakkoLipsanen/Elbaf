#pragma once
#include <Math\Vector.h>

enum class KeyCode;
enum class MouseButton;
class IInputModule;

namespace Input
{
	// TODO: add events!  glfwSetKeyCallback, glfwSetCharCallback, glfwSetMouseButtonCallback etc etc
	bool IsKeyPressed(KeyCode keyCode);
	bool WasKeyPressed(KeyCode keyCode);
	bool IsNewKeyPress(KeyCode keyCode);

	bool IsMouseButtonPressed(MouseButton mouseButton);
	bool WasMouseButtonPressed(MouseButton mouseButton);
	bool IsNewMouseButtonPress(MouseButton mouseButton);

	int GetScrollWheelDelta();

	Vector2f GetMousePosition();
	Vector2f GetPreviousMousePosition();
	Vector2f GetMousePositionDelta();
}