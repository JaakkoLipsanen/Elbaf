#pragma once
#include "InputModule.h"
#include <Input\KeyboardState.h>
#include <system_error>
#include <Core\Diagnostics\Logger.h>
#include <algorithm>
#include <Core\Array.h>
#include <Input\BaseInputModule.h>

struct CustomKeyboardState : public KeyboardState
{
	void SetValue(KeyCode keyCode, bool value)
	{
		_isPressed[static_cast<int>(keyCode)] = value;
	}
};

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
	std::unique_ptr<CustomKeyboardState> CurrentKeyboardState;
	std::unique_ptr<CustomKeyboardState> PreviousKeyboardState;

	Impl() : CurrentKeyboardState(new CustomKeyboardState), PreviousKeyboardState(new CustomKeyboardState) { }
};


GLFW::InputModule::InputModule(Engine& engine) : BaseInputModule(engine), _pImpl()
{
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->PreviousKeyboardState->SetValue(static_cast<KeyCode>(i), false);
		_pImpl->CurrentKeyboardState->SetValue(static_cast<KeyCode>(i), false);
	}
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
	// Mouse Buttons
/*	std::swap(OldMouseButtons, MouseButtons);
	for (int i = 0; i < MouseButtonCount; i++)
	{
		MouseButtons[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
	} */

	std::swap(_pImpl->PreviousKeyboardState, _pImpl->CurrentKeyboardState);
	for (int i = 0; i < KeyboardState::KeyCount; i++)
	{
		_pImpl->CurrentKeyboardState->SetValue(static_cast<KeyCode>(i), true);
	}

	// Keys
	//std::swap(OldKeys, Keys);
	//for (int i = 0; i < KeyCount; i++)
	{
	//	Keys[i] = glfwGetKey(window, KeyCodeToGLFWKey(static_cast<KeyCode>(i))) == GLFW_PRESS;
	}
}

void GLFW::InputModule::EndFrame()
{

}