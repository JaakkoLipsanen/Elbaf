#include <Input\Input.h>

#include <Diagnostics\Ensure.h>
#include <Input\IInputModule.h>
#include <Input\KeyboardState.h>
#include <Input\MouseState.h>
#include <Core\IEngine.h>

// todo: make 'Input' use IEngine::GetModule<IInputModule> instead?
static IInputModule& GetInputModule()
{
	return IEngine::GetInstance().GetModule<IInputModule>();
}

// keyboard
bool Input::IsKeyPressed(KeyCode keyCode)
{
	return GetInputModule().GetKeyboardState().IsKeyPressed(keyCode);
}

bool Input::WasKeyPressed(KeyCode keyCode)
{
	return GetInputModule().GetPreviousKeyboardState().IsKeyPressed(keyCode);
}

bool Input::IsNewKeyPress(KeyCode keyCode)
{
	return Input::IsKeyPressed(keyCode) && !Input::WasKeyPressed(keyCode);
}

// mouse
bool Input::IsMouseButtonPressed(MouseButton mouseButton)
{
	return GetInputModule().GetMouseState().IsButtonPressed(mouseButton);
}

bool Input::WasMouseButtonPressed(MouseButton mouseButton)
{
	return GetInputModule().GetPreviousMouseState().IsButtonPressed(mouseButton);
}

bool Input::IsNewMouseButtonPress(MouseButton mouseButton)
{
	return Input::IsMouseButtonPressed(mouseButton) && !Input::WasMouseButtonPressed(mouseButton);
}

// other mouse
int Input::GetScrollWheelDelta()
{
	return GetInputModule().GetMouseState().ScrollWheelDelta;
}

Vector2f Input::GetMousePosition()
{
	return GetInputModule().GetMouseState().MousePosition;
}

Vector2f Input::GetPreviousMousePosition()
{
	return GetInputModule().GetPreviousMouseState().MousePosition;
}

Vector2f Input::GetMousePositionDelta()
{
	return Input::GetMousePosition() - Input::GetPreviousMousePosition();
}