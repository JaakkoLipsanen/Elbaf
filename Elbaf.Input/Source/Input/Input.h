#include <Input\KeyCode.h>
#include <Input\MouseButton.h>
#include <Math\Vector.h>
#include <Input\IInputModule.h>

namespace Input
{
	// TODO: add events!  glfwSetKeyCallback, glfwSetCharCallback, glfwSetMouseButtonCallback etc etc
	// todo: make Vector2 class and then add MousePosition, PreviousMousePos & MouseDelta
	bool IsKeyPressed(KeyCode keyCode);
	bool WasKeyPressed(KeyCode keyCode);
	bool IsNewKeyPress(KeyCode keyCode);

	bool IsMouseButtonPressed(MouseButton mouseButton);
	bool WasMouseButtonPressed(MouseButton mouseButton);
	bool IsNewMouseButtonPress(MouseButton mouseButton);

//	bool IsMouseInsideWindow();
	int GetScrollWheelDelta();

	Vector2f GetMousePosition();
	Vector2f GetPreviousMousePosition();
	Vector2f GetMousePositionDelta();

	void RegisterInputModule(IInputModule* inputModule);
	void UnregisterInputModule();
}