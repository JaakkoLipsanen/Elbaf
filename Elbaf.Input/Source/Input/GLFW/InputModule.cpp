#pragma once
#include "InputModule.h"
#include <Input\KeyboardState.h>
#include <system_error>
#include <Core\Diagnostics\Logger.h>
#include <algorithm>
#include <Core\Array.h>
#include <Input\BaseInputModule.h>
#include <Core\Engine.h>
#include <GLFW\glfw3.h>
#include <Core\IGameWindow.h>
#include <Math\Vector.h>
#include <Input\MouseButton.h>
#include <Input\MouseState.h>
#include <Math\Vector.h>

static int LatestScrollWheelValue = 0;
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
		this->CurrentMouseState->ScrollWheelDelta = (int)yOffset;
	}
};

GLFW::InputModule::InputModule(Engine& engine) : BaseInputModule(engine), _pImpl(new GLFW::InputModule::Impl())
{
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->PreviousKeyboardState->IsPressed[i] = false; // SetValue(static_cast<KeyCode>(i), false);
		_pImpl->CurrentKeyboardState->IsPressed[i] = false; //  SetValue(static_cast<KeyCode>(i), false);
	}

	for (int i = 0; i < MouseState::ButtonCount; i++)
	{
		_pImpl->CurrentMouseState->IsPressed[0] = false;
		_pImpl->PreviousMouseState->IsPressed[0] = false;
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
		_pImpl->CurrentMouseState->IsPressed[i] = (glfwGetMouseButton(window, i) == GLFW_PRESS);
	} 

	std::swap(_pImpl->PreviousKeyboardState, _pImpl->CurrentKeyboardState);
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->CurrentKeyboardState->IsPressed[i] = glfwGetKey(window, KeyCodeToGLFWKey(static_cast<KeyCode>(i)));
	}


	// Mouse Buttons
	//std::swap(OldKeys, Keys);
	//for (int i = 0; i < KeyCount; i++)
	{
	//	Keys[i] = glfwGetKey(window, KeyCodeToGLFWKey(static_cast<KeyCode>(i))) == GLFW_PRESS;
	}
}

MouseState const& GLFW::InputModule::GetMouseState()
{
	return *_pImpl->CurrentMouseState;
}

MouseState const& GLFW::InputModule::GetPreviousMouseState()
{
	return *_pImpl->PreviousMouseState;
}

static void OnScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	LatestScrollWheelValue = (int)yOffset;
}

void GLFW::InputModule::Initialize()
{
	_pImpl->GlfwWindow = static_cast<GLFWwindow*>(_engine.GetWindow()->GetInternalHandle());
	glfwSetScrollCallback(_pImpl->GlfwWindow, OnScrollWheelCallback);
	/*ScrollWheelInput += Event<void(int)>::FunctionPointer([this](int x)
	{
		this->
	}); */
}

void GLFW::InputModule::Terminate()
{
	glfwSetScrollCallback(_pImpl->GlfwWindow, nullptr);
}

void GLFW::InputModule::EndFrame()
{

}