#include "Input.h"
#include "Core\Game.h"
#include "Graphics\GameWindow.h"
#include "Core\Common.h"

#include <array>
#include <algorithm>
#include <GLFW\glfw3.h>

const static int MouseButtonCount = 8;
static bool* OldMouseButtons = new bool[MouseButtonCount]();
static bool* MouseButtons = new bool[MouseButtonCount]();

const static int KeyCount = static_cast<int>(KeyCode::RightSuper) + 1;
static bool* OldKeys = new bool[KeyCount]();
static bool* Keys = new bool[KeyCount]();

static bool IsMouseInsideWindow = true;

static int KeyCodeToGLFWKey(KeyCode keyCode)
{
	struct Temp { KeyCode Key; int Value; bool operator <(const Temp& rhs) const { return Key < rhs.Key; } };
#define CREATE(x, y) Temp { KeyCode::##x##, y }

	// magic value from GLFW docs. Basically map end of all contigous key values to KeyCode, then binary-search
	static const Temp arr[] = { 
		CREATE(Space, 32), CREATE(Minus, 45), CREATE(D9, 57), CREATE(Z, 90),
		CREATE(End, 269), CREATE(Pause, 284), CREATE(F12, 301), CREATE(RightSuper, 347) };

	auto start = arr;
	auto end = arr + length(arr);
	auto found = std::lower_bound(start, end, Temp{ keyCode });
	if (found >= end)
	{
		Logger::LogError("Input.cpp: KeyCodeToGLFWKey: Did you forget to update 'arr'?");
		throw new std::logic_error("Something is wrong. You probably need to update 'arr'");
	}

	int index = found->Value;
	return index - (static_cast<int>(found->Key) - static_cast<int>(keyCode));
}

// text input basicly
static void GLFWCharCallback(GLFWwindow* window, uint value)
{
}

static void GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
}

static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//bool isPressed = (action == GLFW_PRESS);
//	MouseButtons[button] = isPressed;
}

static void GLFWCursorPositionCallback(GLFWwindow* window, double x, double y)
{
}

static void GLFWCursorEnteredCallback(GLFWwindow* window, int entered)
{
	IsMouseInsideWindow = (entered == GL_TRUE);
}

static void GLFWScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
}

InputManager::InputManager()
{
}

void InputManager::Initialize()
{
	// set callbacks
	auto window = Game::GetInstance().GetWindow()._window.get();
	glfwSetCharCallback(window, GLFWCharCallback);
	glfwSetKeyCallback(window, GLFWKeyCallback);
	glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);
	glfwSetCursorPosCallback(window, GLFWCursorPositionCallback);
	glfwSetCursorEnterCallback(window, GLFWCursorEnteredCallback);
	glfwSetScrollCallback(window, GLFWScrollCallback);
}

void InputManager::Update()
{
	auto window = Game::GetInstance().GetWindow()._window.get();

	// Mouse Buttons
	std::swap(OldMouseButtons, MouseButtons);
	for (int i = 0; i < MouseButtonCount; i++)
	{
		MouseButtons[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
	}

	// Keys
	std::swap(OldKeys, Keys);
	for (int i = 0; i < KeyCount; i++)
	{
		Keys[i] = glfwGetKey(window, KeyCodeToGLFWKey(static_cast<KeyCode>(i))) == GLFW_PRESS;
	}
}

InputManager::~InputManager()
{
}

namespace Input
{
	bool IsMouseButtonPressed(MouseButton mouseButton)
	{
		return MouseButtons[static_cast<int>(mouseButton)];
	}

	bool IsNewMouseButtonPress(MouseButton mouseButton)
	{
		return Input::IsMouseButtonPressed(mouseButton) && !Input::WasMouseButtonPressed(mouseButton);
	}

	bool WasMouseButtonPressed(MouseButton mouseButton)
	{
		return OldMouseButtons[static_cast<int>(mouseButton)];
	}

	bool IsKeyPressed(KeyCode keyCode)
	{
		return Keys[static_cast<int>(keyCode)];
	}

	bool WasKeyPressed(KeyCode keyCode)
	{
		return OldKeys[static_cast<int>(keyCode)];
	}

	bool IsNewKeyPress(KeyCode keyCode)
	{
		return Input::IsKeyPressed(keyCode) && !Input::WasKeyPressed(keyCode);
	}

	bool IsMouseInsideWindow()
	{
		return IsMouseInsideWindow;
	}
}