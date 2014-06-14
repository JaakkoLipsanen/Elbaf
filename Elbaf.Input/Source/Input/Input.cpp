#include "Input.h"
#include <Input\KeyboardState.h>
#include <Input\IInputModule.h>
#include <Core\Diagnostics\Ensure.h>

// todo: make 'Input' use IEngine::GetModule<IInputModule> instead?
static IInputModule* _inputModule = nullptr;
void Input::RegisterInputModule(IInputModule* inputModule)
{
	_inputModule = inputModule;
}

void Input::UnregisterInputModule()
{
	_inputModule = nullptr;
}

// keyboard
bool Input::IsKeyPressed(KeyCode keyCode)
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetKeyboardState().IsKeyPressed(keyCode);
}

bool Input::WasKeyPressed(KeyCode keyCode)
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetPreviousKeyboardState().IsKeyPressed(keyCode);
}

bool Input::IsNewKeyPress(KeyCode keyCode)
{
	Ensure::NotNull(_inputModule);
	return Input::IsKeyPressed(keyCode) && !Input::WasKeyPressed(keyCode);
}

// mouse
bool Input::IsMouseButtonPressed(MouseButton mouseButton)
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetMouseState().IsButtonPressed(mouseButton);
}

bool Input::WasMouseButtonPressed(MouseButton mouseButton)
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetPreviousMouseState().IsButtonPressed(mouseButton);
}

bool Input::IsNewMouseButtonPress(MouseButton mouseButton)
{
	Ensure::NotNull(_inputModule);
	return Input::IsMouseButtonPressed(mouseButton) && !Input::WasMouseButtonPressed(mouseButton);
}

// other mouse
int Input::GetScrollWheelDelta()
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetMouseState().ScrollWheelDelta;
}

Vector2f Input::GetMousePosition()
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetMouseState().MousePosition;
}

Vector2f Input::GetPreviousMousePosition()
{
	Ensure::NotNull(_inputModule);
	return _inputModule->GetPreviousMouseState().MousePosition;
}

Vector2f Input::GetMousePositionDelta()
{
	Ensure::NotNull(_inputModule);
	return Input::GetMousePosition() - Input::GetPreviousMousePosition();
}