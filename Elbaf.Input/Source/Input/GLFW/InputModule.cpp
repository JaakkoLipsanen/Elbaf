#pragma once
#include "InputModule.h"

#include <GLFW\glfw3.h>
#include <algorithm>
#include <Input\KeyboardState.h>
#include <Diagnostics\Logger.h>
#include <Core\Array.h>
#include <Core\Engine.h>
#include <Core\IGameWindow.h>

static int KeyCodeToGLFWKey(KeyCode keyCode)
{
	struct Temp { KeyCode Key; int Value; bool operator <(const Temp& rhs) const { return Key < rhs.Key; } };
#define CREATE(x, y) Temp { KeyCode::##x##, y }

	// magic value from GLFW docs. Basically map end of all contigous key values to KeyCode, then binary-search
	static const Temp arr[] = {
		CREATE(Space, 32), CREATE(Minus, 45), CREATE(D9, 57), CREATE(Z, 90),
		CREATE(End, 269), CREATE(Pause, 284), CREATE(F12, 301), CREATE(RightSuper, 347) };

	auto start = arr;
	auto end = arr + Array::Length(arr);
	auto found = std::lower_bound(start, end, Temp{ keyCode });
	if (found >= end)
	{
		Logger::LogError("Input.cpp: KeyCodeToGLFWKey: Did you forget to update 'arr'?");
		throw new std::logic_error("Something is wrong. You probably need to update 'arr'");
	}

	int index = found->Value;
	return index - (static_cast<int>(found->Key) - static_cast<int>(keyCode));
}

struct GLFW::InputModule::Impl
{
	GLFWwindow* GlfwWindow;
	std::unique_ptr<KeyboardState> CurrentKeyboardState;
	std::unique_ptr<KeyboardState> PreviousKeyboardState;

	std::unique_ptr<MouseState> CurrentMouseState;
	std::unique_ptr<MouseState> PreviousMouseState;

	Impl() : CurrentKeyboardState(new KeyboardState), PreviousKeyboardState(new KeyboardState), CurrentMouseState(new MouseState), PreviousMouseState(new MouseState) { }

	void GLFWScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		this->CurrentMouseState->ScrollWheelDelta = static_cast<int>(yOffset);
	}
};

GLFW::InputModule::InputModule(IEngine& engine) : IInputModule(engine), _pImpl(new GLFW::InputModule::Impl())
{
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->PreviousKeyboardState->SetValue(i, false);
		_pImpl->CurrentKeyboardState->SetValue(i, false);
	}

	for (int i = 0; i < MouseState::ButtonCount; i++)
	{
		_pImpl->CurrentMouseState->SetValue(i, false);
		_pImpl->PreviousMouseState->SetValue(i, false);
	}

	_pImpl->CurrentMouseState->ScrollWheelDelta = 0;
	_pImpl->CurrentMouseState->MousePosition = Vector2f(0, 0);

	_pImpl->PreviousMouseState->ScrollWheelDelta = 0;
	_pImpl->PreviousMouseState->MousePosition = Vector2f(0, 0);
}

KeyboardState const& GLFW::InputModule::GetKeyboardState()
{
	return *_pImpl->CurrentKeyboardState;
}

KeyboardState const& GLFW::InputModule::GetPreviousKeyboardState()
{
	return *_pImpl->PreviousKeyboardState;
}

MouseState const& GLFW::InputModule::GetMouseState()
{
	return *_pImpl->CurrentMouseState;
}

MouseState const& GLFW::InputModule::GetPreviousMouseState()
{
	return *_pImpl->PreviousMouseState;
}

// okay. what is this? Basically, GLFW doesn't support polling scroll value, but instead only callbacks. and obviously, in C++ you can't subscribe a member-function to a callback that is meant for static callbacks.
// so yeah.. I have to do this instead.. yay...
static int LatestScrollWheelValue = 0;
static void OnScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	LatestScrollWheelValue = static_cast<int>(yOffset);
}

void GLFW::InputModule::Initialize()
{
	_pImpl->GlfwWindow = static_cast<GLFWwindow*>(_engine.GetWindow()->GetInternalHandle());
	glfwSetScrollCallback(_pImpl->GlfwWindow, OnScrollWheelCallback);

	// enable sticky keys. sticky keys means, that key press will be registered even if key has been pressed & released between frames. todo: make this into options?
	glfwSetInputMode(_pImpl->GlfwWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(_pImpl->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); // same for mouse buttons
}

void GLFW::InputModule::Terminate()
{
	glfwSetScrollCallback(_pImpl->GlfwWindow, nullptr);
}

void GLFW::InputModule::BeginFrame()
{
	GLFWwindow* window = _pImpl->GlfwWindow;

	// Mouse Buttons
	std::swap(_pImpl->PreviousMouseState, _pImpl->CurrentMouseState);

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	_pImpl->CurrentMouseState->MousePosition = Vector2f(x, y);
	_pImpl->CurrentMouseState->ScrollWheelDelta = LatestScrollWheelValue;
	LatestScrollWheelValue = 0;
	for (int i = 0; i < MouseState::ButtonCount; i++)
	{
		_pImpl->CurrentMouseState->SetValue(i, glfwGetMouseButton(window, i) == GLFW_PRESS);
	}

	std::swap(_pImpl->PreviousKeyboardState, _pImpl->CurrentKeyboardState);
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->CurrentKeyboardState->SetValue(i, glfwGetKey(window, KeyCodeToGLFWKey(static_cast<KeyCode>(i))) == GLFW_PRESS);
	}
}

void GLFW::InputModule::EndFrame()
{
}