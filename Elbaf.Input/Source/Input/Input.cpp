#include <Input\Input.h>

#include <Diagnostics\Ensure.h>
#include <Input\InputModule.h>
#include <Input\KeyboardState.h>
#include <Input\MouseState.h>
#include <Core\IEngine.h>
#include <Input\IInputProvider.h>

static IInputProvider& GetInputProvider()
{
	return IEngine::GetInstance().GetModule<InputModule>().GetInputProvider();
}

// keyboard
bool Input::IsKeyPressed(KeyCode keyCode)
{
	return GetInputProvider().GetKeyboardState().IsKeyPressed(keyCode);
}

bool Input::WasKeyPressed(KeyCode keyCode)
{
	return GetInputProvider().GetPreviousKeyboardState().IsKeyPressed(keyCode);
}

bool Input::IsNewKeyPress(KeyCode keyCode)
{
	return Input::IsKeyPressed(keyCode) && !Input::WasKeyPressed(keyCode);
}

// mouse
bool Input::IsMouseButtonPressed(MouseButton mouseButton)
{
	return GetInputProvider().GetMouseState().IsButtonPressed(mouseButton);
}

bool Input::WasMouseButtonPressed(MouseButton mouseButton)
{
	return GetInputProvider().GetPreviousMouseState().IsButtonPressed(mouseButton);
}

bool Input::IsNewMouseButtonPress(MouseButton mouseButton)
{
	return Input::IsMouseButtonPressed(mouseButton) && !Input::WasMouseButtonPressed(mouseButton);
}

// other mouse
int Input::GetScrollWheelDelta()
{
	return GetInputProvider().GetMouseState().ScrollWheelDelta;
}

Vector2f Input::GetMousePosition()
{
	return GetInputProvider().GetMouseState().MousePosition;
}

Vector2f Input::GetPreviousMousePosition()
{
	return GetInputProvider().GetPreviousMouseState().MousePosition;
}

Vector2f Input::GetMousePositionDelta()
{
	return Input::GetMousePosition() - Input::GetPreviousMousePosition();
}